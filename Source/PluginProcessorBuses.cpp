/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                     GET ALL BUSES                                        //
//////////////////////////////////////////////////////////////////////////////////////////////

AudioProcessor::BusesProperties CamomileAudioProcessor::getDefaultBusesProperties()
{
    BusesProperties busesProperties;
    auto const& busesLayouts = CamomileEnvironment::getBusesLayouts();
    for(size_t i = 0; i < busesLayouts.size(); ++i)
    {
        auto const& busesLayout = busesLayouts[i];
        for(size_t j = 0; j < busesLayout.size(); ++j)
        {
            auto const& bus = busesLayout[j];
            if(bus.inputs > 0)
            {
                auto const name = bus.name.empty() ? String("Bus ") + String(j+1) + juce::String(" Input") : juce::String(bus.name);
                busesProperties.addBus(true, name, AudioChannelSet::canonicalChannelSet(bus.inputs), i == 0);
            }
            if(bus.outputs > 0)
            {
                auto const name = bus.name.empty() ? String("Bus ") + String(j+1) + juce::String(" Output"): juce::String(bus.name);
                busesProperties.addBus(false, name, AudioChannelSet::canonicalChannelSet(bus.outputs), i == 0);
            }
        }
    }
    return busesProperties;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                  IS BUSES LAYOUT SUPPORTED                               //
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileAudioProcessor::isBusesLayoutSupported(juce::AudioProcessor::BusesLayout const& requestedLayout) const
{
    using buses_layout = CamomileEnvironment::buses_layout;
    auto const& busesLayouts = CamomileEnvironment::getBusesLayouts();
    return std::any_of(busesLayouts.cbegin(), busesLayouts.cend(), [&](buses_layout const& busesLayout)
    {
        auto getNumChannels = [](juce::Array<AudioChannelSet> const& buses, size_t index)
        {
            return buses.size() > index ? buses[index].size() : 0;
        };
        for(size_t i = 0; i < busesLayout.size(); ++i)
        {
            if(getNumChannels(requestedLayout.inputBuses, i) < busesLayout[i].inputs)
            {
                return false;
            }
            if(getNumChannels(requestedLayout.outputBuses, i) < busesLayout[i].outputs)
            {
                return false;
            }
        }
        return true;
    });
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                              SEND CURRENT BUSES LAYOUT INFORMATION                       //
//////////////////////////////////////////////////////////////////////////////////////////////

void CamomileAudioProcessor::sendCurrentBusesLayoutInformation()
{
    auto getBusInformation = [](AudioProcessor::Bus const& bus)
    {
        auto getFormattedChannelSetDescription = [](AudioChannelSet const& channelSet)
        {
            auto const description = channelSet.getDescription().toLowerCase();
            return description.contains("discrete") ? std::string("discrete") : description.toStdString();
        };
        
        auto const& layout = bus.getCurrentLayout();
        auto const index = static_cast<float>(bus.getBusIndex());
        auto const type = bus.isInput() ? std::string("input") : std::string("output");
        auto const size = static_cast<float>(layout.size());
        auto const description  = getFormattedChannelSetDescription(layout);
        return std::vector<pd::Atom>{index, type, size, description};
    };
    
    const int nBuses = std::max(getBusCount(true), getBusCount(false));
    for(int i = 0; i < nBuses; ++i)
    {
        auto const* inBus = getBus(true, i);
        auto const* outBus = getBus(false, i);
        if(inBus != nullptr && inBus->isEnabled())
        {
            sendList("bus", getBusInformation(*inBus));
        }
        if(outBus != nullptr && outBus->isEnabled())
        {
            sendList("bus", getBusInformation(*outBus));
        }
    }
}
