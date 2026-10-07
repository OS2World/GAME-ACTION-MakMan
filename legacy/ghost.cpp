//
// ghost.cc
//
// Implementation of ghost (logic)


#define INCL_DOSPROCESS
#include <os2.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <pmbitmap.h>

#include "sndengine.hpp"
#include "playfield.hpp"
#include "ghost.hpp"

#include "debug.h"

extern snd* SndEng;

char* ghost_bitmaps[] =
{
 "Inky1.bmp",
 "Inky2.bmp",
 "InkyE1.bmp",
 "InkyE2.bmp",
 "InkyEat.bmp",
 "V200.bmp",
 "V400.bmp",
 "V800.bmp",
 "V1600.bmp"
};


const int maxPh = 3; // 4 - 1

const int value_tiles [4] =
{ 5, 6, 7, 8 };
const int tiles[5][5][4] =
{
 // Hatching
 { {0,0,0,0}, // move_none (unused)
   {0,0,1,1}, // move_up
   {0,0,1,1}, // move_down
   {0,0,1,1}, // move_left
   {0,0,1,1}  // move_right
 },
 // Eatable
 { {0,0,0,0}, // move_none (unused)
   {2,2,3,3}, // move_up
   {2,2,3,3}, // move_down
   {2,2,3,3}, // move_left
   {2,2,3,3}  // move_right
 },
 // Eating
 { {0,0,0,0}, // move_none (unused)
   {0,0,1,1}, // move_up
   {0,0,1,1}, // move_down
   {0,0,1,1}, // move_left
   {0,0,1,1}  // move_right
 },
 // Dying
 { {0,0,0,0}, // move_none (unused)
   {4,4,4,4}, // move_up
   {4,4,4,4}, // move_down
   {4,4,4,4}, // move_left
   {4,4,4,4}  // move_right
 },
 // Recovering (internal)
 { {0,0,0,0}, // move_none (unused)
   {2,2,1,1}, // move_up
   {2,2,1,1}, // move_down
   {2,2,1,1}, // move_left
   {2,2,1,1}  // move_right
 },
};

ghost::ghost ()
    : sprite(sizeof(ghost_bitmaps)/sizeof(char*), ghost_bitmaps)
{

    phaseDir = +1;
    crntMove  = move_right;
    crntStatus= hatching;

    set_pos ( 10, 9 );

}

ghost::~ghost()
{
}


ghost::live( movement )
{

    assert (pixOfs>=0);

    int newPos[2];
    int newOfs;
    int blocks[2];
    int change_now = FALSE;

    // my heart keeps ticking!
    heartbeat++;

    // A change of status as a result of a timeout?
    switch (crntStatus)
    {
        case eating:
            if (heartbeat >= myFld->ghost_path_time)
            {
                heartbeat = 0;
                // maybe we should consider a change of direction
                // at specific intervals
            }
            break;
        case eatable:
             if (heartbeat >= myFld->pill_duration)
             {
                heartbeat = 0;
                crntStatus = eating;
             }
            if (heartbeat % 2 != 1)
                return 1;
             break;
        case dying:
            // We're at the door, go in
            if (pixOfs==0 && pos[vertical] == nestDoorY && pos[horizontal] == nestDoorX)
                crntMove = move_down;
            // We're in, regenerate
            if (pixOfs==0 && pos[vertical] == nestDoorY+2 && pos[horizontal] == nestDoorX)
            {
                heartbeat  = 0;
                crntStatus = hatching;
            }
            break;
        case hatching:
             if (heartbeat >= myFld->ghost_hatch_time)
             {
                if (pos[vertical] == nestDoorY && pixOfs == 0)
                {
                    heartbeat = 0;
                    crntStatus = eating;
                }
                else
                if (pos[vertical] == nestDoorY + 2 && pixOfs == 0)
                {
                    // we're wandering along the upper line of the nest
                    movement oldMove = crntMove;
                    // go up
                    crntMove = move_up;
                    // if we can't go up keep going
                    if (!sprite::move( newPos, newOfs, blocks ))
                        crntMove = oldMove;
                }
             }
             break;
    }

    // use next bitmap
    myPhase+= phaseDir;
    if (myPhase == maxPh || myPhase == 0)
        phaseDir = -phaseDir;

    // recovering is an internal status, so let's check it here
    int Stat = crntStatus;
    if (Stat == eatable && heartbeat >= myFld->pill_duration - 2*32 )
        Stat = 4; // set status to recovering, just for the bitmaps

    crntPhase = tiles[Stat][crntMove][myPhase];


   if (sprite::move( newPos, newOfs, blocks))
   {
        // Keep on moving on the current direction
        pos[horizontal] = newPos[horizontal];
        pos[vertical]   = newPos[vertical];
        pixOfs          = newOfs;
   }
   else
        change_now = TRUE; // we can't go on any further!



    movement circle[5] = { move_none, move_left, move_right, move_down, move_up };

    // Change the direction of the movement, if neccessary:
    switch (crntStatus)
    {
        case hatching:
            // we want the to circle in the nest
            // and change direction only by change_now
            if (change_now)
                crntMove = circle[crntMove];
            break;

        case dying:
        case eating:
        case eatable:
            intelligence( change_now );
            break;
        } // end switch



    // I've lived my life....

    return 1;

}


