/*
  ==============================================================================

    SynthesisEngine.h
    Created: 19 Dec 2017 1:12:58pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <assert.h>



struct Partial
{
    Partial (double freq, double ampl, double angDelta, double ang = 0)
    : frequency (freq), amplitude (ampl), angleDelta (angDelta), angle (ang)
    { }
    
    double frequency;
    double amplitude;
    double angleDelta;
    double angle;
    
};



class SynthesisEngine
{
public:
    static SynthesisEngine& Instance();
    
    void setSampleRate (double sampleRate);
    const double getSampleRate() const;
    
    void setCurrentLevel (double currLevel);
    const double getCurrentLevel() const;
    
    void setCurrentFundFrequency (double currFundFrequency);
    const double getCurrentFundFrequency() const;
    
    void setWaveType (int waveType);
    const int getWaveType() const;
    
    void setNbPartials (int nbPartials);
    const int getNbPartials() const;
    
    const std::vector<Partial>& getVecPartials() const;
    
    float getCurrentBufferSample();
    
    double getAngleDelta (double freq, double currSampleRate);
    
    void fillVecPartials ();
    
    
private:
    SynthesisEngine();
    
    ~SynthesisEngine();
    
    static SynthesisEngine m_synth;
    
    double m_sampleRate, m_currentLevel, m_currentFundFrequency;
    int m_waveType, m_nbPartials;
    
    std::vector<Partial> m_vecPartials;
    
    void normalizePartialsAmp(std::vector<Partial>& vec);
    
};
