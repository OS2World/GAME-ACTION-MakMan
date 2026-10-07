//
//
// Implementation of a GFX (bitmap output class for MakMan/2)
// using OS/2 GPI (Graphics Programming Interface) calls
//

#define INCL_GPILOGCOLORTABLE
#define INCL_GPIBITMAPS
#include "pmmain.hpp"
#include "pmvars.hpp"
#include "pmids.hpp"

#include "makEngine.hpp"
#include "VideoEngine.hpp"
#include "debug.h"

#include <stdlib.h>

BITMAPINFO2 *bitH;
HPS hpsScreen;

// constructor
gpi::gpi()
{
    max_bmp = MAXBMP;

    for (int i = 0; i<max_bmp; i++)
        bitmap_free[i] = TRUE;

    bitmap_data = new char[ 32 * 32 * max_bmp ];

    assert(bitmap_data);
}

// destructor
gpi::~gpi()
{

    delete[] bitmap_data;
}


#define PAL_LENGTH 1028

gpi::load_palette()
{

    FILE* fpal;
    char  palFilename[400];
    char  palFileContents[PAL_LENGTH];

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
            bitH->argbColor[i].bBlue = palFileContents[cnt++];
            bitH->argbColor[i].bGreen= palFileContents[cnt++];
            bitH->argbColor[i].bRed  = palFileContents[cnt++];
            bitH->argbColor[i].fcOptions = PC_EXPLICIT;
            if (i==1 || i==2 || i==3 || i== 253 || i==254 || i==255)
            {
                fprintf(debOut, "%4i = %03i,%03i,%03i\n",i,
                        bitH->argbColor[i].bRed,
                        bitH->argbColor[i].bGreen,
                        bitH->argbColor[i].bBlue);
                fflush(debOut);
            }
         }
      }
   else
   { // if couldn't read from file, get system palette
     GpiQueryRealColors(hpsScreen, 0, 0, 256, (PLONG) &bitH->argbColor[0]);
     if (debOut)
     {
        fprintf(debOut, "Palette : Queried System\n");
        fflush(debOut);
     }
    }

}


// init DIVE
gpi::open()
{
    APIRET rc;

    bitH = (BITMAPINFO2*) malloc ( sizeof(BITMAPINFOHEADER2) + 256 * sizeof (RGB2));

    // Initialize the bitmap header
    bitH->cbFix = sizeof(BITMAPINFOHEADER2);
    bitH->cx = 32;
    bitH->cy = 32;
    bitH->cPlanes = 1;
    bitH->cBitCount = 8;
    bitH->ulCompression = BCA_UNCOMP;
    bitH->cclrUsed = 256;
    bitH->cclrImportant = 256;

    HDC hdc = WinOpenWindowDC ( hwndFrame );
    SIZEL sizl;
    sizl.cx = sizl.cx = 0;

    hpsScreen = GpiCreatePS (habMain, hdc, &sizl,
			     PU_PELS | GPIT_MICRO | GPIA_ASSOC | GPIF_DEFAULT);


    assert(hpsScreen != 0);
    if (debOut)
    {
	fprintf(debOut, "Screen PS %li, DC %li\n", hpsScreen, hdc);
	fflush(debOut);
    }
    return TRUE;

}

// close DIVE
gpi::close()
{

  if (bitH)
     free (bitH);

  return TRUE;
}

// set the output offset for the graphics engine
gpi::set_offset ( int, int )
{
    // nothing to do when using GPI
}

char* gpi::alloc_bitmap( int sizex, int sizey, int &id )
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
            return &bitmap_data [i*sizex*sizey];
        }

    if (debOut)
    {
	fprintf(debOut, "BMP %3i, ok = %i\n", id, ok);
	fflush(debOut);
    }

    assert(ok);

    return NULL;
}

gpi::free_bitmap ( int id )
{
    assert (id > 0);
    assert (id < max_bmp);
    bitmap_free[id] = TRUE;

    return TRUE;
}

gpi::show_bitmap ( int id, int posX, int posY )
{
    APIRET rc;
    POINTL pts[4];

    // There are no visible areas of the game
    if (numVisRects == 0)
        return 0;

    // where to go
    pts[0].x = posX + 1;
    pts[0].y = posY + 1;
    pts[1].x = posX + 32;
    pts[1].y = posY + 32;
    // where to get data from
    pts[2].x = 0;
    pts[2].y = 0;
    pts[3].x = 32;
    pts[3].y = 32;

    rc = GpiDrawBits (hpsScreen, // handle for Screen
		      &bitmap_data[id*32*32], // data
		      bitH,  // Info header
		      4,     // number of points
		      pts,   // points
		      ROP_SRCCOPY, // copy data
		      BBO_OR);

    return rc;
}
