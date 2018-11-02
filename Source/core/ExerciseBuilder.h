/*
  ==============================================================================

    ExerciseBuilder.h
    Created: 23 Oct 2018 1:42:51am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include <vector>

#include "Exercise.h"
#include "Partials.h"


class ExerciseBuilder
{
private:
    
    Partials m_partials = Partials::all;
    int m_audibleRange = 100;
    int m_baseFreq = 200;
    int m_nbAmplitudeRatios = 2;
    
    std::vector<std::shared_ptr<Exercise>> m_vecExercises;
    
public:
    ExerciseBuilder()
    {
        
    }
    
    
    void createExercise()
    {
        
        m_vecExercises.push_back(std::shared_ptr<Exercise>());
    }
    
    void configExercises(int partialsOption, int audibleRange, int baseFreq, int nbAmpRatios)
    {
        switch(partialsOption)
        {
            case 1:
                m_partials = Partials::odd;
                break;
            case 2:
                m_partials = Partials::all;
                break;
            default:
                m_partials = Partials::both;
                
        };
        
        m_audibleRange = audibleRange;
        m_baseFreq = baseFreq;
        m_nbAmplitudeRatios = nbAmpRatios;
    }
    
    
    
    

};
