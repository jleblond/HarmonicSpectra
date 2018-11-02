/*
  ==============================================================================

    StatsView.h
    Created: 23 Oct 2018 1:24:50am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class StatsView    : public Component
{
public:
    StatsView()
    {
        addAndMakeVisible(mTitle);
        mTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mTitle.setFont(Font("Arial", 18, Font::bold));
        
        addAndMakeVisible(mNbQuestions);
        mNbQuestions.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mNbQuestions.setFont(14);
        
        addAndMakeVisible(mScoreTitleLabel);
        mScoreTitleLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mScoreTitleLabel.setFont(14);
        
        addAndMakeVisible(mScoreLabel);
        mScoreLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mScoreLabel.setFont(Font("Arial", 36, Font::bold));
        
        addAndMakeVisible(mPercentScoreLabel);
        mPercentScoreLabel.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        mPercentScoreLabel.setFont(14);

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
        mTitle.setBounds(0.05*getWidth(), 0.1*getHeight(), 150, 30);
        mNbQuestions.setBounds(0.05*getWidth(), 0.15*getHeight(), 150, 50);
        
        mScoreTitleLabel.setBounds(0.08*getWidth(), 0.395*getHeight(), 130, 30);
        mScoreLabel.setBounds(0.08*getWidth(), 0.42*getHeight(), 150, 60);
        mPercentScoreLabel.setBounds(0.08*getWidth(), 0.6*getHeight(), 130, 75);

    }

private:
    Label mTitle{{}, "STATISTICS"};
    
    Label mScoreTitleLabel{{}, "SCORE:"};
    Label mScoreLabel{{}, "[ ]"};
    Label mPercentScoreLabel{{}, ""};
    
    Label mNbQuestions{{}, "# of questions: 0"};
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatsView)
};
