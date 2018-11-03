/*
  ==============================================================================

    MainWindow.h
    Created: 23 Oct 2018 3:01:23am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once



class MainWindow : public Component
{
public:
    MainWindow()
    {
         addAndMakeVisible(m_allLabel);
         addAndMakeVisible(m_oddLabel);
         addAndMakeVisible(m_arLabel);
        
        
        for (int i = 0; i < 5; i++)
        {
            TextButton* newARButton = new TextButton();
            
            String buttonText = static_cast<String>(m_vecARPercents[i])+"%";
            newARButton->setButtonText(buttonText);
            
            m_arrARButtons.add (newARButton);
            
            //add listener
            
            addAndMakeVisible (newARButton);
        }
        
       // displayAudioRangeSection(false);
        
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
        m_allLabel.setBounds (0.08*getWidth(), 0.1*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_oddLabel.setBounds (0.08*getWidth(), 0.3*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_arLabel.setBounds (0.08*getWidth(), 0.6*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        
        for(int i=0;i<5;i++)
        {
            m_arrARButtons.getUnchecked(i)->setBounds( (0.3*getWidth()+i*0.12*getWidth()),
                                                        0.6*getHeight(),
                                                       0.1*getWidth(), 0.15*getHeight());
        }
    }

    void displayAudioRangeSection(bool isVisible)
    {
        m_arLabel.setVisible(isVisible);
        
        for(int i=0;i<5;i++)
        {
            m_arrARButtons.getUnchecked(i)->setVisible(isVisible);
        }
    }
    
protected:
    TextButton m_all1Button, m_all2Button, m_all3Button, m_all4Button, m_all5Button;
    TextButton m_odd1Button, m_odd2Button, m_odd3Button, m_odd4Button, m_odd5Button;
    
    OwnedArray<TextButton>  m_arrARButtons;
    std::vector<int> m_vecARPercents {10, 25, 50, 75, 100};
    
    Label m_allLabel{{}, "ALL"}, m_oddLabel{{}, "ODD"}, m_arLabel{{}, "AUDIBLE RANGE"};
};

