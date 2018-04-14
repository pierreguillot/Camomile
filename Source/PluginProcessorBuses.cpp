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
            const std::string busStr = std::string(" bus ") + std::to_string(busidx);
            add(ConsoleLevel::Log, layoutStr + busStr + " input: " + std::to_string(inputBus.size()) +
                " \"" + CamomileBusesLayoutHelper::getFormattedChannelSetDescription(inputBus) + "\"");
            add(ConsoleLevel::Log, layoutStr + busStr + " output: " + std::to_string(outputBus.size()) + " \"" + CamomileBusesLayoutHelper::getFormattedChannelSetDescription(outputBus) + "\"");
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                     GET ALL BUSES                                        //
//////////////////////////////////////////////////////////////////////////////////////////////

static bool busAlreadyExistsInAnotherLayout(const size_t is_input, const size_t layoutidx, const size_t busidx,
                                            std::vector<CamomileEnvironment::buses_layout> const& layouts)
{
    using buses_layout_t = CamomileEnvironment::buses_layout;
    const size_t ncomp = is_input ? layouts[layoutidx][busidx].first : layouts[layoutidx][busidx].second;
    for(size_t i = layoutidx; i; --i)
    {
        buses_layout_t const& layout = layouts[i-1];
        if(layout.size() > busidx)
        {
            if(is_input && layout[busidx].first == ncomp)
            {
                return true;
            }
            else if(!is_input && layout[busidx].second == ncomp)
            {
                return true;
            }
        }
    }
    return false;
}

static bool busIndexAlreadyExistsInAnotherLayout(const size_t is_input, const size_t layoutidx, const size_t busidx,
                                            std::vector<CamomileEnvironment::buses_layout> const& layouts)
{
    using buses_layout_t = CamomileEnvironment::buses_layout;
    for(size_t i = layoutidx; i; --i)
    {
        buses_layout_t const& layout = layouts[i-1];
        if(layout.size() > busidx)
        {
            if(is_input && layout[busidx].first != 0)
            {
                return true;
            }
            else if(!is_input && layout[busidx].second != 0)
            {
                return true;
            }
        }
    }
    return false;
}

AudioProcessor::BusesProperties CamomileAudioProcessor::getBusesProperties(const bool canonical)
{
    BusesProperties all_default_buses;
    using buses_layout_t = CamomileEnvironment::buses_layout;
    std::vector<buses_layout_t> const& env_buses_layouts = CamomileEnvironment::getBusesLayouts();
    // Add support for the all the buses of the first layout
    if(!env_buses_layouts.empty())
    {
        buses_layout_t const& env_main_layout = env_buses_layouts[0];
        for(size_t busidx = 0; busidx <  env_main_layout.size(); ++busidx)
        {
            const int size_in = static_cast<int>(env_main_layout[busidx].first);
            if(size_in)
            {
                all_default_buses.addBus(true, String("Bus ") + String(busidx) + String(" Input "),
                                         AudioChannelSet::canonicalChannelSet(size_in), true);
            }
            const int size_out = static_cast<int>(env_main_layout[busidx].second);
            if(size_out)
            {
                all_default_buses.addBus(false, String("Bus ") + String(busidx) + String(" Output "),
                                         AudioChannelSet::canonicalChannelSet(size_out), true);
            }
        }
    }
    // Add support for the buses of the other layouts if the bus doesn't already exist
    for(size_t layoutidx = 1; layoutidx < env_buses_layouts.size(); ++layoutidx)
    {
        buses_layout_t const& env_main_layout = env_buses_layouts[layoutidx];
        for(size_t busidx = 0; busidx <  env_main_layout.size(); ++busidx)
        {
            if(!busIndexAlreadyExistsInAnotherLayout(true, layoutidx, busidx, env_buses_layouts))
            {
                const int size = static_cast<int>(env_main_layout[busidx].first);
                if(size)
                {
                    all_default_buses.addBus(true, String("Bus ") + String(busidx) + String(" Input "), AudioChannelSet::canonicalChannelSet(size), false);
                }
            }
            if(!busIndexAlreadyExistsInAnotherLayout(false, layoutidx, busidx, env_buses_layouts))
            {
                const int size = static_cast<int>(env_main_layout[busidx].second);
                if(size)
                {
                    all_default_buses.addBus(false, String("Bus ") + String(busidx) + String(" Output "), AudioChannelSet::canonicalChannelSet(size), false);
                }
            }
        }
    }
    /*
    for(size_t layoutidx = 1; layoutidx <  env_buses_layouts.size(); ++layoutidx)
    {
        buses_layout_t const& env_main_layout = env_buses_layouts[layoutidx];
        for(size_t busidx = 0; busidx <  env_main_layout.size(); ++busidx)
        {
            if(!busAlreadyExistsInAnotherLayout(true, layoutidx, busidx, env_buses_layouts))
            {
                const int size = static_cast<int>(env_main_layout[busidx].first);
                if(size)
                {
                    all_default_buses.addBus(true, String("Input Bus ") + String(busidx), AudioChannelSet::canonicalChannelSet(size), false);
                }
            }
            if(!busAlreadyExistsInAnotherLayout(false, layoutidx, busidx, env_buses_layouts))
            {
                const int size = static_cast<int>(env_main_layout[busidx].second);
                if(size)
                {
                    all_default_buses.addBus(false, String("Output Bus ") + String(busidx), AudioChannelSet::canonicalChannelSet(size), false);
                }
            }
            
        }
    }
     */
    return all_default_buses;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      BUSES SUPPORTED                                     //
//////////////////////////////////////////////////////////////////////////////////////////////

static bool isBusesLayoutCompatible(const AudioProcessor::BusesLayout& requestedLayout,
                                    const CamomileEnvironment::buses_layout& supportedLayout)
{
    Array<AudioChannelSet> const& inputBuses = requestedLayout.inputBuses;
    Array<AudioChannelSet> const& outputBuses = requestedLayout.outputBuses;

    const int nInputBusRequested = inputBuses.size();
    for(int i = 0; i < nInputBusRequested; ++i)
    {
        if(!inputBuses[i].isDisabled())
        {
            if(i > supportedLayout.size())
            {
                return false;
            }
            if(i != supportedLayout[i].first)
            {
                return false;
            }
        }
    }
    
    const int nOutputBusRequested = outputBuses.size();
    for(int i = 0; i < nOutputBusRequested; ++i)
    {
        if(!outputBuses[i].isDisabled())
        {
            if(i > supportedLayout.size())
            {
                return false;
            }
            if(i != supportedLayout[i].second)
            {
                return false;
            }
        }
    }
    return true;
}

bool CamomileAudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    using buses_layout_t = CamomileEnvironment::buses_layout;
    std::vector<buses_layout_t> const& envLayouts = CamomileEnvironment::getBusesLayouts();
    for(buses_layout_t const& envLayout : envLayouts)
    {
        if(isBusesLayoutCompatible(layouts, envLayout))
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
