/*
  ==============================================================================

    SynthesisEngine.cpp
    Created: 19 Dec 2017 1:12:58pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "SynthesisEngine.h"

SynthesisEngine SynthesisEngine::m_synth = SynthesisEngine();

SynthesisEngine& SynthesisEngine::Instance()
{
    return m_synth;
}

SynthesisEngine::SynthesisEngine()
    : m_sampleRate (0.0),
      m_currentLevel (1.0),
      m_currentFundFrequency (20),
      m_waveType (1),
      m_nbPartials (1) //default nb at intialization
{
    
}

SynthesisEngine::~SynthesisEngine()
{
    
}

void SynthesisEngine::setSampleRate (double sampleRate)
{
    m_sampleRate = sampleRate;
}

const double SynthesisEngine::getSampleRate() const
{
    return m_sampleRate;
}

void SynthesisEngine::setCurrentLevel (double currLevel)
{
    m_currentLevel = currLevel;
}

const double SynthesisEngine::getCurrentLevel() const
{
    return m_currentLevel;
}

void SynthesisEngine::setCurrentFundFrequency (double currFundFrequency)
{
    m_currentFundFrequency = currFundFrequency;
}

const double SynthesisEngine::getCurrentFundFrequency() const
{
    return m_currentFundFrequency;
}

void SynthesisEngine::setWaveType (int waveType)
{
    m_waveType = waveType;
}

const int SynthesisEngine::getWaveType() const
{
    return m_waveType;
}

void SynthesisEngine::setNbPartials (int nbPartials)
{
    m_nbPartials = nbPartials;
}

const int SynthesisEngine::getNbPartials() const
{
    return m_nbPartials;
}

const std::vector<Partial>& SynthesisEngine::getVecPartials() const
{
    return m_vecPartials;
}


float SynthesisEngine::getCurrentBufferSample()
{
    float currentSample = 0;
    
    if(m_vecPartials.size()==1)  //sine wave case
    {
        float partialSample = (float) std::sin (m_vecPartials[0].angle);
        m_vecPartials[0].angle += m_vecPartials[0].angleDelta;
        currentSample += partialSample * m_vecPartials[0].amplitude;
    }
    else if (m_vecPartials.size() > 1)
    {
        for (int i=0; i<m_nbPartials; i++)
        {
            float partialSample = (float) std::sin (m_vecPartials[i].angle);
            m_vecPartials[i].angle += m_vecPartials[i].angleDelta;
            currentSample += partialSample * m_vecPartials[i].amplitude;
        }
    }
    
    return currentSample;
}


double SynthesisEngine::getAngleDelta (double freq, double sampleRate)
{
    assert (sampleRate > 0.0);
    const double cyclesPerSample = freq / sampleRate;
    double angleDelta =  cyclesPerSample * 2.0 * double_Pi;
        
    return angleDelta;
}
    
    
void SynthesisEngine::fillVecPartials ()
{
    m_vecPartials.clear();
    
    bool neg = false;
    
    if(m_waveType == 1)
    {
        double partialFreq = m_currentFundFrequency;
        double partialLevel = 1;
        
        m_vecPartials.push_back (
                                Partial ( partialFreq, partialLevel, getAngleDelta (partialFreq, m_sampleRate) )
                                );
        
    }
    else //waveType is not sine
    {
        
        for (int i=1; i<=m_nbPartials; i++)
        {
            double partialFreq = i*m_currentFundFrequency;
            double partialLevel = 0;

            
            switch (m_waveType)
            {
                    //SQUARE
                case 2:
                    if (i % 2 != 0)
                        partialLevel = m_currentLevel/i;
                    
                    break;
                    
                case 3:
                    if (i % 2 != 0)
                        partialLevel = m_currentLevel/pow (i, 1.25);
                    
                    break;
                    
                case 4:
                    if (i % 2 != 0)
                        partialLevel = m_currentLevel/pow (i, 1.50);
                    
                    break;
                    
                case 5:
                    if (i % 2 != 0)
                        partialLevel = m_currentLevel/pow (i, 1.75);
                    
                    break;
                    
                    //TRI
                case 6:
                    if (i % 2 != 0)
                    {
                        partialLevel = m_currentLevel/(i*i);
                        
                        if(neg)
                            partialLevel = -partialLevel;
                        
                        neg = !neg;
                    }
                    break;
                    
                    //SAW
                case 7:
                    partialLevel = m_currentLevel/(i);
                    break;
                    
                    // STEEPER SAW
                case 8:
                    partialLevel = m_currentLevel/pow (i, 1.25);
                    break;
                    
                case 9:
                    partialLevel = m_currentLevel/pow (i, 1.5);
                    break;
                    
                case 10:
                    partialLevel = m_currentLevel/pow (i, 1.75);
                    break;
                
                case 11:
                    partialLevel = m_currentLevel/pow (i, 2.0);
                    break;
                    
            }; //switch
            
            
            m_vecPartials.push_back (
                                    Partial ( partialFreq, partialLevel, getAngleDelta (partialFreq, m_sampleRate) )
                                    );
        } //for loop
        
    } //else
   
    normalizePartialsAmp(m_vecPartials);

        
}

void SynthesisEngine::normalizePartialsAmp(std::vector<Partial>& vec)
{
    double sum = 0;
    
    for(const auto &partial : vec)
    {
        sum += partial.amplitude;
    }
    
    if(sum > 1)
    {
        for(auto &partial : vec)
        {
            partial.amplitude *= (1/sum);
        }
    }
    
}


    

    
