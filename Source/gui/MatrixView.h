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

#include "components/ColourSquare.h"
#include "components/RatioFormula.h"

#include "../../JuceLibraryCode/JuceHeader.h"

const float ODD_HEIGHT = 0.1;
const float FORMULAS_HEIGHT = 0.29;
const float ALL_HEIGHT = 0.4;
const float AR_HEIGHT = 0.8;

class MatrixView : public Component,
public Button::Listener
{
public:
    OwnedArray<ImageButton> m_arrImgButtons;
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
        
        
        m_arrRatioImages.push_back(img1);
        m_arrRatioImages.push_back(img2);
        m_arrRatioImages.push_back(img3);
        m_arrRatioImages.push_back(img4);
        m_arrRatioImages.push_back(img5);
        m_arrRatioImages.push_back(img6);
        m_arrRatioImages.push_back(img7);
        m_arrRatioImages.push_back(img8);
        m_arrRatioImages.push_back(img9);
        m_arrRatioImages.push_back(img10);
        
        //Order is important due to z-index
        
        for (int i = 0; i < 5; i++)
        {
            //Audible Range Row
            
            ColourSquare* newARColourSquare = new ColourSquare();
            m_arrARCSquares.add (newARColourSquare);
            addAndMakeVisible (newARColourSquare);
            
            TextButton* newARButton = new TextButton();
            String arButtonText = static_cast<String>(m_vecARPercents[i])+"%";
            newARButton->setButtonText(arButtonText);
            m_arrARButtons.add (newARButton);
            newARButton->addListener(this);
            addAndMakeVisible (newARButton);
            
            
            //ODD row
            
            ColourSquare* newColourSquare = new ColourSquare();
            m_arrWavesCSquares.add (newColourSquare);
            addAndMakeVisible (newColourSquare);
            
            
            
            ImageButton* imgButton = new ImageButton();
            m_arrImgButtons.add(imgButton);
            imgButton->setImages (false, true, false,
                                  m_arrRatioImages[i], 1.0f, Colours::transparentBlack,
                                m_arrRatioImages[i], 1.0f, Colours::white.withAlpha (0.8f),
                                 m_arrRatioImages[i], 1.0f, Colours::transparentBlack,
                                0.5f);
            addAndMakeVisible(imgButton);
            imgButton->addListener(this);
            //    mLogoButton.setTooltip ("Information about the Inner Ear Project");
            
            
            //Ratio Formulas
            RatioFormula* ratioLabel = new RatioFormula(m_vecRatioStr[i]);
            m_arrRatiosLabels.add(ratioLabel);
            addAndMakeVisible(ratioLabel);
            ratioLabel->setBackgroundColour(Colour(0xffefefef));
            ratioLabel->setVisible(false);
            
        }
        
        //ALL row
        for (int i = 0; i < 5; i++)
        {
            ColourSquare* newColourSquare = new ColourSquare();
            m_arrWavesCSquares.add (newColourSquare);
            addAndMakeVisible (newColourSquare);
            
            ImageButton* imgButton = new ImageButton();
            m_arrImgButtons.add(imgButton);
            imgButton->setImages (false, true, false,
                                  m_arrRatioImages[i+5], 1.0f, Colours::transparentBlack,
                                  m_arrRatioImages[i+5], 1.0f, Colours::white.withAlpha (0.8f),
                                   m_arrRatioImages[i+5], 1.0f, Colours::transparentBlack,
                                  0.5f);
            addAndMakeVisible(imgButton);
            imgButton->addListener(this);
        
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
        
        m_oddLabel.setBounds (0.18*getWidth(), ODD_HEIGHT*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_allLabel.setBounds (0.18*getWidth(), ALL_HEIGHT*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_arLabel.setBounds (0.08*getWidth(), AR_HEIGHT*getHeight(), 0.2*getWidth(), 0.1*getHeight());
    
        
        
        //AUDIBLE RANGE : Buttons OR Label with fixed AR text
        
        int sizeVecAR = Config::vecAudibleRanges.size();
        
        if (sizeVecAR > 1)
        {
            for (int i=0;i<sizeVecAR;i++)
            {
                m_arrARCSquares.getUnchecked(i)->setBounds( (0.3*getWidth()+i*0.12*getWidth()),
                                                           AR_HEIGHT*getHeight(),
                                                           0.11*getWidth(), 0.16*getHeight());
                
                m_arrARButtons.getUnchecked(i)->setBounds( (0.3*getWidth()+i*0.12*getWidth()),
                                                          AR_HEIGHT*getHeight(),
                                                          0.1*getWidth(), 0.15*getHeight());
                
                m_fixedARLabel.setVisible(false);
            }
            displayAudioRangeButtons(true);
        }
        else if (sizeVecAR == 1)
        {
            m_fixedARLabel.setText (static_cast<String>(Config::vecAudibleRanges[0])+"%", dontSendNotification);
            m_fixedARLabel.setBounds (0.3*getWidth(),AR_HEIGHT*0.97*getHeight(),
                                      0.3*getWidth(), 0.15*getHeight());
            
            m_fixedARLabel.setVisible(true);
            
            displayAudioRangeButtons(false);
        }
        
        
        //AMPLITUDE RATIOS FORMULA LABELS
        
        int nbAmpRatios = Config::nbAmplitudeRatios;
        int j = 0;
        int formulaIndex = j;
        
        for( int i=0;i<nbAmpRatios;i++)
        {
            
            m_arrRatiosLabels[formulaIndex]->setBounds ( (0.335*getWidth()+j*0.12*getWidth()), FORMULAS_HEIGHT*getHeight(), 0.1*getWidth(), 0.09*getHeight());
            m_arrRatiosLabels[formulaIndex]->setVisible(true);
 
            j++;
            
            if(nbAmpRatios == 2)
            {
                formulaIndex += 4;
            }
            else if(nbAmpRatios == 3)
            {
                formulaIndex += 2;
            }
            else if(nbAmpRatios == 5)
            {
                formulaIndex += 1;
            }
        
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
                                                                      ODD_HEIGHT*getHeight(),
                                                                      0.11*getWidth(), 0.16*getHeight());
                

                m_arrImgButtons[waveID-1]->setBounds ((0.3*getWidth()+j*0.12*getWidth()),
                                                     ODD_HEIGHT*getHeight(),
                                                     0.1*getWidth(), 0.15*getHeight());
                m_arrImgButtons[waveID-1]->setVisible(true);
                
            }
            else if(waveID > 5) //all partials waves
            {
                m_arrWavesCSquares.getUnchecked(waveID-1)->setBounds ((0.3*getWidth()+indexALLPartials*0.12*getWidth()), ALL_HEIGHT*getHeight(),
                                                    0.11*getWidth(), 0.16*getHeight());
                
                m_arrImgButtons[waveID-1]->setBounds (
                                                         (0.3*getWidth()+indexALLPartials*0.12*getWidth()), ALL_HEIGHT*getHeight(),0.1*getWidth(), 0.15*getHeight()
                                                    );
                
                m_arrImgButtons[waveID-1]->setVisible(true);
                
                
                indexALLPartials++;
            }
        }
        
        if (Config::partials == Partials::odd)
        {
             m_NALabel.setBounds(0.3*getWidth(),ALL_HEIGHT*0.97*getHeight(),
                                0.3*getWidth(), 0.15*getHeight());
             m_NALabel.setVisible(true);
        }
        else if (Config::partials == Partials::all)
        {
            m_NALabel.setBounds(0.3*getWidth(),ODD_HEIGHT*0.8*getHeight(),
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
                m_arrImgButtons[i]->setVisible(showODD);
            }
            for(int i=5;i<m_arrImgButtons.size();i++)
            {
                m_arrImgButtons[i]->setVisible(showALL);
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
            m_selectedAudibleRange = m_vecARPercents[index];
            
            resetEnabledARButtons();
            m_arrARButtons[index]->setEnabled(false);
        }
    }
                             
    void pressWaveButton(int index)
    {
        if(m_isQuestionMode || m_isTestMode)
        {
            m_selectedWaveTypeID = (index+1);
            
            resetEnabledWavesButtons();
            m_arrImgButtons[index]->setEnabled(false);
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
        for(int i=0;i<m_arrWavesCSquares.size();i++)
        {
            m_arrWavesCSquares[i]->setColour(Colours::transparentWhite);
        }
    }
    
    void resetFormulasDisplayed()
    {
        for(int i=0;i<m_arrRatiosLabels.size();i++)
        {
            m_arrRatiosLabels[i]->setVisible(false);
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
        for(int i=0;i<m_arrImgButtons.size();i++)
        {
            m_arrImgButtons[i]->setEnabled(true);
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
    
    
    std::vector<Image> m_arrRatioImages;
     Image img1 = ImageCache::getFromMemory (BinaryData::_1_png, BinaryData::_1_pngSize);
     Image img2 = ImageCache::getFromMemory (BinaryData::_2_png, BinaryData::_2_pngSize);
     Image img3 = ImageCache::getFromMemory (BinaryData::_3_png, BinaryData::_3_pngSize);
     Image img4 = ImageCache::getFromMemory (BinaryData::_4_png, BinaryData::_4_pngSize);
     Image img5 = ImageCache::getFromMemory (BinaryData::_5_png, BinaryData::_5_pngSize);
     Image img6 = ImageCache::getFromMemory (BinaryData::_6_png, BinaryData::_6_pngSize);
     Image img7 = ImageCache::getFromMemory (BinaryData::_7_png, BinaryData::_7_pngSize);
     Image img8 = ImageCache::getFromMemory (BinaryData::_8_png, BinaryData::_8_pngSize);
     Image img9 = ImageCache::getFromMemory (BinaryData::_9_png, BinaryData::_9_pngSize);
     Image img10 = ImageCache::getFromMemory (BinaryData::_10_png, BinaryData::_10_pngSize);
    
    
    OwnedArray<RatioFormula> m_arrRatiosLabels;
    std::vector<String> m_vecRatioStr = {"", "1.25", "1.5", "1.75", "2"};


};
