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
    static int calculateMaxScore();
    
    static int maxPartialsScore();
    static int maxAmplitudeRatiosScore();
    static int maxAudibleRangeScore();
    static int maxBaseFreqScore();
    
private:
    StatsBuilder(){}
    ~StatsBuilder(){}
};
    
