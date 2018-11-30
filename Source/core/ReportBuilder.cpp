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
    
    assert(Config::user != nullptr);
    r->username = Config::user->getUsername();
    r->date = CustomDate::getStrCurrentTime();
    
    r->baseFreq = Config::baseFreq;
    r->nbAmplitudeRatios = Config::nbAmplitudeRatios;
    r->partials = Config::partials;
    r->vecAudibleRanges = Config::vecAudibleRanges;
    
    assert(Config::user->getLastSession() != nullptr);
    r->stats = Config::user->getLastSession()->getStats();

    //    timePractised: updated in MainApplication::buttonClicked(&m_endSessionButton)
    //    String timePractised = "";

    //    Comments: push_back in Notepad::buttonClicked(&m_saveCommentButton)
    //    std::vector<std::shared_ptr<Comment>> comments;
    
    return r;
}

String ReportBuilder::getReportStr()
{
    String content = "";
    
    return content;
}

void ReportBuilder::saveReport()
{
    String reportFilePath =
    Config::reportDirectory.getFullPathName()+"/report_"+CustomDate::getStrFormatCurrentTime()+".txt";
    
    File reportFile(reportFilePath);
    reportFile.create();
    reportFile.appendText( getReportStr());
    
    juce::AlertWindow *alertFileSaved = new juce::AlertWindow ("Report Succesfully Generated!",
                                                               "File saved as...\n" + reportFilePath, juce::AlertWindow::NoIcon );
    alertFileSaved->setColour(AlertWindow::backgroundColourId, Colours::black);
    alertFileSaved->setBounds(330,200,600,200);
    alertFileSaved->addButton ("OK",     1, KeyPress (KeyPress::returnKey, 0, 0));
    int returnValue = alertFileSaved->runModalLoop();
    delete alertFileSaved;
    
    reportFile.revealToUser();
}
