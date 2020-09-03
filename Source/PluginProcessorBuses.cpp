/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                  CAMOMILE BUSES LAYOUTS HELPER                           //
//////////////////////////////////////////////////////////////////////////////////////////////
class CamomileBusesLayoutHelper
{
public:
    class InternalBusesLayout
    {
    public:
        Array<String>               names;
        AudioProcessor::BusesLayout buses;
    };
    
    //! @brief Get an array with all the supported buses layouts in the Juce format.
    static const Array<InternalBusesLayout> getSupportedBusesLayouts()
    {
        Array<InternalBusesLayout> layouts;
        if(layouts.isEmpty())
        {
            auto const& envSupportedLayouts = CamomileEnvironment::getBusesLayouts();
            for(auto const& envBusesLayout : envSupportedLayouts)
            {
                InternalBusesLayout pluginLayout;
                for(auto const& envBus : envBusesLayout)
                {
                    pluginLayout.buses.inputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(envBus.inputs)));
                    pluginLayout.buses.outputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(envBus.outputs)));
                    pluginLayout.names.add(envBus.name);
                }
                layouts.add(std::move(pluginLayout));
            }
        }
        return layouts;
    }
    
    //! @brief Get a lower case description of a channel set.
    static std::string getFormattedChannelSetDescription(AudioChannelSet const& channelSet)
    {
        String const description = channelSet.getDescription().toLowerCase();
        return description.contains("discrete") ? std::string("discrete") : description.toStdString();
    }
    
    //! @brief Get a lower case description of a channel set.
    static std::vector<pd::Atom> getBusInformation(AudioProcessor::Bus const& bus)
    {
        auto const& layout          = bus.getCurrentLayout();
        const bool is_input         = bus.isInput();
        const float index           = static_cast<float>(bus.getBusIndex());
        const float size            = static_cast<float>(layout.size());
        std::string const descptn   = getFormattedChannelSetDescription(layout);
        return std::vector<pd::Atom>{index, is_input ? std::string("input") : std::string("output"), size, descptn};
    }
    
    //! @brief Get a lower case description of a channel set.
    static AudioProcessor::BusesLayout getCanonicalEquivalent(const AudioProcessor::BusesLayout& requestedLayout)
    {
        AudioProcessor::BusesLayout equivalentLayout;
        auto& equivalentInputBuses = equivalentLayout.inputBuses;
        auto& equivalentOutputBuses = equivalentLayout.outputBuses;
        
        for(auto const& bus : requestedLayout.inputBuses)
        {
            equivalentInputBuses.add(AudioChannelSet::canonicalChannelSet(bus.size()));
        }
        for(auto const& bus : requestedLayout.outputBuses)
        {
            equivalentOutputBuses.add(AudioChannelSet::canonicalChannelSet(bus.size()));
        }
        return equivalentLayout;
    }

};

//////////////////////////////////////////////////////////////////////////////////////////////
//                                  LOG BUSES LAYOUTS INFORMATION                           //
//////////////////////////////////////////////////////////////////////////////////////////////