ghost::set_status ( status newStatus )
{

    crntStatus = newStatus;

    switch (newStatus)
    {
    case dying:
        crntPhase = value_tiles [ myFld->ghost_value ];
        myFld->update(0);
	SndEng->play(snd_ghost);
        DosSleep( 300 );
        crntMove = (movement) opposite[crntMove];
        break;
    case eatable:
        heartbeat = 0;
        crntMove = (movement) opposite[crntMove];
        break;
    }

}




//
// standard ghost behaviour
//
ghost::intelligence ( int& change_now )
{
    int neighbours[5];
    int emptys = 0;

    // What kind-a-tiles are arround me?
    sprite::get_srnd( neighbours );

    // and how many of them are empty?
    for (int j=1; j<5; j++)
        if (neighbours[j] == dot || neighbours[j] == spc || neighbours[j] == bdt)
            emptys++;

    // We're at some kind of a crossing OR at a dead-end
    if ( (emptys > 2 || change_now) && (pixOfs == 0) )
    {
        movement newMove;

        // for each status, MakMan (i.e. trgtPos) attracts/repells/dont-care-about ghosts
        int gravity[4] = { 0, -1, +1, +1};
        int makPos[2], dummy = 0;
        int iq = myFld->ghost_iq[get_my_id()];

        // get position of MakMan
        myFld->Sprites[0]->get_position( makPos[0], makPos[1], dummy, dummy,
                                         dummy, dummy, dummy, dummy, myFld->maxX, myFld->maxY);

        // Go back to your nest dummy!
        if (crntStatus == dying)
        {
            makPos[0] = nestDoorX;
            makPos[1] = nestDoorY;
            iq = 100;
        }

        int dist[5];
        dist [ move_none ] = 999;

        for (int jj = (int) move_up; jj <= move_right; jj++)
        {
            int distance = pos[directions[jj]] - makPos[directions[jj]];
            dist[jj] = gravity[crntStatus] * distance * signs[jj];
            // randomize on low iq, max iq = 100
            dist[jj] += (1 - iq/100) * ( (20*rand())/RAND_MAX - 10);
        }

        do
        {
            // find minimal value
            movement min = move_none;
            for (int l= (int) move_up; l <= move_right; l++)
                if (dist[l] < dist[min])
                    min = (movement) l;
            newMove   = min;
            dist[min] = 999;
        } while (   (neighbours[newMove]!=dot && neighbours[newMove]!=spc && neighbours[newMove]!=bdt)
                    || (change_now && crntMove==newMove) || (crntMove == opposite[newMove]) );

        crntMove = newMove;
    }
}
