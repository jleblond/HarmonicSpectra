/*
  ==============================================================================

    AnswerChecker.h
    Created: 8 Nov 2018 3:47:36pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "Config.h"


class AnswerChecker
{
public:
    static float scoreWaveTypeID();
    static float scoreAudibleRange();
    
    static bool lastQuestionExists();

    
private:
    AnswerChecker()
    {
        
    }
    
    ~AnswerChecker()
    {
        
    }
    
};
