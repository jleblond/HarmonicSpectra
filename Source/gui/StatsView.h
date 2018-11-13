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
#include "StatsBar.h"
#include <stdlib.h>
//==============================================================================
/*
*/
class StatsView    : public Component
{
public:
    StatsView()
    {
        //Left section
        
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
        
        
        //Labels section
        
        addAndMakeVisible(m_countsTitle);
        m_countsTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_countsTitle.setFont(14);
        m_countsTitle.setJustificationType(juce::Justification::right);
        
        addAndMakeVisible(m_percentsTitle);
        m_percentsTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_percentsTitle.setFont(14);
        m_percentsTitle.setJustificationType(juce::Justification::right);
        
        addAndMakeVisible(m_ratiosTitle);
        m_ratiosTitle.setColour(juce::Label::textColourId, juce::Colour(0.0f, 0.0f, 0.0f));
        m_ratiosTitle.setFont(14);
        m_ratiosTitle.setJustificationType(juce::Justification::right);
        
        
        
        
        for(int i=0;i<5;i++)
        {
            StatsBar* oddWaveBar = new StatsBar();
            oddWaveBar->setColour(Colours::dodgerblue);
            m_arrBars.add(oddWaveBar);
            addAndMakeVisible(oddWaveBar);
            
            Label* ratioLabel = new Label();
            m_arrRatiosLabels.add(ratioLabel);
            addAndMakeVisible(ratioLabel);
            
            Label* countLabel = new Label();
            m_arrCountsLabels.add(countLabel);
            addAndMakeVisible(countLabel);
        }
        for(int i=0;i<5;i++)
        {
            StatsBar* allWaveBar = new StatsBar();
            allWaveBar->setColour(Colours::deepskyblue);
            m_arrBars.add(allWaveBar);
            addAndMakeVisible(allWaveBar);
            
            Label* ratioLabel = new Label();
            m_arrRatiosLabels.add(ratioLabel);
            addAndMakeVisible(ratioLabel);
            
            Label* countLabel = new Label();
            m_arrCountsLabels.add(countLabel);
            addAndMakeVisible(countLabel);
        }
        

        m_ARBar.setColour(Colours::darkblue);
        addAndMakeVisible(m_ARBar);
        
        addAndMakeVisible(m_ARLabel);
        
        resized();

    }

    ~StatsView()
    {
      
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        g.fillAll(Colours::white);
        g.setColour (Colours::grey);
        g.setColour (Colours::white);
        g.setFont (14.0f);
        
        assert(Config::user != nullptr);
        assert(Config::user->getLastSession() != nullptr);
        
        StatsSheet& stats = Config::user->getLastSession()->getStats();
        
        for(int i=0;i<m_arrBars.size();i++)
        {
            m_arrBars[i]->updateValues(stats.vecWaves[i].getPercent(), stats.vecWaves[i].count);
        }
        
        if(Config::vecAudibleRanges.size() > 1)
        {
            m_ARBar.updateValues(stats.audibleRange.getPercent(), stats.audibleRange.count);
        }
      
    }

    void resized() override
    {
        m_title.setBounds(0.05*getWidth(), 0.05*getHeight(), 150, 30);
        m_nbQuestions.setBounds(0.05*getWidth(), 0.1*getHeight(), 150, 50);
        
        m_scoreTitleLabel.setBounds(0.08*getWidth(), 0.345*getHeight(), 130, 30);
        m_scoreLabel.setBounds(0.08*getWidth(), 0.37*getHeight(), 150, 60);
        m_percentScoreLabel.setBounds(0.08*getWidth(), 0.55*getHeight(), 130, 75);
        
        m_countsTitle.setBounds(0.2*getWidth(), 0.05*getHeight(), 70, 30);
        m_percentsTitle.setBounds(0.2*getWidth(), 0.42*getHeight(), 70, 30);
        m_ratiosTitle.setBounds(0.2*getWidth(), 0.8*getHeight(), 70, 30);
        
        for(int i=0;i<m_arrBars.size();i++)
        {
            m_arrCountsLabels[i]->setBounds( m_vecXPos[i]*getWidth(), 0.05*getHeight(),
                                          m_barSize, m_barSize );

            m_arrBars[i]->setBounds (m_vecXPos[i]*getWidth(), 0.2*getHeight(),
                                     m_barSize, 0.6*getHeight() );
            m_arrRatiosLabels[i]->setBounds (m_vecXPos[i]*getWidth(),
                                       0.72*getHeight(),
                                       m_barSize*1.25, m_barSize*2);
        }

        m_ARBar.setBounds(0.9*getWidth(), 0.2*getHeight(), m_barSize, 0.6*getHeight() );
        m_ARLabel.setBounds(0.9*getWidth(), 0.72*getHeight(), m_barSize*2, m_barSize*2 );

    }

private:
    Label m_title{{}, "STATISTICS"};
    
    Label m_scoreTitleLabel{{}, "SCORE:"};
    Label m_scoreLabel{{}, "[ ]"};
    Label m_percentScoreLabel{{}, ""};
    
    Label m_nbQuestions{{}, "# of questions: 0"};
    
    
    
    Label m_countsTitle{{}, "Count:"};
    Label m_percentsTitle{{}, "Score:"};
    Label m_ratiosTitle{{}, "Amplitude ratios"};
    
    
    float m_barSize = 40; //0.05*getWidth(); //35
    
    OwnedArray<StatsBar> m_arrBars;
    OwnedArray<Label> m_arrRatiosLabels;
    OwnedArray<Label> m_arrCountsLabels;
    StatsBar m_ARBar;
    Label m_ARLabel{{}, "Audible Range"};
    std::vector<double> m_vecXPos = {0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatsView)
};
