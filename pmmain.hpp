/*
//
//
// Header file for PmMain
//
//

 -- Use standard C comments for the resource compiler brcc

*/



#define INCL_BITMAPFILEFORMAT

#define INCL_DOSMEMMGR
#define INCL_DOSINFOSEG
#define INCL_DOSPROCESS
#define INCL_DOSSEMAPHORES

#define INCL_DEV
#define INCL_BASE

#define INCL_WINSYS
#define INCL_WINSTDFILE
#define INCL_WINHELP
#define INCL_WININPUT
#define INCL_WINMENUS
#define INCL_WINDIALOGS
#define INCL_WINFRAMEMGR
#define INCL_WINPOINTERS
#define INCL_WINWINDOWMGR
#define INCL_WINMESSAGEMGR
#define INCL_WINRECTANGLES
#define INCL_WINSCROLLBARS
#define INCL_WINSWITCHLIST
#define INCL_WINENTRYFIELDS

#define INCL_GPIPATHS
#define INCL_GPILCIDS
#define INCL_GPIREGIONS
#define INCL_GPICONTROL
#define INCL_GPIBITMAPS
#define INCL_GPIPRIMITIVES
#define INCL_GPITRANSFORMS

#define INCL_ERRORS

#include <os2.h>

#include <dive.h>


#define MESSAGELEN          80   /* standard message length */

BOOL Initialize(int, char **);

VOID  ReportError( HAB hab);
VOID  DispErrorMsg(HAB hab, HWND hwndFrame, PCH FileName, LONG LineNum);
ULONG MessageBox(HWND hwndOwner, ULONG idMsg, ULONG fsStyle, BOOL fBeep);
VOID  Finalize( VOID);
BOOL  CreateBitmapHdcHps( PHDC phdc, PHPS phps);
MRESULT EXPENTRY
      ClientWndProc( HWND hwnd, ULONG msg, MPARAM mp1, MPARAM  mp2);
/*
 *   Macro frontend to error message box.  We only want this particular
 *   message box for debugging.  If DEBUG is not defined (when MakMan
 *   is done), the macro expands to nothing, and the real function isn't
 *   called.
 */

#if defined(DEBUG)
   #define DispError(a,b)   DispErrorMsg(a,b,(PCH)__FILE__,(LONG)__LINE__)
#else
   #define DispError(a,b)
#endif
