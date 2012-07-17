//
// Seek.h
//

#include <dlistimp.h>

//
// the smallest element of a Path
class path_elem
{
    public:
        path_elem();
        path_elem( const path_elem & );
        ~path_elem();

        void operator= ( const path_elem& );

        // Data members
        int      curPos[2];
        movement drctn, next_drctn;


};

typedef BI_DoubleListImp < path_elem* > Path;

// global function, returns the next direction of any given one, IF any
movement get_next_direction ( movement curDir );

// Builds a path to trgPos (sort of, anyway...)
Path *seekTarget(playfield* myFld, Path *myPath, int *curPos, int* trgPos);
