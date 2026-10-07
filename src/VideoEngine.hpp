//
//
// Class used to model a
// Direct-to-Screen Interface
//
// Could be used to implement
// various 'Game' interfaces, e.g. DIVE

const int MAXBMP=150;

//
// The ABSTRACT class for a graphics output interface
class gfx
{
public:
    gfx();
    virtual ~gfx();

    virtual int   open()  = 0;
    virtual void  close() = 0;

    virtual void  set_offset  ( int, int ) = 0;
    virtual char* alloc_bitmap( int, int, int& ) = 0;
    virtual void  free_bitmap ( int ) = 0;
    virtual void  load_palette () = 0;

    virtual void  show_bitmap ( int, int, int ) = 0;

};

//
// The gfx output class using DIVE
class dive : public gfx
{
public:
    dive();
    virtual ~dive();

    virtual int   open();
    virtual void  close();

    virtual void  set_offset  ( int, int );
    virtual char* alloc_bitmap( int, int, int& );
    virtual void  free_bitmap ( int );
    virtual void  load_palette();

    virtual void  show_bitmap ( int, int, int );

private:
    // instance dependent data
    char* bitmap_data;
    int   bitmap_free[MAXBMP];
    int   max_bmp;
    int   scX, scY;
    ULONG hEngBuffer; // DIVE buffer handle


};


//
// The gfx output class using Gpi calls
class gpi : public gfx
{
public:
    gpi();
    virtual ~gpi();

    virtual int   open();
    virtual void  close();

    virtual void  set_offset  ( int, int );
    virtual char* alloc_bitmap( int, int, int& );
    virtual void  free_bitmap ( int );
    virtual void  load_palette();

    virtual void  show_bitmap ( int, int, int );

private:
    // instance dependent data
    char* bitmap_data;
    int   bitmap_free[MAXBMP];
    int   max_bmp;
    int   scX, scY;
};



