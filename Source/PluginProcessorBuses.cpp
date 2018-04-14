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
    //! @brief Get an array with all the supported buses layouts in the Juce format.
    static const Array<AudioProcessor::BusesLayout>& getSupporttedBusesLayouts()
    {
        static Array<AudioProcessor::BusesLayout> layouts;
        if(layouts.isEmpty())
        {
            auto const& envSupportedLayouts = CamomileEnvironment::getBusesLayouts();
            for(auto const& envBusesLayout : envSupportedLayouts)
            {
                AudioProcessor::BusesLayout pluginLayout;
                for(auto const& envBus : envBusesLayout)
                {
                    pluginLayout.inputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(envBus.first)));
                    pluginLayout.outputBuses.add(AudioChannelSet::canonicalChannelSet(static_cast<int>(envBus.second)));
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
    auto const& supportedLayouts = CamomileBusesLayoutHelper::getSupporttedBusesLayouts();
    for(int layoutidx = 0; layoutidx < supportedLayouts.size(); ++layoutidx)
    {
        auto const& buses = supportedLayouts[layoutidx];
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
    auto const& supportedLayouts = CamomileBusesLayoutHelper::getSupporttedBusesLayouts();
    for(int layoutidx = 0; layoutidx < supportedLayouts.size(); ++layoutidx)
    {
        auto const& buses = supportedLayouts[layoutidx];
        const int  nCurrentBuses = buses.inputBuses.size();
        assert(buses.inputBuses.size() == buses.outputBuses.size());
        for(int busidx = nBuses; busidx < nCurrentBuses; ++busidx)
        {
            auto const& inputBus = buses.inputBuses[busidx];
            auto const& outputBus = buses.outputBuses[busidx];
            defaultBusesProperties.addBus(true, String("bus ") + String(busidx+1) + String(" input"), inputBus, layoutidx == 0);
            defaultBusesProperties.addBus(false, String("bus ") + String(busidx+1) + String(" output"), outputBus, layoutidx == 0);
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
    auto const& supportedLayouts = CamomileBusesLayoutHelper::getSupporttedBusesLayouts();
    return supportedLayouts.contains(CamomileBusesLayoutHelper::getCanonicalEquivalent(requestedLayout));
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
            if(isInput && supportedLayout[nbus].first != 0)
            {
                return true;
            }
            if(!isInput && supportedLayout[nbus].second != 0)
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
    AudioProcessor::BusesLayout const busLayout = getBusesLayout();
    const int ninput_buses  = getBusCount(true);
    const int noutput_buses = getBusCount(false);
    const int nbuses = std::max(ninput_buses, noutput_buses);
    for(int i = 0; i < nbuses; ++i)
    {
        if(i < ninput_buses)
        {
            sendList(std::string("bus"), CamomileBusesLayoutHelper::getBusInformation(*(getBus(true, i))));
        }
        if(i < noutput_buses)
        {
            sendList(std::string("bus"), CamomileBusesLayoutHelper::getBusInformation(*(getBus(false, i))));
        }
    }
}
