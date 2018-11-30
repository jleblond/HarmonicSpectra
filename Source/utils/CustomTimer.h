/*
  ==============================================================================

    CustomTimer.h
    Created: 3 Nov 2018 7:33:28pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include <chrono>
#include<iostream>

typedef std::chrono::high_resolution_clock Clock;


class CustomTimer
{
public:
    CustomTimer()
    {
        resetTimer();
    }
    
    ~CustomTimer()
    {
        
    }
    
    void startTimer()
    {
        m_timeStarted = Clock::now();
    }
    
    void stopTimer()
    {
        m_timeStopped = Clock::now();
    }
    
    void resetTimer()
    {
        m_timeStarted = m_timeStopped = {};
    }
    
    double timeElapsedMS()
    {
        double eT = 0;
        eT = std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - m_timeStarted).count();
        return eT;
    }
    
    double durationInMS()
    {
        double dur = 0;
        dur = std::chrono::duration_cast<std::chrono::milliseconds>(m_timeStopped - m_timeStarted).count();
        return dur;
    }
    
    int durationInS()
    {
        return (durationInMS()/1000);
    }
    
    bool isRunning()
    {
        bool wasStarted = m_timeStarted.time_since_epoch().count();
        return wasStarted;
    }
    
    
protected:
    Clock::time_point m_timeStarted;
    Clock::time_point m_timeStopped;
    

};
