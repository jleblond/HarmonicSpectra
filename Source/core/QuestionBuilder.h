/*
  ==============================================================================

    ExerciseBuilder.h
    Created: 23 Oct 2018 1:42:51am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "Config.h"
#include "Question.h"
#include "Partials.h"

#include <vector>
#include <map>
#include <utility>      /* make_pair */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <math.h>       /* floor */


typedef std::pair<Partials::Options, int> keys;


class QuestionBuilder
{
public:
    
    static QuestionBuilder& Instance(); //Singleton class

    void buildQuestion();

    int computeNbPartials(int audioRange);
    
    std::vector<int> getVecWaves();

   
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

    static QuestionBuilder m_exerciseBuilder;
    
    QuestionBuilder()
    {
        //note: insert and emplace are equivalent fcts
        m_tableOfWaves.insert(std::make_pair(keys(Partials::Options::odd, 2), odd2));
        m_tableOfWaves.insert(std::make_pair(keys(Partials::Options::odd, 3), odd3));
        m_tableOfWaves.insert(std::make_pair(keys(Partials::Options::odd, 5), odd5));
        
        m_tableOfWaves.emplace(keys(Partials::Options::all, 2), all2);
        m_tableOfWaves.emplace(keys(Partials::Options::all, 3), all3);
        m_tableOfWaves.emplace(keys(Partials::Options::all, 5), all5);
        
        m_tableOfWaves.emplace(keys(Partials::Options::both, 2), both2);
        m_tableOfWaves.emplace(keys(Partials::Options::both, 3), both3);
        m_tableOfWaves.emplace(keys(Partials::Options::both, 5), both5);
    }
    
    int rndWaveTypeID();

    int generateAudioRange();
    
};
