/*
  ==============================================================================

    HeaderView.h
    Created: 23 Oct 2018 1:22:53am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class HeaderView : public Component,
                   public Button::Listener
{
public:
    HeaderView()
    {
        menu1.setButtonText(MENU_1);
        menu1.addListener(this);
        addAndMakeVisible(menu1);
        menu1.setColour(TextButton::buttonColourId, juce::Colours::white);
        menu1.setVisible(false);
        
        menu2.setButtonText(MENU_2);
        menu2.addListener(this);
        addAndMakeVisible(menu2);
        menu2.setColour(TextButton::buttonColourId, juce::Colours::white);
        
//        g_EndSessionButton.setButtonText(MENU_3);
//        // g_EndSessionButton.addListener(this);
//        addAndMakeVisible(g_EndSessionButton);
//        g_EndSessionButton.setColour(TextButton::buttonColourId, juce::Colours::white);
//        g_EndSessionButton.setVisible(false);
//        // g_EndSessionButton.setEnabled(false);
        
        
        addAndMakeVisible(mUserLabel);
        mUserLabel.setJustificationType(juce::Justification::right);
        mUserLabel.setColour(juce::Label::textColourId, juce::Colours::white);
        
    
        
        
        
        Image logoImage = ImageCache::getFromMemory (BinaryData::logo_png, BinaryData::logo_pngSize);
        
        mLogoButton.setImages (true, true, true,
                               logoImage, 0.7f, Colours::transparentBlack,
                               logoImage, 1.0f, Colours::transparentBlack,
                               logoImage, 1.0f, Colours::lightgrey.withAlpha (0.8f),
                               0.5f);
        
        mLogoButton.setTooltip ("Information about the Inner Ear Project");
        addAndMakeVisible(mLogoButton);
        mLogoButton.addListener(this);
        
    }
    
    ~HeaderView()
    {
        delete mTextEditor;
    }
    
    void paint(Graphics& g)override
    {
        g.fillAll(Colour (0xff001331));
        
        g.setColour (Colours::white);
        
        g.setFont (26.0f);
        g.drawText (TITLE, 0.4*getWidth()+15, getHeight()/2, getWidth(), getHeight()/2,
                    Justification::left, true);
    
    }
    
    void resized() override
    {
        float menuxoffset=getWidth()*0.75;
        float elementheight=getHeight()/6;
        float elementwidth=getWidth()/12;
        
        Rectangle<int> area = getLocalBounds();
        
     
        mLogoButton.setBounds(0.08*getWidth(), 0*getHeight()-20, 120, 140);
        
        //USERNAME
        mUserLabel.setBounds(menuxoffset-10, 3*elementheight, 3*elementwidth, elementheight);
        //INFO
        // menu2.setBounds(menuxoffset-45, 0, elementwidth, elementheight);
        //ADD COMMENT
        menu1.setBounds(menuxoffset+elementwidth-5, 0, elementwidth, elementheight);
        //END SESSION
       // g_EndSessionButton.setBounds(menuxoffset+2*elementwidth, 0, elementwidth, elementheight);
        

    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &mLogoButton)
        {
            infoDialogBox();
        }
        
        if(button== &menu1)
        {
            std::cout<<"menu1"<<std::endl;
            commentDialogBox();
            
            
        }
        else if(button == &menu2)
        {
            std::cout<<"menu2"<<std::endl;
            infoDialogBox();
            
        }
    
        
    }
    
    void displayCommentButton(bool b)
    {
        menu1.setVisible(b);
    }
    
    void displayEndSessionButton(bool b)
    {
        //g_EndSessionButton.setVisible(b);
    }
    
    
    void setUserLabel(String user)
    {
        if( user.toStdString().size() == 0 )
        {
            mUserLabel.setText("user: [  ]     ", dontSendNotification);
        }
        else
            mUserLabel.setText("user: "+user, dontSendNotification);
    }
    
    void commentDialogBox()
    {
        juce::AlertWindow *alert = new juce::AlertWindow ("Comments","Comments will be added to your session report.", juce::AlertWindow::NoIcon );
        alert->setColour(AlertWindow::backgroundColourId, Colours::black);
        
        alert->addCustomComponent(mTextEditor);
        mTextEditor->setSize(350,300);
        mTextEditor->setMultiLine(true);
        mTextEditor->setReturnKeyStartsNewLine (true);
        
        alert->addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
        alert->addButton ("Cancel", 0, KeyPress (KeyPress::escapeKey, 0, 0));
        
        alert->setBounds(430,200,425, 500);
        
        int returnValue = alert->runModalLoop();
        delete alert;
        
        if(returnValue)
        {
            String commentText = mTextEditor->getText();
//            (g_User.getLastSession())->addComment(commentText);
//            (g_User.getLastSession())->printAllComments();
        }
        
        mTextEditor->clear();
        
       
    }
    
    void infoDialogBox()
    {
        String creditsStr = String(CharPointer_UTF8 (
                                                     "Ear Training software implemented by Jasmine Leblond-Chartrand     \nfor Concordia's Music Department, Montreal, 2018  \n\nThe Inner Ear Project is supervised by:\n  Dr. Eldad Tsabary at Concordia University\nin collaboration with:\n  Dr. David Ogborn at McMaster University\n  Dr. Andrea Szigetvári at Liszt Academy of Music  \n")
                                   );
        
        
        AlertWindow::AlertIconType icon = AlertWindow::InfoIcon;
        setColour(AlertWindow::backgroundColourId, Colours::black);
        
        
        AlertWindow::showMessageBoxAsync (icon,
                                          "Inner Ear [Harmonic Spectrum] 1.0 (MacOSX version)",
                                          creditsStr,
                                          "OK");
        
       
    }
    
    
    
private:
    
    const String TITLE=" HARMONIC SPECTRUM ";
    const String SUBTITLE="INNER EAR";
    
    TextButton menu1;
    const String MENU_1="Add Comment";
    
    TextButton menu2;
    const String MENU_2="ABOUT";
    
    //string for g_EndSessionButton
    const String MENU_3="END SESSION";
    
    Label mUserLabel;
    
    TextEditor* mTextEditor = new TextEditor("Enter your comment here: ");
    
    ImageButton mLogoButton;
    Image mLogo;
    ImageComponent mLogoImageComponent;
};
