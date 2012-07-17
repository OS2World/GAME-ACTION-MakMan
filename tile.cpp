//
// Tile.C
//
// Implementation of the TILE class


#include <iostream.h>
#include <stdlib.h>
#include <stdio.h>

#include "pmMain.hpp"
#include "pmVars.hpp"
#include "makEngine.hpp"
#include "VideoEngine.hpp"

#include <pmBitmap.h>    // PM bitmaps
#define  _MEERROR_H_
#include <mmioos2.h>     // MMPM
#include <fourcc.h>      // Four character codes

#include "tile.hpp"

#include "debug.h"
//
//
// Access the graphic engine
extern gfx *GfxEng;

tile::tile ( )
{
    sizex = sizey = 32;
    pbImg = GfxEng->alloc_bitmap( sizex, sizey, hBitmap);
}

// copy constructor
tile::tile ( tile& src )
{

    sizex = src.sizex;
    sizey = src.sizey;

    pbImg      = GfxEng->alloc_bitmap ( 32, 32, hBitmap );

    memcpy ( pbImg, src.pbImg, 32*32 );
}

tile::tile ( char* filename )
{
    pbImg = GfxEng->alloc_bitmap( 32, 32, hBitmap );
    load (filename);
}


int tile::load ( char* filename )
{
   HFILE  hFile;
   PBITMAPFILEHEADER2 pbmfHeader;
   PBYTE pbBMP;
   ULONG ulNumBytes, ulFileLength;
   char  pathFilename[200];

   sprintf(pathFilename, "%s\\%s", defaultTilePath, filename);

   //
   // Load data from file, aborting program on failure...
   if ( DosOpen ( (PSZ)pathFilename, &hFile, &ulNumBytes, 0L, FILE_NORMAL,
              OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW,
              OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE |
              OPEN_FLAGS_SEQUENTIAL | OPEN_FLAGS_NO_CACHE, 0L ) )
    {
        char buf[80];
        sprintf(buf, "File \"%s\" not found.", pathFilename);
        Eng_Abort(buf);
    }

   DosSetFilePtr ( hFile, 0L, FILE_END, &ulFileLength );
   DosSetFilePtr ( hFile, 0L, FILE_BEGIN, &ulNumBytes );
   if ( DosAllocMem ( (PPVOID) &pbBMP, ulFileLength,
                   (ULONG) PAG_COMMIT | PAG_READ | PAG_WRITE) )
      {
      DosClose ( hFile );
      Eng_Abort("Error while opening up some system RAM.");
      }
   DosRead ( hFile, pbBMP, ulFileLength, &ulNumBytes );
   DosClose ( hFile );

   // 'extract' the header of the bitmap
   pbmfHeader = (PBITMAPFILEHEADER2) pbBMP;

   if ( ulNumBytes!=ulFileLength || pbmfHeader->usType!=BFT_BMAP )
            cerr << filename << " if not a type \"BM\" bitmap!" << endl;

   // Check a few things to see if we can proceed.
   if ( pbmfHeader->bmp2.cPlanes!=1 )
        cerr << "Only single plane bitmaps are supported" << endl;
   if ( pbmfHeader->bmp2.cBitCount!=8 )
        cerr << "Only 8 bit bitmaps are supported" << endl;
   if ( pbmfHeader->bmp2.ulCompression )
        cerr << "Only uncompressed bitmaps are supported" << endl;
   if ( pbmfHeader->bmp2.cy>480 || pbmfHeader->bmp2.cx>640 )
        cerr << "Bitmaps with dimensions larger than 640x480 are not supported" << endl;

   // Copy data
   memcpy (pbImg, pbBMP+pbmfHeader->offBits, 32*32);

   // Free temporary buffer
   DosFreeMem(pbBMP);

   return 0;

}

tile::~tile()
{
    GfxEng->free_bitmap(hBitmap);
}


tile::show ( int posx, int posy )
{
 
    return GfxEng->show_bitmap ( hBitmap, posx, posy );
}


//
// overlay data from the src tile to this one, respecting offset and direction (hor/vertical)
tile::overlay ( tile& src, int ofs, int direction )
{
    assert(direction == horizontal || direction == vertical);

    if (direction == horizontal)
    {
        int Y = sizey;
        PBYTE   pbSrc, pbDst;


        int cvrLength = (ofs>=0) ? sizex - ofs : sizex + ofs;  // pixels to copy
        int cvrDst    = (ofs>=0) ? ofs : 0;    // offset to copy to
        int cvrSrc    = (ofs>=0) ? 0   : -ofs;  // offset to copy from

        pbDst = pbImg      + cvrDst;
        pbSrc = src.pbImg  + cvrSrc;

        while (Y--)
        {
            for (int i=0; i < cvrLength; i++, pbSrc++, pbDst++)
                if (*pbSrc)
                    *pbDst = *pbSrc;

            // and now go to the next line
            pbDst += sizex - cvrLength;
            pbSrc += sizex - cvrLength;

        }
    }

    if (direction == vertical)
    {
        PBYTE   pbSrc, pbDst;

        int cvrLength = (ofs>=0) ? sizey - ofs : sizey + ofs;  // pixels to copy
        int cvrDst    = (ofs>=0) ? ofs : 0;    // offset to copy to
        int cvrSrc    = (ofs>=0) ? 0   : -ofs; // offset to copy from

        int Y = cvrLength;
        pbDst = pbImg      + cvrDst * sizex;
        pbSrc = src.pbImg  + cvrSrc * src.sizex;

        while (Y--)
            for (int i=0; i < sizex; i++, pbSrc++, pbDst++)
                if (*pbSrc)
                    *pbDst = *pbSrc;
    }
    return 0;


}
