//
//
// PmMain.cc
//
// Presentation Manager 'Shell' for MakMan/2
//

// (c) 1995 Markellos J. Diorinos
// All rights reserved
// Check the readme file for (Copy)rights

/*

   We will try to isolate the Shell from the MakMan engine
   which we will try to run in another thread.

   */


#define INCL_DOS
#define INCL_GPI
#define INCL_WIN

#include "pmmain.hpp"
#include "pmvars.hpp"
#include "pmhelp.hpp"
#include "pmids.hpp"
#include "pmkeys.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "debug.h"

#include "tile.hpp"
#include "playfield.hpp"

#include "VideoEngine.hpp"
#include "SndEngine.hpp"
#include "MakEngine.hpp"

#include "joyos2.h"

VOID EnableMenu(ULONG id, BOOL fEnable);
VOID GetOptionsFromIni( VOID );
VOID GetScoresFromIni ( VOID );
VOID SaveOptionsToIni ( VOID );
VOID SaveScoresToIni  ( VOID );

/******************************************************************************
 *
 *  Name        : main
 *
 *  Description : Main thread will initialize the process for PM services and
 *                process the application message queue until a WM_QUIT message
 *                is received.  It will then destroy all PM resources and
 *                terminate.  Any error during initialization will be reported
 *                and the process terminated.
 *
 ******************************************************************************/

VOID main(int argc, char* argv[])
{
    QMSG  qmsg;

    if( Initialize(argc, argv))
    {
        while( WinGetMsg( habMain, &qmsg, NULLHANDLE, 0, 0))
            WinDispatchMsg( habMain, &qmsg);
        Finalize();
    }
    else ;
        { ReportError( habMain); }

}   /* end main() */


/******************************************************************************
 *
 *  Name        : Initialize
 *
 *  Description :
 *
 *  The Initialize function will initialize the PM interface,
 *  create an application message queue, a standard frame window and a new
 *  thread to control drawing operations.  It will also initialize static
 *  strings.
 *
 ******************************************************************************/

extern gfx *GfxEng;
extern snd *SndEng;
extern GAME_2DPOS_STRUCT joyCal[];

