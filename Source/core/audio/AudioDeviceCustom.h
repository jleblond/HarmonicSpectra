/*
  ==============================================================================

    AudioDev.h
    Created: 25 Nov 2018 12:23:01am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class AudioDeviceCustom
{
public:
    AudioDeviceCustom();
    
    ~AudioDeviceCustom();
    
    static AudioDeviceManager& getSharedAudioDeviceManager();
    
    static void runtimePermissionsCallback (bool wasGranted);
    
    
private:
    
};
