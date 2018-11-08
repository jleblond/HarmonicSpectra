/*
  ==============================================================================

    MatrixView.h
    Created: 4 Nov 2018 9:53:24pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../core/Config.h"
#include "../core/QuestionBuilder.h"
#include "../core/AnswerChecker.h"

#include "../utils/ColourSquare.h"

class MatrixView : public Component,
public Button::Listener
{
public:
    OwnedArray<TextButton> m_arrWavesButtons;
    OwnedArray<ColourSquare> m_arrWavesCSquares;
    
    OwnedArray<TextButton>  m_arrARButtons;
    OwnedArray<ColourSquare> m_arrARCSquares;
    
    
    MatrixView()
    {
        addAndMakeVisible(m_oddLabel);
        addAndMakeVisible(m_allLabel);
        addAndMakeVisible(m_arLabel);
        
        addAndMakeVisible(m_NALabel);
        addAndMakeVisible(m_fixedARLabel);
        
        
        //Order is important due to z-index
        
        for (int i = 0; i < 5; i++)
        {
            ColourSquare* newARColourSquare = new ColourSquare();
            m_arrARCSquares.add (newARColourSquare);
            addAndMakeVisible (newARColourSquare);
            
            TextButton* newARButton = new TextButton();
            String arButtonText = static_cast<String>(m_vecARPercents[i])+"%";
            newARButton->setButtonText(arButtonText);
            m_arrARButtons.add (newARButton);
            newARButton->addListener(this);
            addAndMakeVisible (newARButton);
            
            
            
            ColourSquare* newColourSquare = new ColourSquare();
            m_arrWavesCSquares.add (newColourSquare);
            addAndMakeVisible (newColourSquare);
            
            TextButton* newODDButton = new TextButton();
            newODDButton->setButtonText("ODD"+static_cast<String>(i+1));
            m_arrWavesButtons.add (newODDButton);
            newODDButton->addListener(this);
            addAndMakeVisible (newODDButton);
        }
        for (int i = 0; i < 5; i++)
        {
            ColourSquare* newColourSquare = new ColourSquare();
            m_arrWavesCSquares.add (newColourSquare);
            addAndMakeVisible (newColourSquare);
            
            TextButton* newALLButton = new TextButton();
            newALLButton->setButtonText("ALL"+static_cast<String>(i+1));
            m_arrWavesButtons.add (newALLButton);
            newALLButton->addListener(this);
            addAndMakeVisible (newALLButton);
        
        }
        
        
        
        
        
    }
    
    ~MatrixView()
    {
        
    }
    
    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
        
    }
    
    void resized() override
    {
        
        // General-Main LABELS
        
        m_oddLabel.setBounds (0.08*getWidth(), 0.1*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_allLabel.setBounds (0.08*getWidth(), 0.3*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_arLabel.setBounds (0.08*getWidth(), 0.7*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        
        //reset
        
        
        
        //AUDIBLE RANGE : Buttons OR Label with fixed AR text
        
        int sizeVecAR = Config::vecAudibleRanges.size();
        
        if (sizeVecAR > 1)
        {
            for (int i=0;i<sizeVecAR;i++)
            {
                m_arrARCSquares.getUnchecked(i)->setBounds( (0.3*getWidth()+i*0.12*getWidth()),
                                                           0.7*getHeight(),
                                                           0.11*getWidth(), 0.16*getHeight());
                
                m_arrARButtons.getUnchecked(i)->setBounds( (0.3*getWidth()+i*0.12*getWidth()),
                                                          0.7*getHeight(),
                                                          0.1*getWidth(), 0.15*getHeight());
                
                m_fixedARLabel.setVisible(false);
            }
            displayAudioRangeButtons(true);
        }
        else if (sizeVecAR == 1)
        {
            m_fixedARLabel.setText (static_cast<String>(Config::vecAudibleRanges[0])+"%", dontSendNotification);
            m_fixedARLabel.setBounds (0.3*getWidth(),0.68*getHeight(),
                                      0.3*getWidth(), 0.15*getHeight());
            
            m_fixedARLabel.setVisible(true);
            
            displayAudioRangeButtons(false);
        }
        
        
        
        // WAVETYPES: Buttons OR Labels 'N/A'
        
        std::vector<int> vecWaves = QuestionBuilder::Instance().getVecWaves();
        int indexALLPartials = 0;
        
        displayWaveTypeButtons(false, false);
        
        for (int j=0;j<vecWaves.size();j++)
        {
            int waveID = vecWaves[j];
            
            if (waveID <=5) //odd partials waves
            {
                m_arrWavesCSquares.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+j*0.12*getWidth()),
                                                                      0.1*getHeight(),
                                                                      0.11*getWidth(), 0.16*getHeight());
                
                m_arrWavesButtons.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+j*0.12*getWidth()),
                                                                     0.1*getHeight(),
                                                                     0.1*getWidth(), 0.15*getHeight());
                m_arrWavesButtons.getUnchecked(waveID-1)->setVisible(true);
            }
            else if(waveID > 5) //all partials waves
            {
                m_arrWavesCSquares.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+indexALLPartials*0.12*getWidth()),
                                                                      0.3*getHeight(),
                                                                      0.11*getWidth(), 0.16*getHeight());
                m_arrWavesButtons.getUnchecked(waveID-1)->setBounds (
                                                                     (0.3*getWidth()+indexALLPartials*0.12*getWidth()),0.3*getHeight(),0.1*getWidth(), 0.15*getHeight());
                m_arrWavesButtons.getUnchecked(waveID-1)->setVisible(true);
                indexALLPartials++;
            }
        }
        
        if (Config::partials == Partials::odd)
        {
            m_NALabel.setBounds(0.3*getWidth(),0.28*getHeight(),
                                0.3*getWidth(), 0.15*getHeight());
             m_NALabel.setVisible(true);
        }
        else if (Config::partials == Partials::all)
        {
            m_NALabel.setBounds(0.3*getWidth(),0.075*getHeight(),
                                0.3*getWidth(), 0.15*getHeight());
            m_NALabel.setVisible(true);
        }
        else if (Config::partials == Partials::both)
        {
            m_NALabel.setVisible(false);
        }
        
    }
    
    
    void displayAudioRangeButtons(bool isVisible)
    {
        for( int i=0;i<5;i++)
        {
            m_arrARButtons.getUnchecked(i)->setVisible(isVisible);
        }
    }
    
    void displayWaveTypeButtons (bool showODD, bool showALL)
    {
        for(int i=0;i<5;i++)
        {
            m_arrWavesButtons[i]->setVisible(showODD);
        }
        for(int i=5;i<m_arrWavesButtons.size();i++)
        {
            m_arrWavesButtons[i]->setVisible(showALL);
        }
    }
    
    void displayColourSquares (bool isVisible)
    {
        for(int i=0;i<m_arrARCSquares.size();i++)
        {
            m_arrARCSquares[i]->setVisible(isVisible);
        }
        for(int j=0;j<m_arrWavesCSquares.size();j++)
        {
            m_arrWavesCSquares[j]->setVisible(isVisible);
        }
    }
    
    void buttonClicked(Button* button) override
    {
        
    }
    
    void pressARButton(int index)
    {
        if(m_isQuestionMode || m_isTestMode)
        {
            //                    resetARButtonsColours();
            //                    m_arrARCSquares[i]->setColour(Colours::black);
            m_selectedAudibleRange = m_vecARPercents[index];
            
            resetEnabledARButtons();
            m_arrARButtons[index]->setEnabled(false);
            
        }
    }
                             
    void pressWaveButton(int index)
    {
        if(m_isQuestionMode || m_isTestMode)
        {
            //                    resetWaveButtonsColours();
            //                    m_arrWavesCSquares[i]->setColour(Colours::black);
            m_selectedWaveTypeID = (index+1);
            
            resetEnabledWavesButtons();
            m_arrWavesButtons[index]->setEnabled(false);
        }
    }

    
    void displayCorrectWaveTypeID(int selectedWaveTypeID, int correctWaveTypeID)
    {
        float score = AnswerChecker::Instance().scoreWaveTypeID();
        
        if(score == 1)
        {
            m_arrWavesCSquares[selectedWaveTypeID-1]->setColour(Colours::green);
        }
        else if(score == 0.5)
        {
            m_arrWavesCSquares[selectedWaveTypeID-1]->setColour(Colours::orange);
        }
        else
        {
            m_arrWavesCSquares[selectedWaveTypeID-1]->setColour(Colours::red);
        }
 
         m_arrWavesCSquares[correctWaveTypeID-1]->setColour(Colours::green);

    }
    
    void displayCorrectAudibleRange(int selectedAudibleRange, int correctAudibleRange)
    {
        int selectedAudibleRangeIndex = 0;
        int correctAudibleRangeIndex = 0;
        
        
        for(int i=0;i<m_vecARPercents.size();i++)
        {
            if (m_vecARPercents[i] == selectedAudibleRange)
            {
                selectedAudibleRangeIndex = i;
            }
            if(m_vecARPercents[i] == correctAudibleRange)
            {
                correctAudibleRangeIndex = i;
            }
            
        }
        
        float score = AnswerChecker::Instance().scoreAudibleRange();
        
        if(score == 1)
        {
             m_arrARCSquares[selectedAudibleRangeIndex]->setColour(Colours::green);
        }
        else if(score == 0.5)
        {
             m_arrARCSquares[selectedAudibleRangeIndex]->setColour(Colours::orange);
        }
        else
        {
            m_arrARCSquares[selectedAudibleRangeIndex]->setColour(Colours::red);
        }
        
        
    
        //must be separed loop to guarantee green color identifed
        for(int i=0;i<m_arrARCSquares.size();i++)
        {
            if(m_vecARPercents[i] == correctAudibleRange)
            {
                m_arrARCSquares[i]->setColour(Colours::green);
            }
        }
        
      

    }
    
    void setQuestionMode (bool isQuestionMode)
    {
        m_isQuestionMode = isQuestionMode;
    }
    
    void setTestMode (bool isTestMode)
    {
        m_isTestMode = isTestMode;
    }
    
    int getSelectedWaveTypeID()
    {
        return m_selectedWaveTypeID;
    }
    
    int getSelectedAudibleRange()
    {
        return m_selectedAudibleRange;
    }
    
    void resetSelectedValues()
    {
        m_selectedWaveTypeID = 0;
        m_selectedAudibleRange = 0;
    }
    
    void resetARButtonsColours()
    {
        for(int i=0;i<m_arrARButtons.size();i++)
        {
            m_arrARCSquares[i]->setColour(Colours::transparentWhite);
        }
    }
    
    void resetWaveButtonsColours()
    {
        for(int i=0;i<m_arrWavesButtons.size();i++)
        {
            m_arrWavesCSquares[i]->setColour(Colours::transparentWhite);
        }
    }
    
    void resetEnabledARButtons()
    {
        for(int i=0;i<m_arrARButtons.size();i++)
        {
            m_arrARButtons.getUnchecked(i)->setEnabled(true);
        }
    }
    
    void resetEnabledWavesButtons()
    {
        for(int i=0;i<m_arrWavesButtons.size();i++)
        {
            m_arrWavesButtons.getUnchecked(i)->setEnabled(true);
        }
    }
    
protected:
    bool m_isQuestionMode = false;
    bool m_isTestMode = true; //default value at init
    int m_selectedWaveTypeID = 0;
    int m_selectedAudibleRange = 0;

    std::vector<int> m_vecARPercents {10, 25, 50, 75, 100};
    
    Label m_allLabel{{}, "ALL:"}, m_oddLabel{{}, "ODD:"}, m_arLabel{{}, "AUDIBLE RANGE:"};
    Label m_NALabel{{}, "N/A"};
    Label m_fixedARLabel;
};
