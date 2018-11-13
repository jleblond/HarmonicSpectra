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
    float correctanswer = 0.0;
    
    float getPercent()
    {
        if(count == 0)
        {
            return 0;
        }
        
        return (correctanswer/static_cast<float>(count));
    }
};


struct StatsSheet
{
    std::vector<StatsValue> vecWaves;
    StatsValue audibleRange;
    
    float score = -1;
    float percentTotalScore = 0;
    int maxScore = 100;
    float weightedAverage = 0;
    int countInvolvedValues = 0;
    int questionsCount = 0 ;
    
    
    StatsSheet()
    {
        for(int i=0;i<10;i++)
        {
            vecWaves.push_back(StatsValue());
        }
    }
    
    void print()
    {
        std::cout<<"--StatsSheet::print()"<<std::endl;
        std::cout<<"AudibleRange: count "<<audibleRange.count<<", correctanswer "<<audibleRange.correctanswer<<", percent "<<audibleRange.getPercent()<<std::endl;
        
        for(int i=0;i<vecWaves.size();i++)
        {
            std::cout<<"vecWaves["<<i<<"]: count "<<vecWaves[i].count<<", correctanswer "<<vecWaves[i].correctanswer<<", percent "<<vecWaves[i].getPercent()<<std::endl;
        }
    }
};
