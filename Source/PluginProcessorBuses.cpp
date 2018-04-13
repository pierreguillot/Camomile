/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"

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

AudioProcessor::BusesProperties CamomileAudioProcessor::getBusesProperties(const bool canonical)
{
    BusesProperties all_default_buses;
    using buses_layout_t = CamomileEnvironment::buses_layout;
    std::vector<buses_layout_t> const& env_buses_layouts = CamomileEnvironment::getBusesLayouts();
    
    if(!env_buses_layouts.empty())
    {
        buses_layout_t const& env_main_layout = env_buses_layouts[0];
        for(size_t busidx = 0; busidx <  env_main_layout.size(); ++busidx)
        {
            const int size_in = static_cast<int>(env_main_layout[busidx].first);
            if(size_in)
            {
                all_default_buses.addBus(true, String("Input Bus ") + String(busidx),
                                         AudioChannelSet::canonicalChannelSet(size_in), true);
            }
            const int size_out = static_cast<int>(env_main_layout[busidx].second);
            if(size_out)
            {
                all_default_buses.addBus(false, String("Output Bus ") + String(busidx),
                                         AudioChannelSet::canonicalChannelSet(size_out), true);
            }
        }
    }
    
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
    return all_default_buses;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          BUSES SUPPORTED                                 //
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
//                                       SEND BUSES INFORMATION                             //
//////////////////////////////////////////////////////////////////////////////////////////////


static std::string getFormattedBusDescription(AudioProcessor::Bus const& bus)
{
    auto const& layout = bus.getCurrentLayout();
    String const description = layout.getDescription().toLowerCase();
    return description.contains("discrete") ? std::string("discrete") : description.toStdString();
}

static std::vector<pd::Atom> getBusInformation(AudioProcessor::Bus const& bus)
{
    auto const& layout = bus.getCurrentLayout();
    const bool is_input = bus.isInput();
    const float index = static_cast<float>(bus.getBusIndex());
    const float size = static_cast<float>(layout.size());
    std::string const name = bus.getName().toStdString();
    std::string const descptn = getFormattedBusDescription(bus);
    return std::vector<pd::Atom>{index, is_input ? std::string("input") : std::string("output"), size, descptn};
}

void CamomileAudioProcessor::sendBusesLayoutInformation()
{
    AudioProcessor::BusesLayout const busLayout = getBusesLayout();
    const int ninput_buses  = getBusCount(true);
    const int noutput_buses = getBusCount(false);
    const int nbuses = std::max(ninput_buses, noutput_buses);
    for(int i = 0; i < nbuses; ++i)
    {
        if(i < ninput_buses)
        {
            sendList(std::string("bus"), getBusInformation(*(getBus(true, i))));
        }
        if(i < noutput_buses)
        {
            sendList(std::string("bus"), getBusInformation(*(getBus(false, i))));
        }
    }
}
