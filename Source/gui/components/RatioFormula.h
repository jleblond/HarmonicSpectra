/*
  ==============================================================================

    RatioFormula.h
    Created: 14 Nov 2018 4:48:44pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class RatioFormula    : public Component
{
public:
    
    RatioFormula(String exp) : m_expStr(exp)
    {
        m_numStr = "1";
        m_baseStr = "x";
        
        addAndMakeVisible(m_numerator);
        addAndMakeVisible(m_base);
        addAndMakeVisible(m_exponent);
        
        m_exponent.setFont(10);
        
        updateValues();
    }
    
    RatioFormula()
    {
        m_numStr = "1";
        m_baseStr = "x";
        m_expStr = "";
        
        addAndMakeVisible(m_numerator);
        addAndMakeVisible(m_base);
        addAndMakeVisible(m_exponent);
        
        updateValues();
    }
    

    ~RatioFormula()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (m_backgroundColour);   // clear the background

        g.setColour (Colours::black);

        
        // g.drawHorizontalLine(<#int y#>, <#float left#>, <#float right#>)
        
        g.drawLine (0, 0.5*getHeight(), 0.3*getWidth(), 0.5*getHeight(), 0.02*getHeight()) ;
    }

    void resized() override
    {
        m_numerator.setBounds (0, 0, getWidth(), 0.3*getHeight());
        
        m_base.setBounds (0, 0.6*getHeight(), 0.6*getWidth(), 0.3*getHeight());
        m_exponent.setBounds(0.15*getWidth(), 0.55*getHeight(), 0.5*getWidth(), 0.3*getHeight());

    }
    
    
    
    void setExp(String exp)
    {
        m_expStr = exp;
        
        updateValues();
    }
    
    void setBackgroundColour(juce::Colour bckgColour)
    {
        m_backgroundColour = bckgColour;
        repaint();
    }

private:
    Label m_numerator;
    Label m_base;
    Label m_exponent;
    
    String m_numStr, m_baseStr, m_expStr;
    
    juce::Colour m_backgroundColour = Colours::white;
    
    
    void updateValues()
    {
        m_numerator.setText(m_numStr, dontSendNotification);
        m_base.setText(m_baseStr, dontSendNotification);
        m_exponent.setText(m_expStr, dontSendNotification);
        
        repaint();
    }
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RatioFormula)
};
