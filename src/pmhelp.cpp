//
// PmHelp.cpp
//
// Online help (IPF .hlp files in the "help" folder next to makman.exe,
// one per language).
//

#include "PmMain.hpp"
#include "PmVars.hpp"
#include "PmIDs.hpp"
#include "PmHelp.hpp"
#include "lang.h"

#include <stdio.h>
#include <string.h>

static const char *pszHelpFiles[LANG_COUNT] =
{
    "MakMan_en.hlp", "MakMan_es.hlp", "MakMan_nl.hlp",
    "MakMan_de.hlp", "MakMan_fr.hlp", "MakMan_it.hlp"
};

static HWND  hwndHelpInstance = NULLHANDLE;
static BOOL  fHelpEnabled     = FALSE;
static CHAR  szExeDir[CCHMAXPATH];       // folder of makman.exe with trailing backslash
static CHAR  szHelpLib[CCHMAXPATH + 20];

static VOID QueryExeDir(VOID)
{
    PTIB  ptib;
    PPIB  ppib;
    char *p;

    szExeDir[0] = '\0';
    DosGetInfoBlocks(&ptib, &ppib);
    if (DosQueryModuleName(ppib->pib_hmte, sizeof(szExeDir), szExeDir) == 0)
    {
        p = strrchr(szExeDir, '\\');
        if (p)
            p[1] = '\0';
        else
            szExeDir[0] = '\0';
    }
}

static VOID DropHelpInstance(VOID)
{
    if (hwndHelpInstance != NULLHANDLE)
    {
        WinAssociateHelpInstance(NULLHANDLE, hwndFrame);
        WinDestroyHelpInstance(hwndHelpInstance);
        hwndHelpInstance = NULLHANDLE;
    }
    fHelpEnabled = FALSE;
}

static VOID HelpMissing(const char *pszFile)
{
    CHAR szMsg[CCHMAXPATH + 200];

    sprintf(szMsg, tr(STR_HELP_MISSING), pszFile);
    WinMessageBox(HWND_DESKTOP, hwndFrame, szMsg, "MakMan/2", 0,
                  MB_OK | MB_APPLMODAL | MB_MOVEABLE | MB_ERROR);
}

// (Re)create the help instance for the current language.
VOID HelpInit(VOID)
{
    HELPINIT heini;
    FILE    *fp;
    const char *pszFile = pszHelpFiles[(current_lang >= 0 && current_lang < LANG_COUNT)
                                       ? current_lang : LANG_EN];

    DropHelpInstance();

    if (szExeDir[0] == '\0')
        QueryExeDir();

    strcpy(szHelpLib, szExeDir);
    strcat(szHelpLib, "help\\");
    strcat(szHelpLib, pszFile);
    fp = fopen(szHelpLib, "rb");
    if (fp)
        fclose(fp);
    else
        strcpy(szHelpLib, pszFile);     // let the system look along HELP and BOOKSHELF

    memset(&heini, 0, sizeof(heini));
    heini.cb                 = sizeof(HELPINIT);
    heini.phtHelpTable       = (PHELPTABLE)MAKELONG(MAIN_HELP_TABLE, 0xFFFF);
    heini.pszHelpWindowTitle = tr(STR_HELP_TITLE);
    heini.fShowPanelId       = CMIC_HIDE_PANEL_ID;
    heini.pszHelpLibraryName = szHelpLib;

    hwndHelpInstance = WinCreateHelpInstance(habMain, &heini);
    if (hwndHelpInstance == NULLHANDLE || heini.ulReturnCode)
    {
        hwndHelpInstance = NULLHANDLE;
        HelpMissing(pszFile);
        return;
    }
    if (!WinAssociateHelpInstance(hwndHelpInstance, hwndFrame))
    {
        WinDestroyHelpInstance(hwndHelpInstance);
        hwndHelpInstance = NULLHANDLE;
        HelpMissing(pszFile);
        return;
    }
    fHelpEnabled = TRUE;
}

VOID DestroyHelpInstance(VOID)
{
    DropHelpInstance();
}

VOID HelpHelpForHelp(VOID)
{
    if (fHelpEnabled)
        WinSendMsg(hwndHelpInstance, HM_DISPLAY_HELP, 0L, 0L);
}

VOID HelpExtended(VOID)
{
    if (fHelpEnabled)
        WinSendMsg(hwndHelpInstance, HM_EXT_HELP, 0L, 0L);
}

VOID HelpIndex(VOID)
{
    if (fHelpEnabled)
        WinSendMsg(hwndHelpInstance, HM_HELP_INDEX, 0L, 0L);
}
