/*
  ==============================================================================

    AnswerChecker.cpp
    Created: 8 Nov 2018 3:50:21pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "AnswerChecker.h"

#include <assert.h>


float AnswerChecker::scoreWaveTypeID()
{
    assert(lastQuestionExists() == true);
    
    auto lastSession = Config::user->getLastSession();
    auto lastQuestion = lastSession->getLastQuestion();
    
    int selectedWaveTypeID = lastQuestion->getAnsweredWaveTypeID();
    int correctWaveTypeID = lastQuestion->getWaveTypeID();
    
    
    int hDiff = 0;
    int vDiff = 0;
    
    if(Config::nbAmplitudeRatios == 5)
    {
        hDiff = 1;
        vDiff = 5;
    }
    else if(Config::nbAmplitudeRatios == 3)
    {
        hDiff = 2;
        vDiff = 5;
    }
    
    
    if(selectedWaveTypeID == correctWaveTypeID)
    {
        std::cout<<"[Scoring waveTypeID] 1"<<std::endl;
        return 1; //green
    }
    else if(selectedWaveTypeID == correctWaveTypeID+hDiff || selectedWaveTypeID == correctWaveTypeID - hDiff
            || selectedWaveTypeID == correctWaveTypeID+vDiff || selectedWaveTypeID == correctWaveTypeID - vDiff)
    {
        if( !(selectedWaveTypeID == 5 && correctWaveTypeID ==6) &&
           !(selectedWaveTypeID == 6 && correctWaveTypeID ==5) )
        {
            std::cout<<"[Scoring waveTypeID] 0.5"<<std::endl;
            return 0.5; //orange
        }
        else
        {
            std::cout<<"[Scoring waveTypeID] 0"<<std::endl;
            return 0; //red
        }
    }
    else
    {
        std::cout<<"[Scoring waveTypeID] 0"<<std::endl;
        return 0; //red
    }
    
}


float AnswerChecker::scoreAudibleRange()
{
    assert(lastQuestionExists() == true);
    
    auto lastSession = Config::user->getLastSession();
    auto lastQuestion = lastSession->getLastQuestion();
    
    int selectedAudibleRange = lastQuestion->getAnsweredAudibleRange();
    int correctAudibleRange = lastQuestion->getAudibleRange();
    
    int selectedAudibleRangeIndex = 0;
    int correctAudibleRangeIndex = 0;
    
    for(int i=0;i<Config::vecAudibleRanges.size();i++)
    {
        if (Config::vecAudibleRanges[i] == selectedAudibleRange)
        {
            selectedAudibleRangeIndex = i;
        }
        if(Config::vecAudibleRanges[i] == correctAudibleRange)
        {
            correctAudibleRangeIndex = i;
        }
        
    }
    
    if(selectedAudibleRangeIndex == correctAudibleRangeIndex)
    {
        return 1; //green
    }
    else if(selectedAudibleRangeIndex == correctAudibleRangeIndex+1 ||selectedAudibleRangeIndex == correctAudibleRangeIndex-1)
    {
        return 0.5; //orange
    }
    else
    {
        return 0; //red
    }
    
}


bool AnswerChecker::lastQuestionExists()
{
    if (Config::user != nullptr)
    {
        if (Config::user->getVecSessions().size()>0)
        {
            if (Config::user->getLastSession()->getVecQuestions().size()>0)
            {
                return true;
            }
        }
    }
    
    return false;
}
