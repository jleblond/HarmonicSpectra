/*
  ==============================================================================

    StatsBuilder.h
    Created: 8 Nov 2018 9:23:19pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "Config.h"


class StatsBuilder
{
public:
    static StatsBuilder& Instance();
    
    static StatsBuilder m_statsBuilder;
    
    int calculateMaxScore()
    {
        int maxScore = 0;
        
        maxScore += maxPartialsScore();
    
        maxScore += maxAmplitudeRatiosScore();
        
        maxScore += maxAudibleRangeScore();
        
        maxScore += maxBaseFreqScore();
        
        std::cout<<"--StatsBuilder::calculateMaxScore"<<std::endl;
        std::cout<<"maxScore: "<<maxScore<<std::endl;
        
        return maxScore;
    }
    
    int maxPartialsScore()
    {
        //ODD, ALL or Both partials
        if(Config::partials == Partials::both)
        {
            return 125;
        }
        else if(Config::partials == Partials::odd || Config::partials == Partials::all)
        {
            return 25;
        }
        
        return 0;
    }
    
    
    int maxAmplitudeRatiosScore()
    {
        //# of amplitude ratios
        if (Config::nbAmplitudeRatios == 2)
        {
            return 25;
        }
        else if (Config::nbAmplitudeRatios == 3)
        {
            return 175;
        }
        else if (Config::nbAmplitudeRatios == 5)
        {
            return 375;
        }
        
        return 0;
    }

    int maxAudibleRangeScore()
    {
        //Audible range
        assert(Config::vecAudibleRanges.size()>= 1);
        
        if(Config::vecAudibleRanges.size()>1)
        {
            return 375;
        }
        else if (Config::vecAudibleRanges[0] == 100)
        {
            return 25;
        }
        else if (Config::vecAudibleRanges[0] == 75)
        {
            return 75;
        }
        else if (Config::vecAudibleRanges[0] == 50)
        {
            return 125;
        }
        else if (Config::vecAudibleRanges[0] == 25)
        {
            return 175;
        }
        else if (Config::vecAudibleRanges[0] == 10)
        {
            return 225;
        }
        
        return 0;
    }
    
    int maxBaseFreqScore()
    {
        if (Config::baseFreq == 50)
        {
            return 125;
        }
        else if (Config::baseFreq == 100)
        {
            return 100;
        }
        else if (Config::baseFreq == 200 || Config::baseFreq == 400 || Config::baseFreq == 800)
        {
            return 25;
        }
        else if (Config::baseFreq == 1600)
        {
            return 125;
        }
        
        return 0;
    }
    
private:
    StatsBuilder(){}
    
    ~StatsBuilder(){}
};
    
