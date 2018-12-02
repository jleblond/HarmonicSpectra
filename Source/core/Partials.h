/*
  ==============================================================================

    Partials.h
    Created: 1 Nov 2018 10:08:45pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"


//enum class Partials {odd, all, both};


class Partials
{
public:
    enum Options{ odd, all, both };
    static Options options;
    
    static String partialsToString(Partials::Options po);
};
