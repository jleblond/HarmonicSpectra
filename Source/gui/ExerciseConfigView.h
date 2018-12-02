/*
  ==============================================================================

    ExerciseConfigView.h
    Created: 23 Oct 2018 1:27:33am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../core/Partials.h"

//==============================================================================
/*
*/
class ExerciseConfigView :  public Component,
                            public Button::Listener,
                            public Slider::Listener,
                            public ComboBox::Listener
{
public:
    enum RadioButtonIds
    {
        PartialsButtons = 1001,
        NbAmplitudeRatiosButtons = 1002
    };
    
    
    ExerciseConfigView()
    {
        addAndMakeVisible(m_titleLabel);
        
        
        // PARTIALS
        
        addAndMakeVisible (m_partialsLabel);
        
        addAndMakeVisible (m_allPartialsButton);
        addAndMakeVisible (m_oddPartialsButton);
        addAndMakeVisible (m_oddorallPartialsButton);

        m_allPartialsButton.setRadioGroupId (PartialsButtons);
        m_oddPartialsButton.setRadioGroupId (PartialsButtons);
        m_oddorallPartialsButton.setRadioGroupId (PartialsButtons);
        
        m_allPartialsButton .setClickingTogglesState (true);
        m_oddPartialsButton   .setClickingTogglesState (true);
        m_oddorallPartialsButton  .setClickingTogglesState (true);
        
        m_allPartialsButton.triggerClick();
        
        
        // # of AMPLITUDE RATIOS
        
        addAndMakeVisible (m_nbAmplitudeRatiosLabel);
       
        addAndMakeVisible (m_2ampRatiosButton);
        addAndMakeVisible (m_3ampRatiosButton);
        addAndMakeVisible (m_5ampRatiosButton);
        
        m_2ampRatiosButton.setRadioGroupId (NbAmplitudeRatiosButtons);
        m_3ampRatiosButton.setRadioGroupId (NbAmplitudeRatiosButtons);
        m_5ampRatiosButton.setRadioGroupId (NbAmplitudeRatiosButtons);
        
        m_2ampRatiosButton.setClickingTogglesState (true);
        m_3ampRatiosButton.setClickingTogglesState (true);
        m_5ampRatiosButton.setClickingTogglesState (true);
       
        m_2ampRatiosButton.triggerClick();
        
        
        // AUDIBLE RANGE
        
        addAndMakeVisible(m_audibleRangeLabel);
        
        addAndMakeVisible(m_audibleRangeComboBox);
        m_audibleRangeComboBox.addItem("100%", 1);
        m_audibleRangeComboBox.addItem("75%", 2);
        m_audibleRangeComboBox.addItem("50%", 3);
        m_audibleRangeComboBox.addItem("25%", 4);
        m_audibleRangeComboBox.addItem("10%", 5);
        m_audibleRangeComboBox.addItem("Identify 10-25-50-75-100%", 6);
        m_audibleRangeComboBox.setSelectedId(1);
        m_audibleRangeComboBox.addListener(this);
        
        
        // BASE FREQUENCY
        
        addAndMakeVisible(m_baseFreqLabel);
        
        addAndMakeVisible(m_baseFreqSlider);
        m_baseFreqSlider.setRange(1, 6, 1);
        m_baseFreqSlider.setSliderStyle(juce::Slider::LinearHorizontal);
        m_baseFreqSlider.setTextBoxStyle(Slider::NoTextBox, false, 0, m_baseFreqSlider.getTextBoxHeight());
        m_baseFreqSlider.setValue(3);
        m_baseFreqSlider.addListener(this);
        
        addAndMakeVisible(m_baseFreqTextLabel);
    }
    
    
    ~ExerciseConfigView()
    {
        
    }
    
    
    void paint(Graphics& g) override
    {
       g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
    }
    
    
    void resized() override
    {
        m_titleLabel.setBounds(0.45*getWidth(), 0.07*getHeight(), 0.6*getWidth(), 0.08*getHeight());
        
        m_partialsLabel.setBounds(0.15*getWidth(), 0.23*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_allPartialsButton.setBounds(0.15*getWidth(), 0.3*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_oddPartialsButton.setBounds(0.25*getWidth(), 0.3*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_oddorallPartialsButton.setBounds(0.35*getWidth(), 0.3*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        
        m_nbAmplitudeRatiosLabel.setBounds(0.15*getWidth(), 0.45*getHeight(), 0.6*getWidth(), 0.07*getHeight());
        m_2ampRatiosButton.setBounds(0.15*getWidth(), 0.52*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_3ampRatiosButton.setBounds(0.25*getWidth(), 0.52*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_5ampRatiosButton.setBounds(0.35*getWidth(), 0.52*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        
        m_baseFreqLabel.setBounds(0.15*getWidth(), 0.7*getHeight(), 0.6*getWidth(), 0.07*getHeight());
        m_baseFreqSlider.setBounds(0.15*getWidth(), 0.77*getHeight(), 0.3*getWidth(), 0.07*getHeight());
        m_baseFreqTextLabel.setBounds(0.46*getWidth(), 0.77*getHeight(), 0.2*getWidth(), 0.07*getHeight());
        
        m_audibleRangeLabel.setBounds(0.6*getWidth(), 0.23*getHeight(), 0.6*getWidth(), 0.07*getHeight());
        m_audibleRangeComboBox.setBounds(0.6*getWidth(), 0.3*getHeight(), 0.25*getWidth(), 0.07*getHeight());
        
    }
    
    
    void buttonClicked(Button* button) override
    {
    
    }
    
    void sliderValueChanged (Slider* slider) override
    {
        if(slider == &m_baseFreqSlider)
        {
            String text = static_cast<String>(getBaseFreq())+" Hz";
            m_baseFreqTextLabel.setText(text, dontSendNotification);
        }
    }
    
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
      
    }

    
    int getBaseFreq()
    {
        int baseFreq = 0;
        
        switch( static_cast<int>(m_baseFreqSlider.getValue()) )
        {
            case 1:
                baseFreq = 50;
                break;
            case 2:
                baseFreq = 100;
                 break;
            case 3:
                baseFreq = 200;
                 break;
            case 4:
                baseFreq = 400;
                 break;
            case 5:
                baseFreq = 800;
                 break;
            case 6:
                baseFreq = 1600;
                 break;
        };
        
        
        return baseFreq;
    }
   
    
    Partials::Options getPartials()
    {
        if(m_oddPartialsButton.getToggleState() == true)
        {
            return Partials::Options::odd;
        }
        
        if(m_oddorallPartialsButton.getToggleState() == true)
        {
            return Partials::Options::both;
        }
        
        //else default
        return Partials::Options::all;
    }
    
    
    int getNbAmplitudeRatios()
    {
        if(m_3ampRatiosButton.getToggleState() == true)
        {
            return 3;
        }
        
        if(m_5ampRatiosButton.getToggleState() == true)
        {
            return 5;
        }
        
        //else default
        return 2;
    }
    
    
    std::vector<int> getVecAudibleRange()
    {
        std::vector<int> vecAudibleRanges;
        vecAudibleRanges.clear();
        
        switch(m_audibleRangeComboBox.getSelectedId() )
        {
            case 2:
                vecAudibleRanges.push_back(75);
                break;
            case 3:
                vecAudibleRanges.push_back(50);
                break;
            case 4:
                vecAudibleRanges.push_back(25);
                break;
            case 5:
                vecAudibleRanges.push_back(10);
                break;
            case 6: //case 'identify all'
                vecAudibleRanges.push_back(10);
                vecAudibleRanges.push_back(25);
                vecAudibleRanges.push_back(50);
                vecAudibleRanges.push_back(75);
                vecAudibleRanges.push_back(100);
                break;
            default: // case 1, as well
                 vecAudibleRanges.push_back(100);
        };
    
        return vecAudibleRanges;
    }
    
    
private:
    Label m_titleLabel { {}, "EXERCISE CONFIGURATION"};
    
    Label m_partialsLabel { {}, "Partials"};
    TextButton m_allPartialsButton {"All"};
    TextButton m_oddPartialsButton {"Odd"};
    TextButton m_oddorallPartialsButton {"Odd OR All"};
    
    Label m_nbAmplitudeRatiosLabel { {}, "# of amplitude ratios"};
    TextButton m_2ampRatiosButton {"2"};
    TextButton m_3ampRatiosButton {"3"};
    TextButton m_5ampRatiosButton {"5"};
    
    Label m_audibleRangeLabel { {}, "Audible Range"};
    ComboBox m_audibleRangeComboBox;
    
    Label m_baseFreqLabel { {}, "Base Frequency (1st partial)"};
    Slider m_baseFreqSlider;
    Label m_baseFreqTextLabel { {}," (Hz)"};
    
};

