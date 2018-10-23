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


class ExerciseBuilder
{
public:
    ExerciseBuilder()
    {
        
    }
    
    
    void createExercise()
    {
        
        
        m_vecExercises.push_back(std::shared_ptr<Exercise>());
    }
    
    
    
    
    
private:
    enum class Partials {odd, all, both};
    
    Partials m_partials = Partials::all;
    int m_audibleRange = 100;
    int m_baseFreq = 200;
    int m_nbAmplitudeRatios = 2;
    
    std::vector<std::shared_ptr<Exercise>> m_vecExercises;
};
