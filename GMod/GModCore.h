//
//  GModCore.h
//  GMod
//
//  Created by Uriel Griffin on 24/08/2015.
//  Copyright (c) 2015 Vetra Games. All rights reserved.
//

#ifndef __GMod__GModCore__
#define __GMod__GModCore__

#include <stdio.h>
#include <vector>
#include <string>
#include "VSSynthesiseSingleton.h"
#include "returnmessages.h"
#include "includes.h"


class GModTrack {
public:
    std::string filePath;
    DWORD flags;
    std::string trackName;
    char* file;
    int size;
    
    GModTrack(std::string theFilePath,DWORD theFlags,std::string theTrackName,char* theFile,int theSize);
    
    ~GModTrack();
};

typedef struct vs_returnfile
{
    GModReturnMessage errorMessage;
    GModTrack* theTrack = NULL;
}GModTrackFile;

class GModCore
{
    VS_DECLARESINGLETON(GModCore,instance);
    
private:
    bool isInitialised = false;
    std::vector<GModTrack*> trackList;
    GModReturnMessage latestError = GModReturnNotInitialised;
    
    GModReturnMessage deInitialiseGModCore();
    
public:
    
    //Initialisation stuff...
    GModReturnMessage initialiseGMod(int device,int frequency, DWORD flags);
    GModReturnMessage releaseGMod();
    bool GModIsInitialised();
    
    //Error handling stuff...
    GModReturnMessage latestReturnError(GModReturnMessage theLatestError);
    GModReturnMessage latestReturnError();
    int latestBassError(); //Use this when you need more detailed information on WHY exactly something went wrong...
    
    //File load/release stuff
    GModTrackFile loadTrackToMemory(std::string theFilePath,DWORD flags);
    GModTrackFile loadTrackToMemory(std::string theFilePath,DWORD flags,std::string theTrackName);
    
    GModReturnMessage releaseTrack(GModTrack* theTrack);
    GModReturnMessage releaseTrack(int trackIndex);
    GModReturnMessage releaseTrack(std::string theTrackName);
    
    //Playback methods.
    GModReturnMessage playTrack(GModTrack* theTrack);
    GModReturnMessage playTrack(int trackIndex);
    GModReturnMessage playTrack(std::string theTrackName);
    
    
    
};

#endif /* defined(__GMod__GModCore__) */
