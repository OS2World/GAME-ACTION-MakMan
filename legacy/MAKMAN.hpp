#ifndef MAKMAN_HH
#define MAKMAN_HH
//
// makman.hpp
//
// class makman
// Mak man is derived from the sprite class
// and only overloads the logic of the sprite
// (as well as constructor/destructor)

#include "sprite.hpp"

class makman : public sprite
{
public:
    makman  ();
    ~makman ();

    virtual int live ( movement );
    virtual     set_status ( status );

private:
   int      myPhase, phaseDir;
};

#endif
