/*
  ==============================================================================

    ReportBuilder.h
    Created: 23 Oct 2018 1:41:20am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

#include "Config.h"
#include "QuestionBuilder.h"
#include "Report.h"
#include "Partials.h"

#include "../utils/CustomDate.h"


const int MAX_DIFFICULTY = 1000;


class ReportBuilder
{
public:
    ReportBuilder();
    ~ReportBuilder();
    static std::shared_ptr<Report> createReport();
    static void saveReport();
    static String getReportStr();

private:
    static String chartContent();
    static String getChartLine(int waveID);
    static String getLinesPercent(float percent);
    static std::vector<String> m_vecRatioStr;

};
