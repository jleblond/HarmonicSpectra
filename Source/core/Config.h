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

class Config
{
public:
    
    static Config& Instance();
    static std::shared_ptr<User> user;
    
    
    //Current session parameters
    static Partials partials;
    static int nbAmplitudeRatios;
    static std::vector<int> vecAudibleRanges;
    
    static int baseFreq;
    
    //Current synthesis parameters
    static int nbPartials;
    
    
    //Audio parameters
    static float mainVolume;
    

    
private:
    
    Config(){}
    
    ~Config(){}
    
    static Config globalConfig;
    

    
};
