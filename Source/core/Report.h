/*
  ==============================================================================

    Report.h
    Created: 23 Oct 2018 1:29:50am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "StatsSheet.h"
#include "Partials.h"
#include "Comment.h"


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
    //Image statsImg;
    
    void print()
    {
        std::cout<<"--Report::print()"<<"\n"
                 <<"***PRINT SESSION REPORT***"<<"\n"
                 <<username<<"\n"
                 <<date<<"\n"
                 <<"Time practised: "<<timePractised<<"\n"
        
                 <<"\n\n[Session settings]"<<"\n"
                 <<"Base freq: "<<static_cast<String>(baseFreq)<<"Hz"<<"\n"
                 <<"Partials: "<<Partials::partialsToString(partials)<<"\n"
                 <<"# of amplitude ratios: "<<static_cast<String>(nbAmplitudeRatios)<<"\n"
        
                 <<"\n\n[Stats]"<<"\n"
                 <<"# of questions:"<<stats.questionsCount<<"\n"
                 <<"Score:"<<stats.score<<"\n"
                 <<"Max score:"<<stats.maxScore<<"\n"
                 <<"Score (%):"<<stats.percentScore<<"\n"
        
                 <<"\n\n[Comments]"<<std::endl;
            for(int i=0;i<comments.size();i++)
            {
                std::cout<<"Comment "<<(i+1)<<" - "<<comments[i]->date<<"\n"
                         <<comments[i]->text<<"\n"<<std::endl;
            }
    }
 
    
};
