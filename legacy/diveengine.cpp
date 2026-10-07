//
//
// Implementation of a GFX (bitmap output class for MakMan/2)
// using DIVE (Direct Interface Video Extension).
//


#define INCL_GPILOGCOLORTABLE
#define INCL_GPIBITMAPS
#include "pmmain.hpp"
#include "pmvars.hpp"
#include "pmids.hpp"

#include <dive.h>        // DIVE
#define  _MEERROR_H_
#include <mmioos2.h>     // MMPM
#include <fourcc.h>      // Four character codes


#include "makEngine.hpp"
#include "VideoEngine.hpp"
#include "debug.h"


gfx::gfx()
{
}

gfx::~gfx()
{
}

// constructor
dive::dive()
{
    max_bmp = MAXBMP;

    // set screen offset
    scX = scY = 0;

    for (int i = 0; i<max_bmp; i++)
        bitmap_free[i] = TRUE;

    bitmap_data = new char[ 32 * 32 * max_bmp ];

    assert(bitmap_data);
}

// destructor
dive::~dive()
{

    delete[] bitmap_data;
}


#define PAL_LENGTH 1028

dive::load_palette()
{
    FILE* fpal;
    char  palFilename[400];
    char  palFileContents[PAL_LENGTH];
    RGB2  pal[256];


    // read the palette from a file
    sprintf(palFilename, "%s\\%s", defaultTilePath, "makman.pal");

    fpal = fopen(palFilename,"rb");
    if (fpal)
     {
         fread(palFileContents, PAL_LENGTH, 1, fpal);
         fclose(fpal);
         if (debOut)
         {
            fprintf(debOut, "Palette : %s\n",palFilename);
            fflush(debOut);
         }
         for (int i = 0, cnt=4; i < 256; i++)
         {
            pal[i].bBlue = palFileContents[cnt++];
            pal[i].bGreen= palFileContents[cnt++];
            pal[i].bRed  = palFileContents[cnt++];
            pal[i].fcOptions = PC_EXPLICIT;
         }
         DiveSetSourcePalette(hDive, 0, 256, (PBYTE) pal);
      }

}

// init DIVE
dive::open()
{

   APIRET rc;

   //
   // Initialize DIVE
   //

   if ( rc = DiveOpen ( &hDive, FALSE, 0 ) )
   {
      char szBuf[365];

      switch (rc) {
        case DIVE_ERR_TOO_MANY_INSTANCES:
          WinLoadString( habMain, 0, IDS_DIVETOOMANY, sizeof(szTitle), szTitle);
          break;
        case DIVE_ERR_NO_DIRECT_ACCESS:
          WinLoadString( habMain, 0, IDS_DIVENODIRECT, sizeof(szTitle), szTitle);
          break;
        case DIVE_ERR_SSMDD_NOT_INSTALLED:
          WinLoadString( habMain, 0, IDS_DIVENODRIVER, sizeof(szTitle), szTitle);
          break;
        }

      WinMessageBox( HWND_DESKTOP, HWND_DESKTOP,
                     (PSZ)szBuf,
                     (PSZ)szTitle, 0, MB_OK | MB_INFORMATION );
      return FALSE;
   }

   //
   // And now create one TALL bitmap
   // in which we'll store all out bitmaps...
   //
   if (rc = DiveAllocImageBuffer ( hDive,               // DIVE instance
                                   &hEngBuffer,         // allocated buf num
                                   FOURCC_LUT8,         // 8bit bitmap data
                                   32,                  // width
                                   32*max_bmp,          // height
                                   32,                  // scan line size
                                   bitmap_data          // Image Buffer
                                   ))
        return FALSE;

    return TRUE;

}

// close DIVE
dive::close()
{
  DiveFreeImageBuffer(hDive, hEngBuffer);
  DiveClose(hDive);

  return TRUE;
}

char* dive::alloc_bitmap( int sizex, int sizey, int &id )
{
    int ok = FALSE;

    // we only support 32x32 bitmaps
    assert(sizex == 32);
    assert(sizey == 32);

    int next;

    for (int i = 0; i < max_bmp; i++)
        if ( bitmap_free[i] )
        {
            ok = TRUE;
            id = i;
            bitmap_free[i] = FALSE;
        if (id>max_bmp && debOut)
	    {
		fprintf(debOut, "bmp %i = %i",id, ok);
		fflush (debOut);
	    }
            return &bitmap_data [i*sizex*sizey];
        }

    if (debOut)
    {
	fprintf(debOut, "bmp %i = %i",id, ok);
	fflush (debOut);
    }

    assert(ok);

    return NULL;
}

dive::free_bitmap ( int id )
{
    assert (id > 0);
    assert (id < max_bmp);
    bitmap_free[id] = TRUE;

    return id;
}

dive::show_bitmap ( int id, int posX, int posY )
{
    APIRET rc;
    SETUP_BLITTER blit;

    // There are no visible areas of the game
    if (numVisRects == 0)
        return 0;

    // Setup the DIVE blitter for the position of the bitmap
    blit.ulStructLen       = sizeof ( SETUP_BLITTER );
    blit.fInvert           = TRUE;
    blit.fccSrcColorFormat = FOURCC_LUT8;
    blit.ulSrcWidth        = 32;
    blit.ulSrcHeight       = 32;
    blit.ulSrcPosX         = 0;
    blit.ulSrcPosY         = 32 * id;
    blit.ulDitherType      = 0; // no dither
    blit.fccDstColorFormat = FOURCC_SCRN;
    blit.ulDstWidth        = 32;
    blit.ulDstHeight       = 32;
    blit.lDstPosX          = 0;
    blit.lDstPosY          = 0;
    blit.lScreenPosX       = posX + scX;
    blit.lScreenPosY       = posY + scY;
    blit.ulNumDstRects     = numVisRects;
    blit.pVisDstRects      = VisRects;

    rc = DiveSetupBlitter(hDive, &blit);

    // Bitblit the bitmap on screen (we won't scale our bitmap, so just put it
    // on the graphics plane).
    // diveBufNum is a member variable!
    rc = DiveBlitImage(hDive, hEngBuffer, DIVE_BUFFER_GRAPHICS_PLANE);

    // since we'll never scale or such our imaged, we'll use put ur data
    // directly in the frame buffer, using DIVE_BUFFER_GRAPHICS_PLANE

    return rc;
}

//
// set the offset for bitmap output
dive::set_offset( int scOfsX, int scOfsY )
{
    scX = scOfsX;
    scY = scOfsY;

    return TRUE;
}
