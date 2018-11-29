/*
  ==============================================================================

    Notepad.h
    Created: 28 Nov 2018 6:55:18pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"
#include "../../core/Config.h"
//==============================================================================
/*
*/
class Notepad    : public Component,
                   public Button::Listener
{
public:
    Notepad()
    {
        setSize(0.4*getParentWidth(), 0.5*getParentHeight());
        
        
        addAndMakeVisible(m_textEditor);
      //  m_textEditor.setSize(350,300);
        m_textEditor.setMultiLine(true);
        m_textEditor.setReturnKeyStartsNewLine (true);
        
        addAndMakeVisible(m_saveCommentButton);
        m_saveCommentButton.addListener(this);

    }

    ~Notepad()
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
        m_textEditor.setBounds (0.15*getWidth(), 0.2*getHeight(), 0.7*getWidth(), 0.3*getHeight());
        m_saveCommentButton.setBounds (0.4*getWidth(), 0.51*getHeight(), 0.2*getWidth(), 0.1*getHeight());

    }
    
    void buttonClicked(Button* button) override
    {
        if (button == &m_saveCommentButton)
        {
            std::shared_ptr<Comment> c = std::make_shared<Comment>();
            c->text = m_textEditor.getText();
           // c->date
            
            assert(Config::user != nullptr);
            assert(Config::user->getLastSession() != nullptr);
            assert(Config::user->getLastSession()->getReport() != nullptr);
            
            std::shared_ptr<Report> report = Config::user->getLastSession()->getReport();
            report->comments.push_back(c);
            
            c->print();
            
            m_textEditor.clear();
            
        }
    }

private:
    //Label
    TextEditor m_textEditor;
    TextButton m_saveCommentButton{"Save!"};
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Notepad)
};
