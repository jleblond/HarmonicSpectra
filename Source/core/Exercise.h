/*
  ==============================================================================

    Exercise.h
    Created: 23 Oct 2018 1:42:37am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


class Exercise
{
public:
    Exercise (int waveTypeID, int audibleRange)
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
    
protected:
    int m_waveTypeID = 1; //default ToBeMOdified
    int m_audibleRange = 100;
    
};
