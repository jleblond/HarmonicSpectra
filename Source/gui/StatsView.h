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
            oddWaveBar->setColour(Colour (0xffBBFFFF));
            m_arrBars.add(oddWaveBar);
            
            Label* ratioLabel = new Label();
            m_arrRatiosLabels.add(ratioLabel);
            
            Label* countLabel = new Label();
            m_arrCountsLabels.add(countLabel);
        }
        for(int i=0;i<5;i++)
        {
            StatsBar* allWaveBar = new StatsBar();
            allWaveBar->setColour(Colour (0xff80D9FF));
            m_arrBars.add(allWaveBar);
            
            Label* ratioLabel = new Label();
            m_arrRatiosLabels.add(ratioLabel);
            
            Label* countLabel = new Label();
            m_arrCountsLabels.add(countLabel);
        }
        
        m_ARBar = new StatsBar();
        m_ARBar->setColour(Colour (0xffE2CFC8));

    }

    ~StatsView()
    {
        delete m_ARBar;
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        g.fillAll(Colours::white);

        g.setColour (Colours::grey);
        //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
        
        assert(Config::user != nullptr);
        assert(Config::user->getLastSession() != nullptr);
        
        StatsSheet& stats = Config::user->getLastSession()->getStats();
        
        
        for(int i=0;i<m_arrBars.size();i++)
        {
            m_arrBars[i]->updateValues(stats.vecWaves[i].percent, stats.vecWaves[i].count);
            m_arrBars[i]->repaintBar();
        }
      
    }

    void resized() override
    {
        m_title.setBounds(0.05*getWidth(), 0.1*getHeight(), 150, 30);
        m_nbQuestions.setBounds(0.05*getWidth(), 0.15*getHeight(), 150, 50);
        
        m_scoreTitleLabel.setBounds(0.08*getWidth(), 0.395*getHeight(), 130, 30);
        m_scoreLabel.setBounds(0.08*getWidth(), 0.42*getHeight(), 150, 60);
        m_percentScoreLabel.setBounds(0.08*getWidth(), 0.6*getHeight(), 130, 75);
        
        m_countsTitle.setBounds(0.2*getWidth(), 0.1*getHeight(), 70, 30);
        m_percentsTitle.setBounds(0.2*getWidth(), 0.47*getHeight(), 70, 30);
        m_ratiosTitle.setBounds(0.2*getWidth(), 0.8*getHeight(), 70, 30);
        
        for(int i=0;i<m_arrBars.size();i++)
        {
            m_arrCountsLabels[i]->setBounds( m_vecXPos[i]*getWidth(), 0.1*getHeight(),
                                          m_barSize, m_barSize );
            
            m_arrBars[i]->setBounds (m_vecXPos[i]*getWidth(), 0.25*getHeight(),
                                     m_barSize, 0.6*getHeight() );
            m_arrRatiosLabels[i]->setBounds (m_vecXPos[i]*getWidth(),
                                       0.77*getHeight(),
                                       m_barSize*1.25, m_barSize*2);
        }

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
    
    
     float m_barSize = 0.05*getWidth(); //35
    
    OwnedArray<StatsBar> m_arrBars;
    OwnedArray<Label> m_arrRatiosLabels;
    OwnedArray<Label> m_arrCountsLabels;
    StatsBar* m_ARBar = nullptr;
    Label m_ARLabel{{}, "Audible Range"};
    std::vector<double> m_vecXPos = {0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 0.7, 0.75, 0.8, 0.85};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatsView)
};
