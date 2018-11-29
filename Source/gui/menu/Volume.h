/*
  ==============================================================================

    VolumeView.h
    Created: 23 Oct 2018 1:24:33am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../core/Config.h"
//==============================================================================
/*
*/
class Volume    : public Component,
                      public Slider::Listener
{
public:
    Volume()
    {
        addAndMakeVisible(m_volumeSlider);
        m_volumeSlider.setRange(1, 10, 1);
        m_volumeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
        m_volumeSlider.setTextBoxIsEditable(false);
        m_volumeSlider.setValue(Config::mainVolume*10);
        m_volumeSlider.addListener(this);
        
        addAndMakeVisible(m_volumeLabel);
        //m_volumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    }

    ~Volume()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        //g.fillAll(Colours::black);
        
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    }

    void resized() override
    {
        m_volumeLabel.setBounds( 0.35*getWidth(), 0.1*getHeight(), 0.7*getWidth(), 0.1*getHeight() );
        m_volumeSlider.setBounds( 0.1*getWidth(), 0.3*getHeight(), 0.8*getWidth(), 0.5*getHeight() );
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        
        if(slider == &m_volumeSlider)
            Config::mainVolume = static_cast<float>(m_volumeSlider.getValue()) /10.0;
    }

private:
    Slider m_volumeSlider;
    Label m_volumeLabel { {}, "Master Volume"};
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Volume)
    
    
};
