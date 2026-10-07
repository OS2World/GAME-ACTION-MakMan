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

    virtual int  open() = 0;
    virtual void close() = 0;

    virtual int  load ( char* ) = 0;
    virtual void unload ( int ) = 0;

    virtual void play ( int ) = 0;
    virtual void INT_play ( int ) = 0;

    virtual void notify ( long, long, long ) = 0;

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void wait() = 0;

};

#define maxWaveEffects 69

class mmpm2 : public snd
{
public:
    mmpm2();
    virtual ~mmpm2();

    virtual int  open();
    virtual void close();

    virtual int  load ( char* );
    virtual void unload ( int );

    virtual void play ( int );
    virtual void INT_play ( int );

    virtual void notify ( long, long, long );

    virtual void start();
    virtual void stop();
    virtual void wait();

private:

    //
    // Data members
    //
};


