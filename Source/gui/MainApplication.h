/*
  ==============================================================================

    MainApplication.h
    Created: 23 Oct 2018 1:28:55am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "../core/Config.h"
#include "../core/StatsBuilder.h"
#include "../core/ReportBuilder.h"

#include "HeaderView.h"
#include "UserConfigView.h"
#include "ExerciseConfigView.h"
#include "MainWindow.h"
#include "StatsView.h"

#include "menu/SettingsPanel.h"
#include "menu/Notepad.h"

#include "../utils/CustomTimer.h"
#include "../utils/CustomDate.h"


//const int HEIGHT = 700;
//const int WIDTH = 900;

const float HEADER_PERCENT_HEIGHT = 0.15;

const float BOTTOM_BUTTONS_HEIGHT = 0.20; //height relative to espace left without header

const float STATSVIEW_HEIGHT = 0.35;

const float ENDSESSIONBUTTON_WIDTH = 0.10;


class MainApplication    :  public Component,
                            public Button::Listener
{
public:
    
    MainApplication();

    ~MainApplication();

    void paint (Graphics& g) override;

    void resized() override;

    void buttonClicked(Button* button) override;
    
    void displayPanel(int panelNb);
    
    void showUserConfig(bool isVisible);
    
    void showExerciseConfig(bool isVisible);
    
    void showMainWindow(bool isVisible);
    
    void initUser();
    
    void initSession();
    
    void createSnapshotFromStats();

    
protected:
   // LookAndFeel *m_LF = new LookAndFeel_V4( (LookAndFeel_V4::getLightColourScheme() ) );

    HeaderView m_headerView;
    UserConfigView m_userConfigView;
    ExerciseConfigView m_exerciseConfigView;
    
    TextButton m_createUserButton;
    TextButton m_startSessionButton;
    TextButton m_endSessionButton{"SESSION [X]"};
    TextButton m_settingsButton{"Settings"};
    TextButton m_notepadButton{"Notepad"};
   
    MainWindow m_mainWindow;
    
    SettingsPanel m_settingsPanel;
    Notepad m_notepadPanel;
    
    CustomTimer m_sessionTimer;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainApplication)
};
