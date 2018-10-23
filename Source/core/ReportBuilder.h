/*
  ==============================================================================

    ReportBuilder.h
    Created: 23 Oct 2018 1:41:20am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ReportBuilder    : public Component
{
public:
    ReportBuilder();
    ~ReportBuilder();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ReportBuilder)
};
