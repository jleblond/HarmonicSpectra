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

#include "Note.h"

#include <algorithm> /*std::count*/

//==============================================================================
/*
*/


//const float LINE_HEIGHT = 30;  in Note.h
const float LINE_WORDS_LENGTH = 40;
const float NOTES_SPACING = 5;


class NotepadComments    : public Component
{
public:
    NotepadComments()
    {
        setSize (0.27*getParentWidth(), LINE_HEIGHT);
        addAndMakeVisible(m_label);
    }

    
    ~NotepadComments()
    {
        
    }

    
    void paint (Graphics& g) override
    {
        g.fillAll (Colour(0xff00011B));
        
        loadNotes();
    }

    
    void resized() override
    {
        int nbNotes = m_notes.size();
        
        if(nbNotes > 0)
        {
            assert(Config::user != nullptr);
            assert(Config::user->getLastSession() != nullptr);
            auto comments = Config::user->getLastSession()->getReport()->comments;
            
            for (int i=(nbNotes-1); i>=0; i--)
            {
                m_notes[i]->setBounds(0, m_notesStartY[i]+i*NOTES_SPACING, getWidth(), getNoteHeight(comments[i]->text));
            }
        }
        else
        {
            m_label.setBounds (0.3*getWidth(), 0.3*getHeight(), 0.5*getWidth(), 0.4*getHeight());
        }
       
    }
    
    
    void loadNotes()
    {
        m_notes.clear();
        m_notesStartY.clear();
        float height = NOTES_SPACING;
        
        assert(Config::user != nullptr);
        assert(Config::user->getLastSession() != nullptr);
        auto comments = Config::user->getLastSession()->getReport()->comments;
        
        m_notesStartY.push_back(0);
        
        for (auto& c : comments)
        {
            Note* n = new Note();
            m_notes.add (n);
            n->setNote(c->date, c->text);
            addAndMakeVisible(n);
            
            height += getNoteHeight(c->text);
            m_notesStartY.push_back(height);
        }
        
        int nbComments = comments.size();
        
        if(nbComments == 0)
        {
            setSize(getWidth(), LINE_HEIGHT*2);
        }
        else
        {
            setSize(getWidth(), height+(nbComments*NOTES_SPACING));
        }
        
        resized();
        
    }
    
    
    float getNoteHeight(const String& txt)
    {
        //count # of \n
        std::string s = txt.toStdString();
        size_t count = std::count(s.begin(), s.end(), '\n');
        
        std::cout<<count<<std::endl;
        
        float addSpace = 0;
        if(count != 0)
        {
            addSpace = count*LINE_WORDS_LENGTH/3;
        }
        
        float linesQt = (txt.length()+addSpace)/LINE_WORDS_LENGTH+2;
        return linesQt*LINE_HEIGHT;
    }

    
private:
    OwnedArray<Note> m_notes;
    std::vector<float> m_notesStartY;
    Label m_label{{}, "[No user notes found]"};
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NotepadComments)
};
