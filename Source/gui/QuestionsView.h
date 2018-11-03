/*
  ==============================================================================

    ExerciseView.h
    Created: 23 Oct 2018 1:26:34am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../core/ExerciseBuilder.h"
#include "../core/Config.h"
#include "../core/audio/Synthesis.h"
//==============================================================================
/*
*/
class QuestionsView    : public Component,
                         public Button::Listener
{
public:
    QuestionsView()
    {
        addAndMakeVisible(m_newQuestionButton);
        m_newQuestionButton.addListener(this);
        
        addAndMakeVisible(m_playQuestionButton);
        m_playQuestionButton.addListener(this);
        
        addAndMakeVisible(m_playSineWaveButton);
        m_playSineWaveButton.addListener(this);
        
        addAndMakeVisible(m_answerButton);
        m_answerButton.addListener(this);

        
        displayPanel(1);
    }

    ~QuestionsView()
    {
    }

    void paint (Graphics& g) override
    {

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);

        g.setColour (Colours::white);
        g.setFont (14.0f);
//        g.drawText ("QuestionsView", getLocalBounds(),
//                    Justification::centred, true);
    }

    void resized() override
    {
        m_newQuestionButton.setBounds (0.3*getWidth(), 0.2*getHeight(), 0.5*getWidth(), 0.2*getHeight());
        
        
        m_playQuestionButton.setBounds (0.1*getWidth(), 0.2*getHeight(), 0.4*getWidth(), 0.2*getHeight());
        m_playSineWaveButton.setBounds (0.5*getWidth(), 0.2*getHeight(), 0.4*getWidth(), 0.2*getHeight());
        
        m_answerButton.setBounds (0.3*getWidth(), 0.6*getHeight(), 0.5*getWidth(), 0.2*getHeight());


    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &m_newQuestionButton)
        {
            ExerciseBuilder::Instance().buildExercise();
            displayPanel(2);
        }
        
        if(button == &m_playQuestionButton)
        {
            auto lastExercise = Config::user->getLastSession()->getLastExercise();
            Config::waveTypeID = lastExercise->getWaveTypeID();
            int audioRange = lastExercise->getAudibleRange();
            
            Config::nbPartials = ExerciseBuilder::Instance().computeNbPartials(audioRange);
            
            Synthesis::Instance().updateSynthesisValues();
            Config::isPlaying = true;
        }
        
        if(button == &m_playSineWaveButton)
        {
            Config::waveTypeID = 11; //sine wave
            Config::nbPartials = 1; //facultative for sine, but changed for clarity
            
            Synthesis::Instance().updateSynthesisValues();
            Config::isPlaying = true;
        }
        
        if(button == &m_answerButton)
        {
            //correct answer
            
            //temporary
            Config::isPlaying = false;
            
            displayPanel(1);
        }
        
    }
    
    void displayPanel(int panelNb)
    {
        switch(panelNb)
        {
            case 1: //Press new button
                m_newQuestionButton.setVisible(true);
                m_playQuestionButton.setVisible(false);
                m_playSineWaveButton.setVisible(false);
                m_answerButton.setVisible(false);
                break;
            case 2: //Play the sound (and then select the correct answer)
                m_newQuestionButton.setVisible(false);
                m_playQuestionButton.setVisible(true);
                m_playSineWaveButton.setVisible(true);
                m_answerButton.setVisible(true);
                break;
        };
    }

private:
    TextButton m_newQuestionButton{"New Question"};
    TextButton m_playQuestionButton{"*PLAY*"};
    TextButton m_playSineWaveButton{"Play Sine Wave (reference)"};
    TextButton m_answerButton{"Answer"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuestionsView)
};
