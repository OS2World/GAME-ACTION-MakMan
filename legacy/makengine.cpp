//
//
//
// MakEngine.cc
//
//

#define INCL_DOSSEMAPHORES
#define INCL_DOSDATETIME
#define INCL_DOSERRORS

#include "PmMain.hpp"
#include "PmVars.hpp"
#include "PmHelp.hpp"
#include "PmIDs.hpp"

#include <PmBitmap.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "debug.h"

#include "makengine.hpp"
#include "videoengine.hpp"
#include "sndengine.hpp"

#include "tile.hpp"
#include "playfield.hpp"
#include "sprite.hpp"
#include "ghost.hpp"
#include "makman.hpp"

#include "joyos2.h"

//
// Variables used for communication with the other thread.
//
int fieldRedraw; // playfield needs to be redrawn
int useJoystick;
GAME_2DPOS_STRUCT joyCal[3] = // let pos 0 empty, pos 1 and 2 for joystick A and B respectively
    { {0,0},{0,0},{0,0} };

char  defaultTilePath[100] = "3dtiles";

char* tilePaths[] = {
    "tiles",
    "3dtiles",
    "newtiles"
    };

/* the data for the various levels */
#include <levels.inc>


char *pillBitmaps[] =
{
  "pd.bmp",
  "pd1.bmp",
  "pd2.bmp",
  "pd3.bmp"
  };

char *doorBitmaps[] =
{
  "gd1.bmp",
  "gd2.bmp",
  "gd3.bmp",
  "gd4.bmp"
  };

// How often the pill icon changes ( in ticks )
#define pillFrequency 5
#define doorFrequency 7

movement usrMove;

gfx    *GfxEng;
snd    *SndEng;
//
// Sprites
makman *myman;
ghost  *ainky,
       *ablinky,
       *apinky,
       *astinky;

game   myGame;

//
// Instantiate playfield
playfield *myfld;

//
// Housekeeping stuff
int  lostEvents;
int  engineFailure;
long myScore;
int Eng_KillThread ( void )
{
    APIRET rc = 0;
    // quit the existing thread, if any
    if (tidAsync)
    {
        DosPostEventSem((ULONG) hevTermGame);
        DosPostEventSem((ULONG) hevTick);
        rc = DosWaitThread( &tidAsync, DCWW_WAIT );
    }

    return rc;

}

int Eng_Abort( char* pszErrMsg)
{
  char szErrTitle[] = "GFX Engine Error";

  WinMessageBox(HWND_DESKTOP,
		hwndFrame,
		(PSZ)(pszErrMsg),
		(PSZ)szErrTitle,
		0,
	        MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL );

  engineFailure = 1;

  return engineFailure;
}

int Eng_Close ( VOID )
{
  
  Eng_KillThread();

  delete myfld;    
  delete myman;
  delete apinky;
  delete ablinky;
  delete ainky;
  delete astinky;

  SndEng->unload(snd_start);
  SndEng->unload(snd_mak);
  SndEng->unload(snd_ghost);
  SndEng->unload(snd_dot);
  SndEng->unload(snd_empty);

  return 0;
}

int Eng_Init ( VOID )
{
   
  engineFailure = 0;
  tidAsync = 0;

  myfld = new playfield  ( fieldSizeX, fieldSizeY, 0, 0);

  // load the (hopefully appropriate) palette
  GfxEng->load_palette();

  myfld->load_backtile ( "blank.bmp" );
  myfld->load_backtile ( "hor.bmp" );
  myfld->load_backtile ( "vert.bmp" );
  myfld->load_backtile ( "ltd.bmp" );
  myfld->load_backtile ( "rtu.bmp" );
  myfld->load_backtile ( "utl.bmp" );
  myfld->load_backtile ( "dtr.bmp" );
  myfld->load_backtile ( "dru.bmp" );
  myfld->load_backtile ( "ldr.bmp" );
  myfld->load_backtile ( "rul.bmp" );
  myfld->load_backtile ( "uld.bmp" );
  myfld->load_backtile ( "de.bmp" );
  myfld->load_backtile ( "le.bmp" );
  myfld->load_backtile ( "re.bmp" );
  myfld->load_backtile ( "ue.bmp" );
  myfld->load_backtile ( "dot.bmp");
  myfld->load_backtile ( sizeof(doorBitmaps)/sizeof(char*), doorBitmaps, doorFrequency, FALSE);
  myfld->load_backtile ( "lere.bmp");
  myfld->load_backtile ( sizeof(pillBitmaps)/sizeof(char*), pillBitmaps, pillFrequency, TRUE);
  myfld->load_backtile ( "mmr.bmp");
  myfld->load_backtile ( "score0.bmp");
  myfld->load_backtile ( "score1.bmp");
  myfld->load_backtile ( "score2.bmp");
  myfld->load_backtile ( "score3.bmp");
  myfld->load_backtile ( "score4.bmp");
  myfld->load_backtile ( "score5.bmp");
  myfld->load_backtile ( "score6.bmp");
  myfld->load_backtile ( "score7.bmp");
  myfld->load_backtile ( "score8.bmp");
  myfld->load_backtile ( "score9.bmp");
  myfld->load_backtile ( "Cherry.bmp");
  myfld->load_backtile ( "Strawb.bmp");

  // Instantiate sprites
  myman  = new makman;
  apinky = new inky;
  ablinky = new blinky;
  ainky   = new stinky;
  astinky = new pinky;

  myfld->register_sprite (myman);
  myfld->register_sprite (ainky);
  myfld->register_sprite (ablinky);
  myfld->register_sprite (astinky);
  myfld->register_sprite (apinky);

  lostEvents = 0;


  snd_empty = SndEng->load("sounds\\empty.wav");
  snd_dot   = SndEng->load("sounds\\dot.wav");
  snd_ghost = SndEng->load("sounds\\eating.wav");
  snd_mak   = SndEng->load("sounds\\eaten.wav");
  snd_start = SndEng->load("sounds\\ready.wav");


  if (engineFailure)
    return FALSE; // an error has occurred

  return TRUE; // init ok
}

