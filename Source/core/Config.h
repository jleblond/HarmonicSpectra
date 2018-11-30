/*
  ==============================================================================

    Config.h
    Created: 31 Oct 2018 9:39:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "Partials.h"
#include "User.h"

#include <chrono>

class Config
{
public:
    
    static std::shared_ptr<User> user;
    
    
    //Current session parameters
    static Partials::Options partials;
    static int nbAmplitudeRatios;
    static std::vector<int> vecAudibleRanges;
    
    static int baseFreq;
    
    //Current synthesis parameters
    static int nbPartials;
    static int waveTypeID;
    
    
    //Audio parameters
    static float mainVolume;
    

    static bool isPlaying;
    static bool hasStartedPlaying;
    
    static double soundDuration;
    
    
    static double sampleRate;
    
    
    static File reportDirectory;
    
    
private:
    
    Config(){}
    
    ~Config(){}

    

    
};
