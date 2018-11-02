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

class Config
{
public:
    
    static Config& Instance();
    static std::shared_ptr<User> user;
    
    
    //Current parameters
    static int baseFreq;
    static Partials partials;
    static int nbAmplitudeRatios;
    static std::vector<int> vecAudibleRanges;
    
private:
    
    Config(){}
    
    ~Config(){}
    
    static Config globalConfig;
    

    
};
