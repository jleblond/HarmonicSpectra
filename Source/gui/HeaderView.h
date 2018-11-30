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
    }
    
    void buttonClicked(Button* button) override
    {
        if(button == &mLogoButton)
        {
            infoDialogBox();
        }
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
    
    
    void infoDialogBox()
    {
        String creditsStr = String(CharPointer_UTF8 (
                                                     "Ear Training software implemented by Jasmine Leblond-Chartrand     \nfor Concordia's Music Department, Montreal, 2018  \n\nThe Inner Ear Project is supervised by:\n  Dr. Eldad Tsabary at Concordia University\nin collaboration with:\n  Dr. David Ogborn at McMaster University\n  Dr. Andrea Szigetvári at Liszt Academy of Music  \n\nThe Inner Ear team: Eldad Tsabary, David Ogborn, Andrea Szigetvári, \nJasmine Leblond-Chartrand, Luis Navarro Del Angel, Jamie Beverley, \nSpencer Park, Danielle Savage, Farkas Soma Szakál ")
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
    
    Label mUserLabel;
    
    ImageButton mLogoButton;
    Image mLogo;
    ImageComponent mLogoImageComponent;
};
