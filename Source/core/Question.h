/*
  ==============================================================================

    Exercise.h
    Created: 23 Oct 2018 1:42:37am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


class Question
{
public:
    Question (int waveTypeID, int audibleRange)
    : m_waveTypeID(waveTypeID), m_audibleRange(audibleRange)
    {
        
    }
    
    int getWaveTypeID()
    {
        return m_waveTypeID;
    }
    
    int getAudibleRange()
    {
        return m_audibleRange;
    }
    
    int getAnsweredWaveTypeID()
    {
        return m_answeredWaveTypeID;
    }
    
    int getAnsweredAudibleRange()
    {
        return m_answeredAudibleRange;
    }
    
    void setAnsweredWaveTypeID(int answeredWaveTypeID)
    {
        m_answeredWaveTypeID = answeredWaveTypeID;
    }
    
    void setAnsweredAudibleRange(int answeredAudibleRange)
    {
        m_answeredAudibleRange = answeredAudibleRange;
    }
    
protected:
    int m_waveTypeID = 1; //default ToBeMOdified
    int m_audibleRange = 100;
    
    int m_answeredWaveTypeID = 0;
    int m_answeredAudibleRange = 0;
    
};
