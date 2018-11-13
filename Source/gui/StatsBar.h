/*
  ==============================================================================

    StatsBar.h
    Created: 2 Nov 2018 12:08:34am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
 */
class StatsBar    : public Component
{
public:
    StatsBar()
    {

    }
    
    ~StatsBar()
    {
    }
    
    void paint (Graphics& g) override
    {
        
        //        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        
        float startY = std::abs(getHeight() - m_percent*getHeight());
        
        if(m_count == 0)
        {
            paintRectangle(g, Colours::black, 0, getWidth(),
                           getHeight() - 0.005*getHeight(), 0.005*getHeight() );
        }
        else if(m_percent < 0.005)
        {
            paintRectangle(g, m_colour, 0, getWidth(),
                           getHeight() - 0.005*getHeight(), 0.005*getHeight() );
        }
        else
        {
            paintRectangle(g, m_colour, 0, getWidth(),
                           startY, std::abs(getHeight() - startY ) );
        }
        
        
        //Percent text within bars
        float percentValue = ( m_percent )*100.0;
        float percentRounded = static_cast<float>( static_cast<int>(percentValue * 10.) ) / 10.;
        String bartext = static_cast<String> (percentRounded) + "%";
        
        g.setColour (Colours::black);
        g.setFont (12.0f);
        g.drawText (bartext, getLocalBounds(),
                    Justification::centred, true);
    }
    
    void resized() override
    {
        
        
    }
    
    void paintRectangle (Graphics& g, Colour c,
                         float startX, float widthX, float startY, float heightY)
    {
        
        
        Rectangle<float> rect( startX, startY, widthX, heightY );
        
        g.setColour (c);
        g.setOpacity (0.5f);
        g.drawRect( rect, 1.0f );
        g.fillRect(rect);
    }
    
    void setColour(juce::Colour c)
    {
        m_colour = c;
        this->repaint();
    }
    
    void updateValues(float percent, int count)
    {
        m_percent = percent;
        m_count = count;
        this->repaint();
    }

    

private:
    float m_percent = 0;
    int m_count = 0;
    
    juce::Colour m_colour = Colours::darkred;
};

