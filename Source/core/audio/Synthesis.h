/*
  ==============================================================================

    Synthesis.h
    Created: 19 Dec 2017 1:12:58pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include <assert.h>

#include "../Config.h"

const double NORMALIZE_FACTOR = 0.75;

struct Partial
{
    Partial (double freq, double ampl, double angDelta, double ang = 0)
    : frequency (freq), amplitude (ampl), angleDelta (angDelta), angle (ang)
    { }
    
    double frequency;
    double amplitude;
    double angleDelta;
    double angle;
    
    void print()
    {
        std::cout<<"[Partial] freq: "<<frequency<<", amplitude: "<<amplitude<<", angleDelta: "<<angleDelta<<", angle: "<<angle<<std::endl;
    }
    
};



class Synthesis
{
public:
    static Synthesis& Instance();
    
    
    void setSampleRate (double sampleRate);
    const double getSampleRate() const;
    
    void setCurrentFundFrequency (int currFundFrequency);
    const int getCurrentFundFrequency() const;
    
    void setAmplitudeFactor(double amplitudeFactor);
    const double getAmplitudeFactor() const;
    
    void setWaveType (int waveType);
    const int getWaveType() const;
    
    void setNbPartials (int nbPartials);
    const int getNbPartials() const;
    
    const std::vector<Partial>& getVecPartials() const;
    
    
    float getCurrentBufferSample();
    
    double getAngleDelta (double freq, double currSampleRate);
    
    void fillVecPartials ();
    
    
    void updateSynthesisValues();

    
private:
    Synthesis();
    
    ~Synthesis();
    
    static Synthesis m_synth;
    
    double m_sampleRate, m_amplitudeFactor;
    int m_currentFundFrequency;
    int m_waveType, m_nbPartials;
    
    std::vector<Partial> m_vecPartials;

    void normalizePartialsAmp(std::vector<Partial>& vec);
};
