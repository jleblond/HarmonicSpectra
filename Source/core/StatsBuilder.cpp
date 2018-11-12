/*
  ==============================================================================

    StatsBuilder.cpp
    Created: 8 Nov 2018 9:23:19pm
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "StatsBuilder.h"


StatsBuilder StatsBuilder::m_statsBuilder = StatsBuilder();

StatsBuilder& StatsBuilder::Instance()
{
    return m_statsBuilder;
}
