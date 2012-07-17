#ifndef SPRITE__H
#define SPRITE__H
//
//
// Sprite.h
//
// class sprite definition, used to model moveable characters in playfield
// real sprites should be modelled as derived classes of this
//

#include "tile.hpp"
#include "playfield.hpp"

class tile;
class playfield;

enum status {hatching, eatable, eating, dying };

class sprite
{
public:
    sprite ( int, char** );
    ~sprite();

    set_pos  ( int X, int Y );
    move     ( int*, int&, int*);
    get_srnd ( int* );
    set_fld  ( playfield* some );



    tile*       get_crnt_tile () { return &phases[crntPhase]; }
    status      get_status ()    { return crntStatus; }

    virtual     set_status ( status );
    virtual int live ( movement input_direction );
    virtual     get_position ( int& x1, int& y1, int& o1, int& d1,
                               int& x2, int& y2, int& o2, int& d2,
                               int modX, int modY );



protected:
    // bitmap (tile) info
    int        maxPhase, crntPhase;
    tile*      phases;
    playfield* myFld;

    // current position & direction
    int      pos[2], pixOfs;
    movement crntMove;
    status   crntStatus;
    int      heartbeat;


};


// global function, returns the next direction of any given one, IF any
movement get_next_direction ( movement curDir );
#endif