BOOL Initialize(int argc, char* argv[])
{
    ULONG    flCreate;
    PID      pid;
    TID      tid;


    debOut = fopen ("\\PIPE\\WATCHCAT", "w");

    if (debOut)
    {
	fprintf(debOut, "MakMan/2 Init\n");
	fflush(debOut);
    }

    GetScoresFromIni();

    /*
     * create all semaphores for mutual exclusion and event timing
     */

    if (
        DosCreateEventSem( NULL,  &hevTick     , DC_SEM_SHARED,    FALSE) ||
        DosCreateEventSem( NULL,  &hevSound    , DC_SEM_SHARED,    FALSE) ||
        DosCreateEventSem( NULL,  &hevTermGame , DC_SEM_SHARED,    FALSE) ||
        DosCreateEventSem( NULL,  &hevTermSound, DC_SEM_SHARED,    FALSE)
        )
        return (FALSE);  /* failed to create a semaphore */


    WinShowPointer( HWND_DESKTOP, TRUE);
    habMain = WinInitialize( 0);
    if( !habMain)
	return( FALSE);

    hmqMain = WinCreateMsgQueue( habMain,0);
    if( !hmqMain)
	return( FALSE);

    WinLoadString( habMain, 0, IDS_TITLEBAR, sizeof(szTitle), szTitle);
    WinLoadString( habMain, 0, IDS_ERRORTITLE, sizeof(szErrorTitle), szErrorTitle);

    if( !WinRegisterClass( habMain
			  , (PCH)szTitle
			  , ClientWndProc
			  , CS_SIZEREDRAW | CS_MOVENOTIFY
			  , 0 ))
	return( FALSE);

    flCreate =   (FCF_TITLEBAR | FCF_SYSMENU    | FCF_MENU       | FCF_BORDER   | FCF_ICON |
		  FCF_AUTOICON | FCF_ACCELTABLE | FCF_MINBUTTON  | FCF_SHELLPOSITION  );
    hwndFrame =
	WinCreateStdWindow(
			   HWND_DESKTOP,                       /* handle of the parent window     */
			   0,                                  /* frame-window style              */
			   &flCreate,                          /* creation flags                  */
			   szTitle,                            /* client-window class name        */
			   szTitle,                            /* address of title-bar text       */
			   WS_SYNCPAINT,                       /* client-window style             */
			   0,                                  /* handle of the resource module   */
			   IDR_MAIN,                           /* frame-window identifier         */
			   &hwndClient);                       /* address of client-window handle */

    if( !hwndFrame)
	return( FALSE);


    if (debOut)
    {
	fprintf(debOut, "Creating engine\n");
	fflush(debOut);
    }

    //
    // Instantiate the Gfx Output engine
    //
    if (argc == 2)
    {
    strlwr(argv[1]); // make lower case
	if (strcmp(argv[1], "gpi") == 0)
        GfxEng = new gpi;
    else
        if (strcmp(argv[1], "dive") == 0)
            GfxEng = new dive;
            else {
                char buf[200];
                sprintf(buf, "Usage : MakMan [gpi | dive]\n"
                             "Unknown option %s\n", argv[1]);
                WinMessageBox(HWND_DESKTOP,
                          hwndFrame,
                          (PSZ) buf,
                          (PSZ) szTitle,
                          0,
                          MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL );
                return FALSE;
            }

    }
    else
        GfxEng = new gpi;

    SndEng = new mmpm2;

    if (debOut)
    {
    fprintf(debOut, "Gfx engine : %p Snd : %p\n", GfxEng, SndEng);
    fflush(debOut);
    }

    if (!GfxEng->open())
    {
	WinMessageBox(HWND_DESKTOP,
		      hwndFrame,
		      (PSZ) "Can't initialize selected Graphics Engine",
		      (PSZ) szTitle,
		      0,
		      MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL );
	return FALSE;
    }

    if (!SndEng->open())
    {
	WinMessageBox(HWND_DESKTOP,
		      hwndFrame,
              (PSZ) "Can't initialize MMPM2 Sound Engine\nSound won't be available for this session",
		      (PSZ) szTitle,
		      0,
		      MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL );
    }


    //
    // Finish up initializing the Window
    //

    // restore the previous position on screen
    int retc = WinRestoreWindowPos(szAppName, szKeyPosition, hwndFrame);
    if (debOut)
    {
        fprintf(debOut, "Restored old pos : %i\n",retc);
        fflush(debOut);
    }


    cxWidthBorder = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CXBORDER);
    cyWidthBorder = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYBORDER);
    cyTitleBar    = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR);
    cyMenu        = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYMENU);
    cyScreen      = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);


    sizlMaxClient.cx = fieldSizeX * tileWidth  + cxWidthBorder * 2;
    sizlMaxClient.cy = fieldSizeY * tileHeight + cyWidthBorder * 2 + cyTitleBar + cyMenu ;

    // And now set the window to the correct size
    WinSetWindowPos( hwndFrame, HWND_TOP, 0, 0,
		    sizlMaxClient.cx, sizlMaxClient.cy,
		    SWP_SIZE | SWP_SHOW  | SWP_ACTIVATE);


    lByteAlignX = WinQuerySysValue( HWND_DESKTOP, SV_CXBYTEALIGN);
    lByteAlignY = WinQuerySysValue( HWND_DESKTOP, SV_CYBYTEALIGN);

    // Turn on visible region notification.
    WinSetVisibleRegionNotify ( hwndClient, TRUE );

    // And invalidate the visible region
    WinPostMsg ( hwndFrame, WM_VRNENABLED, 0L, 0L );

    // Enter the program in the WPS/PM task list
    WinQueryWindowProcess( hwndFrame, &pid, &tid);
    swctl.hwnd      = hwndFrame;
    swctl.idProcess = pid;
    strcpy( swctl.szSwtitle, szTitle);
    hsw = WinAddSwitchEntry(&swctl);

    hwndMenu = WinWindowFromID( hwndFrame, FID_MENU);


    //
    // Disable unused menu entries
    //
    EnableMenu(IDM_LEVEL,           FALSE);
    EnableMenu(IDM_HELPINDEX,       FALSE);
    EnableMenu(IDM_HELPEXTENDED,    FALSE);
    EnableMenu(IDM_HELPHELPFORHELP, FALSE);

    //
    // Look for a Joystick (driver)
    //
    APIRET rc;
    ULONG action;
    GAME_PARM_STRUCT gameParms;
    ULONG dataLen;


    rc = DosOpen(GAMEPDDNAME, &hGame, &action, 0,
                 FILE_READONLY, FILE_OPEN,
                 OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE, NULL);

    if (rc != 0)
        hGame = 0;
    else
    {
        // There is a driver loaded - can we talk to him?
        dataLen = sizeof(gameParms);
        // Look for any (Joy)sticks
        rc = DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_PARMS, NULL, 0, NULL,
                         &gameParms, dataLen, &dataLen);
        if (rc != 0 && debOut)
        {
            fprintf(debOut, "Couldn't call IOCtl for GAME$\n");
            fflush(debOut);
        }
     }

    // ok so far?
    if (hGame == 0 || rc != 0)
       {
            if (debOut)
            {
                fprintf(debOut, "Joystick driver not found\n");
                fflush(debOut);
            }
            DosClose(hGame);
            EnableMenu(IDM_JOY_A, FALSE);
            EnableMenu(IDM_JOY_B, FALSE);
            EnableMenu(IDM_CALIBRATE, FALSE);
            hGame = 0;
       }
        else
        {
            // all ok, deregister any superfluous menu entries
            // and calibrate sticks
            if (debOut)
            {
                fprintf(debOut, "JoyStat A: %i, B:%i\n", gameParms.useA, gameParms.useB);
                fflush(debOut);
            }

           /*
            * Keep only bits defined X and Y axis, they are bit 1 and bit 2
            */
           USHORT usTmp1 = gameParms.useA & GAME_USE_BOTH_NEWMASK;
           USHORT usTmp2 = gameParms.useB & GAME_USE_BOTH_NEWMASK;

            // No Joysticks
            if (gameParms.useA == 0 && gameParms.useB == 0)
            {
                EnableMenu(IDM_JOY_A, FALSE);
                EnableMenu(IDM_CAL_A, FALSE);
                EnableMenu(IDM_JOY_B, FALSE);
                EnableMenu(IDM_CAL_B, FALSE);
            }

            // One Joystick found
            // if usTmp2 is not 0, then Joystick 1 is an extended
            // type joystick (with 3 axes) but we don't care
            if (usTmp1 == GAME_USE_BOTH_NEWMASK &&
                usTmp2 != GAME_USE_BOTH_NEWMASK  )
            {
                EnableMenu(IDM_JOY_B, FALSE);
                EnableMenu(IDM_CAL_B, FALSE);
            }

            // And now read the calibration values
            GAME_CALIB_STRUCT gameCalib;

            dataLen = sizeof(gameCalib);
            rc = DosDevIOCtl(hGame, IOCTL_CAT_USER, GAME_GET_CALIB,
                             NULL, 0, NULL,
                             &gameCalib, dataLen, &dataLen );

            joyCal[1].x = gameCalib.Ax.centre;
            joyCal[1].y = gameCalib.Ay.centre;
            joyCal[2].x = gameCalib.Bx.centre;
            joyCal[2].y = gameCalib.By.centre;

        }


    /*
     * initialise help mechanism
     */
    HelpInit();


    // Set the default values for the various options...
    GetOptionsFromIni();

    // initiate random number generator
    srand(time(NULL));


    return TRUE;



}   /* end Initialize() */


