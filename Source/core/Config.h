/*
  ==============================================================================

    Config.h
    Created: 31 Oct 2018 9:39:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "User.h"
#include "Partials.h"

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
    
    static double sampleRate;
    
    static bool isPlaying;
    static bool hasStartedPlaying;
    
    //Audio parameters
    static float mainVolume;
    
    //Other parameters
    static double soundDuration;
    static File reportDirectory;
    
};
