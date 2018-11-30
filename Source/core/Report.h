/*
  ==============================================================================

    Report.h
    Created: 23 Oct 2018 1:29:50am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "Partials.h"
#include "Comment.h"
#include "StatsSheet.h"

struct Report
{
    String username = "";
    String date = "";
    String timePractised = "";
    
    std::vector<std::shared_ptr<Comment>> comments;
    
    //Current session parameters
    int baseFreq = 0;
    Partials::Options partials;
    int nbAmplitudeRatios = 0;
    std::vector<int> vecAudibleRanges;

    //Stats
    StatsSheet stats;
    Image statsImg;
    
    
    void print()
    {
        std::cout<<"--Report::print()"<<std::endl;
        std::cout<<"***PRINT SESSION REPORT***"<<std::endl;
        std::cout<<username<<std::endl;
        std::cout<<date<<std::endl;
        std::cout<<"Time practised: "<<timePractised<<std::endl;
        
        std::cout<<"\n\n[Session settings]"<<std::endl;
        //SESSION SETTINGS ToBeAdded
        
        std::cout<<"\n\n[Stats]"<<std::endl;
        std::cout<<"# of questions:"<<stats.questionsCount<<std::endl;
        std::cout<<"Score:"<<stats.score<<std::endl;
        std::cout<<"Max score:"<<stats.maxScore<<std::endl;
        std::cout<<"Score (%):"<<stats.percentScore<<std::endl;
        
        std::cout<<"\n\n[Comments]"<<std::endl;
        for(int i=0;i<comments.size();i++)
        {
            std::cout<<"Comment "<<(i+1)<<" - "<<comments[i]->date;
            std::cout<<comments[i]->text<<"\n"<<std::endl;
        }
    }
 
    
    
};
