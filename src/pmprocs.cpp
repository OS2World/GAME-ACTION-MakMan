//
//
// PmProcs.cc
//
// Various PM procedures

#define INCL_OS2MM                      /* Required for MCI & MMIO headers   */
#define INCL_DOS
#define INCL_GPI
#define INCL_WIN
#define INCL_WINWORKPLACE

#include "PmMain.hpp"
#include "PmHelp.hpp"
#include "PmVars.hpp"
#include "PmIDs.hpp"
#include "PmKEYS.hpp"
#include "lang.h"
#include <os2me.h>
#include <stdio.h>
#include <string.h>

#include "makengine.hpp"
#include "VideoEngine.hpp"
#include "sndengine.hpp"
#include "playfield.hpp"
#include "tile.hpp"

#include "debug.h"
#include "joyos2.h"

FILE* debOut = NULL;

extern char* tilePaths[];
extern int   fieldRedraw;
extern int   useJoystick;
extern GAME_2DPOS_STRUCT joyCal[];
extern snd *SndEng;
extern gfx *GfxEng;
extern long myScore;

/* frame control and feature globals (defined in pmmain.cpp) */
extern HWND hwndTitleBar;
extern HWND hwndSysMenu;
extern HWND hwndMinMax;
extern HWND hwndFMenu;
extern HWND hwndObject;
extern BOOL bFrameHidden;
extern BOOL bBackgrndRun;
extern BOOL bSaveOnExit;

VOID set_language( int lang );

ULONG priorityTable[] =
{
    PRTYC_REGULAR,
    PRTYC_TIMECRITICAL,
    PRTYC_FOREGROUNDSERVER
};

int gameRunning = 0;
MRESULT EXPENTRY AboutBoxDlgProc(HWND hwnd, ULONG msg,
             MPARAM mp1, MPARAM mp2);
MRESULT EXPENTRY HighScoreDlgProc(HWND hwnd, ULONG msg,
             MPARAM mp1, MPARAM mp2);
VOID CheckMenu(ULONG id, BOOL fCheck);
VOID EnableMenu(ULONG id, BOOL fEnable);

char topNames[15][100] = {
    "Markellos J. Diorinos",
    "Clark Gable",
    "Cindy Crawford",
    "Louis Armstrong",
    "Nandja Auermann",
    "Miles Davis",
    "Front 242",
    "Hoodlum Priest",
    "Yello",
    "808 State",
    "Tricky",
    "Mouse on Mars",
    "Trans Global Underground",
    "Art Of Noise",
    "Bill Gates" };

long topScores[15] =
{
    5000, 4000, 3000, 2000, 1000,
    900, 800, 700, 600, 500,
    400, 300, 200, 100, 0 };

int newScorePos;

void CheckForHighScore( void )
{
    newScorePos = -1;

    for (int i = 14; i >= 0 ; i--)
         if (topScores[i] < myScore)
            newScorePos = i;

    // a new entry - call up the dialog box
    if (newScorePos >= 0)
         WinDlgBox(HWND_DESKTOP,
                   hwndFrame, (PFNWP)HighScoreDlgProc,
                   NULLHANDLE, IDD_HIGHSCORE, (PVOID)NULL);
}

