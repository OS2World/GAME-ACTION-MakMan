//
//
//


#define STACKSIZE 8192  // Stack size for engine thread

void _System Eng_ThreadProc (ULONG);
int  Eng_Init  ( void  );
int  Eng_Abort ( char* );
int  Eng_Close ( void  );
int  Eng_InitLevel   ( int crntLevel = 0 );
int  Eng_NewGame   ( VOID );
int  Eng_StartGame ( VOID );
int  Eng_SetOfs ( int x, int y );
int  Eng_ShowPlayfield( VOID );
int  Eng_ProcessInput ( SHORT );
//
// 'External' data

#ifndef PLAYFIELD_HH
class playfield;
#endif

extern playfield* myfld;
extern char defaultTilePath[];
