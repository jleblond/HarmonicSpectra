/*
  ==============================================================================

    ExerciseConfigView.h
    Created: 23 Oct 2018 1:27:33am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ExerciseConfigView : public Component,
public Button::Listener, public Slider::Listener, public ComboBox::Listener
{
public:
    enum RadioButtonIds
    {
        PartialsButtons = 1001
    };
    
    ExerciseConfigView()
    {
        addAndMakeVisible(m_titleLabel);
        
        addAndMakeVisible (m_partialsLabel);
        
        addAndMakeVisible (m_allPartialsButton);
        addAndMakeVisible (m_oddPartialsButton);
        addAndMakeVisible (m_oddorallPartialsButton);
//        m_allPartialsButton.onClick = [this] { updateToggleState (&m_allPartialsButton, "All"); };
//        m_oddPartialsButton  .onClick = [this] { updateToggleState (&m_oddPartialsButton,   "Odd");   };
//        m_oddorallPartialsButton .onClick = [this] { updateToggleState (&m_oddorallPartialsButton,  "Odd OR All");  };
        
        m_allPartialsButton.setRadioGroupId (PartialsButtons);
        m_oddPartialsButton.setRadioGroupId (PartialsButtons);
        m_oddorallPartialsButton.setRadioGroupId (PartialsButtons);
        
        m_allPartialsButton .setClickingTogglesState (true);
        m_oddPartialsButton   .setClickingTogglesState (true);
        m_oddorallPartialsButton  .setClickingTogglesState (true);
        
        m_allPartialsButton.triggerClick();
        
    }
    
    ~ExerciseConfigView()
    {
        
    }
    
    void paint(Graphics& g) override
    {
      
    }
    
    void resized() override
    {
        m_titleLabel.setBounds(0.45*getWidth(), 0.03*getHeight(), 0.6*getWidth(), 80);
        
        m_partialsLabel.setBounds(0.15*getWidth(), 0.23*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_allPartialsButton.setBounds(0.15*getWidth(), 0.3*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_oddPartialsButton.setBounds(0.25*getWidth(), 0.3*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_oddorallPartialsButton.setBounds(0.35*getWidth(), 0.3*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        
    }
    
    void buttonClicked(Button* button) override
    {
    
        
    }
    
    void sliderValueChanged (Slider* slider) override
    {

    }
    
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override
    {
      
    }
    
//    void updateToggleState (Button* button, String name)
//    {
//        auto state = button->getToggleState();
//        String stateString    = state ? "ON" : "OFF";
//        String selectedString = state ? " (selected)" : "";
//
//        Logger::outputDebugString (name + " Button changed to " + stateString);
//        button->setButtonText (name + selectedString);
//    }
   
    
private:
    Label m_titleLabel { {}, "EXERCISE PARAMETERS"};
    
    Label m_partialsLabel { {}, "Partials"};
    TextButton m_allPartialsButton {"All"};
    TextButton m_oddPartialsButton {"Odd"};
    TextButton m_oddorallPartialsButton {"Odd OR All"};
};

