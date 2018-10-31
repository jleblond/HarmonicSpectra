/*
  ==============================================================================

    UserConfigView.h
    Created: 31 Oct 2018 6:27:40pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class UserConfigView : public Component,
                       private TextEditor::Listener
{
public:
    UserConfigView()
    {
        addAndMakeVisible(m_TxtFieldLabel);
        m_TxtFieldLabel.setText("Username: ", dontSendNotification);
        m_TxtFieldLabel.setBounds(250, 270, 60, 30);
        
        addAndMakeVisible(m_TextField);
        m_TextField.setBounds(375, 270, 250, 30);
        m_TextField.setColour(juce::TextEditor::textColourId, Colours::black);
        m_TextField.setColour(juce::TextEditor::outlineColourId, juce::Colour::fromRGB(0,0,0));
        m_TextField.setColour(juce::TextEditor::backgroundColourId, juce::Colour::fromRGB(247, 249, 252));
        m_TextField.setColour(juce::TextEditor::focusedOutlineColourId, juce::Colour::fromRGB(0,0,0));
        m_TextField.setText("");
        
    }
    
    ~UserConfigView()
    {
    }
    
    void paint (Graphics& g) override
    {
        
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        
        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
        
        //g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("Start a new session", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }
    
    void resized() override
    {
        Rectangle<int> area (getLocalBounds());
        // m_TextField.setBounds(area.removeFromBottom(0.4*getHeight()));
        
    }
    
    String getTextFieldValue()
    {
        String s = "";
        s = m_TextField.getText();
        return s;
    }
    
    
private:
    TextEditor m_TextField;
    Label m_TxtFieldLabel;
    //JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIStartSession)
};

