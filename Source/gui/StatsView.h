/*
  ==============================================================================

    StatsView.h
    Created: 23 Oct 2018 1:24:50am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class StatsView    : public Component
{
public:
    StatsView()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.

    }

    ~StatsView()
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
        g.drawText ("StatsView", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StatsView)
};