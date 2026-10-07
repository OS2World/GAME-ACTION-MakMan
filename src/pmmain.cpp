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
#include "lang.h"

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

#pragma off(unreferenced)
static const char bldlevel[] =
    "@#Markellos J. Diorinos:1.1#@##1## 10 Sep 2026 21:00:00      "
    "ARCAOS:::0::::@@MakMan/2 - PacMan clone for OS/2\r\n\x1a";
#pragma on(unreferenced)

/* ---- language runtime table ---- */

int current_lang = LANG_EN;

const char *lang_strings[LANG_COUNT][STR_COUNT] = {
    /* LANG_EN */
    {
        "~Game",                         "~New\tCtrl+N",
        "~Pause Game\tCtrl+P",           "~Quit Game\tCtrl+Q",
        "E~xit\tCtrl+X",                 "~Options",
        "~Tile Set",                     "~Classic",
        "~3D Look",                      "~Fufitos",
        "~Controls",                     "~Keyboard",
        "Joystick ~A",                   "Joystick ~B",
        "Cali~brate",                    "Joystick ~A",
        "Joystick ~B",                   "~Sound",
        "~On",                           "O~ff",
        "~Priority",                     "~Normal",
        "~Critical",                     "~Server",
        "~Language",                     "~Save Settings on Exit",
        "~Background Run\tCtrl+B",       "~Frame Controls\tCtrl+F",
        "~Help",                         "~About MakMan/2...",
        "Help ~index", "~General help", "~Using help",
        "MakMan/2 Help Window",
        "The help file %s was not found.\nPlease put it in the help folder next to the program."
    },
    /* LANG_ES */
    {
        "~Juego",                        "~Nuevo\tCtrl+N",
        "~Pausar Juego\tCtrl+P",         "~Terminar Juego\tCtrl+Q",
        "Sa~lir\tCtrl+X",               "~Opciones",
        "~Conjunto de Fichas",           "~Clasico",
        "~3D",                           "~Fufitos",
        "~Controles",                    "~Teclado",
        "Joystick ~A",                   "Joystick ~B",
        "~Calibrar",                     "Joystick ~A",
        "Joystick ~B",                   "~Sonido",
        "~Activar",                      "~Desactivar",
        "~Prioridad",                    "~Normal",
        "~Critica",                      "~Servidor",
        "~Idioma",                       "~Guardar ajustes al salir",
        "~Fondo Activo\tCtrl+B",         "~Controles Marco\tCtrl+F",
        "~Ayuda",                        "~Acerca de MakMan/2...",
        "~Indice de ayuda", "Ayuda ~general", "~Usar la ayuda",
        "Ventana de Ayuda MakMan/2",
        "No se encontro el archivo de ayuda %s.\nPongalo en la carpeta help junto al programa."
    },
    /* LANG_NL */
    {
        "~Spel",                         "~Nieuw\tCtrl+N",
        "~Pauze Spel\tCtrl+P",           "~Spel Stoppen\tCtrl+Q",
        "~Afsluiten\tCtrl+X",           "~Opties",
        "~Tegelset",                     "~Klassiek",
        "~3D-Stijl",                     "~Fufitos",
        "~Besturing",                    "~Toetsenbord",
        "Joystick ~A",                   "Joystick ~B",
        "~Kalibreren",                   "Joystick ~A",
        "Joystick ~B",                   "~Geluid",
        "~Aan",                          "~Uit",
        "~Prioriteit",                   "~Normaal",
        "~Kritiek",                      "~Server",
        "~Taal",                         "~Instellingen opslaan bij afsluiten",
        "~Achtergrond Actief\tCtrl+B",   "~Raambediening\tCtrl+F",
        "~Help",                         "~Over MakMan/2...",
        "Help~index", "~Algemene help", "Help ~gebruiken",
        "MakMan/2 Help Venster",
        "Het helpbestand %s is niet gevonden.\nPlaats het in de map help naast het programma."
    },
    /* LANG_DE */
    {
        "~Spiel",                        "~Neu\tCtrl+N",
        "~Pause\tCtrl+P",               "~Spiel Beenden\tCtrl+Q",
        "~Beenden\tCtrl+X",             "~Optionen",
        "~Kachelsatz",                   "~Klassisch",
        "~3D-Stil",                      "~Fufitos",
        "~Steuerung",                    "~Tastatur",
        "Joystick ~A",                   "Joystick ~B",
        "~Kalibrieren",                  "Joystick ~A",
        "Joystick ~B",                   "~Sound",
        "~Ein",                          "~Aus",
        "~Prioritaet",                   "~Normal",
        "~Kritisch",                     "~Server",
        "~Sprache",                      "~Einstellungen beim Beenden speichern",
        "~Hintergrundlauf\tCtrl+B",      "~Rahmenbedienung\tCtrl+F",
        "~Hilfe",                        "~Ueber MakMan/2...",
        "Hilfe~index", "~Allgemeine Hilfe", "Hilfe ~verwenden",
        "MakMan/2 Hilfe Fenster",
        "Die Hilfedatei %s wurde nicht gefunden.\nBitte in den Ordner help neben dem Programm legen."
    },
    /* LANG_FR */
    {
        "~Jeu",                          "~Nouveau\tCtrl+N",
        "~Pause Jeu\tCtrl+P",           "~Quitter Jeu\tCtrl+Q",
        "~Sortir\tCtrl+X",              "~Options",
        "~Jeu de Carreaux",              "~Classique",
        "~3D",                           "~Fufitos",
        "~Controles",                    "~Clavier",
        "Joystick ~A",                   "Joystick ~B",
        "~Calibrer",                     "Joystick ~A",
        "Joystick ~B",                   "~Son",
        "~Activer",                      "~Desactiver",
        "~Priorite",                     "~Normale",
        "~Critique",                     "~Serveur",
        "~Langue",                       "~Sauver les reglages a la sortie",
        "~Arriere-plan Actif\tCtrl+B",   "~Controles Cadre\tCtrl+F",
        "~Aide",                         "~A propos de MakMan/2...",
        "~Index de l'aide", "Aide ~generale", "~Utiliser l'aide",
        "Fenetre d'aide MakMan/2",
        "Le fichier d'aide %s est introuvable.\nPlacez-le dans le dossier help a cote du programme."
    },
    /* LANG_IT */
    {
        "~Gioco",                        "~Nuovo\tCtrl+N",
        "~Pausa Gioco\tCtrl+P",          "~Esci dal Gioco\tCtrl+Q",
        "~Esci\tCtrl+X",                "~Opzioni",
        "~Set di Tessere",               "~Classico",
        "~3D",                           "~Fufitos",
        "~Controlli",                    "~Tastiera",
        "Joystick ~A",                   "Joystick ~B",
        "~Calibra",                      "Joystick ~A",
        "Joystick ~B",                   "~Suono",
        "~Attiva",                       "~Disattiva",
        "~Priorita",                     "~Normale",
        "~Critico",                      "~Server",
        "~Lingua",                       "~Salva impostazioni all'uscita",
        "~Sfondo Attivo\tCtrl+B",        "~Controlli Cornice\tCtrl+F",
        "~Guida",                        "~Informazioni su MakMan/2...",
        "~Indice dell'aiuto", "Aiuto ~generale", "~Usare l'aiuto",
        "Finestra Aiuto MakMan/2",
        "Il file di aiuto %s non e stato trovato.\nMetterlo nella cartella help accanto al programma."
    },
};

/* ---- frame controls and new feature globals ---- */
HWND hwndTitleBar = NULLHANDLE;
HWND hwndSysMenu  = NULLHANDLE;
HWND hwndMinMax   = NULLHANDLE;
HWND hwndFMenu    = NULLHANDLE;
HWND hwndObject   = NULLHANDLE;
BOOL bFrameHidden = FALSE;
BOOL bBackgrndRun = FALSE;
BOOL bSaveOnExit  = TRUE;

VOID EnableMenu(ULONG id, BOOL fEnable);
VOID GetOptionsFromIni( VOID );
VOID GetScoresFromIni ( VOID );
VOID SaveOptionsToIni ( VOID );
VOID SaveScoresToIni  ( VOID );
VOID set_language( int lang );

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

int main(int argc, char* argv[])
{
    QMSG  qmsg;

    if( Initialize(argc, argv))
    {
        while( WinGetMsg( habMain, &qmsg, NULLHANDLE, 0, 0))
            WinDispatchMsg( habMain, &qmsg);
        Finalize();
    }
    else
        { ReportError( habMain); }

    return 0;
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

    /* Most of the program writes to debOut without checking it, so it must
       never be NULL: when the WatchCat pipe is not there, throw the text away */
    if (!debOut)
        debOut = fopen ("NUL", "w");

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
			   0,                                  /* frame-window style (invisible)  */
			   &flCreate,                          /* creation flags                  */
			   szTitle,                            /* client-window class name        */
			   "MakMan/2",                         /* title-bar text                  */
			   WS_SYNCPAINT,                       /* client-window style             */
			   0,                                  /* handle of the resource module   */
			   IDR_MAIN,                           /* frame-window identifier         */
			   &hwndClient);                       /* address of client-window handle */

    if( !hwndFrame)
	return( FALSE);

    /* capture frame control handles before any reparenting */
    hwndTitleBar = WinWindowFromID(hwndFrame, FID_TITLEBAR);
    hwndSysMenu  = WinWindowFromID(hwndFrame, FID_SYSMENU);
    hwndFMenu    = WinWindowFromID(hwndFrame, FID_MENU);
    hwndMinMax   = WinWindowFromID(hwndFrame, FID_MINMAX);

    /* private object window used as reparent target when hiding controls */
    hwndObject = WinCreateWindow(HWND_OBJECT, WC_FRAME, " ", 0L,
                                 0,0,0,0, NULLHANDLE, HWND_TOP, 2, NULL, NULL);


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

    cxWidthBorder = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CXBORDER);
    cyWidthBorder = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYBORDER);
    cyTitleBar    = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYTITLEBAR);
    cyMenu        = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYMENU);
    cyScreen      = (LONG) WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);

    sizlMaxClient.cx = fieldSizeX * tileWidth  + cxWidthBorder * 2;
    sizlMaxClient.cy = fieldSizeY * tileHeight + cyWidthBorder * 2 + cyTitleBar + cyMenu;

    /* center window on desktop, defaulting to 1024x768 minimum */
    {
        LONG cxScr = WinQuerySysValue(HWND_DESKTOP, SV_CXSCREEN);
        LONG cyScr = WinQuerySysValue(HWND_DESKTOP, SV_CYSCREEN);
        LONG winW  = sizlMaxClient.cx > 0 ? sizlMaxClient.cx : 1024L;
        LONG winH  = sizlMaxClient.cy > 0 ? sizlMaxClient.cy :  768L;
        if (winW > cxScr) winW = cxScr;
        if (winH > cyScr) winH = cyScr;
        LONG x = (cxScr - winW) / 2;
        LONG y = (cyScr - winH) / 2;
        WinSetWindowPos(hwndFrame, HWND_TOP, x, y, winW, winH,
                        SWP_SIZE | SWP_MOVE | SWP_ACTIVATE | SWP_SHOW);
    }


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
            EnableMenu(IDM_CAL_A, FALSE);
            EnableMenu(IDM_CAL_B, FALSE);
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


    /* help is (re)loaded per language from set_language() */


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
    SaveScoresToIni();
    if (bSaveOnExit)
        SaveOptionsToIni();


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
    int TileSet, Input, Sound, Priority, Lang, SaveExit;

    hini = PrfOpenProfile (habMain, "MAKMAN.INI");

    TileSet  = PrfQueryProfileInt(hini,szAppName,"Tile Set",       1);
    Input    = PrfQueryProfileInt(hini,szAppName,"Input Source",    0);
    Sound    = PrfQueryProfileInt(hini,szAppName,"Sound Enabled",   1);
    Priority = PrfQueryProfileInt(hini,szAppName,"Priority",        0);
    Lang     = PrfQueryProfileInt(hini,szAppName,"Language",        LANG_EN);
    SaveExit = PrfQueryProfileInt(hini,szAppName,"Save On Exit",    1);

    if (Lang < 0 || Lang >= LANG_COUNT) Lang = LANG_EN;

    bSaveOnExit = (SaveExit != 0);
    WinCheckMenuItem(hwndMenu, IDM_SAVEONEXIT, bSaveOnExit);

    SetDefault (IDM_T_CLASSIC + TileSet);
    SetDefault (IDM_KEYBOARD + Input);
    if (Sound)
        SetDefault (IDM_SOUND_ON);
    else
        SetDefault (IDM_SOUND_OFF);
    SetDefault (IDM_PRI_NORMAL + Priority);

    set_language(Lang);

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

    Input = 0;
    if (WinIsMenuItemChecked(hwndMenu, IDM_JOY_A))
        Input = 1;
    if (WinIsMenuItemChecked(hwndMenu, IDM_JOY_B))
        Input = 2;

    Sound = WinIsMenuItemChecked(hwndMenu, IDM_SOUND_ON) ? 1 : 0;

    Priority = 0;
    if (WinIsMenuItemChecked(hwndMenu, IDM_PRI_CRIT))
        Priority = 1;
    if (WinIsMenuItemChecked(hwndMenu, IDM_PRI_SERVER))
        Priority = 2;

    WriteProfileInt ("Tile Set",     TileSet);
    WriteProfileInt ("Input Source", Input);
    WriteProfileInt ("Sound Enabled",Sound);
    WriteProfileInt ("Priority",     Priority);
    WriteProfileInt ("Language",     current_lang);
    WriteProfileInt ("Save On Exit", bSaveOnExit ? 1 : 0);

    PrfCloseProfile(hini);
}

