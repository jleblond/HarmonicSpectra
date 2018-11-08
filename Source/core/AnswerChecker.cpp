/*
  ==============================================================================

    AnswerChecker.cpp
    Created: 8 Nov 2018 3:50:21pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "AnswerChecker.h"

AnswerChecker AnswerChecker::m_answerChecker = AnswerChecker();

AnswerChecker& AnswerChecker::Instance()
{
    return m_answerChecker;
}