/******************************************************************************
 *
 *  Name        : ReportError
 *
 *  Description :
 *
 * ReportError  will display the latest error information for the required
 * thread. No resources to be loaded if out of memory error.
 *
 ******************************************************************************/

VOID ReportError(HAB hab)
{
    PERRINFO  perriBlk;
    PSZ       pszErrMsg;
    PSZ       pszOffSet;

    if (!fErrMem){
	if ((perriBlk = WinGetErrorInfo(hab)) != (PERRINFO)NULL){
	    pszOffSet = ((PSZ)perriBlk) + perriBlk->offaoffszMsg;
	    pszErrMsg = ((PSZ)perriBlk) + *((PULONG)pszOffSet);
	    WinMessageBox(HWND_DESKTOP,
			  hwndFrame,
			  (PSZ)(pszErrMsg),
			  (PSZ)szTitle,
			  0,
			  MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL );
	    WinFreeErrorInfo(perriBlk);
	    return;
	}
    } /* endif */

    MessageBox(                                                       /* ERROR */
	       hwndFrame,
	       IDS_ERROR_OUTOFMEMORY,
	       MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL,
	       TRUE);

}   /* end ReportError() */


/**************************************************************************/
/* DispError -- report an error returned from an API service.             */
/*                                                                        */
/* The error message is displayed using a message box                     */
/*                                                                        */
/**************************************************************************/
VOID DispErrorMsg(HAB hab, HWND hwndFrame, PCH FileName, LONG LineNum)
{
    PERRINFO  pErrInfoBlk;
    PSZ       pszOffSet, pszErrMsg;
    ERRORID   ErrorId;
    PCH       ErrorStr;
    CHAR      szbuff[125];

    DosBeep(800,10);
#if defined(DEBUG)
    DosBeep(800,10);
    DosBeep(800,10);
    DosBeep(800,10);
    DosBeep(800,10);
    DosBeep(800,10);
#endif   /* defined(DEBUG) */

    if (!hab)
    {                                     /* Non-PM Error */
	WinLoadString( habMain,0, IDS_UNKNOWNMSG, sizeof(szbuff), (PSZ)szbuff);
	ErrorStr = (char*) malloc(strlen(szbuff)+strlen(FileName)+10);
	sprintf(ErrorStr, szbuff, FileName, LineNum);
	WinMessageBox(HWND_DESKTOP,         /* Parent window is desk top */
		      hwndFrame,            /* Owner window is our frame */
		      (PSZ)ErrorStr,        /* PMWIN Error message       */
		      szErrorTitle,         /* Title bar message         */
		      MSGBOXID,             /* Message identifier        */
		      MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL ); /* Flags */
	free(ErrorStr);
	return;
    }

    ErrorId = WinGetLastError(hab);

    if ((pErrInfoBlk = WinGetErrorInfo(hab)) != (PERRINFO)NULL)
    {
	pszOffSet = ((PSZ)pErrInfoBlk) + pErrInfoBlk->offaoffszMsg;
	pszErrMsg = ((PSZ)pErrInfoBlk) + *((PULONG)pszOffSet);

	WinLoadString( habMain,0, IDS_ERRORMSG, sizeof(szbuff), (PSZ)szbuff);
	ErrorStr = (char *)malloc(strlen(szbuff)+strlen(pszErrMsg)+strlen(FileName)+10);
	sprintf(ErrorStr, szbuff, pszErrMsg, FileName, LineNum);

	WinMessageBox(HWND_DESKTOP,         /* Parent window is desk top */
		      hwndFrame,            /* Owner window is our frame */
		      (PSZ)ErrorStr,        /* PMWIN Error message       */
		      szErrorTitle,         /* Title bar message         */
		      MSGBOXID,             /* Message identifier        */
		      MB_MOVEABLE | MB_CUACRITICAL | MB_CANCEL ); /* Flags */

	free(ErrorStr);

	WinFreeErrorInfo(pErrInfoBlk);
    }


}



