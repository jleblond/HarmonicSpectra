/*
  ==============================================================================

    ReportBuilder.h
    Created: 23 Oct 2018 1:41:20am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include <ctime>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "Config.h"
//#include "Session.h"
#include "Report.h"

class ReportBuilder
{
public:
    ReportBuilder();
    ~ReportBuilder();
    
    static std::shared_ptr<Report> createReport();
    
    static void saveReport();
    

  
private:
    String getStrCurrentTime()
    {
        // current date/time based on current system
        time_t now = time(0);
        // convert now to string form
        char* dt = ctime(&now);
        
        return dt;
    }
    
    String getStrFormatCurrentTime()
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        
        std::ostringstream oss;
        oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
        auto str = oss.str();
        
        return str;
    }
    
    String convertTimeStr(int timeInSeconds)
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

   
};