// Displays High Scores
void ShowGameHighscore( HPS hps, RECTL rcl )
{
    char txt[700];
    POINTL point;

    GpiSetColor(hps, 69);
    GpiSetBackColor(hps, 0);
    point.x = 0; point.y = 0;
    GpiMove(hps, &point);

    point.x = sizlMaxClient.cx;
    point.y = sizlMaxClient.cy;

    GpiSetColor(hps, CLR_BLACK);
    GpiBox( hps, DRO_FILL, &point,0 ,0);

    long bibibibi = 1;
    FATTRS fat;

    fat.usRecordLength = sizeof(FATTRS);
    fat.fsSelection = 0;
    fat.lMatch = 0L;
    fat.idRegistry = 0;
    fat.usCodePage = 850;
    fat.lMaxBaselineExt = 18L;
    fat.lAveCharWidth = 18L;
    fat.fsType = 0;
    fat.fsFontUse = FATTR_FONTUSE_NOMIX;
    strcpy(fat.szFacename, "Tms Rmn");

    GpiCreateLogFont(hps, NULL, bibibibi, &fat);

    GpiSetCharSet(hps, bibibibi);

    GpiSetColor(hps, CLR_CYAN);


    for (int i=0; i<15; i++)
    {
	point.x = 70;
	point.y = 420 - i*24;	
	sprintf(txt, "%02i. %s", i+1, topNames[i]);
	GpiCharStringAt(hps, &point, strlen(txt), txt);


	point.x = 470;
	point.y = 420 - i*24;	
    sprintf(txt, "%08li", topScores[i]);
	GpiCharStringAt(hps, &point, strlen(txt), txt);
    }

    long bababuba = 2;
    fat.usRecordLength = sizeof(FATTRS);
    fat.fsSelection = 0;
    fat.lMatch = 0L;
    fat.idRegistry = 0;
    fat.usCodePage = 850;
    fat.lMaxBaselineExt = 22L;
    fat.lAveCharWidth = 22L;
    fat.fsType = 0;
    fat.fsFontUse = FATTR_FONTUSE_NOMIX;
    strcpy(fat.szFacename, "Helvetica");

    GpiCreateLogFont(hps, NULL, bababuba, &fat);

    GpiSetCharSet(hps, bababuba);

    GpiSetColor(hps, CLR_RED);
    sprintf(txt, "%s v%s Top 15 Players", szAppName, szAppVersion);
    point.y = 510;
    point.x = 213;
    GpiCharStringAt(hps, &point, strlen(txt), txt);

    long ClopyFont = 3;
    fat.usRecordLength = sizeof(FATTRS);
    fat.fsSelection = 0;
    fat.lMatch = 0L;
    fat.idRegistry = 0;
    fat.usCodePage = 850;
    fat.lMaxBaselineExt = 22L;
    fat.lAveCharWidth = 22L;
    fat.fsType = 0;
    fat.fsFontUse = FATTR_FONTUSE_NOMIX;
    strcpy(fat.szFacename, "Tms Rmn");

    GpiCreateLogFont(hps, NULL, ClopyFont, &fat);

    GpiSetCharSet(hps, ClopyFont);

    GpiSetColor(hps, CLR_YELLOW);
    strcpy(txt, "(C) 1995/6 Markellos J. Diorinos, All rights preserved");
    point.y = 480;
    point.x = 105;
    GpiCharStringAt(hps, &point, strlen(txt), txt);


}

/****************************************************************\
 *  Message Box procedure
 *--------------------------------------------------------------
 *
 *  Name:   MessageBox(hwndOwner, idMsg, fsStyle, fBeep)
 *
 *  Purpose: Displays the message box with the message
 *              given in idMsg retrived from the message table
 *              and using the style flags in fsStyle
 *
 *  Usage:  Called whenever a MessageBox is to be displayed
 *
 *  Method: - Message string is loaded from the process'
 *              message table
 *          - Alarm beep is sounded if desired
 *          - Message box with the message is displayed
 *          - WinMessageBox return value is returned
 *
 *  Returns: return value from WinMessageBox()
 *
 \****************************************************************/
ULONG MessageBox(HWND hwndOwner, ULONG idMsg, ULONG fsStyle, BOOL fBeep)
{
    CHAR szText[MESSAGELEN];
    PSZ  pszTitle;

    if (fsStyle & MB_ERROR)
	pszTitle = NULL;                                 /* default is "Error" */
    else
	pszTitle = szTitle;                     /* use "Jigsaw" for non-errors */

    if (!WinLoadString(habMain,
		       (HMODULE)NULLHANDLE,
		       idMsg,
		       MESSAGELEN,
		       (PSZ)szText))
    {
	if (idMsg == IDS_CANNOTLOADSTRING)
	{
	    strcpy(szText, "Failed to load resource string");
	}
	else
	{
	    WinAlarm(HWND_DESKTOP, WA_ERROR);
	    return MBID_ERROR;
	}
    }

    if (fBeep)
	WinAlarm(HWND_DESKTOP, WA_ERROR);

    return WinMessageBox(HWND_DESKTOP,     /* handle of the parent window     */
			 hwndOwner,                   /* handle of the owner window      */
			 szText,                      /* address of text in message box  */
			 pszTitle,                    /* address of title of message box */
			 MSGBOXID,                    /* message-box identifier          */
			 fsStyle);                    /* type of message box             */

}   /* end MessageBox() */


