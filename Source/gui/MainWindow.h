/*
  ==============================================================================

    MainWindow.h
    Created: 23 Oct 2018 3:01:23am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../core/ExerciseBuilder.h"
#include "../core/Config.h"
#include "../core/audio/Synthesis.h"

#include "MatrixView.h"

const float QUESTIONS_WIDTH = 0.35;
const float MATRIX_WIDTH = 1-QUESTIONS_WIDTH;


class MainWindow    : public Component,
public Button::Listener
{
public:
    MainWindow()
    {
        addAndMakeVisible(m_matrixView);
        
        
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
    
    ~MainWindow()
    {
    }
    
    void paint (Graphics& g) override
    {
        
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        
        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);
        
        g.setColour (Colours::white);
        g.setFont (14.0f);
        //        g.drawText ("MainWindow", getLocalBounds(),
        //                    Justification::centred, true);
    }
    
    void resized() override
    {
        Rectangle<int> area (getLocalBounds());
        m_matrixView.setBounds (area.removeFromRight( MATRIX_WIDTH*getWidth()));
        
        
        
        m_newQuestionButton.setBounds (0.08*getWidth(), 0.2*getHeight(), 0.175*getWidth(), 0.25*getHeight());
        
        
        m_playQuestionButton.setBounds (0.08*getWidth(), 0.2*getHeight(), 0.21*getWidth(), 0.2*getHeight());
        m_playSineWaveButton.setBounds (0.11*getWidth(), 0.45*getHeight(), 0.14*getWidth(), 0.1*getHeight());
        
        m_answerButton.setBounds (0.09*getWidth(), 0.7*getHeight(), 0.175*getWidth(), 0.2*getHeight());
        
        
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
            Config::hasStartedPlaying = true;
        }
        
        if(button == &m_playSineWaveButton)
        {
            Config::waveTypeID = 11; //sine wave
            Config::nbPartials = 1; //facultative for sine, but changed for clarity
            
            Synthesis::Instance().updateSynthesisValues();
            Config::hasStartedPlaying = true;
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
    
    
    void updateMatrixView()
    {
        m_matrixView.resized();
    }
    
private:
    MatrixView m_matrixView;
    
    TextButton m_newQuestionButton{"New Question"};
    TextButton m_playQuestionButton{"PLAY Question"};
    TextButton m_playSineWaveButton{"Play Sine Wave (reference)"};
    TextButton m_answerButton{"Answer"};

};
