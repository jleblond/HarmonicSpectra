/*
  ==============================================================================

    ExerciseView.h
    Created: 23 Oct 2018 1:26:34am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../core/ExerciseBuilder.h"
#include "../core/Config.h"
//==============================================================================
/*
*/
class QuestionsView    : public Component,
                         public Button::Listener
{
public:
    QuestionsView()
    {
        addAndMakeVisible(m_newQuestionButton);
        m_newQuestionButton.addListener(this);
    }

    ~QuestionsView()
    {
    }

    void paint (Graphics& g) override
    {

        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);

        g.setColour (Colours::white);
        g.setFont (14.0f);
//        g.drawText ("QuestionsView", getLocalBounds(),
//                    Justification::centred, true);
    }

    void resized() override
    {
        m_newQuestionButton.setBounds (0.1*getWidth(), 0.1*getHeight(), 0.2*getWidth(), 0.15*getHeight());

    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &m_newQuestionButton)
        {
            ExerciseBuilder::Instance().buildExercise();
        }
        
    }

private:
    TextButton m_newQuestionButton{"NEW QUESTION"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QuestionsView)
};
