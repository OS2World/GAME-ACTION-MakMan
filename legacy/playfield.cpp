//
//
// Playfield.C
//
// Playfield implementation

#define INCL_DOSPROCESS
#include <os2.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <pmbitmap.h>

#include "makengine.hpp"
#include "videoengine.hpp"
#include "sndengine.hpp"

#include "playfield.hpp"
#include "backtile.hpp"
#include "sprite.hpp"
#include "tile.hpp"

#include "debug.h"

extern snd* SndEng;

movement next_dir[5] = {move_none, move_down, move_left, move_right, move_none};
int opposite[5]   = { move_none, move_down, move_up, move_right, move_left };
int directions[5] = { 0, vertical, vertical, horizontal, horizontal };
int signs[5]      = { 0, -1,       +1,       -1,         +1};

playfield::playfield ( int sizex, int sizey, int ofsX, int ofsY )
{

    maxX = sizex;
    maxY = sizey;
    pixOfsX = ofsX;
    pixOfsY = ofsY;
    numLoadedTiles = 0;
    numSprites     = 0;
    ticker         = 0;
    usrInput       = move_left;

    // game data
    lives          = 3;
    score          = 0;

    // level data
    pill_duration    = 400;
    ghost_hatch_time = 100;
    ghost_iq[0]      = 10;
    ghost_iq[1]      = 20;
    ghost_iq[2]      = 30;
    ghost_iq[3]      = 40;
    ghost_path_time  = 32;
    dot_value        = 10;
    big_dot_value    = 50;
    fruit_frequency  = 1000;
    fruit_duration   = 100;
    fruit_value      = 200;
    fruit_value_icon = 0;

    if ( DosAllocMem ( (PPVOID) &field, sizex * sizey * sizeof(int),
                       (ULONG) PAG_COMMIT | PAG_READ | PAG_WRITE) )
        Eng_Abort("Error while opening up some system RAM for playfield.");

    if ( DosAllocMem ( (PPVOID) &frontBuffer, sizex * sizey * sizeof(backtile*),
                       (ULONG) PAG_COMMIT | PAG_READ | PAG_WRITE) )
        Eng_Abort("Error while opening up some system RAM for display frontBuffer.");

    if ( DosAllocMem ( (PPVOID) &backBuffer, sizex * sizey * sizeof(backtile*),
                       (ULONG) PAG_COMMIT | PAG_READ | PAG_WRITE) )
        Eng_Abort("Error while opening up some system RAM for display backBuffer.");

    // don't try to release the objects in the buffer since they are invalid
    clean_buffer (frontBuffer,0);
    clean_buffer (backBuffer,0);
}

playfield::~playfield()
{
    // destroy all loaded tiles
    for (int i =0; i < numLoadedTiles; i++)
	delete backgroundTiles[i];

    DosFreeMem ( field );
}


//
// resets the passed buffer to NULL, releasing backtile objects
// if freemem is set to 1
playfield::clean_buffer ( tile** buffer, int freemem )
{
    if (freemem)
        for (int i=0; i< maxX * maxY; i++)
        {
            if (buffer[i])
            {
                delete buffer[i];
                buffer[i] = NULL;
            }
        }
    else
        for (int i=0; i< maxX * maxY; i++)
            buffer[i] = NULL;

    return 0;
}

//
// switch front and backbuffer
// for the time exchange buffer contents, later use pointers
playfield::switch_buffers ( )
{
    tile* swap;

    for (int i=0; i< maxX * maxY; i++)
    {
        swap = frontBuffer[i];
        frontBuffer[i] = backBuffer[i];
        backBuffer[i]  = swap;
    }

    return 0;
}

int playfield::load_backtile ( char* filename )
{
     if ((backgroundTiles[numLoadedTiles++] = new backtile (filename)) == NULL)
     {
        cerr << " Failed to load backtile "<< filename <<endl;
     }

     // make sure that we don't write past our stupid array
     assert (numLoadedTiles < 99);

     // the unique ID for the loaded backtile
     return numLoadedTiles - 1;
}

