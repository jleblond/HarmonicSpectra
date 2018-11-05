/*
  ==============================================================================

    Session.h
    Created: 23 Oct 2018 1:53:57am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "Question.h"
#include "Partials.h"
#include "StatsSheet.h"


class Session
{
public:
    Session(Partials partialsOption, int nbAmpRatios, int baseFreq, std::vector<int> vecAudRanges)
        : m_partials(partialsOption), m_nbAmplitudeRatios(nbAmpRatios), m_baseFreq(baseFreq), m_vecAudibleRanges(vecAudRanges)
    {

    }
    
    int getNbAmplitudeRatios()
    {
        return m_nbAmplitudeRatios;
    }
    
    int getBaseFreq()
    {
        return m_baseFreq;
    }
    
//    int getNbPartials()
//    {
//        return m_nbPartials;
//    }
    
    const std::vector<std::shared_ptr<Question>>& getVecQuestions()
    {
        return m_vecQuestions;
    }
    
    std::shared_ptr<Question> getLastQuestion()
    {
        int sizeVec = m_vecQuestions.size();
        assert(sizeVec >=1);
        return m_vecQuestions[sizeVec-1];
    }
    
    void addExercise(int waveTypeID, int audibleRange)
    {
        m_vecQuestions.push_back(std::make_shared<Question>(waveTypeID, audibleRange));
    }
    
    int getVecAudibleRangesSize()
    {
        return m_vecAudibleRanges.size();
    }
    
    
protected:
    std::vector<std::shared_ptr<Question>> m_vecQuestions;
    
    //default init
    Partials m_partials = Partials::all;
    int m_nbAmplitudeRatios = 2;
    int m_baseFreq = 200;
    std::vector<int> m_vecAudibleRanges;
    
   // int m_nbPartials = 1;
};