/******************************************************************************/
/*                                                                            */
/* Create a memory DC and an associated PS.                                   */
/*                                                                            */
/******************************************************************************/
BOOL CreateBitmapHdcHps( PHDC phdc, PHPS phps)
{
    SIZEL    sizl;
    HDC      hdc;
    HPS      hps;

    hdc = DevOpenDC( habMain, OD_MEMORY, "*", 3L, (PDEVOPENDATA)&dop, NULLHANDLE);
    if( !hdc)
	return( FALSE);

    sizl.cx = sizl.cy = 1L;
    if ((hps = GpiCreatePS( habMain
			   , hdc
			   , &sizl
			   , PU_PELS | GPIA_ASSOC | GPIT_MICRO )) == GPI_ERROR)
	DispError(habMain,hwndClient);
    if( !hps)
	return( FALSE);

    *phdc = hdc;
    *phps = hps;
    return( TRUE);
}


/******************************************************************************
 *
 *  Name        : ClientWndProc
 *
 *  Description : ClientWndProc is the window procedure associated with the
 *                client window.
 *
 *  Parameters  : HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2
 *
 *  Return      : MRESULT
 *
 ******************************************************************************/


MRESULT EXPENTRY ClientWndProc(HWND hwnd,ULONG msg,MPARAM mp1,MPARAM mp2)
{
    ULONG  rc;
    static int oldTileSet = 0;

    switch (msg)
    {
	


	/**************************************************************************/
	/* Some menu command                                                      */
	/**************************************************************************/
    case WM_COMMAND :
	if (debOut)
	{
	    fprintf(debOut, "Menu Command %i - %i\n" ,SHORT1FROMMP(mp1), SHORT1FROMMP(mp2));
	    fflush(debOut);
	}
	switch ( SHORT1FROMMP ( mp1 ) )
	{
	case IDM_NEW:
	    Eng_NewGame();
	    Eng_InitLevel( gameLevel = 0 );
	    Eng_StartGame();
	    gameRunning = 1;
	    EnableMenu(IDM_SUBMENU_TILESET, FALSE);
	    EnableMenu(IDM_PAUSE,     TRUE);
	    EnableMenu(IDM_QUIT_GAME, TRUE);
	    WinCheckMenuItem(hwndMenu, IDM_PAUSE, FALSE);
	    break;

	case IDM_PAUSE:
	    if (gameRunning) {
	        BOOL bPaused = WinIsMenuItemChecked(hwndMenu, IDM_PAUSE);
	        if (bPaused) {
	            DosResumeThread(tidAsync);
	            WinCheckMenuItem(hwndMenu, IDM_PAUSE, FALSE);
	        } else {
	            DosSuspendThread(tidAsync);
	            WinCheckMenuItem(hwndMenu, IDM_PAUSE, TRUE);
	        }
	    }
	    break;

	case IDM_QUIT_GAME:
	    if (gameRunning) {
	        DosResumeThread(tidAsync);
	        Eng_StopGame();            /* only the game stops: the engine stays for the next game */
	        gameRunning = 0;
	        WinCheckMenuItem(hwndMenu, IDM_PAUSE, FALSE);
	        EnableMenu(IDM_SUBMENU_TILESET, TRUE);
	        EnableMenu(IDM_PAUSE,     FALSE);
	        EnableMenu(IDM_QUIT_GAME, FALSE);
	        WinInvalidateRegion(hwndFrame, NULLHANDLE, TRUE);
	    }
	    break;

	case IDM_EXIT:
	    WinPostMsg( hwnd, WM_QUIT, NULL, NULL);
	case IDM_ENGINE:
	    switch ( SHORT1FROMMP( mp2 ))
	    {
	    case level_done:
            Eng_InitLevel ( ++gameLevel );
            Eng_StartGame();
            break;
	    case game_over:
            gameRunning = 0;
            EnableMenu(IDM_SUBMENU_TILESET, TRUE);
            EnableMenu(IDM_PAUSE,     FALSE);
            EnableMenu(IDM_QUIT_GAME, FALSE);
            WinCheckMenuItem(hwndMenu, IDM_PAUSE, FALSE);
            WinInvalidateRegion(hwndFrame, NULLHANDLE, TRUE);
            CheckForHighScore();
            break;
	    }
	    break;
	case IDM_T_CLASSIC:
	case IDM_T_3D:
    case IDM_T_NEWLOOK:
	    if (oldTileSet)
            CheckMenu(oldTileSet, FALSE);
        Eng_Close();
	    strcpy(defaultTilePath, tilePaths[ SHORT1FROMMP(mp1) - IDM_T_CLASSIC]);
        Eng_Init();
	    CheckMenu(oldTileSet = SHORT1FROMMP(mp1), TRUE);
	    WinInvalidateRegion(hwndFrame, NULLHANDLE, TRUE);
	    break;

    case IDM_KEYBOARD:
	    if (useJoystick)
		CheckMenu(IDM_JOY_A + useJoystick -1, FALSE);
	    CheckMenu(IDM_KEYBOARD, TRUE);
	    useJoystick = 0;
	    break;
    case IDM_JOY_A:
    case IDM_JOY_B:
	    CheckMenu(IDM_KEYBOARD, FALSE);
	    if (useJoystick)
		CheckMenu(IDM_JOY_A + useJoystick -1, FALSE);	
	    CheckMenu(SHORT1FROMMP(mp1), TRUE);
	    useJoystick = SHORT1FROMMP(mp1) - IDM_JOY_A + 1;
	    break;
	
	case IDM_CAL_A:
	case IDM_CAL_B:
	{
	
	    // Joystick Calibration
	    // ********************
	    GAME_STATUS_STRUCT joy;
	    GAME_2DPOS_STRUCT *joyData = &joy.curdata.A;
	    ULONG dataLen = sizeof(joy);
	    ULONG calJoystick;
	
	    calJoystick = SHORT1FROMMP(mp1) - IDM_CAL_A + 1;
	
	    WinMessageBox(HWND_DESKTOP,
			  hwndFrame,
			  (PSZ)"Leave the Joystick alone and click OK",
			  (PSZ)"MakMan/2 Joystick Calibration",
			  0,
			  MB_MOVEABLE | MB_INFORMATION | MB_OK );
	
	    DosDevIOCtl( hGame, IOCTL_CAT_USER, GAME_GET_STATUS,
			NULL, 0, NULL,
			&joy, dataLen, &dataLen);
	
	    joyCal[calJoystick].x = joyData[calJoystick-1].x;
	    joyCal[calJoystick].y = joyData[calJoystick-1].y;
	
	    if (debOut)
	    {
		fprintf(debOut, "Joystick %i X : %i, Y: %i\n",
			calJoystick,
			joyCal[calJoystick].x,
			joyCal[calJoystick].y);
		fflush(debOut);
	    }
	}
	    break;
	
	case IDM_PRI_NORMAL:
	case IDM_PRI_CRIT:
	case IDM_PRI_SERVER:
	    CheckMenu(IDM_PRI_NORMAL, FALSE);
	    CheckMenu(IDM_PRI_CRIT, FALSE);
	    CheckMenu(IDM_PRI_SERVER, FALSE);
	    CheckMenu(SHORT1FROMMP(mp1), TRUE);
	    DosSetPriority(PRTYS_THREAD, priorityTable[SHORT1FROMMP(mp1)-IDM_PRI_NORMAL],
			   PRTYD_MAXIMUM, tidAsync);
	    break;

	case IDM_SOUND_ON:
        SndEng->start();
        CheckMenu(IDM_SOUND_ON , TRUE);
        CheckMenu(IDM_SOUND_OFF, FALSE);

	    break;
	case IDM_SOUND_OFF:
	    CheckMenu(IDM_SOUND_ON , FALSE);
	    CheckMenu(IDM_SOUND_OFF, TRUE);
	    SndEng->stop();
	    break;	

    case IDM_LANG_EN:
    case IDM_LANG_ES:
    case IDM_LANG_NL:
    case IDM_LANG_DE:
    case IDM_LANG_FR:
    case IDM_LANG_IT:
        set_language(SHORT1FROMMP(mp1) - IDM_LANG_EN);
        break;

    case IDM_SAVEONEXIT:
        bSaveOnExit = !bSaveOnExit;
        WinCheckMenuItem(hwndMenu, IDM_SAVEONEXIT, bSaveOnExit);
        break;

    case IDM_BACKGRND:
        bBackgrndRun = !bBackgrndRun;
        WinCheckMenuItem(hwndMenu, IDM_BACKGRND, bBackgrndRun);
        break;

    case IDM_FRAME:
    {
        RECTL  rclFrame;
        HWND   hwndNew = bFrameHidden ? hwndFrame : hwndObject;

        /* the playing field keeps its size: the frame grows or shrinks around it */
        WinQueryWindowRect(hwndClient, &rclFrame);

        /* the controls are parked in a hidden frame, never in HWND_OBJECT itself
           (that would clear their WS_VISIBLE flag) */
        WinSetParent(hwndTitleBar, hwndNew, FALSE);
        WinSetParent(hwndSysMenu,  hwndNew, FALSE);
        WinSetParent(hwndFMenu,    hwndNew, FALSE);
        WinSetParent(hwndMinMax,   hwndNew, FALSE);
        bFrameHidden = !bFrameHidden;

        WinSendMsg(hwndFrame, WM_UPDATEFRAME,
                   MPFROMLONG(FCF_TITLEBAR|FCF_SYSMENU|FCF_MINMAX|FCF_MENU), NULL);

        /* the frame only formats itself again when its size changes */
        WinCalcFrameRect(hwndFrame, &rclFrame, FALSE);
        WinSetWindowPos(hwndFrame, HWND_TOP, 0, 0,
                        rclFrame.xRight - rclFrame.xLeft,
                        rclFrame.yTop - rclFrame.yBottom, SWP_SIZE);

        WinInvalidateRect(hwndFrame, NULL, TRUE);
        WinUpdateWindow(hwndFrame);

        /* the menu is not a child of the frame while it is hidden: use the saved handle */
        WinCheckMenuItem(hwndFMenu, IDM_FRAME, bFrameHidden);
    }
        break;

    case IDM_HELPINDEX:
        HelpIndex();
        break;

    case IDM_HELPEXTENDED:
        HelpExtended();
        break;

    case IDM_HELPHELPFORHELP:
        HelpHelpForHelp();
        break;

    case IDM_HELPABOUT:
	    rc = WinDlgBox(HWND_DESKTOP,
			   hwndFrame,
			   (PFNWP)AboutBoxDlgProc,
			   NULLHANDLE,
			   IDD_ABOUTBOX,
			   (PVOID)NULL);
        break;


	default:
	    break;


	};
	break;
	
	
	/**************************************************************************/
	/* Our window got MOVED                                                   */
	/**************************************************************************/
    case WM_MOVE:
        SWP crntPos;
        WinQueryWindowPos ( hwndClient, &crntPos );
        POINTL aPoint;
        aPoint.x = crntPos.x ;
        aPoint.y = crntPos.y ;
        WinMapWindowPoints ( hwndFrame,
                             HWND_DESKTOP, &aPoint, 1 );
        Eng_SetOfs ( aPoint.x, aPoint.y );
        break;
	
    case WM_PAINT:
        HPS hpsWM;
        RECTL rcl;

        dprint("WM_PAINT\n");
        hpsWM = WinBeginPaint (hwndClient, NULL, &rcl);
        if (gameRunning)
            // game is still playing
            fieldRedraw = 1;
        else
            // we're in demo mode - show highscores
            ShowGameHighscore( hpsWM, rcl );

        WinEndPaint (hpsWM);
        break;

    case WM_CHAR:
        // This is a key down transition and keyboard is used as an Input device
        if (!useJoystick)
            if (!(CHARMSG(&msg)->fs & KC_KEYUP))
                Eng_ProcessInput( CHARMSG(&msg)->vkey );
        break;


    case WM_VRNDISABLED:
        /*
	   HUI = stop video output
	   DiveSetupBlitter ( pwinData->hDive, 0 );
	   */
        break;


   case WM_ACTIVATE:
        if (SHORT1FROMMP(mp1))
        {
            if (gameRunning && !WinIsMenuItemChecked(hwndMenu, IDM_PAUSE))
                DosResumeThread(tidAsync);
        }
        else
        {
            if (!bBackgrndRun && gameRunning)
                DosSuspendThread(tidAsync);
        }
        break;



    case WM_VRNENABLED:

        HPS     hps;
        HRGN    hrgn;
        SWP     swp;
        POINTL  pointl;
        RGNRECT VisRgn;

        hps = WinGetPS ( hwnd );
        if ( !hps )
	    break;
        hrgn = GpiCreateRegion ( hps, 0L, NULL );
        if ( hrgn )
	{
	    /* NOTE: If mp1 is zero, then this was just a move message.
	     ** Illustrate the visible region on a WM_VRNENABLE.
	     */
	    WinQueryVisibleRegion ( hwnd, hrgn );
	    VisRgn.ircStart     = 0;
	    VisRgn.crc          = 100;
	    VisRgn.ulDirection  = 1;

	    /* Get the all ORed rectangles
	     */
	    if ( GpiQueryRegionRects ( hps, hrgn, NULL, &VisRgn, VisRects) )
	    {
		/* Now find the window position and size, relative to parent.
		 */
		WinQueryWindowPos ( hwndClient, &swp );

		/* Convert the point to offset from desktop lower left.
		 */
		pointl.x = swp.x;
		pointl.y = swp.y;
		WinMapWindowPoints ( hwndFrame,
				    HWND_DESKTOP, &pointl, 1 );

		numVisRects = VisRgn.crcReturned;
	    }
	    else
	    {
		numVisRects = 0;
		// Stop output - nothing visible!!!!!!!!!!!
	    }

	    GpiDestroyRegion( hps, hrgn );
	}
        WinReleasePS( hps );
        break;

    case MM_MCIPLAYLISTMESSAGE:
	SndEng->notify(SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp1 ), LONGFROMMP(mp2));
	break;
    case MM_MCINOTIFY :
	/*
	 * A MCI Notify message has been recieved as a result of an MCI_PLAY.
	 * Process as required.
	 */
	SndEng->notify(SHORT1FROMMP( mp1 ), SHORT2FROMMP( mp2 ), SHORT2FROMMP( mp1 ));
	break;


	/**************************************************************************/
	/*  We'll handle background redraw ourselfs, tell PM to do nothing        */
	/**************************************************************************/
    case WM_ERASEBACKGROUND:
	return( ( MRESULT)FALSE);
	// break;
	
    case WM_CLOSE:
	WinPostMsg( hwnd, WM_QUIT, NULL, NULL);
	break;


	/**************************************************************************/
	/* Default for the rest                                                   */
	/**************************************************************************/
    default:
	return( WinDefWindowProc( hwnd, msg, mp1, mp2));
	
    }   /* end switch (msg)  */

    return( FALSE);

}   /* end ClientWndProc() */