int playfield::load_backtile ( int numnames, char** filenames, int freq, int two_way )
{
     if ((backgroundTiles[numLoadedTiles++] = new backtile (numnames, filenames, freq, two_way)) == NULL)
     {
        cerr << " Failed to load backtile "<< filenames[0] <<endl;
     }

     // make sure that we don't write past our stupid array
     assert (numLoadedTiles < 149);

     // the unique ID for the loaded backtile
     return numLoadedTiles - 1;
}

int playfield::register_sprite( sprite* spr)
{

    Sprites[numSprites++] = spr;
    spr->set_fld (this);


    return numSprites - 1;
}



int playfield::set_field_position ( int x, int y, int tileID )
{
    int ret = 0;

    assert(x < maxX);
    assert(y < maxY);

    if (tileID < numLoadedTiles)
        field[x + y*maxX] = tileID;
    else
        ret = 1;

    return ret;
}

int playfield::set_field ( int* newfld, int fldSize)
{
    assert( fldSize == maxX * maxY * sizeof(int) );

    memcpy ( field, newfld, fldSize );

    numDots = 0;
    for (int i=0; i<maxX * maxY; i++)
        if (field[i] == dot || field[i] == bdt)
            numDots++;

    crntGame = level_running;


    return 0;
}


tile* playfield::get_field_position ( int x, int y )
{
    assert(x < maxX);
    assert(y < maxY);

    return (backgroundTiles[ field[ x + y*maxX] ]->get_crnt_tile());
}

//
// Show the whole field layout, ignoring sprites e.t.c.
playfield::show( )
{
    int cnt = 0;

    for (int y=0; y<maxY; y++)
        for (int x=0; x<maxX; x++)
            if (backgroundTiles[ field[cnt] ])
                backgroundTiles[ field[cnt++] ]->get_crnt_tile()->show ( pixOfsX + x * tileWidth, pixOfsY + (fieldSizeY-y-1) * tileHeight );

    return 0;

}

//
// Update the field, showing all sprites in their (new?) positions e.t.c.
playfield::update( int redraw )
{

    ///////////////////////////
    // build the frontbuffer //
    ///////////////////////////

    // with sprites
    for (int i=0; i < numSprites; i++)
    {
        int x1,y1,o1,d1,x2,y2,o2,d2;

        // find out which positions our sprite will occupy
        Sprites[i]->get_position ( x1, y1, o1, d1, x2, y2, o2, d2 , maxX-1, maxY-1);

        // replicate those backtiles, if they aren't allready in the frontbuffer
        if (frontBuffer[ x1+y1*maxX ]==NULL)
            frontBuffer[ x1+y1*maxX ] = new tile ( *get_field_position(x1,y1) );
        if (frontBuffer[ x2+y2*maxX ]==NULL)
            frontBuffer[ x2+y2*maxX ] = new tile ( *get_field_position(x2,y2) );

        // superimpose the sprite on them..
        frontBuffer[ x1+y1*maxX ]->overlay ( *(Sprites[i]->get_crnt_tile()), o1, d1 );
        frontBuffer[ x2+y2*maxX ]->overlay ( *(Sprites[i]->get_crnt_tile()), o2, d2 );

    }

    // and changed tiles:
    for (i=0; i<numLoadedTiles; i++)
        if (backgroundTiles[i]->is_changed())
            for (int x=0; x<maxX; x++)
                for (int y=0; y<maxY; y++)
                    if (frontBuffer[x+y*maxX]==NULL && field[x+y*maxX] == i)
                        frontBuffer[x+y*maxX] = new tile (*get_field_position(x,y));


    // update display :
    // for each position do :
    //     nothing,         if both front and backBuffer are NULL
    //     show background, if only backBuffer != NULL
    //     show front,      if frontBuffer is != NULL

    tile* crnt;
    int cnt = 0;
    for (int y=0; y<maxY; y++)
        for (int x=0; x<maxX; x++, cnt++)
        {
            crnt = NULL;
            if (backBuffer[cnt] || redraw)
                crnt = backgroundTiles [ field[cnt] ]->get_crnt_tile();
            if (frontBuffer[cnt])
                crnt = frontBuffer[cnt];

            if (crnt)
                crnt->show ( pixOfsX + x * tileWidth, pixOfsY + (fieldSizeY-y-1) * tileHeight );
        }

    // make the frontbuffer a backbuffer...
    clean_buffer  (backBuffer);
    switch_buffers();

    // you're done!
    return 0;

}


