/*
  ==============================================================================

    SettingsPanel.h
    Created: 27 Nov 2018 4:07:57pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../../JuceLibraryCode/JuceHeader.h"

#include "../../core/Config.h"

#include "Volume.h"

//==============================================================================
/*
*/
class SettingsPanel    : public Component,
                         public Button::Listener
{
public:
    enum RadioButtonIds
    {
        soundDurationButtons = 2001
    };
    
    
    SettingsPanel()
    {
        setSize(400, 400);
        

        // SOUND DURATION
        
        addAndMakeVisible (m_soundDurationLabel);
        
        addAndMakeVisible (m_dur05Button);
        addAndMakeVisible (m_dur1Button);
        addAndMakeVisible (m_dur2Button);
        
        m_dur05Button.setRadioGroupId (soundDurationButtons);
        m_dur1Button.setRadioGroupId (soundDurationButtons);
        m_dur2Button.setRadioGroupId (soundDurationButtons);
        
        m_dur05Button.setClickingTogglesState (true);
        m_dur1Button.setClickingTogglesState (true);
        m_dur2Button.setClickingTogglesState (true);
        
        m_dur05Button.addListener(this);
        m_dur1Button.addListener(this);
        m_dur2Button.addListener(this);
        
        m_dur1Button.triggerClick();

        
        // SAVE REPORT TO DIRECTORY
        
        addAndMakeVisible (m_saveReportDirectoryLabel);
        m_saveReportDirectoryLabel.attachToComponent(&m_directoryPath, false);
        addAndMakeVisible (m_directoryPath);
        m_directoryPath.setText(Config::reportDirectory.getFullPathName(), false);
        m_directoryPath.setReadOnly(true);
        addAndMakeVisible (m_changeDirectoryButton);
        m_changeDirectoryButton.addListener(this);
        
        
        addAndMakeVisible (m_volumeComponent);
    }

    ~SettingsPanel()
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
        m_soundDurationLabel.setBounds(0.05*getWidth(), 0.1*getHeight(), 0.6*getWidth(), 0.07*getHeight());
        m_dur05Button.setBounds(0.05*getWidth(), 0.17*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_dur1Button.setBounds(0.15*getWidth(), 0.17*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        m_dur2Button.setBounds(0.25*getWidth(), 0.17*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        
        m_saveReportDirectoryLabel.setBounds (0.05*getWidth(), 0.3*getHeight(), 0.6*getWidth(), 0.07*getHeight());
        m_directoryPath.setBounds (0.05*getWidth(), 0.4*getHeight(), 0.8*getWidth(), 0.07*getHeight());
        m_changeDirectoryButton.setBounds (0.85*getWidth(), 0.4*getHeight(), 0.1*getWidth(), 0.07*getHeight());
        
        m_volumeComponent.setBounds (0.05*getWidth(), 0.6*getHeight(), 0.9*getWidth(), 0.3*getHeight());

    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &m_dur05Button)
        {
            Config::soundDuration = 500;
        }
        
        if(button == &m_dur1Button)
        {
            Config::soundDuration = 1000;
        }
        
        if(button == &m_dur2Button)
        {
            Config::soundDuration = 2000;
        }
        
        if(button == &m_changeDirectoryButton)
        {
            changeDirectory();
            String path = Config::reportDirectory.getFullPathName();
            m_directoryPath.setText(path, dontSendNotification);
        }
        
    }
    
    void changeDirectory()
    {
        FileChooser fc ("Save the report in folder..",
                        File::getSpecialLocation(File::userDesktopDirectory),
                        "*",
                        true);
        
        if (fc.browseForDirectory())
        {
            File chosenDirectory = fc.getResult();
            Config::reportDirectory = chosenDirectory;
            //reportDirectoryPath = chosenDirectory.getFullPathName();
        }
        
    }
    
    

private:
    Label m_soundDurationLabel { {}, "Sound duration (s): "};
    TextButton m_dur05Button {"0.5"};
    TextButton m_dur1Button {"1"};
    TextButton m_dur2Button {"2"};
    
    Label m_saveReportDirectoryLabel {{}, "Save report to directory..."};
    TextEditor m_directoryPath;
    TextButton m_changeDirectoryButton {"..."};
    
    Volume m_volumeComponent;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SettingsPanel)
};
