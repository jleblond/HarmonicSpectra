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

#include "../utils/ColourSquare.h"

class MatrixView : public Component,
public Button::Listener
{
public:
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
        for (int i = 5; i < 10; i++)
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
            }
            displayAudioRangeButtons(true);
        }
        else if (sizeVecAR == 1)
        {
            m_fixedARLabel.setText (static_cast<String>(Config::vecAudibleRanges[0])+"%", dontSendNotification);
            m_fixedARLabel.setBounds (0.3*getWidth(),0.68*getHeight(),
                                      0.3*getWidth(), 0.15*getHeight());
            
            displayAudioRangeButtons(false);
        }
        
        
        
        // WAVETYPES: Buttons OR Labels 'N/A'
        
        std::vector<int> vecWaves = QuestionBuilder::Instance().getVecWaves();
        int indexALLPartials = 0;
        
        for (int j=0;j<vecWaves.size();j++)
        {
            int waveID = vecWaves[j];
            std::cout<<static_cast<String>(waveID);
            
            if (waveID <=5) //odd partials waves
            {
                m_arrWavesCSquares.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+j*0.12*getWidth()),
                                                                      0.1*getHeight(),
                                                                      0.11*getWidth(), 0.16*getHeight());
                
                m_arrWavesButtons.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+j*0.12*getWidth()),
                                                                     0.1*getHeight(),
                                                                     0.1*getWidth(), 0.15*getHeight());
            }
            else if(waveID > 5) //all partials waves
            {
                m_arrWavesCSquares.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+indexALLPartials*0.12*getWidth()),
                                                                      0.3*getHeight(),
                                                                      0.11*getWidth(), 0.16*getHeight());
                m_arrWavesButtons.getUnchecked(waveID-1)->setBounds (
                                                                     (0.3*getWidth()+indexALLPartials*0.12*getWidth()),0.3*getHeight(),0.1*getWidth(), 0.15*getHeight());
                
                indexALLPartials++;
            }
        }
        
        if (Config::partials == Partials::odd)
        {
            m_NALabel.setBounds(0.3*getWidth(),0.28*getHeight(),
                                0.3*getWidth(), 0.15*getHeight());
            
            displayWaveTypeButtons(true, false);
        }
        else if (Config::partials == Partials::all)
        {
            m_NALabel.setBounds(0.3*getWidth(),0.075*getHeight(),
                                0.3*getWidth(), 0.15*getHeight());
            displayWaveTypeButtons(false, true);
        }
        else if (Config::partials == Partials::both)
        {
            displayWaveTypeButtons(true,true);
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
        for(int i=0;i<m_arrARButtons.size();i++)
        {
            if(button == m_arrARButtons.getUnchecked(i))
            {
                if(m_isQuestionMode)
                {
                    resetARButtonsColours();
                    m_arrARCSquares[i]->setColour(Colours::black);
                    m_answeredAudibleRange = m_vecARPercents[i];
                }
            }
        }
        
        for(int i=0;i<m_arrWavesButtons.size();i++)
        {
            if(button == m_arrWavesButtons.getUnchecked(i))
            {
                if(m_isQuestionMode)
                {
                    resetWaveButtonsColours();
                    m_arrWavesCSquares[i]->setColour(Colours::black);
                    m_answeredWaveTypeID = (i+1);
                }
                
            }
        }
        
        
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
    
    void correctWaveTypeID(int correctWaveTypeID)
    {
        m_arrWavesCSquares[correctWaveTypeID-1]->setColour(Colours::green);
        m_answeredWaveTypeID = 0;
    }
    
    void correctAudibleRange(int correctAudibleRange)
    {
        for(int i=0;i<m_arrARCSquares.size();i++)
        {
            if(m_vecARPercents[i] == correctAudibleRange)
            {
                m_arrARCSquares[i]->setColour(Colours::green);
            }
        }
        m_answeredAudibleRange = 0;
    }
    
    void setQuestionMode (bool isQuestionMode)
    {
        m_isQuestionMode = isQuestionMode;
    }
    
    int getAnsweredWaveTypeID()
    {
        return m_answeredWaveTypeID;
    }
    
    int getAnsweredAudibleRange()
    {
        return m_answeredAudibleRange;
    }
    
    
protected:
    bool m_isQuestionMode = false;
    int m_answeredWaveTypeID = 0;
    int m_answeredAudibleRange = 0;
    
    OwnedArray<TextButton> m_arrWavesButtons;
    OwnedArray<ColourSquare> m_arrWavesCSquares;
    
    OwnedArray<TextButton>  m_arrARButtons;
    OwnedArray<ColourSquare> m_arrARCSquares;
    std::vector<int> m_vecARPercents {10, 25, 50, 75, 100};
    
    Label m_allLabel{{}, "ALL:"}, m_oddLabel{{}, "ODD:"}, m_arLabel{{}, "AUDIBLE RANGE:"};
    Label m_NALabel{{}, "N/A"};
    Label m_fixedARLabel;
};
