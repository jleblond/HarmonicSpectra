/*
  ==============================================================================

    maincomponent.h
    Created: 19 Dec 2017 5:03:16pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"
#include "../util/utility.h"
#include "../audio/synthesis.h"


class MainContentComponent   :  public AudioAppComponent,
                                public Slider::Listener,
                                public ComboBox::Listener
{
public:
    MainContentComponent()
    :   mMaxNbPartials (128)
    {
        addAndMakeVisible (mFrequencySlider);
        mFrequencySlider.setRange (20.0, 20000.0);
        mFrequencySlider.setSkewFactorFromMidPoint (500.0);
        mFrequencySlider.addListener (this);
        
        addAndMakeVisible (mNumberPartialsSlider);
        mNumberPartialsSlider.setRange (1, mMaxNbPartials, 1);
        mNumberPartialsSlider.addListener (this);
        
        addAndMakeVisible (mWaveformCombobox);
        mWaveformCombobox.addItem ("Sine", 1);
        mWaveformCombobox.addSeparator();
        mWaveformCombobox.addSectionHeading ("ODD Partials");
        mWaveformCombobox.addItem ("Square", 2);
        mWaveformCombobox.addItem ("Square Triangled", 3);
        mWaveformCombobox.addItem ("Square-Tri or Tri-Square", 4);
        mWaveformCombobox.addItem ("Triangle Squared", 5);
        mWaveformCombobox.addItem ("Triangle", 6);
        mWaveformCombobox.addSeparator();
        mWaveformCombobox.addSectionHeading ("ALL Partials");
        mWaveformCombobox.addItem ("Sawtooth", 7);
        mWaveformCombobox.addItem ("Steeper Saw", 8);
        mWaveformCombobox.addItem ("Very Steep Saw", 9);
        mWaveformCombobox.addItem ("Almost-Exponential Saw", 10);
        mWaveformCombobox.addItem ("Exponential Saw", 11);
        mWaveformCombobox.setSelectedId (1);
        mWaveformCombobox.addListener (this);
        
        setSize (600, 200);
        setAudioChannels (0, 1);
    }
    
    ~MainContentComponent()
    {
        shutdownAudio();
    }
    
    void resized() override
    {
        mWaveformCombobox.setBounds (10, 10, 120, 30);
        mFrequencySlider.setBounds (10, 50, getWidth() - 20, 20);
        mNumberPartialsSlider.setBounds (10, 100, getWidth() - 20, 20);
    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
        if (comboBoxThatHasChanged == &mWaveformCombobox)
        {
            int waveType = mWaveformCombobox.getSelectedId();
            Synthesis::Instance().setWaveType (waveType);
            
            Synthesis::Instance().fillVecPartials();
        }
    }
    
    void sliderDragEnded (Slider* slider) override
    {
        if (slider == &mFrequencySlider)
        {
            int currentFundFrequency = mFrequencySlider.getValue();
            Synthesis::Instance().setCurrentFundFrequency (currentFundFrequency);
            
            Synthesis::Instance().fillVecPartials();
            
        }
        
        if (slider == &mNumberPartialsSlider)
        {
            int nbPartials = static_cast<int> ( mNumberPartialsSlider.getValue() );
            Synthesis::Instance().setNbPartials (nbPartials);
            
            Synthesis::Instance().fillVecPartials();
        }
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {
    }
    
    
    void prepareToPlay (int /*samplesPerBlockExpected*/, double sampleRate) override
    {
        Synthesis::Instance().setSampleRate (sampleRate);
        
        Synthesis::Instance().fillVecPartials();
        
    }
    
    void releaseResources() override
    {
    }
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override
    {
        float* const buffer = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
        
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            buffer[sample] = Synthesis::Instance().getCurrentBufferSample();
            
        }
    }
    
    
    
    
private:
    Slider mFrequencySlider, mNumberPartialsSlider;
    ComboBox mWaveformCombobox;
    
    int mMaxNbPartials;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};

Component* createMainContentComponent()     { return new MainContentComponent(); }

