/*
  ==============================================================================

    MainApplication.h
    Created: 23 Oct 2018 1:28:55am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "HeaderView.h"


const int HEIGHT = 700;
const int WIDTH = 900;


class MainApplication    : public Component,
                            public Button::Listener
{
public:
    MainApplication()
    {
        setSize (WIDTH, HEIGHT);
        setLookAndFeel( m_LF );
        
        addAndMakeVisible(mHeader);
        
    }

    ~MainApplication()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("MainApplication", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    LookAndFeel *m_LF = new LookAndFeel_V4( (LookAndFeel_V4::getLightColourScheme() ) );
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainApplication)
};
