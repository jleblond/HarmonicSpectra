/*
  ==============================================================================

    ColourSquare.h
    Created: 4 Nov 2018 10:30:44pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/

class ColourSquare    : public Component
{
public:
    ColourSquare()
    {

    }

    ~ColourSquare()
    {
        
    }

    void paint (Graphics& g) override
    {
//        auto area = getLocalBounds().toFloat().reduced (0.5f);
//        float cornerSize = 0.f;
//        g.setColour (m_colour);
//        g.fillRoundedRectangle (area, cornerSize);
//        //g.setColour (m_colour);
//        g.drawRoundedRectangle (area, cornerSize, 200.f);
        
        
        g.setColour (m_colour);
        g.drawRect (getLocalBounds(), 0.05*getWidth());   // draw an outline around the component

    }

    void resized() override
    {

    }
    
    void setColour(juce::Colour c)
    {
        m_colour = c;
        this->repaint();
    }

    
private:
    juce::Colour m_colour = Colours::transparentWhite;
    
};
