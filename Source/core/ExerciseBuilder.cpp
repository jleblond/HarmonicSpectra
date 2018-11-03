/*
  ==============================================================================

    ExerciseBuilder.cpp
    Created: 23 Oct 2018 1:42:51am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "ExerciseBuilder.h"

ExerciseBuilder ExerciseBuilder::m_exerciseBuilder = ExerciseBuilder();

ExerciseBuilder& ExerciseBuilder::Instance()
{
    return m_exerciseBuilder;
}
