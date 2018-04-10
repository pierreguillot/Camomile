/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginBusesLayoutManager.h"
#include "PluginEnvironment.h"
#include "PluginProcessor.h"

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

std::string CamomileAudioBusesLayoutManager::getFormattedBusDescription(AudioProcessor::Bus const& bus)
{
    auto const& layout = bus.getCurrentLayout();
    String const description = layout.getDescription().toLowerCase();
    return description.contains("discrete") ? std::string("discrete") : description.toStdString();
}

void CamomileAudioBusesLayoutManager::sendBusInformation(CamomileAudioProcessor const& instance, AudioProcessor::Bus const& bus)
{
    if(1)
    {
        auto const& layout = bus.getCurrentLayout();
        const bool is_input = bus.isInput();
        const float index = static_cast<float>(bus.getBusIndex());
        const float size = static_cast<float>(layout.size());
        std::string const name = bus.getName().toStdString();
        std::string const descptn = getFormattedBusDescription(bus);
        instance.sendList(std::string("bus"), {index, is_input ? std::string("input") : std::string("output"), size, descptn});
    }
}

void CamomileAudioBusesLayoutManager::sendBusLayoutInformation(CamomileAudioProcessor const& processor)
{
    AudioProcessor::BusesLayout const busLayout = processor.getBusesLayout();
    const int ninput_buses  = processor.getBusCount(true);
    const int noutput_buses = processor.getBusCount(false);
    const int nbuses = std::max(ninput_buses, noutput_buses);
    for(int i = 0; i < nbuses; ++i)
    {
        if(i < ninput_buses)
        {
            CamomileAudioBusesLayoutManager::sendBusInformation(processor, *(processor.getBus(true, i)));
        }
        if(i < noutput_buses)
        {
            CamomileAudioBusesLayoutManager::sendBusInformation(processor, *(processor.getBus(false, i)));
        }
    }
    
}
