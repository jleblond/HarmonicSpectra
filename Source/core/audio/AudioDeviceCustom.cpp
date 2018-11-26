/*
  ==============================================================================

    AudioDev.cpp
    Created: 25 Nov 2018 5:51:20pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "AudioDeviceCustom.h"

static ScopedPointer<AudioDeviceManager> sharedAudioDeviceManager;

AudioDeviceCustom::AudioDeviceCustom()
{
    
}

AudioDeviceCustom::~AudioDeviceCustom()
{

  sharedAudioDeviceManager = nullptr;
}

AudioDeviceManager& AudioDeviceCustom::getSharedAudioDeviceManager()
{
    if (sharedAudioDeviceManager == nullptr)
    {
        sharedAudioDeviceManager = new AudioDeviceManager();
        RuntimePermissions::request (RuntimePermissions::recordAudio, runtimePermissionsCallback);
    }
    
    return *sharedAudioDeviceManager;
}

void AudioDeviceCustom::runtimePermissionsCallback (bool wasGranted)
{
    int numInputChannels = wasGranted ? 2 : 0;
    sharedAudioDeviceManager->initialise (numInputChannels, 2, nullptr, true, String(), nullptr);
}



