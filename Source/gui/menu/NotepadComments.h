/*
  ==============================================================================

    NotepadComments.h
    Created: 29 Nov 2018 8:52:23pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../core/Config.h"
//==============================================================================
/*
*/
class NotepadComments    : public Component
{
public:
    NotepadComments()
    {
        setSize (0.24*getParentWidth(), 0.3*getParentHeight());
    }

    ~NotepadComments()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
    }

    void resized() override
    {

    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NotepadComments)
};
