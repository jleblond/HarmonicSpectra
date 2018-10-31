/*
  ==============================================================================

    MainApplication.h
    Created: 23 Oct 2018 1:28:55am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "HeaderView.h"
#include "UserConfigView.h"
#include "ExerciseConfigView.h"
#include "MainWindow.h"
#include "QuestionsView.h"
#include "VolumeView.h"
#include "StatsView.h"


const int HEIGHT = 700;
const int WIDTH = 900;

const float HEADER_PERCENT_HEIGHT = 0.15;
const float BOTTOM_BUTTONS_HEIGHT = 0.20; //height relative to espace left without header


class MainApplication    : public Component,
                            public Button::Listener
{
public:
    MainApplication()
    {
        setSize (WIDTH, HEIGHT);
        setLookAndFeel( m_LF );
        
        addAndMakeVisible(m_headerView);
        addAndMakeVisible(m_userConfigView);
        addAndMakeVisible(m_createUserButton);
        m_createUserButton.setButtonText("NEXT");
        m_createUserButton.addListener(this);
        
        addAndMakeVisible(m_exerciseConfigView);
        m_exerciseConfigView.setVisible(false);
        
        addAndMakeVisible(m_startSessionButton);
        m_startSessionButton.setVisible(false);
        
        
    }

    ~MainApplication()
    {
        delete m_LF;
    }

    void paint (Graphics& g) override
    {

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("MainApplication", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        Rectangle<int> area (getLocalBounds());
        m_headerView.setBounds (area.removeFromTop( HEADER_PERCENT_HEIGHT*getHeight()));
        
        Rectangle<int> area1 (area);
        m_createUserButton.setBounds (area1.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
        m_userConfigView.setBounds(area1);
        
        Rectangle<int> area2 (area);
        m_createUserButton.setBounds (area2.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
        m_exerciseConfigView.setBounds(area2);
        
        Rectangle<int> area3 (area);
        
        
    }
    
    void buttonClicked(Button* button) override
    {
    }

private:
    LookAndFeel *m_LF = new LookAndFeel_V4( (LookAndFeel_V4::getLightColourScheme() ) );
    
    HeaderView m_headerView;
    UserConfigView m_userConfigView;
    ExerciseConfigView m_exerciseConfigView;
    
    TextButton m_createUserButton;
    TextButton m_startSessionButton;
    TextButton m_endSessionButton;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainApplication)
};
