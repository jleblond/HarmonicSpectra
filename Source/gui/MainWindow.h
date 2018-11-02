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
        m_allLabel.setBounds (0.05*getWidth(), 0.1*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_oddLabel.setBounds (0.05*getWidth(), 0.3*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        m_arLabel.setBounds (0.05*getWidth(), 0.6*getHeight(), 0.2*getWidth(), 0.1*getHeight());
    }

protected:
    TextButton m_all1Button, m_all2Button, m_all3Button, m_all4Button, m_all5Button;
    TextButton m_odd1Button, m_odd2Button, m_odd3Button, m_odd4Button, m_odd5Button;
    TextButton m_ar10Button, m_ar25Button, m_ar50Button, m_ar75Button, m_ar100Button;
    
    Label m_allLabel{{}, "ALL"}, m_oddLabel{{}, "ODD"}, m_arLabel{{}, "AUDIBLE RANGE"};
};

