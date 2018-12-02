/*
  ==============================================================================

    Partials.cpp
    Created: 29 Nov 2018 11:45:34pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "Partials.h"


Partials::Options Partials::options;


String Partials::partialsToString(Partials::Options po)
{
    switch(po)
    {
        case Partials::Options::odd:
            return "ODD";
            break;
            
        case Partials::Options::all:
            return "ALL";
            break;
            
        case Partials::Options::both:
            return "BOTH";
            break;
    };
    
    return "";
}