int ghost_values[] =
{
     200,
     400,
     800,
    1600
};

game playfield::tick( movement& usrInput )
{

    ticker++;

    //
    // give a chance to all sprites to live
    //
    for (int i=0; i<numSprites; i++)
        Sprites[i]->live( usrInput );

    for (i=0; i<numLoadedTiles; i++)
        backgroundTiles[i]->live();

    //
    // take care of fruit display
    //

    // DISPLAY FRUIT
    // duration should be < 1/2 * frequency
    if ( ticker % fruit_frequency == fruit_duration)
    {
        // set field pos
        field     [ fruitX + fruitY * maxX ] = fruit_icon;
        backBuffer[ fruitX + fruitY * maxX ] = new tile (*get_field_position(fruitX, fruitY));
    }

    // REMOVE FRUIT
    if (field[ fruitX+fruitY*maxX ] == fruit_icon && ticker%fruit_frequency >= 2*fruit_duration)
    {
        // set field pos
        field     [ fruitX + fruitY * maxX ] = spc;
        backBuffer[ fruitX + fruitY * maxX ] = new tile (*get_field_position(fruitX, fruitY));
    }



    // ok, have there been any important 'events'?

    // Did the user win?
    if (numDots == 0)
    {
        crntGame = level_done;
        // some music and stuff... fancy displays e.t.c...
        Sprites[0]->set_status(dying); // just to delay a bit...
        Sprites[0]->set_status(eatable);
    }

    // we can assume that makman is the first sprite there is...
#define makman Sprites[0]

    int makpos[2];
    int makofs, makdir, dummy;

    makman->get_position( makpos[0], makpos[1], makofs, makdir,
                          dummy, dummy, dummy, dummy, maxX, maxY);

    makpos[0] *= 32;
    makpos[1] *= 32;
    makpos[ makdir ] += abs(makofs);

    for (i=1;i<numSprites;i++)
    {
        int    gh[2], ghofs, ghdir;
        status foe;
        Sprites[i]->get_position( gh[0], gh[1], ghofs, ghdir,
                                  dummy, dummy, dummy, dummy, maxX, maxY);
        gh[0] *= 32;
        gh[1] *= 32;
        gh[ ghdir ] += abs(ghofs);



        // DETECT colision, if any!
        int colision = FALSE;

        // X colision?
        int xm = (makpos[0]+5 <= gh[0]     && gh[0]     <= makpos[0]+26);
        int xg = (gh[0]+5     <= makpos[0] && makpos[0] <= gh[0]    +26);
        int ym = (makpos[1]+5 <= gh[1   ]  && gh[1   ]  <= makpos[1]+26);
        int yg = (gh[1]+5      <= makpos[1] && makpos[1] <= gh[1]    +26);
        int xx = ( makpos[1] == gh[1] && (xm || xg));
        int yy = ( makpos[0] == gh[0] && (ym || yg));

        if ( xx || yy || ((xm||xg) && (ym||yg)) )
            colision = TRUE;


        foe = Sprites[i]->get_status();

        if (colision)
            if (foe == eating)
            {
                makman->set_status(dying);
                lives--;
                if (lives)
                {   // erase a makman, if there is one
                    field[lives-1] = spc;
                    backBuffer[lives-1] = new tile (*get_field_position(lives-1,0));
                }
                usrInput = move_left;
                if (lives)
                {
                    SndEng->play(snd_start);
                    // remove fruit
                    field [ fruitX + fruitY * maxX ] = spc;
                    makman->set_status(eatable);
                    makman->set_pos(10,11);
                    for (int j=1; j<numSprites; j++)
                    {
                        Sprites[j]->set_pos(7+j,9);
                        Sprites[j]->set_status(hatching);
                    }
                    update(FALSE);
                    SndEng->wait();
                }
                else
                    crntGame = game_over;
            }
            else
            if (foe == eatable)
                if (Sprites[i]->get_status() == eatable)
                {
                    Sprites[i]->set_status(dying);
                    score += ghost_values [ ghost_value++ ];
                }

    }

    put_score();


    return crntGame;

}