/******************************************************************************
 *
 *  Name        : Finalize
 *
 *  Description :
 *
 * Finalize will destroy the asynchronous drawing thread, all Presentation
 * Manager resources, and terminate the process.
 *
 ******************************************************************************/

VOID Finalize(VOID)
{
    APIRET rc;

    // Save Options to INI file
    SaveScoresToIni();
    SaveOptionsToIni();
    WinStoreWindowPos(szAppName, szKeyPosition, hwndFrame);


    // close the game engine and the associated async thread, if any
    Eng_Close();
    dprint("gameEng close\n");

    GfxEng->close();
    dprint("GfxEng close\n");


    // close the sound engine
    // this also takes care of any sound threads
    SndEng->close();
    dprint("SoundEng close");

    if( hrgnInvalid)
	GpiDestroyRegion( hpsClient, hrgnInvalid);
    if( hpsClient)
    {
        GpiAssociate( hpsClient, NULLHANDLE);
        GpiDestroyPS( hpsClient);
    }

    if( hpsPaint)
        GpiDestroyPS( hpsPaint);

    dprint("Destroyed hPS\n");

    DestroyHelpInstance();

    if (hwndFrame)
        WinDestroyWindow( hwndFrame);
    if (hmqMain)
        WinDestroyMsgQueue( hmqMain);
    if (habMain)
        WinTerminate( habMain);
    if (hGame)
        DosClose(hGame);

    dprint("Destroyed handles\n");


    if (debOut)
    {
        fprintf(debOut, "Exiting MakMan/2\n");
        fflush(debOut);
        fclose(debOut);
    }

    DosExit( EXIT_PROCESS, 0);

}   /* end Finalize() */


/******************************************************************************
 *
 *  Name        : EnableMenu
 *
 *  Description : Enable/Disable bitmap size submenus
 *
 *  Parameters  : ULONG id        - menu id (ASSUME: id = submenu of FID_MAIN
 *                BOOL  fEnable   - enable/disable?
 *
 *  Return      : VOID
 *
 ******************************************************************************/

