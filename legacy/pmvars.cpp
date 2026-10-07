/******************************************************************************
*
*  File Name   : PmVars.cc
*
*  Description : global data for MakMan/2
*
*
******************************************************************************/

#include "PmMain.hpp"

/*-------------------------- general definitions -----------------------------*/

HDIVE     hDive;                          /* handle for DIVE                  */
RECTL     VisRects[100];                  /* Visible area, for DIVE           */
ULONG     numVisRects;                    /* Number of rectangle in VisRects  */
HAB       habMain          = NULLHANDLE;  /* main thread anchor block handle  */
HMQ       hmqMain          = NULLHANDLE;  /* main thread queue handle         */
HWND      hwndFrame        = NULLHANDLE;  /* frame control handle             */
HWND      hwndClient       = NULLHANDLE;  /* client area handle               */
HWND      hwndMenu         = NULLHANDLE;  /* Menu handle                      */
HDC       hdcClient        = NULLHANDLE;  /* window dc handle                 */
HPS       hpsClient        = NULLHANDLE;  /* client area Gpi ps handle        */
SIZEL     sizlMaxClient;                  /* max client area size             */
LONG      cxWidthBorder, cyWidthBorder,
          cyTitleBar, cyMenu, cyScreen;   /* size of OS/2 window decorations  */
HPS       hpsPaint         = NULLHANDLE;  /* ps for use in Main Thread        */
HRGN      hrgnInvalid      = NULLHANDLE;  /* handle to the invalid region     */

HAB       habAsync         = NULLHANDLE;  /* async thread anchor block handle */
HMQ       hmqAsync         = NULLHANDLE;  /* async thread queue handle        */
TID       tidAsync,
          tidSound;
SEL       selStack;                       /* async thread stack selector      */
SHORT     sPrty            = -1;          /* async thread priority            */

HWND      hwndHorzScroll   = NULLHANDLE;  /* horizontal scroll bar window     */
HWND      hwndVertScroll   = NULLHANDLE;  /* vertical scroll bar window       */

POINTS    ptsScrollPos,
          ptsOldScrollPos;
POINTS    ptsScrollMax,
          ptsHalfScrollMax;
POINTS    ptsScrollLine;
POINTS    ptsScrollPage;

LONG      lScale;                         /* current zoom level               */
POINTL    ptlScaleRef;                    /* scalefactor, detects size change */

POINTL    ptlOffset;
POINTL    ptlBotLeft       = { 0, 0};
POINTL    ptlTopRight      = { 3000, 3000};
POINTL    ptlMoveStart;                /* model space point at start of move  */
LONG      lLastSegId;                  /* last segment id assigned to a piece */
LONG      lPickedSeg       = 0L;       /* seg id of piece selected for drag   */
POINTL    ptlOffStart;                 /* segment xform xlate at move start   */
RECTL     rclBounds;                   /* pict bounding box in model coords.  */
POINTL    ptlOldMouse      = {0L, 0L}; /* current mouse posn                  */
POINTL    ptlMouse         = {0L, 0L}; /* current mouse posn                  */
BOOL      fButtonDownMain  = FALSE;    /* only drag if mouse down             */
BOOL      fButtonDownAsync = FALSE;    /* only drag if mouse down             */

POINTL    ptlUpdtRef;
POINTL    aptlUpdt[3];
BOOL      fUpdtFirst;
BOOL      fFirstLoad       = TRUE;
BOOL    fPictureAssembled = TRUE;

/*-------------------------- bitmap-related data -----------------------------*/

HPS        hpsBitmapFile      = NULLHANDLE; /* bitmap straight from the file */

HDC        hdcBitmapFile      = NULLHANDLE;
HBITMAP    hbmBitmapFile      = NULLHANDLE;

BITMAPINFOHEADER2  bmp2BitmapFile;
PBITMAPINFOHEADER2 pbmp2BitmapFile    = &bmp2BitmapFile;
BITMAPINFOHEADER2  bmp2BitmapFileRef;
PBITMAPINFOHEADER2 pbmp2BitmapFileRef = &bmp2BitmapFileRef;

HPS        hpsBitmapSize  = NULLHANDLE;  /* bitmap sized to the current size */
HDC        hdcBitmapSize  = NULLHANDLE;
HBITMAP    hbmBitmapSize  = NULLHANDLE;

HPS        hpsBitmapBuff  = NULLHANDLE;/* image composed here, copied to scrn */
HDC        hdcBitmapBuff  = NULLHANDLE;
HBITMAP    hbmBitmapBuff  = NULLHANDLE;

HPS        hpsBitmapSave  = NULLHANDLE;/* save part of screen during dragging */
HDC        hdcBitmapSave  = NULLHANDLE;
HBITMAP    hbmBitmapSave  = NULLHANDLE;

BITMAPINFOHEADER2  bmp2BitmapSave;
PBITMAPINFOHEADER2 pbmp2BitmapSave    = &bmp2BitmapSave;

DEVOPENSTRUC dop = { NULL
                     , "DISPLAY"
                     , NULL
                     , NULL
                     , NULL
                     , NULL
                     , NULL
                     , NULL
                     , NULL };


/*--------------------------- Miscellaneous ----------------------------------*/

/*
 *   These event semaphores are loosely used to signal events between Jigsaw's
 *   two threads.  No DosWaitEventSem() calls are made at this time, since,
 *   without reworking the code, this could block out a thread that should
 *   continually process the message queue.  Semaphores are "Reset" while
 *   being used (to signal event) and "Posted" when the event is over.
 */

HEV hevTermSound, hevTermGame,
    hevTick, hevSound;
HTIMER hTimer;

PSZ     pszBlankMsg    = "";

SWCNTRL swctl       = { 0, 0, 0, 0, 0, SWL_VISIBLE, SWL_JUMPABLE, 0, 0 };
HSWITCH hsw;                           /* handle to a switch list entry       */
char    szTitle[MESSAGELEN];           /* Title bar text                      */
char    szErrorTitle[MESSAGELEN];      /* error Title bar text                */
LONG    lByteAlignX, lByteAlignY;      /* memory alignment constants          */

BOOL fErrMem      = FALSE;             /* set if alloc async stack fails      */
BOOL BmpLoaded    = FALSE;

//
// Game specific data
//

int gameLevel;
HFILE hGame = 0;
/******************************* end GLOBALS.C *******************************/
