/*  assert.h

    assert macro

    Copyright (c) Borland International 1987,1988,1990,1991
    All Rights Reserved.
*/

#include <stdio.h>

extern FILE* debOut;

#undef assert

#define assert(p)    
/*
#define assert(p)   ((p) ? (void)0 : (void)fprintf(debOut, "ASSERT : %s in %s at %s\n",#p, __FILE__, __LINE__))
*/

#define dprint(a)        if (debOut) { fprintf(debOut, (a)); fflush(debOut); }
#define dprint2(a,b)     if (debOut) { fprintf(debOut, (a),(b)); fflush(debOut); }
#define dprint3(a,b,c)   if (debOut) { fprintf(debOut, (a),(b),(c)); fflush(debOut); }
#define dprint4(a,b,c,d) if (debOut) { fprintf(debOut, (a),(b),(c),(d)); fflush(debOut); }
