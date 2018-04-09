/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginBusesLayoutManager.h"
#include "PluginEnvironment.h"

// ======================================================================================== //
//                                      PROCESSOR                                           //
// ======================================================================================== //

AudioProcessor::BusesLayout CamomileAudioBusesLayoutManager::getDefaultBusesLayout()
{
    size_t i = 1;
    AudioProcessor::BusesLayout mainBusesLayout;
    auto const& busesLayouts = CamomileEnvironment::getBusesLayouts();
    if(!busesLayouts.empty() && !busesLayouts[0].empty())
    {
#if JucePlugin_Build_VST3
        for(auto const& buses : busesLayouts[0])
        {
            if(buses.first)
            {
                mainBusesLayout.inputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(busesLayouts[0][i].first)));
            }
            if(buses.second)
            {
                mainBusesLayout.outputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(busesLayouts[0][i].second)));
            }
        }
#else
        for(auto const& buses : busesLayouts[0])
        {
            if(buses.first)
            {
                mainBusesLayout.inputBuses.add(AudioChannelSet::discreteChannels(static_cast<int>(busesLayouts[0][i].first)));
            }
            if(buses.second)
            {
                mainBusesLayout.outputBuses.add(AudioChannelSet::discreteChannels(static_cast<int>(busesLayouts[0][i].second)));
            }
        }
#endif
    }
    return mainBusesLayout;
}

bool CamomileAudioBusesLayoutManager::isBusesLayoutSupported(const AudioProcessor::BusesLayout& layouts)
{
    auto const& busesLayouts = CamomileEnvironment::getBusesLayouts();
    
    const size_t nins  = static_cast<size_t>(layouts.getMainInputChannels());
    const size_t nouts  = static_cast<size_t>(layouts.getMainOutputChannels());
    for(auto const& busesLayout : busesLayouts)
    {
        if(!busesLayout.empty() && busesLayout[0].first == nins && busesLayout[0].second == nouts)
        {
            int here_check_the_other_buses;
            return true;
        }
        
    }
    return false;
}
