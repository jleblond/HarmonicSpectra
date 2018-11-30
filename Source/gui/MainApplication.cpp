/*
  ==============================================================================

    MainApplication.cpp
    Created: 31 Oct 2018 8:23:57pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "MainApplication.h"



MainApplication::MainApplication()
{
    //setSize (WIDTH, HEIGHT);
    //setLookAndFeel( m_LF );
    
        
    addAndMakeVisible(m_headerView);
    
    addAndMakeVisible(m_userConfigView);
    addAndMakeVisible(m_createUserButton);
    m_createUserButton.setButtonText("NEXT");
    m_createUserButton.addListener(this);
        
    addAndMakeVisible(m_exerciseConfigView);
    m_exerciseConfigView.setVisible(false);
    addAndMakeVisible(m_startSessionButton);
    m_startSessionButton.setButtonText("START");
    m_startSessionButton.addListener(this);
    m_startSessionButton.setVisible(false);
    
    addAndMakeVisible(m_mainWindow);
    m_mainWindow.setVisible(false);
    addAndMakeVisible(m_mainWindow.m_statsView);
    m_mainWindow.m_statsView.setVisible(false);
    
    addAndMakeVisible(m_settingsButton);
    m_settingsButton.setColour(TextButton::buttonColourId, Colour (0xff003F5F));
    m_settingsButton.setColour(TextButton::textColourOffId, Colours::white);
    m_settingsButton.addListener(this);
    m_settingsButton.setVisible(true);
    
    addAndMakeVisible(m_notepadButton);
    m_notepadButton.setColour(TextButton::buttonColourId, Colour (0xff003F5F));
    m_notepadButton.setColour(TextButton::textColourOffId, Colours::white);
    m_notepadButton.addListener(this);
    m_notepadButton.setVisible(false);
    
    addAndMakeVisible(m_endSessionButton);
    m_endSessionButton.setColour(TextButton::buttonColourId, Colour (0xff003F5F));
    m_endSessionButton.setColour(TextButton::textColourOffId, Colours::white);
    m_endSessionButton.addListener(this);
    m_endSessionButton.setVisible(false);
    
}
    
MainApplication::~MainApplication()
{
    //delete m_LF;
}
    
void MainApplication::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (Colours::white);
    g.setFont (14.0f);
    g.drawText ("MainApplication", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}
    
void MainApplication::resized()
{
    m_notepadButton.setBounds (getWidth() - 0.1 -  3*ENDSESSIONBUTTON_WIDTH*getWidth(), 0, ENDSESSIONBUTTON_WIDTH*getWidth(), 0.03*getHeight());
    m_settingsButton.setBounds (getWidth() - 0.08 -  2*ENDSESSIONBUTTON_WIDTH*getWidth(), 0, ENDSESSIONBUTTON_WIDTH*getWidth(), 0.03*getHeight());
    
    m_endSessionButton.setBounds (getWidth() - 0.05 -  ENDSESSIONBUTTON_WIDTH*getWidth(), 0, ENDSESSIONBUTTON_WIDTH*getWidth(), 0.03*getHeight());
    
    Rectangle<int> area (getLocalBounds());
    m_headerView.setBounds (area.removeFromTop( HEADER_PERCENT_HEIGHT*getHeight()));
        
    Rectangle<int> area1 (area);
    m_createUserButton.setBounds (area1.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
    m_userConfigView.setBounds(area1);
        
    Rectangle<int> area2 (area);
    m_startSessionButton.setBounds (area2.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
    m_exerciseConfigView.setBounds(area2);
        
    Rectangle<int> area3 (area);
    m_mainWindow.m_statsView.setBounds(area3.removeFromBottom(STATSVIEW_HEIGHT*getHeight()));
    m_mainWindow.setBounds(area3);
        
}
    
void MainApplication::buttonClicked(Button* button)
{
    if(button == &m_createUserButton)
    {
        String username = m_userConfigView.getTextFieldValue();
        Config::user = std::make_shared<User>(username);
        m_headerView.setUserLabel(username);
        
        displayPanel(1);
    }
    if(button == &m_startSessionButton)
    {
        initSession();
        
        displayPanel(2);
        
        m_sessionTimer.startTimer();
    }
    
    if(button == &m_endSessionButton)
    {
        m_sessionTimer.stopTimer();
        
        assert(Config::user != nullptr);
        assert(Config::user->getLastSession() != nullptr);
        auto lastSession = Config::user->getLastSession();
        
        lastSession->getReport()->timePractised = CustomDate::convertTimeStr(m_sessionTimer.durationInS());
        
        if(lastSession->getStats().questionsCount>0)
        {
            lastSession->getReport()->statsImg = m_mainWindow.m_statsView.createComponentSnapshot(m_mainWindow.m_statsView.getLocalBounds(), false);
            FileOutputStream stream (File ( Config::reportDirectory.getFullPathName()+"/stats_"+CustomDate::getStrFormatCurrentTime()+".png"));
            PNGImageFormat pngWriter;
            pngWriter.writeImageToStream(lastSession->getReport()->statsImg, stream);
            
            
            ReportBuilder::saveReport();
        }
        
        m_sessionTimer.resetTimer();

        m_mainWindow.resetAll(); //includes both GUI and model m_ values (for waveType and audibleRange)
        displayPanel(3);
    }

    if(button == &m_settingsButton)
    {
        DialogWindow::showModalDialog ("Settings", &m_settingsPanel, nullptr, Colours::white, true, false, false);
    }
    
    if(button == &m_notepadButton)
    {
        DialogWindow::showModalDialog ("Notepad", &m_notepadPanel, nullptr, Colours::white, true, false, false);
    }
    
}

void MainApplication::displayPanel(int panelNb)
{
    switch(panelNb)
    {
        case 1: //Pressing 'create user' -> Exercise config
            showUserConfig(false);
            showExerciseConfig(true);
            break;
        case 2: //Pressing 'new session' -> Main Window
            showExerciseConfig(false);
            showMainWindow(true);
            m_notepadButton.setVisible(true);
            m_endSessionButton.setVisible(true);
            m_mainWindow.updateMatrixView();
            m_mainWindow.m_statsView.updateBarsVisibility();
            m_mainWindow.displayPanel(1);
            break;
        case 3: //Pressing 'end session' -> ExerciseConfig view
            showMainWindow(false);
            showExerciseConfig(true);
            m_notepadButton.setVisible(false);
            m_endSessionButton.setVisible(false);
            break;
    };
}
    
void MainApplication::showUserConfig(bool isVisible)
{
    m_userConfigView.setVisible(isVisible);
    m_createUserButton.setVisible(isVisible);
}
    
void MainApplication::showExerciseConfig(bool isVisible)
{
    m_exerciseConfigView.setVisible(isVisible);
    m_startSessionButton.setVisible(isVisible);
}

void MainApplication::showMainWindow(bool isVisible)
{
    m_mainWindow.setVisible(isVisible);
    m_mainWindow.m_statsView.setVisible(isVisible);
}


void MainApplication::initSession()
{
    Config::partials = m_exerciseConfigView.getPartials();
    Config::nbAmplitudeRatios = m_exerciseConfigView.getNbAmplitudeRatios();
    Config::vecAudibleRanges = m_exerciseConfigView.getVecAudibleRange();
    Config::baseFreq = m_exerciseConfigView.getBaseFreq();
        Synthesis::Instance().setCurrentFundFrequency(Config::baseFreq);
    
    assert(Config::user != nullptr);
    Config::user->createSession(Config::partials, Config::nbAmplitudeRatios, Config::baseFreq, Config::vecAudibleRanges);
    
    assert(Config::user->getLastSession() != nullptr);
    auto lastSession = Config::user->getLastSession();
    lastSession->getStats().maxScore = StatsBuilder::Instance().calculateMaxScore();
    
    lastSession->attachReport(ReportBuilder::createReport());
}
