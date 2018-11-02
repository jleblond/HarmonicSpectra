/*
  ==============================================================================

    VolumeView.h
    Created: 23 Oct 2018 1:24:33am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../core/Config.h"
//==============================================================================
/*
*/
class VolumeView    : public Component,
                      public Slider::Listener
{
public:
    VolumeView()
    {
        addAndMakeVisible(m_volumeSlider);
        m_volumeSlider.setRange(0, 10, 0.1);
        m_volumeSlider.setSliderStyle(juce::Slider::LinearVertical);
        m_volumeSlider.setTextBoxIsEditable(false);
        m_volumeSlider.setValue(5);
        m_volumeSlider.addListener(this);
        
        addAndMakeVisible(m_volumeLabel);
        //m_volumeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    }

    ~VolumeView()
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
        m_volumeLabel.setBounds( 0.15*getWidth(), 0.1*getHeight(), 0.7*getWidth(), 0.1*getHeight() );
        m_volumeSlider.setBounds( 0.3*getWidth(), 0.3*getHeight(), 0.3*getWidth(), 0.5*getHeight() );
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        
        if(slider == &m_volumeSlider)
            Config::mainVolume = m_volumeSlider.getValue() /10;
    }

private:
    Slider m_volumeSlider;
    Label m_volumeLabel { {}, "MASTER VOLUME"};
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VolumeView)
    
    
};