void CamomileAudioProcessor::logBusesLayoutsInformation()
{
    auto const supportedLayouts = CamomileBusesLayoutHelper::getSupportedBusesLayouts();
    for(int layoutidx = 0; layoutidx < supportedLayouts.size(); ++layoutidx)
    {
        auto const& buses = supportedLayouts[layoutidx].buses;
        assert(buses.inputBuses.size() == buses.outputBuses.size());
        const int nBuses = buses.inputBuses.size();
        const std::string layoutStr = std::string("layout ") + std::to_string(layoutidx);
        for(int busidx = 0; busidx < nBuses; ++busidx)
        {
            auto const& inputBus = buses.inputBuses[busidx];
            auto const& outputBus = buses.outputBuses[busidx];
            const std::string busStr = std::string(" bus ") + std::to_string(busidx+1);
            add(ConsoleLevel::Log, layoutStr + busStr + " input: " + std::to_string(inputBus.size()) +
                " \"" + CamomileBusesLayoutHelper::getFormattedChannelSetDescription(inputBus) + "\"");
            add(ConsoleLevel::Log, layoutStr + busStr + " output: " + std::to_string(outputBus.size()) + " \"" + CamomileBusesLayoutHelper::getFormattedChannelSetDescription(outputBus) + "\"");
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                     GET ALL BUSES                                        //
//////////////////////////////////////////////////////////////////////////////////////////////

AudioProcessor::BusesProperties CamomileAudioProcessor::getDefaultBusesProperties(const bool canonical)
{
    int nBuses = 0;
    BusesProperties defaultBusesProperties;
    auto const supportedLayouts = CamomileBusesLayoutHelper::getSupportedBusesLayouts();
    for(int layoutidx = 0; layoutidx < supportedLayouts.size(); ++layoutidx)
    {
        auto const& buses = supportedLayouts[layoutidx];
        const int nCurrentBuses = buses.buses.inputBuses.size();
        assert(buses.buses.inputBuses.size() == buses.buses.outputBuses.size());
        for(int busidx = nBuses; busidx < nCurrentBuses; ++busidx)
        {
            auto const& inputBus = buses.buses.inputBuses[busidx];
            auto const& outputBus = buses.buses.outputBuses[busidx];
            auto name = buses.names[busidx];
            if(!inputBus.isDisabled())
            {
                if(name.isEmpty())
                {
                    name = String("bus ") + String(busidx+1) + String(" input");
                }
                defaultBusesProperties.addBus(true, name, inputBus, true);
            }
            if(!outputBus.isDisabled())
            {
                if(name.isEmpty())
                {
                    name = String("bus ") + String(busidx+1) + String(" output");
                }
                defaultBusesProperties.addBus(false, name, outputBus, true);
            }
        }
        nBuses = nCurrentBuses;
    }
    return defaultBusesProperties;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                  IS BUSES LAYOUT SUPPORTED                               //
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileAudioProcessor::isBusesLayoutSupported(const BusesLayout& requestedLayout) const
{
    const auto canoBus = CamomileBusesLayoutHelper::getCanonicalEquivalent(requestedLayout);
    const auto supportedBuses = CamomileBusesLayoutHelper::getSupportedBusesLayouts();
    for(auto& bus : supportedBuses)
    {
        if(bus.buses == canoBus)
        {
            return true;
        }
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      ADD AND REMOVE BUSES                                //
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileAudioProcessor::canAddBus(bool isInput) const
{
    // This method is only used with Audio Units
    using buses_layout_t = CamomileEnvironment::buses_layout;
    std::vector<buses_layout_t> const& supportedLayouts = CamomileEnvironment::getBusesLayouts();
    const size_t nbus = getBusCount(isInput);
    for(size_t i = 0; i < supportedLayouts.size(); ++i)
    {
        buses_layout_t const& supportedLayout = supportedLayouts[i];
        if(supportedLayout.size() > nbus)
        {
            if(isInput && supportedLayout[nbus].inputs != 0)
            {
                return true;
            }
            if(!isInput && supportedLayout[nbus].outputs != 0)
            {
                return true;
            }
        }
    }
    return false;
}

bool CamomileAudioProcessor::CamomileAudioProcessor::canRemoveBus(bool isInput) const
{
    // This method is only used with Audio Units
    return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                              SEND CURRENT BUSES LAYOUT INFORMATION                       //
//////////////////////////////////////////////////////////////////////////////////////////////

void CamomileAudioProcessor::sendCurrentBusesLayoutInformation()
{
    const int nBuses = std::max(getBusCount(true), getBusCount(false));
    for(int i = 0; i < nBuses; ++i)
    {
        AudioProcessor::Bus const* inBus = getBus(true, i);
        AudioProcessor::Bus const* outBus = getBus(false, i);
        if(inBus && inBus->isEnabled())
        {
            sendList("bus", CamomileBusesLayoutHelper::getBusInformation(*inBus));
        }
        if(outBus && outBus->isEnabled())
        {
            sendList("bus", CamomileBusesLayoutHelper::getBusInformation(*outBus));
        }
    }
}
