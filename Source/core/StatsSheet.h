/*
  ==============================================================================

    StatsSheet.h
    Created: 23 Oct 2018 1:43:43am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

struct StatsValue
{
    int count = 0;
    float percent = 0.0;
};


struct StatsSheet
{
    std::vector<StatsValue> vecWaves;
    StatsValue audibleRange;
    
    StatsSheet()
    {
        for(int i=0;i<10;i++)
        {
            vecWaves.push_back(StatsValue());
        }
    }
};
