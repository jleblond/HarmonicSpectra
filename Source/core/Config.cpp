/*
  ==============================================================================

    Config.cpp
    Created: 31 Oct 2018 9:39:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "Config.h"


Config Config::globalConfig = Config();

Config& Config::Instance()
{
    return globalConfig;
}

std::shared_ptr<User> Config::user = nullptr;

//Current session parameters (Default init)
Partials Config::partials = Partials::all;
int Config::nbAmplitudeRatios = 2;
std::vector<int> Config::vecAudibleRanges {100};

int Config::baseFreq = 200;

//Current synthesis parameters (Default init)
int Config::nbPartials = 1;
int Config::waveTypeID = 1;

//Audio parameters
float Config::mainVolume = 1.0;


double Config::sampleRate = 0;

bool Config::isPlaying = false;
bool Config::hasStartedPlaying = false;

double Config::soundDuration = 1000;

