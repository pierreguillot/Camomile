/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginChannelsManager.h"
#include "PluginAtomParser.h"
#include "PluginParameter.h"

void CamomileEffectManager::parseOptions(const std::vector<pd::Atom>& list)
{
    
}

bool CamomileEffectManager::process(const std::vector<pd::Atom>& list)
{
    if(list.size() > 1 && list[0].isSymbol())
    {
        const std::string mode(list[0].getSymbol());
        //////////////////////////////////////////////////////////////////////////////////////
        //                                      OPTIONS                                     //
        //////////////////////////////////////////////////////////////////////////////////////
        if(mode == std::string("options"))
        {
            m_midi_in_support   = CamomileAtomParser::parseBool(list, "-midiin", m_midi_in_support);
            m_midi_out_support  = CamomileAtomParser::parseBool(list, "-midiout", m_midi_out_support);
            m_play_head_support = CamomileAtomParser::parseBool(list, "-playhead", m_play_head_support);
            m_midi_only         = CamomileAtomParser::parseBool(list, "-midionly", m_midi_only);
            return true;
        }
        //////////////////////////////////////////////////////////////////////////////////////
        //                                      CHANNELS                                    //
        //////////////////////////////////////////////////////////////////////////////////////
        else if(mode == std::string("channels"))
        {
            m_input_sets = CamomileAtomParser::parseList(list, "-inputs");
            for(int i = 0; i < m_input_sets.size(); ++i)
            {
                m_input_sets.getReference(i) = m_input_sets[i].toLowerCase();
            }
            m_output_sets = CamomileAtomParser::parseList(list, "-outputs");
            for(int i = 0; i < m_output_sets.size(); ++i)
            {
                m_output_sets.getReference(i) = m_output_sets[i].toLowerCase();
            }
            return true;
        }
        //////////////////////////////////////////////////////////////////////////////////////
        //                                      PARAM                                       //
        //////////////////////////////////////////////////////////////////////////////////////
        else if(mode == std::string("param"))
        {
            if(list.size() > 2 && list[1].isFloat())
            {
                const int index = static_cast<int>(list[1].getFloat());
                if(index == getParameters().size()+1)
                {
                    std::vector<pd::Atom> const args(list.begin()+2, list.end());
                    addParameter(CamomileAudioParameter::parse(args));
                }
                else { std::cerr << "define param : index out of range.\n"; }
            }
            else { std::cerr << "define param : first arg is an index.\n"; }
        }
        //////////////////////////////////////////////////////////////////////////////////////
        //                                      PARAM                                       //
        //////////////////////////////////////////////////////////////////////////////////////
        if(mode == std::string("program"))
        {
            /*
            if(list.size() >= 2 && list[0].isSymbol() && list[1].isFloat())
            {
                std::string const method = list[0].getSymbol();
                int const index = static_cast<int>(list[1].getFloat());
                if(method == "define")
                {
                    if(list.size() >= 3 && list[2].isSymbol())
                    {
                        if(index == m_programs.size()+1)
                        {
                            m_programs.add({list[2].getSymbol(), "", Array<float>()});
                            for(int i = 3; i < list.size(); ++i)
                            {
                                m_programs.getReference(index-1).values.add(list[i].getFloat());
                            }
                        }
                        else { std::cerr << "program define method: index out of range.\n"; }
                    }
                    else { std::cerr << "program error syntax: define index name...\n"; }
                }
                else { std::cerr << "program unknown method: index out of range.\n"; }
            }
            else { std::cerr << "program error syntax: method index...\n"; }
            return true;
             */
        }
    }
    return false;
}

bool supportInput(const String& name)
{
    return true;
}

bool supportOutput(const String& name)
{
    return true;
}
