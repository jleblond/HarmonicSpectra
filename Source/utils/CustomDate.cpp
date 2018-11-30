/*
  ==============================================================================

    CustomDate.cpp
    Created: 29 Nov 2018 1:22:16am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "CustomDate.h"


String CustomDate::getStrCurrentTime()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    
    return dt;
}

String CustomDate::getStrFormatCurrentTime()
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
    auto str = oss.str();
    
    return str;
}

String CustomDate::convertTimeStr(int timeInSeconds)
{
    String durationStr = "";
    
    int seconds, hours, minutes;
    minutes = timeInSeconds / 60;
    seconds = timeInSeconds % 60;
    hours = minutes / 60;
    minutes = minutes % 60;
    
    if(hours>=1)
    {
        durationStr += static_cast<String>(hours) + "h";
    }
    if(minutes>=1)
    {
        durationStr += static_cast<String>(minutes) + "m";
    }
    if(seconds>=1)
    {
        durationStr += static_cast<String>(seconds) + "s";
    }
    
    
    return durationStr;
}
