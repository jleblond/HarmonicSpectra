/*
  ==============================================================================

    ExerciseBuilder.h
    Created: 23 Oct 2018 1:42:51am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include <vector>
#include <map>
#include <utility>      /* make_pair */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* floor */

#include "Exercise.h"
#include "Partials.h"

#include "Config.h"



typedef std::pair<Partials, int> keys;

class ExerciseBuilder
{
public:
    
    static ExerciseBuilder& Instance();
    
    
    
    // FROM: session/config
    // (Partials partialsOption, int nbAmpRatios, int baseFreq, std::vector<int> vecAudRanges)
    
    // TO: exercise
    // int waveTypeID, int nbAmplitudeRatios, int audioRange
    
    void buildExercise()
    {
        assert(Config::user->getVecSessions().size() >= 1);
        
        int audioRange = generateAudioRange();
        Config::nbPartials = computeNbPartials(audioRange);
        
        int waveTypeID = rndWaveTypeID();
        Config::waveTypeID = waveTypeID;
        
        Config::user->getLastSession()->addExercise(waveTypeID, audioRange);
        
        std::cout<<"-- ExerciseBuilder::buildExercise()"<<std::endl;
        std::cout<<"audioRange: "<<audioRange<<" nbPartials: "<<Config::nbPartials<<" waveTypeID: "<< waveTypeID <<std::endl;
    
        
        
    }
    
    int computeNbPartials(int audioRange)
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
    
    std::vector<int> getVecWaves()
    {
        auto search = m_tableOfWaves.find(keys(Config::partials, Config::nbAmplitudeRatios));
        
        auto const vecWaves = (search->second);
        
        return vecWaves;
    }

   
    
    
private:
    std::multimap<keys, std::vector<int>> m_tableOfWaves;
    
    std::vector<int> odd2{1,5};
    std::vector<int> odd3{1,3,5};
    std::vector<int> odd5{1,2,3,4,5};
    std::vector<int> all2{6,10};
    std::vector<int> all3{6,8,10};
    std::vector<int> all5{6,7,8,9,10};
    std::vector<int> both2{1,5,6,10};
    std::vector<int> both3{1,3,5,6,8,10};
    std::vector<int> both5{1,2,3,4,5,6,7,8,9,10};

    static ExerciseBuilder m_exerciseBuilder;
    
    ExerciseBuilder()
    {
        //note: insert and emplace are equivalent fcts
        m_tableOfWaves.insert(std::make_pair(keys(Partials::odd, 2), odd2));
        m_tableOfWaves.insert(std::make_pair(keys(Partials::odd, 3), odd3));
        m_tableOfWaves.insert(std::make_pair(keys(Partials::odd, 5), odd5));
        
        m_tableOfWaves.emplace(keys(Partials::all, 2), all2);
        m_tableOfWaves.emplace(keys(Partials::all, 3), all3);
        m_tableOfWaves.emplace(keys(Partials::all, 5), all5);
        
        m_tableOfWaves.emplace(keys(Partials::both, 2), both2);
        m_tableOfWaves.emplace(keys(Partials::both, 3), both3);
        m_tableOfWaves.emplace(keys(Partials::both, 5), both5);

    }
    
    
    
    int rndWaveTypeID()
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
    
    
    int generateAudioRange()
    {
        int audioRange = 100;
        
        srand(static_cast<unsigned int>(time(nullptr)));
    
        int sizeVecAR = Config::vecAudibleRanges.size();
        assert(sizeVecAR >= 1);
        int rndIndex = rand() % (Config::vecAudibleRanges.size());
        audioRange = Config::vecAudibleRanges[rndIndex];
        
        return audioRange;
    }
    
    

    
   
    
    
    
    

};