VOID EnableMenu(ULONG id, BOOL fEnable)
{
    WinSendMsg(hwndMenu,                          /* global main menu handle */
	       MM_SETITEMATTR,                                 /* set menu attribute */
	       MPFROM2SHORT(id, TRUE),                                    /* menu id */
	       MPFROM2SHORT(MIA_DISABLED,                      /* mask = disable bit */
			    fEnable ? ~MIA_DISABLED : MIA_DISABLED)); /* turn off/on */

}   /* end EnableMenu() */


//
// Load MakMan/2 Options from INI files
//

HINI hini;

VOID SetDefault ( int WinMsg)
{
    WinPostMsg ( hwndClient, WM_COMMAND, (VOID *) WinMsg, (VOID *)0);
}

VOID WriteProfileInt ( char* key, int value )
{
    char buf[80];

    sprintf(buf, "%i", value);
    PrfWriteProfileString( hini, szAppName, key, buf );
}

VOID GetOptionsFromIni( VOID )
{
    int TileSet, Input, Sound, Priority;

    hini = PrfOpenProfile (habMain, "MAKMAN.INI");

    TileSet  = PrfQueryProfileInt(hini,szAppName,"Tile Set", 1);
    Input    = PrfQueryProfileInt(hini,szAppName,"Input Source", 0);
    Sound    = PrfQueryProfileInt(hini,szAppName,"Sound Enabled", 1);
    Priority = PrfQueryProfileInt(hini,szAppName,"Priority", 0);

    if (debOut)
    {
        fprintf(debOut, "TS : %i, Input %i, Sound %i, Prio %i\n", TileSet, Input, Sound, Priority);
        fflush(debOut);
    }

    SetDefault (IDM_T_CLASSIC + TileSet);
    SetDefault (IDM_KEYBOARD + Input);
    if (Sound)
        SetDefault (IDM_SOUND_ON);
    else
        SetDefault (IDM_SOUND_OFF);
    SetDefault (IDM_PRI_NORMAL + Priority);

    PrfCloseProfile(hini);
}


//
// Save MakMan/2 Options from INI files
//
VOID SaveOptionsToIni( VOID )
{
    int TileSet, Input, Sound, Priority;

    hini = PrfOpenProfile(habMain, "MAKMAN.INI");

    if (WinIsMenuItemChecked(hwndMenu, IDM_T_CLASSIC))
        TileSet = 0;
    else
       if (WinIsMenuItemChecked(hwndMenu, IDM_T_3D))
          TileSet = 1;
       else
            TileSet = 2;


    if (WinIsMenuItemChecked(hwndMenu, IDM_KEYBOARD))
        Input = 0;
    if (WinIsMenuItemChecked(hwndMenu, IDM_JOY_A))
        Input = 1;
    if (WinIsMenuItemChecked(hwndMenu, IDM_JOY_B))
        Input = 2;


    if (WinIsMenuItemChecked(hwndMenu, IDM_SOUND_ON))
        Sound = 1;
    else
        Sound = 0;

    if (WinIsMenuItemChecked(hwndMenu, IDM_PRI_NORMAL))
        Priority = 0;
    if (WinIsMenuItemChecked(hwndMenu, IDM_PRI_CRIT))
        Priority = 1;
    if (WinIsMenuItemChecked(hwndMenu, IDM_PRI_SERVER))
        Priority = 2;


    if (debOut)
    {
        fprintf(debOut, "TS : %i, Input %i, Sound %i, Prio %i\n", TileSet, Input, Sound, Priority);
        fflush(debOut);
    }

    WriteProfileInt ("Tile Set", TileSet);
    WriteProfileInt ("Input Source", Input);
    WriteProfileInt ("Sound Enabled", Sound);
    WriteProfileInt ("Priority", Priority);

    PrfCloseProfile(hini);
}


extern char topNames[15][100];
extern long topScores[15];

VOID GetScoresFromIni ( VOID )
{
    ULONG bMax;

    hini = PrfOpenProfile(habMain, "MAKMAN.INI");

    bMax = 15*100;
    PrfQueryProfileData(hini, szAppName, "ScoreNames", topNames, &bMax);
    bMax = 15 * sizeof(long);
    PrfQueryProfileData(hini, szAppName, "Scores", topScores, &bMax);

    PrfCloseProfile(hini);
}

VOID SaveScoresToIni( VOID )
{
    hini = PrfOpenProfile(habMain, "MAKMAN.INI");

    PrfWriteProfileData(hini, szAppName, "ScoreNames", topNames, 15*100);
    PrfWriteProfileData(hini, szAppName, "Scores", topScores, 15 * sizeof(long));

    PrfCloseProfile(hini);

}
