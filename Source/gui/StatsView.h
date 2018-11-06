/*
  ==============================================================================

    StatsView.h
    Created: 23 Oct 2018 1:24:50am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../core/Config.h"
//==============================================================================
/*
*/
class StatsView    : public Component
{
public:
    StatsView()
    {
        addAndMakeVisible(m_title);
        m_title.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_title.setFont(Font("Arial", 18, Font::bold));
        
        addAndMakeVisible(m_nbQuestions);
        m_nbQuestions.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_nbQuestions.setFont(14);
        
        addAndMakeVisible(m_scoreTitleLabel);
        m_scoreTitleLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_scoreTitleLabel.setFont(14);
        
        addAndMakeVisible(m_scoreLabel);
        m_scoreLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_scoreLabel.setFont(Font("Arial", 36, Font::bold));
        
        addAndMakeVisible(m_percentScoreLabel);
        m_percentScoreLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_percentScoreLabel.setFont(14);

    }

    ~StatsView()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        g.fillAll(Colours::white);

        g.setColour (Colours::grey);
        //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
      
    }

    void resized() override
    {
        m_title.setBounds(0.05*getWidth(), 0.1*getHeight(), 150, 30);
        m_nbQuestions.setBounds(0.05*getWidth(), 0.15*getHeight(), 150, 50);
        
        m_scoreTitleLabel.setBounds(0.08*getWidth(), 0.395*getHeight(), 130, 30);
        m_scoreLabel.setBounds(0.08*getWidth(), 0.42*getHeight(), 150, 60);
        m_percentScoreLabel.setBounds(0.08*getWidth(), 0.6*getHeight(), 130, 75);

    }

private:
    Label m_title{{}, "STATISTICS"};
    
    Label m_scoreTitleLabel{{}, "SCORE:"};
    Label m_scoreLabel{{}, "[ ]"};
    Label m_percentScoreLabel{{}, ""};
    
    Label m_nbQuestions{{}, "# of questions: 0"};
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatsView)
};
