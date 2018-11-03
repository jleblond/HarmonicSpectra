/*
  ==============================================================================

    Session.h
    Created: 23 Oct 2018 1:53:57am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "Exercise.h"
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
    
    int getNbPartials()
    {
        return m_nbPartials;
    }
    
    const std::vector<std::shared_ptr<Exercise>>& getVecExercises()
    {
        return m_vecExercises;
    }
    
    std::shared_ptr<Exercise> getLastExercise()
    {
        int sizeVec = m_vecExercises.size();
        assert(sizeVec >=1);
        return m_vecExercises[sizeVec-1];
    }
    
    void addExercise(int waveTypeID, int audibleRange)
    {
        m_vecExercises.push_back(std::make_shared<Exercise>(waveTypeID, audibleRange));
    }
    
    
protected:
    std::vector<std::shared_ptr<Exercise>> m_vecExercises;
    
    //default init
    Partials m_partials = Partials::all;
    int m_nbAmplitudeRatios = 2;
    int m_baseFreq = 200;
    std::vector<int> m_vecAudibleRanges;
    
    int m_nbPartials = 1;
};
