/*
  ==============================================================================

    Comment.h
    Created: 23 Oct 2018 1:44:02am
    Author:  Jasmine Leblond-Chartrand

  ==============================================================================
*/

#pragma once


struct Comment
{
    String text = "";
    String date = "";
    
    void print()
    {
        std::cout<<"--Comment-- "<<date;
        std::cout<<text<<std::endl;
    }
    
};
