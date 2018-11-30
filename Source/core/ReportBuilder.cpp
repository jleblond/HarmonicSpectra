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


String ReportBuilder::getReportStr()
{
    assert(Config::user != nullptr);
    assert(Config::user->getLastSession() != nullptr);
    auto lastSession = Config::user->getLastSession();
    std::shared_ptr<Report> report = lastSession->getReport();
    
    auto stats = lastSession->getStats();
    
    String s = "";
    s+= "\t\t \n";
    s+="\t\t\tInner Ear: HARMONIC SPECTRUM MODULE\n";
    s+="\t\t\tREPORT\n";
    s+="\t\t*********************************************\n";
    s+="\n";
    s+="\t\t\tUser ["+report->username+"]\n";
    s+="\t\t\tDate: "+report->date+"\n";
    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***SESSION INFORMATION***\n";
    s+="\n";
    s+="\n";
    s+="Time practiced ["+report->timePractised+"]\n";
    s+="\n";
    s+="Exercise settings\n";
    s+="\tBase frequency ["+static_cast<String>(report->baseFreq)+"Hz]\n";
    s+="\t# of amplitude ratios ["+static_cast<String>(report->nbAmplitudeRatios)+"]\n";
    s+="\tPartials ["+Partials::partialsToString(report->partials)+"]";
    s+="\n";
    s+="\n";
    s+="Total number of questions asked ["+ static_cast<String>(lastSession->getStats().questionsCount) +"]\n";
//    s+="\n";
//    s+="\n";
//    s+="\n";
//    s+="\n";
//    s+="\n";
//    s+="\t***GRAPH***\n";
//    s+="\n";
//    s+="center\     #times  \n";
//    s+="freq        involved         score (%)\n";
//    s+="————————————————————————--------------\n";
//    s+=freqChartStr(report);
//

        s+="\n";
        s+="Your score at the present level ["+ static_cast<String>((int)(100 * stats.score/stats.maxScore)) +"%]\n";
        s+="\n";
        s+="\n";
        s+="Maximum score (Exercises Difficulty) ["+ static_cast<String>(stats.maxScore) +"] / "+static_cast<String>(MAX_DIFFICULTY)+"\n\n";
        s+="Your score ["+ static_cast<String>((int)stats.score) +"] / " + static_cast<String>(stats.maxScore) +"\n\n";

        float globalProgScore = stats.score / MAX_DIFFICULTY * 100 ;
        std::cout<<"globalProgScore "<<globalProgScore<<std::endl;
        globalProgScore = std::floor( (globalProgScore) * 5 + 0.5) / 5;
        std::cout<<"globalProgScore floor .5"<<globalProgScore<<std::endl;

        s+="Global Progress Score ["+ static_cast<String>( globalProgScore) +"%]\n";
        s+="(based on your score and the difficulty of your exercises)\n";

    s+="\n";
    s+="\n";
    s+="\n";
    s+="\t***USER COMMENTS SECTION***\n";
    s+="\n";
    for(int i=0;i<(report->comments).size();i++)
    {
        s+="[["+(report->comments[i])->date+"\n";
        s+="\t["+(report->comments[i])->text+"]\n";
        s+="\n";
        s+="\n";
    }
    s+="\n";
    
    return s;
}