VOID set_language( int lang )
{
    if (lang < 0 || lang >= LANG_COUNT) lang = LANG_EN;
    current_lang = lang;

    /* update all top-level and submenu item texts */
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_GAME),
               MPFROMP(tr(STR_MENU_GAME)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_NEW),
               MPFROMP(tr(STR_MENU_NEW)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_PAUSE),
               MPFROMP(tr(STR_MENU_PAUSE)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_QUIT_GAME),
               MPFROMP(tr(STR_MENU_QUIT)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_EXIT),
               MPFROMP(tr(STR_MENU_EXIT)));

    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_OPTS),
               MPFROMP(tr(STR_MENU_OPTIONS)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_TILESET),
               MPFROMP(tr(STR_MENU_TILESET)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_T_CLASSIC),
               MPFROMP(tr(STR_MENU_CLASSIC)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_T_3D),
               MPFROMP(tr(STR_MENU_3D)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_T_NEWLOOK),
               MPFROMP(tr(STR_MENU_FUFITOS)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_CONTROLS),
               MPFROMP(tr(STR_MENU_CONTROLS)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_KEYBOARD),
               MPFROMP(tr(STR_MENU_KEYBOARD)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_JOY_A),
               MPFROMP(tr(STR_MENU_JOYA)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_JOY_B),
               MPFROMP(tr(STR_MENU_JOYB)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_CAL),
               MPFROMP(tr(STR_MENU_CALIBRATE)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_CAL_A),
               MPFROMP(tr(STR_MENU_CALJOYSTICK_A)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_CAL_B),
               MPFROMP(tr(STR_MENU_CALJOYSTICK_B)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_SOUND),
               MPFROMP(tr(STR_MENU_SOUND)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SOUND_ON),
               MPFROMP(tr(STR_MENU_SOUND_ON)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SOUND_OFF),
               MPFROMP(tr(STR_MENU_SOUND_OFF)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_PRI),
               MPFROMP(tr(STR_MENU_PRIORITY)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_PRI_NORMAL),
               MPFROMP(tr(STR_MENU_PRI_NORMAL)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_PRI_CRIT),
               MPFROMP(tr(STR_MENU_PRI_CRITICAL)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_PRI_SERVER),
               MPFROMP(tr(STR_MENU_PRI_SERVER)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_LANG),
               MPFROMP(tr(STR_MENU_LANGUAGE)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SAVEONEXIT),
               MPFROMP(tr(STR_MENU_SAVEONEXIT)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_BACKGRND),
               MPFROMP(tr(STR_MENU_BACKGRND)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_FRAME),
               MPFROMP(tr(STR_MENU_FRAME)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_SUBMENU_HELP),
               MPFROMP(tr(STR_MENU_HELP)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_HELPABOUT),
               MPFROMP(tr(STR_MENU_ABOUT)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_HELPINDEX),
               MPFROMP(tr(STR_MENU_HELPINDEX)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_HELPEXTENDED),
               MPFROMP(tr(STR_MENU_HELPGEN)));
    WinSendMsg(hwndMenu, MM_SETITEMTEXT, MPFROMSHORT(IDM_HELPHELPFORHELP),
               MPFROMP(tr(STR_MENU_HELPUSING)));

    /* check active language in Language submenu */
    WinCheckMenuItem(hwndMenu, IDM_LANG_EN, lang == LANG_EN);
    WinCheckMenuItem(hwndMenu, IDM_LANG_ES, lang == LANG_ES);
    WinCheckMenuItem(hwndMenu, IDM_LANG_NL, lang == LANG_NL);
    WinCheckMenuItem(hwndMenu, IDM_LANG_DE, lang == LANG_DE);
    WinCheckMenuItem(hwndMenu, IDM_LANG_FR, lang == LANG_FR);
    WinCheckMenuItem(hwndMenu, IDM_LANG_IT, lang == LANG_IT);

    /* load the help file of the new language (once the window exists) */
    if (hwndFrame)
        HelpInit();
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
