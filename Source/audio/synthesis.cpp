/*
  ==============================================================================

    synthesis.cpp
    Created: 19 Dec 2017 1:12:58pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "synthesis.h"

Synthesis Synthesis::mSynth = Synthesis();

Synthesis& Synthesis::Instance()
{
    return mSynth;
}

Synthesis::Synthesis()
    : mSampleRate (0.0),
      mCurrentLevel (1.0),
      mCurrentFundFrequency (20),
      mWaveType (1),
      mNbPartials (1) //default nb at intialization
{
    
}

Synthesis::~Synthesis()
{
    
}

void Synthesis::setSampleRate (double sampleRate)
{
    mSampleRate = sampleRate;
}

const double Synthesis::getSampleRate() const
{
    return mSampleRate;
}

void Synthesis::setCurrentLevel (double currLevel)
{
    mCurrentLevel = currLevel;
}

const double Synthesis::getCurrentLevel() const
{
    return mCurrentLevel;
}

void Synthesis::setCurrentFundFrequency (double currFundFrequency)
{
    mCurrentFundFrequency = currFundFrequency;
}

const double Synthesis::getCurrentFundFrequency() const
{
    return mCurrentFundFrequency;
}

void Synthesis::setWaveType (int waveType)
{
    mWaveType = waveType;
}

const int Synthesis::getWaveType() const
{
    return mWaveType;
}

void Synthesis::setNbPartials (int nbPartials)
{
    mNbPartials = nbPartials;
}

const int Synthesis::getNbPartials() const
{
    return mNbPartials;
}

const std::vector<Partial>& Synthesis::getVecPartials() const
{
    return mVecPartials;
}


float Synthesis::getCurrentBufferSample() 
{
    float currentSample = 0;
    
    if(mVecPartials.size()==1)  //sine wave case
    {
        float partialSample = (float) std::sin (mVecPartials[0].angle);
        mVecPartials[0].angle += mVecPartials[0].angleDelta;
        currentSample += partialSample * mVecPartials[0].amplitude;
    }
    else if (mVecPartials.size() > 1)
    {
        for (int i=0; i<mNbPartials; i++)
        {
            float partialSample = (float) std::sin (mVecPartials[i].angle);
            mVecPartials[i].angle += mVecPartials[i].angleDelta;
            currentSample += partialSample * mVecPartials[i].amplitude;
        }
    }
    
    return currentSample;
}


double Synthesis::getAngleDelta (double freq, double sampleRate)
{
    assert (sampleRate > 0.0);
    const double cyclesPerSample = freq / sampleRate;
    double angleDelta =  cyclesPerSample * 2.0 * double_Pi;
        
    return angleDelta;
}
    
    
void Synthesis::fillVecPartials ()
{
    mVecPartials.clear();
    
    bool neg = false;
    
    if(mWaveType == 1)
    {
        double partialFreq = mCurrentFundFrequency;
        double partialLevel = 1;
        
        mVecPartials.push_back (
                                Partial ( partialFreq, partialLevel, getAngleDelta (partialFreq, mSampleRate) )
                                );
        
    }
    else //waveType is not sine
    {
        
        for (int i=1; i<=mNbPartials; i++)
        {
            double partialFreq = i*mCurrentFundFrequency;
            double partialLevel = 0;
            

            
            switch (mWaveType)
            {
                    //SQUARE
                case 2:
                    if (i % 2 != 0)
                        partialLevel = mCurrentLevel/i;
                    
                    break;
                    
                case 3:
                    if (i % 2 != 0)
                        partialLevel = mCurrentLevel/pow (i, 1.25);
                    
                    break;
                    
                case 4:
                    if (i % 2 != 0)
                        partialLevel = mCurrentLevel/pow (i, 1.50);
                    
                    break;
                    
                case 5:
                    if (i % 2 != 0)
                        partialLevel = mCurrentLevel/pow (i, 1.75);
                    
                    break;
                    
                    //TRI
                case 6:
                    if (i % 2 != 0)
                    {
                        partialLevel = mCurrentLevel/(i*i);
                        
                        if(neg)
                            partialLevel = -partialLevel;
                        
                        neg = !neg;
                    }
                    break;
                    
                    //SAW
                case 7:
                    partialLevel = mCurrentLevel/(i);
                    break;
                    
                    // STEEPER SAW
                case 8:
                    partialLevel = mCurrentLevel/pow (i, 1.25);
                    break;
                    
                case 9:
                    partialLevel = mCurrentLevel/pow (i, 1.5);
                    break;
                    
                case 10:
                    partialLevel = mCurrentLevel/pow (i, 1.75);
                    break;
                
                case 11:
                    partialLevel = mCurrentLevel/pow (i, 2.0);
                    break;
                    
            }; //switch
            
            
            mVecPartials.push_back (
                                    Partial ( partialFreq, partialLevel, getAngleDelta (partialFreq, mSampleRate) )
                                    );
        } //for loop
        
    } //else
   
    normalizePartialsAmp(mVecPartials);

        
}

void Synthesis::normalizePartialsAmp(std::vector<Partial>& vec)
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


    

    

