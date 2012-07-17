#ifndef GHOST_HH
#define GHOST_HH
//
// ghost.hpp
//
// class Ghost
// derived from sprite, defines ghost inteligence


#include "tile.hpp"
#include "playfield.hpp"
#include "sprite.hpp"

class ghost : public sprite
{
public:
    ghost  ();
    ~ghost ();

    virtual int live ( movement );
    virtual     set_status ( status );
    virtual int intelligence ( int& change_now ) ;
    virtual int get_my_id()=0;

private:

   int      myPhase, phaseDir;

};

class inky : public ghost
{
public:
    virtual int get_my_id() { return 1;}
};

class pinky : public ghost
{

public:
    virtual int get_my_id() { return 2;}
};

class blinky : public ghost
{
public:
    virtual int get_my_id() { return 3;}
};

class stinky : public ghost
{
public:
    virtual int get_my_id() { return 4;}
};

#endif
