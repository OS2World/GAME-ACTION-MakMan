#ifndef PLAYFIELD__HH
#define PLAYFIELD__HH
//
//
// Playfield.hpp
//
// Header file for the playfield class
// which is used to model the playfield of the game

class tile;
class backtile;
class sprite;
class makman;

enum movement { move_none = 0, move_up, move_down, move_left, move_right };
extern int       directions[], opposite[];
extern int       signs[];
extern movement  next_dir[];

enum game { level_running, level_done, game_over, usr_exit };

#define fieldSizeX 21
#define fieldSizeY 17
#define nestDoorX 10
#define nestDoorY 6
#define numGhosts 4
#define fruitX    10
#define fruitY    11

#define spc 0
#define hor 1
#define ver 2
#define ld  3
#define ru  4
#define ul  5
#define dr  6
#define dru 7
#define ldr 8
#define rul 9
#define uld 10
#define de  11
#define le  12
#define re  13
#define ue  14
#define dot 15 // Plain, eatable, dot
#define dor 16 // Ghost door
#define lre 17 // Left-end Right-end
#define bdt 18 // big DOT
#define mak 19 // the makman sprite for live display
#define d_0 20
#define d_1 21
#define d_2 22
#define d_3 23
#define d_4 24
#define d_5 25
#define d_6 26
#define d_7 27
#define d_8 28
#define d_9 29
#define cherry 30
#define strawberry 31

class playfield
{
friend class sprite;
friend class makman;
friend class ghost;
friend class inky;
friend class pinky;
friend class blinky;
friend class stinky;

public:

    playfield ( int sizex, int sizey, int ofsX, int ofsY );
    ~playfield();

    void setScreenOfs ( int ofsX, int ofsY );

    int load_backtile (char* filename);
    int load_backtile (int, char**, int, int);
    int register_sprite( sprite* );

    movement check_legal( int*, movement);

    int   set_field_data     ( int, int, int, int* iq, int, int, int, int, int );
    int   set_field_position ( int x, int y, int tileID );
    int   set_field          ( int* newfld,  int fldSize);
    int   check              ( int *src, int* trgt);
    long  get_score          ( void ) { return score; }


    tile* get_field_position ( int x, int y );

         show   ();
         update ( int );
    game tick   ( movement& );
    int  new_game(); // starts new game


private:

    put_score();


protected:

    // Internal data

    int       pixOfsX, pixOfsY;
    int       maxX, maxY;
    int       numLoadedTiles;
    backtile* backgroundTiles[100];
    tile      **frontBuffer, **backBuffer;
    int       numSprites;
    sprite*   Sprites[20];
    int       ticker;

    movement usrInput;

    clean_buffer   (tile** buffer, int freemem = 1);
    switch_buffers ();

    // Game dependent data
    int      lives;
    int      score;
    game     crntGame;
    int      dot_value, big_dot_value;
    int      oldScore, lifeScore;

    // Level dependent data
    // (should be customizeable)
    int*      field;
    int       pill_duration, ghost_hatch_time, ghost_path_time, ghost_iq[numGhosts];
    int       fruit_frequency, fruit_duration, fruit_value, fruit_value_icon, fruit_icon;

    int       numDots, ghost_value; // calculated




};
#endif
