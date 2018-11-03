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

#include <chrono>
#include<iostream>

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
        
        //        bufferToFill.clearActiveBufferRegion();

        if(Config::isPlaying)
        {
            //auto begin = std::chrono::high_resolution_clock::now();
        
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
             auto currentSample = (float) Synthesis::Instance().getCurrentBufferSample();
            
            leftBuffer[sample]  = currentSample * Config::mainVolume; 
            rightBuffer[sample] = currentSample * Config::mainVolume;
        }
           // auto end = std::chrono::high_resolution_clock::now();
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
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


