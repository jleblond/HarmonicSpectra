/*
  ==============================================================================

    ExerciseBuilder.cpp
    Created: 23 Oct 2018 1:42:51am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "QuestionBuilder.h"

#include <assert.h>


QuestionBuilder QuestionBuilder::m_exerciseBuilder = QuestionBuilder();


QuestionBuilder& QuestionBuilder::Instance()
{
    return m_exerciseBuilder;
}


// FROM: session/config
// (Partials partialsOption, int nbAmpRatios, int baseFreq, std::vector<int> vecAudRanges)
// TO: exercise
// int waveTypeID, int nbAmplitudeRatios, int audioRange
void QuestionBuilder::buildQuestion()
{
    assert(Config::user->getVecSessions().size() >= 1);
    
    int audioRange = generateAudioRange();
    Config::nbPartials = computeNbPartials(audioRange);
    
    int waveTypeID = rndWaveTypeID();
    Config::waveTypeID = waveTypeID;
    
    Config::user->getLastSession()->addExercise(waveTypeID, audioRange);
    
    std::cout<<"-- ExerciseBuilder::buildExercise()"<<"\n"
             <<"audioRange: "<<audioRange<<" nbPartials: "<<Config::nbPartials<<" waveTypeID: "<< waveTypeID <<std::endl;
}


int QuestionBuilder::computeNbPartials(int audioRange)
{
    int nbPartials = 1;
    
    //From: baseFreq, To: nb of partials
    assert (Config::baseFreq>1);
    nbPartials = (18000/Config::baseFreq-1);
    
    //Nb of partials might be modified by audible range var
    float nb = static_cast<float>(nbPartials)*(audioRange/100.0);
    nbPartials = static_cast<int>(nb);
    
    return nbPartials;
}


std::vector<int> QuestionBuilder::getVecWaves()
{
    auto search = m_tableOfWaves.find(keys(Config::partials, Config::nbAmplitudeRatios));
    auto const vecWaves = (search->second);
    
    return vecWaves;
}


int QuestionBuilder::rndWaveTypeID()
{
    int waveTypeID = 1;
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    //search === std::multimap<keys, std::vector<int>>::iterator it
    auto search = m_tableOfWaves.find(keys(Config::partials, Config::nbAmplitudeRatios));
    
    auto const vecWaves = &(search->second);
    int sizeVecWaves = vecWaves->size();
    
    assert(sizeVecWaves>=1);
    int rndIndex = rand() % sizeVecWaves;
    waveTypeID = (*vecWaves)[rndIndex];
    
    return waveTypeID;
}


int QuestionBuilder::generateAudioRange()
{
    int audioRange = 100;
    
    srand(static_cast<unsigned int>(time(nullptr)));
    
    int sizeVecAR = Config::vecAudibleRanges.size();
    assert(sizeVecAR >= 1);
    int rndIndex = rand() % (Config::vecAudibleRanges.size());
    audioRange = Config::vecAudibleRanges[rndIndex];
    
    return audioRange;
}