// Puts the new score into the backbuffer for display in the next move
int playfield::put_score ()
{
    char buf[30];

    // put the score in a string
    sprintf(buf, "%7i", score);

    // update the display where neccessary
    for (int i = 0; i<7; i++)
        if (buf[6 - i] != ' ')
            if ( (field[ maxX - i - 2 ] - d_0) != (buf[6 - i] - '0') )
            {
                field     [ maxX - i - 2 ] = d_0 + buf[6 - i] - '0';
                backBuffer[ maxX - i - 2 ] = new tile (*get_field_position(maxX - i - 2, 0));
            }

    // Check if a life has been won....
    if (score>=lifeScore && oldScore<lifeScore)
    {
        field      [ lives-1 ] = mak;
        backBuffer [ lives-1 ] = new tile(*get_field_position(lives-1, 0));
        lives++;
        oldScore   = score; // make sure we don't get more than one each time
        lifeScore *= 2;     // and make it a bit more difficult to get the next one
    }

    oldScore = score;

    return TRUE;

}



// Checks if the box next to pos in direction dir free is.
// If so, returns dir. If not, the next possible direction is returned.
// When no more directions are left (i.e. after move_right), move_none is returned
movement playfield::check_legal( int* pos, movement dir)
{
    int      myPos[2];

    myPos[0] = pos[0];
    myPos[1] = pos[1];
    myPos[directions[dir]] += signs[dir];

    int atpos = field[ myPos[horizontal] + myPos[vertical]*maxX ];

    while ((atpos != spc && atpos != dot && atpos != bdt && atpos != fruit_icon) && dir != move_none)
      dir = get_next_direction(dir);

    return dir;
}

// returns some assesment of how close src to target is ( 0 -> src IS trgt)
int playfield::check ( int *src, int* trgt)
{

    // the quadrat of the distanct between src and trgt
    return (src[0] - trgt[0]) * (src[0] - trgt[0]) + (src[1] - trgt[1]) * (src[1] - trgt[1]);

}

int playfield::new_game()
{
    score = oldScore = 0;
    lifeScore = 10000;
    lives = 3;
    dot_value = 10;
    big_dot_value = 50;

    return TRUE;
}

int playfield::set_field_data( int pill_d, int ghost_hatch, int ghost_path, int* iq,
                               int fruit_f, int fruit_d,    int fruit_v,    int fruit_vi,
                               int fruit_i )
{

    SndEng->play(snd_start);

    pill_duration     = pill_d;
    ghost_hatch_time  = ghost_hatch;
    ghost_path_time   = ghost_path;
    for (int i =0; i < numGhosts; i++)
        ghost_iq[i]          = iq[i];
    fruit_frequency   = fruit_f;
    fruit_duration    = fruit_d;
    fruit_value       = fruit_v;
    fruit_value_icon  = fruit_vi; // refers to an icon in the fruit_tiles array of makman
    fruit_icon        = fruit_i;  // the ID of the loaded tile

    // display lives
    for (i=0; i<lives-1; i++)
        field[i] = mak;

    // and current level
    field[7] = fruit_icon;

    field [ fruitX + fruitY * maxX ] = spc;
    makman->set_status(eatable);
    makman->set_pos(10,11);
    for (int j=1; j<numSprites; j++)
    {
        Sprites[j]->set_pos(7+j,9);
        Sprites[j]->set_status(hatching);
    }

    update(TRUE);

    SndEng->wait();

    return TRUE;
}



//
//
// Access the graphic engine
extern gfx *GfxEng;

void playfield::setScreenOfs ( int ofsX, int ofsY )
{

    // Should relay information to the video engine
    GfxEng->set_offset( ofsX, ofsY );
}
