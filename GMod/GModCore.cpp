//
//  GModCore.cpp
//  GMod
//
//  Created by Uriel Griffin on 24/08/2015.
//  Copyright (c) 2015 Vetra Games. All rights reserved.
//

#include "GModCore.h"
#include <fstream>


int ae_load_file_to_memory(const char *filename, char **result)
{
    int size = 0;
    FILE *f = fopen(filename, "rb");
    if (f == NULL)
    {
        *result = NULL;
        return -1; // -1 means file opening fail
    }
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, 0, SEEK_SET);
    *result = (char *)malloc(size+1);
    if (size != fread(*result, sizeof(char), size, f))
    {
        free(*result);
        return -2; // -2 means file reading fail
    } 
    fclose(f);
    (*result)[size] = 0;
    return size;
}

GModTrack::GModTrack(std::string theFilePath,DWORD theFlags,std::string theTrackName,char* theFile,int theSize)
{
    filePath = theFilePath;
    flags = theFlags;
    trackName = theTrackName;
    file = theFile;
    size = theSize;
}

GModTrack::~GModTrack()
{
    free(file);
}

VS_SYNTHESISESINGLETON(GModCore,instance);

void GModCore::init()
{
    
}

void GModCore::destroy()
{
    
}


GModReturnMessage GModCore::initialiseGMod(int device, int frequency, DWORD flags)
{
    if(BASSMOD_Init(device,frequency, flags))
    {
        isInitialised = true;
        return GModReturnNoError;
    }
    else
    {
        BASSMOD_Free();
        return GModReturnInitError;
    }
}

GModReturnMessage GModCore::deInitialiseGModCore()
{
    
    //Unload memory from BASSMOD...
    BASSMOD_MusicFree();
    
    //Release all the tracks...
    for(int i = 0; i<trackList.size(); i++)
    {
        GModTrack * theTrack = trackList[i];
        trackList[i] = NULL;
        delete theTrack;
    }
    
    trackList.clear();
    
    BASSMOD_Free();
    
    return GModReturnNoError;
    
}

GModReturnMessage GModCore::releaseGMod()
{
    if(isInitialised)
    {
        BASSMOD_Free();
        return this->latestReturnError(this->deInitialiseGModCore());
    }
    else
    {
        return this->latestReturnError(GModReturnNotInitialised);
    }
}

bool GModCore::GModIsInitialised()
{
    return isInitialised;
}

GModReturnMessage GModCore::latestReturnError(GModReturnMessage theLatestError)
{
    latestError = theLatestError;
    return latestError;
}

GModReturnMessage GModCore::latestReturnError()
{
    return latestError;
}

int GModCore::latestBassError()
{
    return (int)BASSMOD_ErrorGetCode();
}

/*Loads a file to memory which BASSMOD can later attempt to play.*/
GModTrackFile GModCore::loadTrackToMemory(std::string theFilePath,DWORD flags,std::string theTrackName)
{
    GModTrackFile theReturnFile;
    
    if (!this->isInitialised)
    {
        theReturnFile.errorMessage = this->latestReturnError(GModReturnNotInitialised);
        return theReturnFile;
    }

    std::ifstream infile(theFilePath);
    if(infile.good())
    {
        //All good, the file exists...
        //Do a test load to see if the file can be loaded...
        char* result;
        int size = ae_load_file_to_memory(theFilePath.c_str(),&result);
        if( !(size == -1 | size == -2) )
        {
            //Track loaded fine....
            theReturnFile.theTrack = new GModTrack(theFilePath,flags,theTrackName,result,size);
            theReturnFile.errorMessage = this->latestReturnError(GModReturnNoError);
            
            trackList.push_back(theReturnFile.theTrack);
            
        }
        else
        {
            if(size == -1)
            {
                theReturnFile.errorMessage = this->latestReturnError(GModReturnFileOpenError);
            }
            else
            {
                theReturnFile.errorMessage = this->latestReturnError(GModReturnFileReadError);
            }
        }
    }
    else
    {
        theReturnFile.errorMessage = this->latestReturnError(GModReturnFileDoesNotExist);
    }
    
    return theReturnFile;
}

GModTrackFile GModCore::loadTrackToMemory(std::string theFilePath, DWORD flags)
{
    std::string trackName = "track"+std::to_string(trackList.size());
    
    return this->loadTrackToMemory(theFilePath,flags,trackName);
}

GModReturnMessage GModCore::releaseTrack(GModTrack *theTrack)
{
    if (!this->isInitialised)
    {
        return this->latestReturnError(GModReturnNotInitialised);
    }
    
    bool found = false;
    
    for(int i = 0; i<trackList.size(); i++)
    {
        GModTrack* potentialTrackToDelete = trackList[i];
        
        if(potentialTrackToDelete == theTrack)
        {
            trackList[i] = NULL;
            potentialTrackToDelete = NULL;
            delete theTrack;
            found = true;
        }
    }
    
    if(!found)
    {
        return this->latestReturnError(GModReturnTrackDoesNotExist);
    }
    else
    {
        return this->latestReturnError(GModReturnNoError);
    }
}

GModReturnMessage GModCore::releaseTrack(int trackIndex)
{
    if (!this->isInitialised)
    {
        return this->latestReturnError(GModReturnNotInitialised);
    }
    
    if( trackIndex >= trackList.size() )
    {
        return this->latestReturnError(GModReturnTrackDoesNotExist);
    }
    
    GModTrack* theTrack = trackList.at(trackIndex);
    
    if(theTrack == NULL)
    {
        return this->latestReturnError(GModReturnTrackAlreadyDeleted);
    }
    else
    {
        delete theTrack;
        trackList[trackIndex] = NULL;
        theTrack = NULL;
        return this->latestReturnError(GModReturnNoError);
    }
    
    
}

GModReturnMessage GModCore::releaseTrack(std::string theTrackName)
{
    if (!this->isInitialised)
    {
        return this->latestReturnError(GModReturnNotInitialised);
    }
    
    bool found = false;
    
    for(int i = 0; i<trackList.size(); i++)
    {
        GModTrack* potentialTrackToDelete = trackList[i];
        
        if(potentialTrackToDelete->trackName == theTrackName)
        {
            trackList[i] = NULL;
            delete potentialTrackToDelete;
            found = true;
        }
    }
    
    if(!found)
    {
        return this->latestReturnError(GModReturnTrackDoesNotExist);
    }
    else
    {
        return this->latestReturnError(GModReturnNoError);
    }
}



