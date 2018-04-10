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

AudioProcessor::BusesLayout CamomileAudioBusesLayoutManager::getDefaultBusesLayout(const bool canonical)
{
    AudioProcessor::BusesLayout mainBusesLayout;
    auto const& busesLayouts = CamomileEnvironment::getBusesLayouts();
    if(!busesLayouts.empty() && !busesLayouts[0].empty())
    {
        if(canonical)
        {
            for(auto const& buses : busesLayouts[0])
            {
                if(buses.first)
                {
                    mainBusesLayout.inputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(buses.first)));
                }
                if(buses.second)
                {
                    mainBusesLayout.outputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(buses.second)));
                }
            }
        }
        else
        {
            for(auto const& buses : busesLayouts[0])
            {
                if(buses.first)
                {
                    mainBusesLayout.inputBuses.add(AudioChannelSet::discreteChannels(static_cast<int>(buses.first)));
                }
                if(buses.second)
                {
                    mainBusesLayout.outputBuses.add(AudioChannelSet::discreteChannels(static_cast<int>(buses.second)));
                }
            }
        }
    }
    return mainBusesLayout;
}

bool CamomileAudioBusesLayoutManager::isBusesLayoutSupported(const AudioProcessor::BusesLayout& layouts)
{
    const size_t nins  = static_cast<size_t>(layouts.getMainInputChannels());
    const size_t nouts  = static_cast<size_t>(layouts.getMainOutputChannels());
    
    auto const& busesLayouts = CamomileEnvironment::getBusesLayouts();
    for(auto const& busesLayout : busesLayouts)
    {
        if(!busesLayout.empty() && busesLayout[0].first == nins && busesLayout[0].second == nouts)
        {
            for(size_t i = 1; i < busesLayout.size(); ++i)
            {
                if(busesLayout[i].first != layouts.getNumChannels(true, static_cast<int>(i)) ||
                   busesLayout[i].second != layouts.getNumChannels(true, static_cast<int>(i)))
                {
                    return false;
                }
            }
            return true;
        }
        
    }
    return false;
}
