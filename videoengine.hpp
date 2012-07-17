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

    virtual open()  = 0;
    virtual close() = 0;

    virtual       set_offset  ( int, int ) = 0;
    virtual char* alloc_bitmap( int, int, int& ) = 0;
    virtual       free_bitmap ( int ) = 0;
    virtual       load_palette () = 0;

    virtual       show_bitmap ( int, int, int ) = 0;

};

//
// The gfx output class using DIVE
class dive : public gfx
{
public:
    dive();
    virtual ~dive();

    virtual open();
    virtual close();

    virtual       set_offset  ( int, int );
    virtual char* alloc_bitmap( int, int, int& );
    virtual       free_bitmap ( int );
    virtual       load_palette();

    virtual       show_bitmap ( int, int, int );

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

    virtual open();
    virtual close();

    virtual       set_offset  ( int, int );
    virtual char* alloc_bitmap( int, int, int& );
    virtual       free_bitmap ( int );
    virtual       load_palette();

    virtual       show_bitmap ( int, int, int );

private:
    // instance dependent data
    char* bitmap_data;
    int   bitmap_free[MAXBMP];
    int   max_bmp;
    int   scX, scY;
};




