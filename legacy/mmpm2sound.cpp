//
//
// Implementation of a sound output engine using MMPM/2
//

#define  INCL_OS2MM                      /* Required for MCI & MMIO headers   */
#define  INCL_WIN                        /* Required to use Win APIs.         */
#define  INCL_PM                         /* Required to use PM APIs.          */
#define  INCL_GPIPRIMATIVES              /* Required to use GPI OS/2 APIs.    */
#define  INCL_DOSSEMAPHORES              /* Required to use Semaphores.       */
#define  INCL_DOSDATETIME                /* Required for get date time info.  */
#define  INCL_DOSPROCESS                 /* Required for OS/2 process APIs.   */
#define  INCL_DOSERRORS
#define  INCL_WINHELP                    /* Required to use IPF.              */
#define  INCL_DOSMEMMGR                  /* Required to use memory API's.     */
#define  INCL_SECONDARYWINDOW            /* required for secondary window     */


#include <os2.h>
#include <os2me.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <bsememf.h>
#include <dive.h>

#include <sw.h>

#include "sndengine.hpp"
#include "mmpm2sound.hpp"
#include "pmvars.hpp"

#include "debug.h"

extern HWND hwndFrame;

HMMIO  waveHandle[maxWaveEffects];
MMIOINFO waveInfo[maxWaveEffects];

//
// Sound file identifiers
int snd_dot, snd_ghost, snd_mak, snd_empty, snd_start;

int SndEngineActive = 0;
void _System SoundServer (ULONG);

extern snd* SndEng;

#define PLAY_START 100
#define PLAY_DONE  101

mmpm2::mmpm2()
{
    // reset WaveData addresses
    for (int i=0; i<maxWaveEffects; i++)   
	waveHandle[i] = NULL;
}

mmpm2::~mmpm2()
{
    // free WaveData 
    for (int i=0; i<maxWaveEffects; i++)
	if (waveHandle[i])
	    mmioClose(waveHandle[i], 0);
}

mmpm2::open()
{

    // everything was OK
    return 1;


}

mmpm2::close()
{
    // wait for the playing sound to finish
    wait();
    stop();

    return 0;

}

mmpm2::unload (int effect )
{
    if (waveHandle[effect])
    {
        mmioClose(waveHandle[effect], 0);
        waveHandle[effect] = NULL;
    }

    return effect;
}

int mmpm2::load ( char* acFileName )
{
    HMMIO  hFile;           
    MMAUDIOHEADER mmHeader;     
    ULONG ulRC, ulBytesRead, newPos;

    // find an empty position for the new wave data
    for (newPos = 0; (waveHandle[newPos]!=NULL) && (newPos < maxWaveEffects); newPos++);

    waveInfo[newPos].ulTranslate = MMIO_TRANSLATEHEADER;

    hFile = mmioOpen( acFileName, (PMMIOINFO) &waveInfo[newPos], MMIO_READ );
    
    // Couldn't open the file
    if ( hFile == (HMMIO) NULL )
	return 0;
    
    waveHandle[newPos] = hFile;

    // Get the header of the wave file
    ulRC = mmioGetHeader ( hFile,
			  (PVOID)&mmHeader,
			  sizeof (mmHeader),
			  (PLONG) &ulBytesRead,
			  (ULONG) NULL,
			  (ULONG) NULL);

    if (debOut)
    {
        fprintf(debOut, "Loaded %s in slot %i\n", acFileName, newPos);
        fflush(debOut);
    }

    return newPos;

} // ::load

// maximum number of queued requests
#define MREQ 100
// requests up to MPRIO can be discarded if other requests are pending
#define MPRIO 1

int requests[MREQ];
int q_start, q_end;

