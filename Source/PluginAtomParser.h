/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "xpd/xpd.h"

// ======================================================================================== //
//                                      PARSER                                             //
// ======================================================================================== //

class CamomileAtomParser
{
public:
    static String parseString(const std::vector<pd::Atom>& list, const String& name);
    static float parseFloat(const std::vector<pd::Atom>& list, const String& name, float const def);
    static int parseInt(const std::vector<pd::Atom>& list, const String& name, int const def);
    static bool parseBool(const std::vector<pd::Atom>& list, const String& name, bool const def);
};