/******************************************************************************
 *
 *  Name        : CheckMenu
 *
 *  Description : Check/Uncheck bitmap size submenus
 *
 *  Parameters  : ULONG id       - menu id  (ASSUME: id = submenu of FID_MAIN
 *                BOOL  fCheck   - check/unckeck?
 *
 *  Return      : VOID
 *
 ******************************************************************************/

VOID CheckMenu(ULONG id, BOOL fCheck)
{
    WinSendMsg(hwndMenu,                          /* global main menu handle */
	       MM_SETITEMATTR,                                 /* set menu attribute */
	       MPFROM2SHORT(id, TRUE),                                    /* menu id */
	       MPFROM2SHORT(MIA_CHECKED,                         /* mask = check bit */
			    fCheck ? MIA_CHECKED : ~MIA_CHECKED));    /* turn on/off */

}   /* end CheckMenu() */


MRESULT EXPENTRY AboutBoxDlgProc(HWND hwnd, ULONG msg,MPARAM mp1,MPARAM mp2)
{

    switch(msg)  {
    case WM_COMMAND:
	/* no matter what the command, close the dialog */
	WinDismissDlg(hwnd, TRUE);
	break;
	
    default:
	return(WinDefDlgProc(hwnd, msg, mp1, mp2));
       break;
    }

    return 0L;

}   /* AboutBoxDlgProc() */



// is he proud of himself?
int proud;
char HighName[400];

MRESULT EXPENTRY HighScoreDlgProc(HWND hwnd, ULONG msg,MPARAM mp1,MPARAM mp2)
{
    int i;

    switch(msg)  {
    case WM_COMMAND:
        switch (SHORT1FROMMP(mp1)) {
            case DID_OK:
                proud = 1;
                break;
            case DID_CANCEL:
                proud = 0;
                break;
        }
        WinQueryDlgItemText(hwnd, DID_HIGHNAME, sizeof(HighName), HighName);
        for (i = 13; i >= newScorePos; i--)
        {
            strcpy(topNames[i+1], topNames[i]);
            topScores[i+1] = topScores[i];
        }

        strcpy(topNames[newScorePos], HighName);
        topScores[newScorePos] = myScore;

        // redraw scores
	    WinInvalidateRegion(hwndFrame, NULLHANDLE, TRUE);

        /* no matter what the command, close the dialog */
        WinDismissDlg(hwnd, TRUE);
    break;

    default:
        return(WinDefDlgProc(hwnd, msg, mp1, mp2));
       break;
    }

    return 0L;

}   /* HighScoreDlgProc() */
