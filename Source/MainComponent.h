/*
  ==============================================================================

    MainComponent.h
    Created: 19 Dec 2017 5:03:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "core/audio/Synthesis.h"
#include "gui/MainApplication.h"
#include "core/Config.h"
#include "utils/CustomTimer.h"

const int HEIGHT = 700;
const int WIDTH = 900;

class MainContentComponent   :  public AudioAppComponent
{
public:
    MainContentComponent()
    {

        setSize (WIDTH, HEIGHT);
        setAudioChannels (0, 2);
        
        setLookAndFeel( m_LF );
        
        addAndMakeVisible(m_mainApp);
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
        
        delete m_LF;
    }
    
    void resized() override
    {
        m_mainApp.setBounds (getLocalBounds());
    }

    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        setSamplingRate(sampleRate);
        
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        
        auto* leftBuffer  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
        
//        bufferToFill.buffer->applyGainRamp (0, bufferToFill.startSample, bufferToFill.numSamples, currentLevel, targetLevel);
//        bufferToFill.buffer->applyGainRamp (1, bufferToFill.startSample, bufferToFill.numSamples, currentLevel, targetLevel);
        
        
//        bufferToFill.clearActiveBufferRegion();
        
        if(Config::hasStartedPlaying)
        {
            m_audioTimer.startTimer();
            Config::hasStartedPlaying = false;
            Config::isPlaying = true;
        }
        
        if(Config::isPlaying)
        {
            for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
            {
                auto currentSample = (float) Synthesis::Instance().getCurrentBufferSample();
                
                leftBuffer[sample]  = currentSample * Config::mainVolume;
                rightBuffer[sample] = currentSample * Config::mainVolume;
            }
            
            
            if(m_audioTimer.timeElapsedMS()> Config::soundDuration-5)
            {
                Config::isPlaying = false;
                m_audioTimer.resetTimer();
                
            }

        }
        
        
    }
    
    
    void setSamplingRate(double sampleRate)
    {
        Synthesis::Instance().setSampleRate (sampleRate);
        Config::sampleRate = sampleRate;
    }
    
    
private:
    LookAndFeel *m_LF = new LookAndFeel_V4( (LookAndFeel_V4::getLightColourScheme() ) );
    
    MainApplication m_mainApp;
    
    CustomTimer m_audioTimer;
    
//    float currentLevel=0.0f;
//    float targetLevel=1.0f;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


