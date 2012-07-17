//
//
// Class used to model some method for sound output
//
//
// We'll just be implementing MMPM2 suppport, but why not keep thing abstracts...


//
// ID's for our sounds
//
extern int snd_dot, snd_ghost, snd_mak, snd_empty, snd_start;

class snd
{
public:
    snd() {};
    virtual ~snd() {};

    virtual open() = 0;
    virtual close() = 0;

    virtual int load ( char* ) = 0;
    virtual unload ( int ) = 0;

    virtual play ( int ) = 0;
    virtual INT_play ( int ) = 0;

    virtual notify ( long, long, long ) = 0;

    virtual start() = 0;
    virtual stop() = 0;
    virtual wait() = 0;

};

#define maxWaveEffects 69

class mmpm2 : public snd
{
public:
    mmpm2();
    virtual ~mmpm2();

    virtual open();
    virtual close();

    virtual int load ( char* );
    virtual unload ( int );

    virtual play ( int );
    virtual INT_play ( int );

    virtual notify ( long, long, long );

    virtual start();
    virtual stop();
    virtual wait();

private:

    //
    // Data members
    //
};


