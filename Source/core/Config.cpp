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
