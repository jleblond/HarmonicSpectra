/*
  ==============================================================================

    ReportBuilder.cpp
    Created: 23 Oct 2018 1:41:20am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#include "ReportBuilder.h"


std::shared_ptr<Report> ReportBuilder::createReport()
{
    std::shared_ptr<Report> r = std::make_shared<Report>();
    
    
    r->username = Config::user->getUsername();
    
    
    return r;
}

void ReportBuilder::saveReport()
{
    
}
