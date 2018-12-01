/*
  ==============================================================================

    Note.h
    Created: 1 Dec 2018 1:07:36am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
const float LINE_HEIGHT = 30;

class Note    : public Component
{
public:
    Note()
    {
        addAndMakeVisible(m_dateLabel);
        addAndMakeVisible(m_noteLabel);
    }

    ~Note()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);

        g.setColour (Colours::white);
        g.setFont (14.0f);

    }

    void resized() override
    {
        m_dateLabel.setBounds(0, 0, getWidth(), LINE_HEIGHT);
        m_noteLabel.setBounds(0, (LINE_HEIGHT+5), getWidth(), getHeight()-(LINE_HEIGHT+5));

    }
    
    void setNote(String date, String comment)
    {
        m_dateLabel.setText(date, dontSendNotification);
        m_noteLabel.setText(comment, dontSendNotification);
        
        repaint();
    }

private:
    Label m_dateLabel{{}, ""};
    Label m_noteLabel{{}, ""};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Note)
};
