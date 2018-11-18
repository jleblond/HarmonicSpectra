/*
  ==============================================================================

    MainWindow.h
    Created: 23 Oct 2018 3:01:23am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../core/QuestionBuilder.h"
#include "../core/Config.h"
#include "../core/audio/Synthesis.h"

#include "../core/AnswerChecker.h"

#include "MatrixView.h"
#include "StatsView.h"

const float QUESTIONS_WIDTH = 0.25;
const float MATRIX_WIDTH = 1-QUESTIONS_WIDTH;


class MainWindow    : public Component,
public Button::Listener
{
public:
    StatsView m_statsView;
    
    MainWindow()
    {
        addAndMakeVisible(m_matrixView);
        
        
        addAndMakeVisible(m_playTestButton);
        m_playTestButton.addListener(this);
        
        addAndMakeVisible(m_playTestLabel);
        m_playTestLabel.setFont(16);
        addAndMakeVisible(m_playTestValuesLabel);
        m_playTestValuesLabel.setFont(14);
        
        addAndMakeVisible(m_newQuestionButton);
        m_newQuestionButton.addListener(this);
        
        addAndMakeVisible(m_playQuestionButton);
        m_playQuestionButton.addListener(this);
        
        addAndMakeVisible(m_playSineWaveButton);
        m_playSineWaveButton.addListener(this);
        
        addAndMakeVisible(m_answerButton);
        m_answerButton.addListener(this);
        
        addAndMakeVisible(m_notAnsweredLabel);
        m_notAnsweredLabel.setColour(juce::Label::textColourId, Colours::red);
        
        
        displayPanel(1);
        
        
        for(int i=0;i<m_matrixView.m_arrARButtons.size();i++)
        {
            m_matrixView.m_arrARButtons[i]->addListener(this);
        }
        for(int i=0;i<m_matrixView.m_arrImgButtons.size();i++)
        {
            m_matrixView.m_arrImgButtons[i]->addListener(this);
        }
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
        g.setFont (12.0f);
    }
    
    void resized() override
    {
        Rectangle<int> area (getLocalBounds());
        m_matrixView.setBounds (area.removeFromRight( MATRIX_WIDTH*getWidth()));
        
        
        m_playTestButton.setBounds (0.13*getWidth(), 0.2*getHeight(), 0.06*getWidth(), 0.12*getHeight());
        
        m_playTestLabel.setBounds (0.05*getWidth(), 0.1*getHeight(), 0.13*getWidth(), 0.15*getHeight());
        
        m_playTestValuesLabel.setBounds (0.025*getWidth(), 0.21*getHeight(), 0.1*getWidth(), 0.2*getHeight());
        
        m_newQuestionButton.setBounds (0.045*getWidth(), 0.6*getHeight(), 0.125*getWidth(), 0.25*getHeight());
        
        
        
        m_playQuestionButton.setBounds (0.04*getWidth(), 0.15*getHeight(), 0.16*getWidth(), 0.2*getHeight());
        m_playSineWaveButton.setBounds (0.07*getWidth(), 0.37*getHeight(), 0.09*getWidth(), 0.1*getHeight());
        
        m_answerButton.setBounds (0.047*getWidth(), 0.62*getHeight(), 0.125*getWidth(), 0.2*getHeight());
        
        m_notAnsweredLabel.setBounds (0.045*getWidth(), 0.83*getHeight(), 0.2*getWidth(), 0.15*getHeight());
        
        m_playTestButton.setEnabled(false);
        
    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &m_playTestButton)
        {
            int waveTypeID = m_matrixView.getSelectedWaveTypeID();
            int nbPartials = getValidNbPartialsFromMatrix();
            
            if (waveTypeID != 0 && nbPartials != 0)
            {
                playSound(waveTypeID, nbPartials);
            }
            
            updatePlayTestValuesLabelText();
           
            
        }
        if(button == &m_newQuestionButton)
        {
            //MODEL
            QuestionBuilder::Instance().buildQuestion();
            m_matrixView.resetSelectedValues();
            
            //VIEW
            m_matrixView.setQuestionMode(true);
            m_matrixView.setTestMode(false);
            resetMatrixButtonsColours();
            resetMatrixButtonsEnabled();
            displayPanel(2);
        }
        
        if(button == &m_playQuestionButton)
        {
            auto lastQuestion = Config::user->getLastSession()->getLastQuestion();
            int waveTypeID = lastQuestion->getWaveTypeID();
            int audioRange = lastQuestion->getAudibleRange();
          
            playSound(waveTypeID, audioRange);
        }
        
        if(button == &m_playSineWaveButton)
        {
            playSine();
        }
        
        if(button == &m_answerButton)
        {
            m_notAnsweredLabel.setText("", dontSendNotification);
      
            correctAnswers();
            
            Config::isPlaying = false; //temporary
            
            if(m_notAnsweredLabel.getText() == "")
            {
                m_matrixView.setQuestionMode(false);
                m_matrixView.setTestMode(true);
                
                displayPanel(1);
                
                compileStats();
                m_statsView.repaint();
            }
        }
        
        
        for(int i=0;i<m_matrixView.m_arrARButtons.size();i++)
        {
            if(button == m_matrixView.m_arrARButtons.getUnchecked(i))
            {
                m_matrixView.pressARButton(i);
                updatePlayTestValuesLabelText();
            }
        }
        
        for(int i=0;i<m_matrixView.m_arrImgButtons.size();i++)
        {
            if(button == m_matrixView.m_arrImgButtons.getUnchecked(i))
            {
                m_matrixView.pressWaveButton(i);
                updatePlayTestValuesLabelText();
            }
        }
        
    }
    
    void playSound(int waveTypeID, int audibleRange)
    {
        Config::waveTypeID = waveTypeID;
        Config::nbPartials = QuestionBuilder::Instance().computeNbPartials(audibleRange);
        Synthesis::Instance().updateSynthesisValues();
        Config::hasStartedPlaying = true;
    }
    
    void playSine()
    {
        Config::waveTypeID = 11;
        Config::nbPartials = 1;
        Synthesis::Instance().updateSynthesisValues();
        Config::hasStartedPlaying = true;
    }
    
    void displayPanel(int panelNb)
    {
        switch(panelNb)
        {
            case 1: //Press new button
                m_playTestButton.setVisible(true);
                m_playTestLabel.setVisible(true);
                m_playTestValuesLabel.setVisible(true);
                    updatePlayTestValuesLabelText();
                m_newQuestionButton.setVisible(true);
                m_playQuestionButton.setVisible(false);
                m_playSineWaveButton.setVisible(false);
                m_answerButton.setVisible(false);
                break;
            case 2: //Play the sound (and then select the correct answer)
                m_playTestButton.setVisible(false);
                m_playTestLabel.setVisible(false);
                m_playTestValuesLabel.setVisible(false);
                    m_playTestValuesLabel.setText("", dontSendNotification);
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
    
    void correctAnswers()
    {
        auto lastSession = Config::user->getLastSession();
        auto lastQuestion = lastSession->getLastQuestion();
        
        String message = "";
        
        //Check 'WaveTypeID'
        int selectedWaveTypeID = m_matrixView.getSelectedWaveTypeID();
        if (selectedWaveTypeID == 0)
        {
            message += "* ODD/ALL not selected *\n";
        }
        
    
        //Check 'AudibleRange'
        //If and only if AUDIBLE RANGE is being tested for this session/question
        
        int selectedAudibleRange = m_matrixView.getSelectedAudibleRange();
        if(lastSession->getVecAudibleRangesSize() >1)
        {
            if (selectedAudibleRange == 0)
            {
                message += "* Audible Range not selected *";
            }
        }

        
        //CORRECTION if both wavetype and audiblerange are ok
        if(message == "")
        {
           lastQuestion->setAnsweredWaveTypeID (selectedWaveTypeID);
            m_matrixView.displayCorrectWaveTypeID (selectedWaveTypeID, lastQuestion->getWaveTypeID() );
            
            if(lastSession->getVecAudibleRangesSize() >1)
            {
                 lastQuestion->setAnsweredAudibleRange(selectedAudibleRange);
                 m_matrixView.displayCorrectAudibleRange (selectedAudibleRange, lastQuestion->getAudibleRange());
            }
        }
        
         m_notAnsweredLabel.setText(message, dontSendNotification);
    }
    

    
    int getValidNbPartialsFromMatrix()
    {
        assert (Config::user != nullptr);
        assert(Config::user->getVecSessions().size()>0);
        auto lastSession = Config::user->getLastSession();
        if(lastSession->getVecAudibleRangesSize() >1)
        {
            int audibleRange = m_matrixView.getSelectedAudibleRange();
            if(audibleRange != 0)
            {
                return QuestionBuilder::Instance().computeNbPartials(audibleRange);
            }// else will reach end of function and return non-valid 0 value;
        }
        else
        {
            int audibleRange = Config::vecAudibleRanges[0];
            return QuestionBuilder::Instance().computeNbPartials(audibleRange);
        }
        
        return 0; //non-valid output
    }
    
    
    int getValidAudibleRangeFromMatrix()
    {
        int audibleRange = 0;
        if(Config::user != nullptr)
        {
            if(Config::user->getVecSessions().size()>0)
            {
                auto lastSession = Config::user->getLastSession();
                if(lastSession->getVecAudibleRangesSize() >1)
                {
                    audibleRange = m_matrixView.getSelectedAudibleRange();
                }
                else
                {
                    audibleRange = Config::vecAudibleRanges[0];
                }
            }
        }
        
        return audibleRange;
    }
    
    void updatePlayTestValuesLabelText()
    {
        String labelText = "Current  values";
        bool waveSelected = false;
        bool arSelected = false;
        
        int waveTypeID = m_matrixView.getSelectedWaveTypeID();
        labelText = "\nWave: \n";
        
        if(waveTypeID == 0)
        {
            labelText += "(not selected)";
        }
        else if(waveTypeID <= 5)
        {
            labelText += "ODD #"+static_cast<String>(waveTypeID);
            waveSelected = true;
        }
        else
        {
            labelText += "ALL #"+static_cast<String>(waveTypeID-5);
            waveSelected = true;
        }
        
        
        int audibleRange = getValidAudibleRangeFromMatrix();
        labelText +="\nAudible Range: \n";
        
        if(audibleRange == 0)
        {
            labelText += "(not selected)";
        }
        else
        {
            labelText += static_cast<String>(audibleRange)+"%";
            arSelected = true;
        }
    
        if (waveSelected && arSelected)
        {
            m_playTestButton.setEnabled(true);
        }
                                                              
        m_playTestValuesLabel.setText(labelText, dontSendNotification);
    }
    

    void resetAll()
    {
        resetMatrixButtonsColours();
        resetMatrixButtonsEnabled();
        resetMatrixFormulasDisplayed();
        m_notAnsweredLabel.setText("", dontSendNotification);
        
        m_matrixView.resetSelectedValues();
    }
        
    void resetMatrixButtonsColours()
    {
        m_matrixView.resetARButtonsColours();
        m_matrixView.resetWaveButtonsColours();
    }
    
    void resetMatrixButtonsEnabled()
    {
        m_matrixView.resetEnabledARButtons();
        m_matrixView.resetEnabledWavesButtons();
    }
    
    void  resetMatrixFormulasDisplayed()
    {
        m_matrixView.resetFormulasDisplayed();
    }
    void compileStats()
    {
        auto stats = &Config::user->getLastSession()->getStats();
        auto lastQuestion = Config::user->getLastSession()->getLastQuestion();
        
        
        //AUDIBLE RANGE
        if(Config::vecAudibleRanges.size() > 1)
        {
            stats->audibleRange.count += 1;
            stats->audibleRange.correctanswer += AnswerChecker::Instance().scoreAudibleRange();
        }
        
        
        //WAVE TYPE
        float waveTypeScore = AnswerChecker::Instance().scoreWaveTypeID();
        
        int waveTypeCorrectAnswer = lastQuestion->getWaveTypeID();
        int waveTypeAnswered = lastQuestion->getAnsweredWaveTypeID();
        
        if(waveTypeScore == 1)
        {
            stats->vecWaves[waveTypeAnswered-1].correctanswer += 1;
            stats->vecWaves[waveTypeAnswered-1].count += 1;
        }
        else if (waveTypeScore == 0.5)
        {
            stats->vecWaves[waveTypeAnswered-1].correctanswer += 0.5;
            stats->vecWaves[waveTypeAnswered-1].count += 1;
            
            stats->vecWaves[waveTypeCorrectAnswer-1].correctanswer += 0.5;
            stats->vecWaves[waveTypeCorrectAnswer-1].count += 1;
        }
        else
        {
            stats->vecWaves[waveTypeAnswered-1].correctanswer += 0;
            stats->vecWaves[waveTypeAnswered-1].count += 1;
            
            stats->vecWaves[waveTypeCorrectAnswer-1].correctanswer += 0;
            stats->vecWaves[waveTypeCorrectAnswer-1].count += 1;
        }
        
        stats->print();
    }

private:
    MatrixView m_matrixView;
    
    TextButton m_newQuestionButton{"New Question"};
    TextButton m_playTestButton{"Play"};
    TextButton m_playQuestionButton{"PLAY Question"};
    TextButton m_playSineWaveButton{"Play Sine Wave (reference)"};
    TextButton m_answerButton{"Answer"};
    
    Label m_notAnsweredLabel{{}, ""};
    Label m_playTestLabel{{}, "Test different values!"};
    Label m_playTestValuesLabel{{}, ""};

};
