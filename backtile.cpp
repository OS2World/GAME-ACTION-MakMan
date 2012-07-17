//
//
// backtile.C
//
// Implementation of class backtile


#include <os2.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <pmbitmap.h>

#include "makengine.hpp"

#include "tile.hpp"
#include "backtile.hpp"

#include "debug.h"

backtile::backtile ( char* filename )
{

    int ret = 0;

    maxPhase    = 1;
    crntPhase   = oldPhase = myPhase = 0;
    phaseDir    = +1;
    change_freq = 1;
    time_counter = 0;

    phases = new tile[maxPhase];
    assert (phases);

    phases[0].load ( filename );

    if (ret)
        Eng_Abort("Some images for a backtile couldn't be laoded!");

}

backtile::backtile ( int nrphases, char** filenames, int freq, int two_way )
{
    int ret = 0;

    maxPhase    = nrphases;
    crntPhase   = oldPhase = myPhase = 0;
    phaseDir    = +1;
    change_freq = freq;
    time_counter = 0;
    alt_dirs    = two_way;

    phases = new tile[maxPhase];
    assert (phases);

    for (int i=0; i<maxPhase; i++)
        ret += phases[i].load ( filenames[i] );

    if (ret)
        Eng_Abort("Some images for a backtile couldn't be loaded!");

}

backtile::~backtile ()
{
    delete[] phases;
}

// returns 1 if backtile is still alive, 0 otherwise
int backtile::live ( )
{


    if (change_freq > 1) // we are changing bitmaps
        if (time_counter++ % change_freq == 0)
        {
            // use next bitmap
            myPhase+= phaseDir;

            if (alt_dirs)
            {
                if (myPhase == maxPhase-1 || myPhase == 0)
                    phaseDir = - phaseDir;
            }
            else
                myPhase = myPhase % maxPhase;


            // Phase used by get_crnt_tile
            // if we need to make the display bitmaps dependent on some event
            // we could addopt the idea of a tile[][] array as in makman.cc
            crntPhase = myPhase;
        }


    return 1;

}

tile* backtile::get_crnt_tile()
{

    return &phases[crntPhase];

}

int backtile::is_changed()
{
    int ret = 0;

    if (crntPhase!=oldPhase)
    {
        oldPhase = crntPhase;
        ret = 1;
    }

    return ret;
}

