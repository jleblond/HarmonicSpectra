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
#include "../../utils/CustomDate.h"

#include "NotepadComments.h"
//==============================================================================
/*
*/
class Notepad    : public Component,
                   public Button::Listener
{
public:
    Notepad()
    {
        setSize(0.4*getParentWidth(), 0.7*getParentHeight());
        
        addAndMakeVisible(m_label);
        
        addAndMakeVisible(m_textEditor);
      //  m_textEditor.setSize(350,300);
        m_textEditor.setMultiLine(true);
        m_textEditor.setReturnKeyStartsNewLine (true);
        
        addAndMakeVisible(m_saveCommentButton);
        m_saveCommentButton.addListener(this);
        
        addAndMakeVisible(m_commentsViewport);
        addAndMakeVisible(m_npComments);
        m_commentsViewport.setViewedComponent (&m_npComments);
        m_commentsViewport.setScrollBarsShown(true, false);

    }

    ~Notepad()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colour(0xff00011B));

        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
    }

    void resized() override
    {
        m_label.setBounds (0.15*getWidth(), 0.05*getHeight(), 0.7*getWidth(), 0.1*getHeight());
        m_textEditor.setBounds (0.15*getWidth(), 0.15*getHeight(), 0.7*getWidth(), 0.25*getHeight());
        m_saveCommentButton.setBounds (0.4*getWidth(), 0.4*getHeight(), 0.2*getWidth(), 0.1*getHeight());
        
        m_commentsViewport.setBounds (0.15*getWidth(), 0.6*getHeight(), 0.7*getWidth(), 0.3*getHeight());

    }
    
    void buttonClicked(Button* button) override
    {
        if (button == &m_saveCommentButton)
        {
            std::shared_ptr<Comment> c = std::make_shared<Comment>();
            c->text = m_textEditor.getText();
            c->date = CustomDate::getStrCurrentTime();
            
            assert(Config::user != nullptr);
            assert(Config::user->getLastSession() != nullptr);
            assert(Config::user->getLastSession()->getReport() != nullptr);
            
            std::shared_ptr<Report> report = Config::user->getLastSession()->getReport();
            report->comments.push_back(c);
            
            c->print();
            
            m_textEditor.clear();
            m_npComments.loadNotes();
            
        }
    }

private:
    Label m_label{{}, "Your notes will be added to your session report."};
    TextEditor m_textEditor;
    TextButton m_saveCommentButton{"Save!"};
    
    Viewport m_commentsViewport;
    NotepadComments m_npComments;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Notepad)
};
