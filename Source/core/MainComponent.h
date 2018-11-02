/*
  ==============================================================================

    MainComponent.h
    Created: 19 Dec 2017 5:03:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../util/Utility.h"
#include "audio/SynthesisEngine.h"


class MainContentComponent   :  public AudioAppComponent,
                                public Slider::Listener,
                                public ComboBox::Listener
{
public:
    MainContentComponent()
    :   m_maxNbPartials (360)
    {
        addAndMakeVisible (m_freqSlider);
        m_freqSlider.setRange (50, 1600, 50);
        m_freqSlider.setSkewFactorFromMidPoint (500.0);
        m_freqSlider.addListener (this);
        
        addAndMakeVisible (m_nbPartialsSlider);
        m_nbPartialsSlider.setRange (1, m_maxNbPartials, 1);
        m_nbPartialsSlider.addListener (this);
        
        addAndMakeVisible (m_amplitudeSlider);
        m_amplitudeSlider.setRange (1, 10, 1);
        m_amplitudeSlider.setValue (10);
        m_amplitudeSlider.addListener (this);
        
        addAndMakeVisible (m_waveformComboBox);
        m_waveformComboBox.addItem ("Sine", 1);
        m_waveformComboBox.addSeparator();
        m_waveformComboBox.addSectionHeading ("ODD Partials");
        m_waveformComboBox.addItem ("Square", 2);
        m_waveformComboBox.addItem ("Square Triangled", 3);
        m_waveformComboBox.addItem ("Square-Tri or Tri-Square", 4);
        m_waveformComboBox.addItem ("Triangle Squared", 5);
        m_waveformComboBox.addItem ("Triangle", 6);
        m_waveformComboBox.addSeparator();
        m_waveformComboBox.addSectionHeading ("ALL Partials");
        m_waveformComboBox.addItem ("Sawtooth", 7);
        m_waveformComboBox.addItem ("Steeper Saw", 8);
        m_waveformComboBox.addItem ("Very Steep Saw", 9);
        m_waveformComboBox.addItem ("Almost-Exponential Saw", 10);
        m_waveformComboBox.addItem ("Exponential Saw", 11);
        m_waveformComboBox.setSelectedId (1);
        m_waveformComboBox.addListener (this);
        
        setSize (600, 200);
        setAudioChannels (0, 2);
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        m_waveformComboBox.setBounds (10, 10, 120, 30);
        m_freqSlider.setBounds (10, 50, getWidth() - 20, 20);
        m_nbPartialsSlider.setBounds (10, 100, getWidth() - 20, 20);
        m_amplitudeSlider.setBounds (10, 150, getWidth() - 20, 20);
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
        if (comboBoxThatHasChanged == &m_waveformComboBox)
        {
            int waveType = m_waveformComboBox.getSelectedId();
            SynthesisEngine::Instance().setWaveType (waveType);
            
            SynthesisEngine::Instance().fillVecPartials();
        }
    }
    
    void sliderDragEnded (Slider* slider) override
    {
        if (slider == &m_freqSlider)
        {
            int currentFundFrequency = m_freqSlider.getValue();
            SynthesisEngine::Instance().setCurrentFundFrequency (currentFundFrequency);
            
            SynthesisEngine::Instance().fillVecPartials();
            
        }
        
        if (slider == &m_nbPartialsSlider)
        {
            int nbPartials = static_cast<int> ( m_nbPartialsSlider.getValue() );
            SynthesisEngine::Instance().setNbPartials (nbPartials);
            
            SynthesisEngine::Instance().fillVecPartials();
        }
        
        if (slider == &m_amplitudeSlider)
        {
            int sliderValue = m_amplitudeSlider.getValue();
            
            double amplitudeFactor = static_cast<double>(sliderValue)/10.0;
            SynthesisEngine::Instance().setAmplitudeFactor(amplitudeFactor);
        }
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
    }
    
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        SynthesisEngine::Instance().setSampleRate (sampleRate);
        
        SynthesisEngine::Instance().fillVecPartials();
        
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
//        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
//
//        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
//        {
//            buffer[sample] = SynthesisEngine::Instance().getCurrentBufferSample();
//
//        }
        
        
        auto* leftBuffer  = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        auto* rightBuffer = bufferToFill.buffer->getWritePointer (1, bufferToFill.startSample);
        for (auto sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            auto currentSample = (float) SynthesisEngine::Instance().getCurrentBufferSample();
    
            leftBuffer[sample]  = currentSample;
            rightBuffer[sample] = currentSample;
        }
        
    }
    
    
    
    
private:
    Slider m_freqSlider, m_nbPartialsSlider, m_amplitudeSlider;
    ComboBox m_waveformComboBox;
    
    int m_maxNbPartials;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }

