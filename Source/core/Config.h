/*
  ==============================================================================

    Config.h
    Created: 31 Oct 2018 9:39:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "User.h"


class Config
{
public:
    
    static Config& Instance();
    static std::shared_ptr<User> user;
    
private:
    
    Config(){}
    
    ~Config(){}
    
    static Config globalConfig;
    

    
};
