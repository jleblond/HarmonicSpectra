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
#include "../core/QuestionBuilder.h"

#include "components/StatsBar.h"
#include "components/RatioFormula.h"

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
            
            Label* partialLabel = new Label("", "ODD");
            m_arrPartialsLabels.add(partialLabel);
            addAndMakeVisible(partialLabel);
            partialLabel->setFont (Font (14.0f, Font::plain));
            
            RatioFormula* ratioLabel = new RatioFormula(m_vecRatioStr[i]);
            m_arrRatiosLabels.add(ratioLabel);
            addAndMakeVisible(ratioLabel);
            ratioLabel->setBackgroundColour(Colours::lightgrey);

            
            Label* countLabel = new Label();
            m_arrCountsLabels.add(countLabel);
            addAndMakeVisible(countLabel);
        }
        for(int i=5;i<10;i++)
        {
            StatsBar* allWaveBar = new StatsBar();
            allWaveBar->setColour(Colours::deepskyblue);
            m_arrBars.add(allWaveBar);
            addAndMakeVisible(allWaveBar);
            
            Label* partialLabel = new Label("", "ALL");
            m_arrPartialsLabels.add(partialLabel);
            addAndMakeVisible(partialLabel);
            partialLabel->setFont (Font (14.0f, Font::plain));
            
            RatioFormula* ratioLabel = new RatioFormula(m_vecRatioStr[i-5]);
            m_arrRatiosLabels.add(ratioLabel);
            addAndMakeVisible(ratioLabel);
            ratioLabel->setBackgroundColour(Colours::lightgrey);
            
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
        
        //Background Formula Ratios Rectangle
        g.setColour (Colours::lightgrey);
        Rectangle<int> area (0.28*getWidth(), 0.82*getHeight(), 0.65*getWidth(), m_barSize*1.1);
        g.fillRect (area);
    
        g.setColour (Colours::grey);
        g.setFont (14.0f);
        
        
        assert(Config::user != nullptr);
        assert(Config::user->getLastSession() != nullptr);
        auto lastSession = Config::user->getLastSession();
        
        StatsSheet& stats = lastSession->getStats();
        
        for(int i=0;i<m_arrBars.size();i++)
        {
            m_arrBars[i]->updateValues(stats.vecWaves[i].getPercent(), stats.vecWaves[i].count);
            m_arrCountsLabels[i]->setText(static_cast<String>(stats.vecWaves[i].count), dontSendNotification);
        }
        
        if(Config::vecAudibleRanges.size() > 1)
        {
            m_ARBar.updateValues(stats.audibleRange.getPercent(), stats.audibleRange.count);
        }
        

        int nbQuestions = lastSession->getVecQuestions().size();
        m_nbQuestions.setText("# of questions: "+static_cast<String>(nbQuestions), dontSendNotification);
        
        int maxScore = lastSession->getStats().maxScore;
        float score = lastSession->getStats().getScoring();
        float nearestScore = floor( (score) * 5 + 0.5) / 5;
        int percentScore = lastSession->getStats().percentScore * 100;
        m_scoreLabel.setText("["+static_cast<String>(nearestScore)+"/"+static_cast<String>(maxScore)+"]", dontSendNotification);
        m_percentScoreLabel.setText(static_cast<String>(percentScore)+"% at the present level", dontSendNotification);
        lastSession->getStats().questionsCount = lastSession->getVecQuestions().size();
      
    }

    
    void resized() override
    {
        m_title.setBounds(0.04*getWidth(), 0.05*getHeight(), 150, 30);
        m_nbQuestions.setBounds(0.04*getWidth(), 0.1*getHeight(), 150, 50);
        
        m_scoreTitleLabel.setBounds(0.05*getWidth(), 0.345*getHeight(), 130, 30);
        m_scoreLabel.setBounds(0.05*getWidth(), 0.37*getHeight(), 150, 60);
        m_percentScoreLabel.setBounds(0.05*getWidth(), 0.5*getHeight(), 130, 75);
        
        m_countsTitle.setBounds(0.2*getWidth(), 0.07*getHeight(), 70, 30);
        m_percentsTitle.setBounds(0.2*getWidth(), 0.44*getHeight(), 70, 30);
        m_ratiosTitle.setBounds(0.2*getWidth(), 0.82*getHeight(), 70, 30);
        
        for(int i=0;i<m_arrBars.size();i++)
        {
            m_arrCountsLabels[i]->setBounds( m_vecXPos[i]*getWidth()+0.25*m_barSize, 0.05*getHeight(),
                                          m_barSize, m_barSize );

            m_arrBars[i]->setBounds (m_vecXPos[i]*getWidth(), 0.2*getHeight(),
                                     m_barSize, 0.6*getHeight() );
            
            m_arrPartialsLabels[i]->setBounds (m_vecXPos[i]*1.005*getWidth(),
                                               0.65*getHeight(),
                                               m_barSize*1.5, m_barSize);
            m_arrRatiosLabels[i]->setBounds (m_vecXPos[i]*getWidth()+0.2*m_barSize,
                                       0.83*getHeight(),
                                       m_barSize*1.5, m_barSize);
        }

        m_ARBar.setBounds(0.94*getWidth(), 0.2*getHeight(), m_barSize, 0.6*getHeight() );
        m_ARLabel.setBounds(0.93*getWidth(), 0.72*getHeight(), m_barSize*2, m_barSize*2 );

    }
    
    
    void updateBarsVisibility()
    {
        //HIDE ALL THE BARS
        for(int i=0;i<m_arrBars.size();i++)
        {
            m_arrCountsLabels[i]->setVisible(false);
            m_arrBars[i]->setVisible(false);
        }
        m_ARBar.setVisible(false);
        m_ARLabel.setVisible(false);
        
        
        //SHOW TESTED WAVES
        std::vector<int> vecWaves = QuestionBuilder::Instance().getVecWaves();
        
        for(int i=0; i<vecWaves.size();i++)
        {
            int waveID = vecWaves[i];
            m_arrCountsLabels[waveID-1]->setVisible(true);
            m_arrBars[waveID-1]->setVisible(true);
        }
        
       //POSSIBLY SHOW AUDIBLERANGE BAR
        if (Config::vecAudibleRanges.size() > 1)
        {
            m_ARBar.setVisible(true);
            m_ARLabel.setVisible(true);
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
    
    float m_barSize = 40; //0.05*getWidth(); //35
    
    OwnedArray<StatsBar> m_arrBars;
    OwnedArray<Label> m_arrPartialsLabels;
    OwnedArray<RatioFormula> m_arrRatiosLabels;
    std::vector<String> m_vecRatioStr = {"", "1.25", "1.5", "1.75", "2"};
    OwnedArray<Label> m_arrCountsLabels;
    StatsBar m_ARBar;
    Label m_ARLabel{{}, "Audible\nRange"};
    std::vector<double> m_vecXPos = {0.3, 0.36, 0.42, 0.48, 0.54, 0.6, 0.66, 0.72, 0.78, 0.84};
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatsView)
};
