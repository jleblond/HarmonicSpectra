/*
  ==============================================================================

    MainWindow.h
    Created: 23 Oct 2018 3:01:23am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../core/Config.h"
#include "../core/ExerciseBuilder.h"


class MainWindow : public Component,
                   public Button::Listener
{
public:
    MainWindow()
    {
         addAndMakeVisible(m_oddLabel);
         addAndMakeVisible(m_allLabel);
         addAndMakeVisible(m_arLabel);
        
        addAndMakeVisible(m_NALabel);
        addAndMakeVisible(m_fixedARLabel);
        
        
        for (int i = 0; i < 5; i++)
        {
            TextButton* newARButton = new TextButton();
            String arButtonText = static_cast<String>(m_vecARPercents[i])+"%";
            newARButton->setButtonText(arButtonText);
            m_arrARButtons.add (newARButton);
            newARButton->addListener(this);
            addAndMakeVisible (newARButton);
            
            
            TextButton* newODDButton = new TextButton();
            newODDButton->setButtonText("ODD"+static_cast<String>(i+1));
            m_arrODDButtons.add (newODDButton);
            newODDButton->addListener(this);
            addAndMakeVisible (newODDButton);
        }
        
        for (int i = 0; i < 5; i++)
        {
            TextButton* newALLButton = new TextButton();
            newALLButton->setButtonText("ALL"+static_cast<String>(i+1));
            m_arrALLButtons.add (newALLButton);
            newALLButton->addListener(this);
            addAndMakeVisible (newALLButton);
        }
        
        
    }
    
    ~MainWindow()
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
        
        std::vector<int> vecWaves = ExerciseBuilder::Instance().getVecWaves();
        int indexALLPartials = 0;

        for (int j=0;j<vecWaves.size();j++)
        {
            int waveID = vecWaves[j];
            std::cout<<static_cast<String>(waveID);

            if (waveID <=5) //odd partials waves
            {
                m_arrODDButtons.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+j*0.12*getWidth()),
                                                                   0.1*getHeight(),
                                                                   0.1*getWidth(), 0.15*getHeight());
            }
            else if(waveID > 5) //all partials waves
            {
                m_arrALLButtons.getUnchecked(waveID-6)->setBounds (
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
        for(int i=0;i<m_arrODDButtons.size();i++)
        {
            m_arrODDButtons[i]->setVisible(showODD);
        }
        for(const auto& j: m_arrALLButtons)
        {
            j->setVisible(showALL);
        }
    }
    
    void buttonClicked(Button* button) override
    {
        for(int i=0;i<m_arrARButtons.size();i++)
        {
            if(button == m_arrARButtons.getUnchecked(i))
            {
                std::cout<<"m_arrARButtons button #"+static_cast<String>(i+1)<<std::endl;
            }
        }
        
        for(int i=0;i<m_arrODDButtons.size();i++)
        {
            if(button == m_arrODDButtons.getUnchecked(i))
            {
                std::cout<<"m_arrODDButtons button #"+static_cast<String>(i+1)<<std::endl;
            }
        }
        
        for(int i=0;i<m_arrALLButtons.size();i++)
        {
            if(button == m_arrALLButtons.getUnchecked(i))
            {
                std::cout<<"m_arrALLButtons button #"+static_cast<String>(i+1)<<std::endl;
            }
        }

        
    }
    
protected:
    OwnedArray<TextButton> m_arrALLButtons;
    OwnedArray<TextButton> m_arrODDButtons;
    
    OwnedArray<TextButton>  m_arrARButtons;
    std::vector<int> m_vecARPercents {10, 25, 50, 75, 100};
    
    Label m_allLabel{{}, "ALL:"}, m_oddLabel{{}, "ODD:"}, m_arLabel{{}, "AUDIBLE RANGE:"};
    Label m_NALabel{{}, "N/A"};
    Label m_fixedARLabel;
};

