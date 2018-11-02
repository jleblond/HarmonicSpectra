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
    setSize (WIDTH, HEIGHT);
    setLookAndFeel( m_LF );
        
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
        
        
}
    
MainApplication::~MainApplication()
{
    delete m_LF;
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
    Rectangle<int> area (getLocalBounds());
    m_headerView.setBounds (area.removeFromTop( HEADER_PERCENT_HEIGHT*getHeight()));
        
    Rectangle<int> area1 (area);
    m_createUserButton.setBounds (area1.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
    m_userConfigView.setBounds(area1);
        
    Rectangle<int> area2 (area);
    m_startSessionButton.setBounds (area2.removeFromBottom(BOTTOM_BUTTONS_HEIGHT*getHeight()));
    m_exerciseConfigView.setBounds(area2);
        
    Rectangle<int> area3 (area);
        
}
    
void MainApplication::buttonClicked(Button* button)
{
    if(button == &m_createUserButton)
    {
        String username = m_userConfigView.getTextFieldValue();
        Config::user = std::make_shared<User>(username);
        
        showUserConfig(false);
        showExerciseConfig(true);
    }
    if(button == &m_startSessionButton)
    {
        
        showExerciseConfig(false);

    }
    
    if(button == &m_endSessionButton)
    {
        //hide curr windows
        
        //report generation options
        
        showUserConfig(true);
    }
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
    

