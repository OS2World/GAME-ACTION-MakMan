//
//
// Sprite.C
//
// Implementation of class sprite


#include <os2.h>
#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>
#include <pmbitmap.h>

#include "makengine.hpp"

#include "tile.hpp"
#include "sprite.hpp"

#include "debug.h"
sprite::sprite ( int nrphases, char** filenames )
{
    int ret = 0;

    myFld = NULL;
    maxPhase = nrphases;

    phases = new tile[maxPhase];
    assert (phases);

    for (int i=0; i<maxPhase; i++)
        ret += phases[i].load ( filenames[i] );

    if (ret)
        Eng_Abort("Some images for a sprite couldn't be laoded!");

    pos[horizontal] = pos[vertical] = 0;
    pixOfs = 0;
    crntPhase = 0;
}

sprite::~sprite ()
{
    delete[] phases;
}

sprite::set_pos ( int X, int Y )
{
    pos[horizontal] = X;
    pos[vertical]   = Y;
    pixOfs          = 0;
    crntMove        = move_left;

    return 0;
}

sprite::set_fld ( playfield* some )
{

    assert (some!=NULL);

    myFld = some;

    return 0;

}



sprite::get_position ( int& x1, int& y1, int& o1, int& d1,
                       int& x2, int& y2, int& o2, int& d2,
                       int modX, int modY )
{

    x1 = x2 = pos[horizontal] % modX;
    y1 = y2 = pos[vertical]   % modY;

    o1 = pixOfs;
    o2 = pixOfs - 32;

    d1 = d2 = directions[crntMove];

    if (directions[crntMove] == horizontal)
        x2 += (pixOfs ? 1 : 0);
    else
    {
        y2 += (pixOfs ? 1 : 0);
        o1 = -o1;
        o2 = -o2;
    }

     return 0;
}

// returns 1 if sprite is still alive, 0 otherwise
int sprite::live ( movement )
{

    return 1;

}

// 1 if next position valid, 0 otherwise
// pos    : int[2]
// blocks : int[2]
int sprite::move ( int* nPos, int& newOfs, int* blocks )
{

    int ret = 0;
    int frt = myFld->fruit_icon;

    nPos[horizontal] = pos[horizontal];
    nPos[vertical]   = pos[vertical];
    newOfs           = pixOfs;

    newOfs += signs[crntMove] * DISP_STEP + DIM;
    newOfs %= DIM;
    if ( (newOfs==0  && pixOfs==28) ||
         (newOfs==28 && pixOfs==0) )
        nPos[directions[crntMove]] += signs[crntMove];

    // calculate the other block our makman is taking up
    int otherPos[2];

    otherPos[0] = nPos[0];
    otherPos[1] = nPos[1];
    if (newOfs)
        otherPos[directions[crntMove]]++;

    // and what is in these blocks
    blocks[0] = myFld->field [nPos[horizontal]     + nPos[vertical] * myFld->maxX];
    blocks[1] = myFld->field [otherPos[horizontal] + otherPos[vertical] * myFld->maxX];


    // is the position valid?
    if ( (blocks[0] == spc || blocks[0] == dot || blocks[0] == bdt || blocks[0] == frt ||
                             (blocks[0] == dor && (crntStatus == dying || crntStatus == hatching))) &&
         (blocks[1] == spc || blocks[1] == dot || blocks[1] == bdt || blocks[1] == frt ||
                             (blocks[1] == dor && (crntStatus == dying || crntStatus == hatching))) )
         ret = 1;


    return ret;

}

int sprite::get_srnd ( int* neighbours )
{

    neighbours[ move_none ] = myFld->field [pos[horizontal]     +  pos[vertical]    * myFld->maxX];
    neighbours[ move_up   ] = myFld->field [pos[horizontal]     + (pos[vertical]-1) * myFld->maxX];
    neighbours[ move_down ] = myFld->field [pos[horizontal]     + (pos[vertical]+1) * myFld->maxX];
    neighbours[ move_left ] = myFld->field [(pos[horizontal]-1) +  pos[vertical]    * myFld->maxX];
    neighbours[ move_right] = myFld->field [(pos[horizontal]+1) +  pos[vertical]    * myFld->maxX];

    return 0;

}

sprite::set_status ( status newStatus )
{
    crntStatus = newStatus;
    heartbeat  = 0;
}



movement get_next_direction ( movement curDir )
{
    return next_dir[curDir];
}
