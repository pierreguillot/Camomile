/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "xpd/xpd.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      PARSER                                              //
//////////////////////////////////////////////////////////////////////////////////////////////

class CamomileParser
{
public:
    static void perform(juce::File const& file);
    
private:
    static var perform(String const& line);
};

