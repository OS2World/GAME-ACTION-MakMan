//
// Makman.cc
//
// Implementation of makman (logic)


#define INCL_DOSPROCESS
#include <os2.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <pmbitmap.h>

#include "playfield.hpp"
#include "sprite.hpp"
#include "makman.hpp"

#include "debug.h"

#include "sndengine.hpp"

extern snd* SndEng;

char* mak__mybitmaps[] =
{
 "baseman.bmp",
 "mmu.bmp",
 "omu.bmp",
 "mmd.bmp",
 "omd.bmp",
 "mml.bmp",
 "oml.bmp",
 "mmr.bmp",
 "omr.bmp",
 "fv200.bmp",
 "fv400.bmp",
 "fv600.bmp",
 "fv800.bmp",
 "fv1000.bmp",
 "fv1500.bmp",
 "fv3000.bmp",
 "fv6000.bmp",
 "fv12000.bmp"
};

const int death_dance[] =
      { 1, 7, 3, 5 };



const int fruit_tiles[] =
 { 9, 10,11,12,13,14,15,16,17 };

const int maxPh = 5; // 6 - 1

const int tiles[5][6] =
 { {0,0,0,0,0,0}, // move_none (unused)
   {0,0,1,1,2,2}, // move_up
   {0,0,3,3,4,4}, // move_down
   {0,0,5,5,6,6}, // move_left
   {0,0,7,7,8,8}  // move_right
 };

makman::makman ()
    : sprite(sizeof(mak__mybitmaps)/sizeof(char*), mak__mybitmaps)
{

    phaseDir  = +1;
    crntMove  = move_left;
    pixOfs    = 0;
    myPhase   = 0;
    crntStatus= eatable;

    set_pos ( 10, 11 );

}

makman::~makman()
{
}

makman::live( movement usrInput )
{
    assert (pixOfs>=0);

    int newPos[2];
    int newOfs;
    int blocks[2];

    heartbeat++;


    if (sprite::move( newPos, newOfs, blocks))
    {
        pos[horizontal] = newPos[horizontal];
        pos[vertical]   = newPos[vertical];
        pixOfs          = newOfs;

        // Did I eat something?
        if (pixOfs==0)
          if (blocks[0] == dot || blocks[0] == bdt || blocks[0] == myFld->fruit_icon) // adjust score e.t.c.
          {
                myFld->set_field_position (newPos[horizontal], newPos[vertical], spc);
                if (blocks[0] == dot)
                {
                    SndEng->play(snd_dot);
                    myFld->score += myFld->dot_value;
                    myFld->numDots--;
                }
                if (blocks[0] == bdt)
                {
                    SndEng->play(snd_ghost);
                    myFld->score += myFld->big_dot_value;
                    myFld->ghost_value  = 0;
                    for (int j=1; j<myFld->numSprites; j++)
                        if (myFld->Sprites[j]->get_status() == eating || myFld->Sprites[j]->get_status() == eatable)
                            myFld->Sprites[j]->set_status( eatable );
                    crntStatus = eating;
                    heartbeat = 0;
                    myFld->numDots--;
                }
                if (blocks[0] == myFld->fruit_icon)
                {
                    SndEng->play(snd_ghost);
                    myFld->score += myFld->fruit_value;
                    // Display the value ICON
                    assert ( myFld->fruit_value_icon < sizeof(fruit_tiles) / sizeof(int));
                    crntPhase = fruit_tiles[ myFld->fruit_value_icon ];
                    myFld->update(0);
                    DosSleep( 300 );
                }
          }
          else
          {
	      // just an empty square
	      // don't play anything, 
	      // SndEng->play(snd_empty);
          }
    }

    // use next bitmap
    myPhase+= phaseDir;
    if (myPhase == maxPh || myPhase == 0)
        phaseDir = -phaseDir;

    // Phase used by get_crnt_tile
    crntPhase = tiles[crntMove][myPhase];

    // Could it be time to change direction?
    if (crntMove != usrInput)
    {
        // we're either moving along the same axis OR we are at offset 0
        if ( (directions[usrInput] == directions[crntMove]) || (pixOfs == 0) )
        { // a change of direction!
            int neighbours[5];

            sprite::get_srnd( neighbours );

            if (neighbours[usrInput] == spc ||
                neighbours[usrInput] == dot ||
                neighbours[usrInput] == bdt ||
                neighbours[usrInput] == myFld->fruit_icon )
                crntMove = usrInput;
         } // if c-o-d
    } // considered a change of direction


    // I've lived my life....
    return 1;
}



makman::set_status ( status newStatus )
{

    crntStatus = newStatus;

    switch (newStatus)
    {
    case dying:
        SndEng->play(snd_mak);
        for (int i = 0; i< 16; i++)
        {
            crntPhase = death_dance[i % 4];
            myFld->update(0);
            DosSleep( 80 );
        }
	SndEng->wait();
        break;
    }

}
