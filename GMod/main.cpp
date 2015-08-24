#include "returnmessages.h"
#include "GModCore.h"

/*Initialises GMod */
/*Returns one of the GMOD_ERROR objects*/
DYLIBEXPORT int gmod_init(int device,float freq,bool mono,bool is8bit)
{
    DWORD flags = 0;
    
    //Yeah, I suck at bitwise stuff. TODO: Learn one day! :P
    if(mono && is8bit)
    {
        flags = BASS_DEVICE_MONO | BASS_DEVICE_8BITS;
    }
    else if (is8bit)
    {
        flags = BASS_DEVICE_8BITS;
    }
    else if (mono)
    {
        flags = BASS_DEVICE_MONO;
    }
    
    return (int)GModCore::instance()->initialiseGMod(device, freq, flags);

}

/*Checks if GMod has been initialised*/
/*Returns true if GMod has been initialised, false otherwise. */
DYLIBEXPORT bool gmod_isinitialised()
{
    return GModCore::instance()->GModIsInitialised();
}

/*Loads a file into memory*/
/*Argument 0: the file path to load the file from*/
/*Returns one of the GMOD_ERROR objects*/
DYLIBEXPORT int gmod_load_file(const char* file)
{
    gmod_checkinit();
    
    if(BASSMOD_MusicLoad(false,(void*)file,0,0,BASS_MUSIC_LOOP|BASS_MUSIC_RAMPS|BASS_MUSIC_SURROUND|BASS_MUSIC_CALCLEN))
    {
        return GMOD_ERROR;
    }
    else
    {
        return GMOD_FILE_LOADERROR;
    }
}