// returns 0 (NO_ERROR) if succesfully started sound engine
mmpm2::start()
{
    APIRET rc = 0;

    if (!SndEngineActive)
    {
        // clear requests form queue
        q_start = 0;
        q_end = 0;

        // create a thread to play the sounds asynchronously
        rc = DosCreateThread(&tidSound,
                            (PFNTHREAD) SoundServer,
                             0,            // parameters
                             CREATE_READY, // start thread
                             8192 );       // stack size

        if (rc == NO_ERROR)
        {
            SndEngineActive = 1;
            dprint("Sound Thread created\n");
        }
    }
    else
        dprint("ERROR - sound engine allready started\n");

    return rc;


}

mmpm2::stop()
{

    if (SndEngineActive)
    {
        // stop the sound generation thread
        SndEngineActive = 0;
        DosPostEventSem((ULONG)hevTermSound);
        DosPostEventSem((ULONG)hevSound);
        dprint("Waiting sound thread to exit...");
        DosWaitThread( &tidSound, DCWW_WAIT );
        dprint("...ok\n");
    }

    return 0;
}

MCI_OPEN_PARMS parms;
MCI_PLAY_PARMS mpp;

mmpm2::play ( int effect )
{

    if (SndEngineActive)
    {
        requests[q_end] = effect;
        q_end++;
        q_end %= MREQ;
        // notify the other thread of the new request
        DosPostEventSem((ULONG)hevSound);
    }
    
}

mmpm2::wait()
{
    // wait for the sound to play to the end
    if (SndEngineActive)
    {
        dprint("waiting...");
        while(q_start != q_end)
            DosSleep(100);
        dprint("...done!\n");
    }
}


void _System SoundServer (ULONG)
{
    ULONG ulPostCt;

    // clear any pending terminate requests
    DosResetEventSem((ULONG)hevTermSound, &ulPostCt);

    while (TRUE)
    {
    DosWaitEventSem ((ULONG)hevSound, SEM_INDEFINITE_WAIT);
    DosResetEventSem((ULONG)hevSound, &ulPostCt);

	// Could be that we wanna exit?
    if (DosWaitEventSem ((ULONG)hevTermSound, SEM_IMMEDIATE_RETURN) == NO_ERROR)
	    break;

    while (q_start != q_end)
	{	    
	    // play only the last request and 'important' (i.e. > MPRIO)
	    // sounds in between
	    if ( (( (q_start+1) % MREQ) == q_end) || (requests[q_start]>MPRIO) )
		SndEng->INT_play( requests[q_start] );

	    q_start++;
	    q_start %= MREQ;
	}
    } // while

    dprint("Sound Thread kill by semaphore!\n");
} // SoundServer
    

mmpm2::INT_play ( int effect )
{

    
    ULONG rc;

    parms.hwndCallback = hwndFrame;
    parms.pszElementName = (PSZ) waveHandle[effect];
    parms.pszDeviceType = (PSZ)MAKEULONG ( MCI_DEVTYPE_WAVEFORM_AUDIO, 1 );
    rc = mciSendCommand(0,
			MCI_OPEN,
			MCI_OPEN_MMIO | MCI_OPEN_SHAREABLE |
			MCI_OPEN_TYPE_ID | MCI_READONLY | MCI_WAIT,
			(PVOID) &parms,
			0);

    rc = mciSendCommand(parms.usDeviceID,
			MCI_SET,
			MCI_SET_AUDIO | MCI_WAIT,
			(PVOID) &parms,
			0);
    
    mpp.ulFrom = 0;
    rc = mciSendCommand(parms.usDeviceID,
			MCI_PLAY,
			MCI_FROM | MCI_WAIT,
			(PVOID) &mpp,
			PLAY_DONE);
		      
    mciSendCommand(parms.usDeviceID,
		   MCI_CLOSE,
		   MCI_WAIT,
		   (PVOID) NULL,
		   0);

    return 0;
}


//
// callback for the MM_MCINOTIFY message
// from the message processing thread
mmpm2::notify( long code , long msg, long param)
{

    return 0;

}
