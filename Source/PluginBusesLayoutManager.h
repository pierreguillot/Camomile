/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include <string>
#include "../JuceLibraryCode/JuceHeader.h"

// ======================================================================================== //
//                                      BUSES LAYOUT MANAGER                                //
// ======================================================================================== //

class CamomileAudioProcessor;

class CamomileAudioBusesLayoutManager
{
public:
    static AudioProcessor::BusesLayout getDefaultBusesLayout(const bool canonical = false);
    static bool isBusesLayoutSupported(const AudioProcessor::BusesLayout& layouts);
    static std::string getFormattedBusDescription(AudioProcessor::Bus const& bus);
    static void sendBusInformation(CamomileAudioProcessor const& processor, AudioProcessor::Bus const& bus);
    static void sendBusLayoutInformation(CamomileAudioProcessor const& processor);
};