int Eng_InitLevel ( int crntLevel )
{
  int* lD;


  crntLevel = crntLevel % numLevels;
  fprintf(debOut, "Level : %i\n",crntLevel);
  fflush(debOut);

  lD = &levelData[crntLevel][0];

  myfld->set_field (fldDsgns[lD[0]], fieldSizeX * fieldSizeY * sizeof(int) );
  fprintf(debOut, "field ok\n");
  fflush(debOut);

  myfld->set_field_data ( lD[1], // pill duration
                          lD[2], // ghost hatch time
                          0, // ghost path time
                          &lD[3], // ghost iq 3,4,5,6
                          lD[7], // fruit time
                          lD[8], // fruit duration
                          lD[9], // fruit value
                          lD[10], // fruit value icon
                          lD[11]); // fruit icon
  fprintf(debOut, "field data ok\n");
  fflush(debOut);


  usrMove = move_left;

  return TRUE;

}

int Eng_NewGame ( VOID )
{
    APIRET rc;

    myfld->new_game();

    Eng_KillThread();

    // ...and create a new one
    rc = DosCreateThread(&tidAsync,
               (PFNTHREAD) Eng_ThreadProc,
               0,
               CREATE_READY, // start thread in suspend mode
               STACKSIZE );

    return TRUE;
}

int Eng_StartGame ( VOID )
{
  APIRET rc;
  myfld->show();
  
  rc = DosStartTimer ( 26, (HSEM)hevTick, &hTimer);
  if (rc)
    {
      char buf[80];
      sprintf(buf, "Couldn't start game timer, code : %u",rc);
      Eng_Abort (buf);
    }

  return rc;
}

int Eng_SetOfs ( int x, int y )
{
  myfld->setScreenOfs( x, y );
  return 0;
}


int  Eng_ShowPlayfield( VOID )
{
  myfld->show();

  return TRUE;
}



int  Eng_ProcessInput ( SHORT key )
{

  switch (key)  {
  case VK_LEFT:
    usrMove = move_left;
    break;
  case VK_RIGHT:
    usrMove = move_right;
    break;
  case VK_UP:
    usrMove = move_up;
    break;
 case VK_DOWN:
    usrMove = move_down;
    break;
default:
    break;
  }

  return key;
}

void _System Eng_ThreadProc (ULONG)
{
  // APIRET rc;
  ULONG  ulPostCt;
  GAME_STATUS_STRUCT joyStatus;
  ULONG  dataLen = sizeof(joyStatus);
  GAME_2DPOS_STRUCT *joyData = &joyStatus.curdata.A;

  // clear any pending terminate requests
  DosResetEventSem((ULONG)hevTermGame, &ulPostCt);

  // do for all eternity
  while(TRUE)
  {
      // wait for a timer tick
      DosWaitEventSem ((ULONG)hevTick, SEM_INDEFINITE_WAIT);
      DosResetEventSem((ULONG)hevTick, &ulPostCt);

      // Time to quit this thread?
      if (DosWaitEventSem ((ULONG)hevTermGame, SEM_IMMEDIATE_RETURN) == NO_ERROR)
          break;

      // did I miss any events?
      if (ulPostCt > 1)
        lostEvents += ulPostCt - 1;

      // If i'm using a joystick, read joystick input
      if (useJoystick)
      {
          DosDevIOCtl( hGame, IOCTL_CAT_USER, GAME_GET_STATUS,
                  NULL, 0, NULL,
                  &joyStatus, dataLen, &dataLen);
          int joyX, joyY;
          joyX = joyData[useJoystick-1].x - joyCal[useJoystick].x;
          joyY = joyData[useJoystick-1].y - joyCal[useJoystick].y;

          // a small tolerance to compensate for joystick drifting
          int tolX = joyCal[useJoystick].x/10;
          int tolY = joyCal[useJoystick].y/10;

          // we're moving on the X axis or on the Y axis?
          if ( abs(joyX) > abs(joyY) )
          { // X axis
              if (joyX > tolX)
              usrMove = move_right;
              if (joyX < -tolX)
              usrMove = move_left;
          }
          else
          { // Y axis
              if (joyY > tolY)
              usrMove = move_down;
              if (joyY < -tolY)
              usrMove = move_up;
          }

      } // joystick input

      // keep the game going
      myGame = myfld->tick( usrMove );
               myfld->update( fieldRedraw );
      fieldRedraw = 0;
      
      // change of status ?
      if (myGame != level_running)
      {
          // what's my score so far ?
          myScore = myfld->get_score();
          // stop timer (suspend thread) and notify main thread
          DosStopTimer (hTimer);
          WinPostMsg ( hwndClient, WM_COMMAND, (VOID *)IDM_ENGINE, (VOID *)myGame);
      }

      // quit thread if game is over
      if (myGame == game_over)
          break;
  }

  // i'm dead
  tidAsync = 0;
}
