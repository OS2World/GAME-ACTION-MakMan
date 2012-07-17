#ifndef TILE__HH
#define TILE__HH
//
// Tile.h
//
// Header file for the TILE class
// which represents the basic displayable unit

#define DIM 32         // Bitmap dimension
#define DISP_STEP 4    // Display/animation step in pixels
#define tileHeight 32
#define tileWidth  32

#define horizontal 0   // used to reference arrays of coordinates
#define vertical   1

class tile
{
public:
     tile ( );
     tile ( char* filename );
     tile ( tile& );
    ~tile ();

            int   overlay ( tile& src, int ofs, int direction );
            int   load ( char* filename );
            int   show ( int posx, int posy );
    virtual int   is_changed () { return 0; };
    virtual tile* get_rep() { return this; };

private:
    PBYTE   pbImg;      /* pointer to the image data */
    int     hBitmap;    /* handle for the gfx Engine bitmap */
    int     sizex, sizey;


};
#endif
