#ifndef BACKTILE__H
#define BACKTILE__H
//
//
// backtile.h
//
// class backtile definition, used to model moveable characters in playfield
// real backtiles should be modelled as derived classes of this
//

#include "tile.hpp"
#include "playfield.hpp"

class backtile
{
public:
    backtile ( char* );
    backtile ( int, char**, int, int );
    ~backtile();

    tile*       get_crnt_tile ();
    virtual int live ();
    virtual int is_changed();


protected:
    // bitmap (tile) info
    int     maxPhase, myPhase, crntPhase, oldPhase, phaseDir, alt_dirs;
    tile*   phases;

    int     time_counter, change_freq;
};

#endif
