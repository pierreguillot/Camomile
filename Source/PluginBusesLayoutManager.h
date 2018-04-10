/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

// ======================================================================================== //
//                                      BUSES LAYOUT MANAGER                                //
// ======================================================================================== //


class CamomileAudioBusesLayoutManager
{
public:
    static AudioProcessor::BusesLayout getDefaultBusesLayout(const bool canonical = false);
    static bool isBusesLayoutSupported(const AudioProcessor::BusesLayout& layouts);
};
