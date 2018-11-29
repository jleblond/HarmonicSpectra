/*
  ==============================================================================

    CustomDate.h
    Created: 29 Nov 2018 1:22:16am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "../../JuceLibraryCode/JuceHeader.h"

class CustomDate
{
public:
    static String getStrCurrentTime();
    
    static String getStrFormatCurrentTime();
    
    static String convertTimeStr(int timeInSeconds);
    
private:
    CustomDate()
    {
        
    }
    ~CustomDate()
    {
        
    }
};
