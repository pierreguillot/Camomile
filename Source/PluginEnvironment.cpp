/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEnvironment.h"
#include "PluginAtomParser.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <cctype>

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      ENVIRONMENT                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

CamomileEnvironment& CamomileEnvironment::get()
{
    static CamomileEnvironment env;
    return env;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          GLOBAL                                          //
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileEnvironment::initialize() { return isValid(); }

const char* CamomileEnvironment::getPluginNameUTF8() { return get().plugin_name.c_str(); }

std::string CamomileEnvironment::getPluginName() { return get().plugin_name; }

unsigned int CamomileEnvironment::getPluginCode() { return get().plugin_code; }

std::string CamomileEnvironment::getPatchPath() { return get().patch_path; }

std::string CamomileEnvironment::getPatchName() { return get().patch_name; }

bool CamomileEnvironment::isValid() { return get().valid; }

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          OPTIONS                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileEnvironment::wantsMidi() { return get().midi_in_support; }

bool CamomileEnvironment::producesMidi() { return get().midi_out_support; }

bool CamomileEnvironment::wantsPlayHead() { return get().play_head_support; }

bool CamomileEnvironment::isMidiOnly() { return get().midi_only; }

float CamomileEnvironment::getTailLengthSeconds() { return get().tail_length_sec; }

int CamomileEnvironment::getLatencySamples() { return get().latency_samples; }

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          PROGRAMS                                        //
//////////////////////////////////////////////////////////////////////////////////////////////

std::vector<std::string> const& CamomileEnvironment::getPrograms() { return get().programs; }

std::vector<std::string> const& CamomileEnvironment::getParams() { return get().params; }

std::vector<std::pair<int, int>> const& CamomileEnvironment::getBuses() { return get().buses; }

std::vector<std::string> const& CamomileEnvironment::getErrors() { return get().errors; }

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          CONSTRUCTOR                                     //
//////////////////////////////////////////////////////////////////////////////////////////////


static void parse(std::string const& name, std::vector<std::string> const& values,
                  std::vector<std::pair<std::string, std::string>>& def, std::vector<std::string>& errors)
{
    if(!values.empty())
    {
        for(size_t i = 0; i < values.size(); ++i)
        {
            const size_t separator = values[0].find_first_of(" ");
            if(separator != std::string::npos)
            {
                std::string const input = values[0].substr(0, separator);
                std::string const output = values[0].substr(separator+1);
                
            }
            else { errors.push_back(name + " " + std::to_string(i) + "needs 2 values."); }
        }
    }
    else { errors.push_back(name + " undefined."); }
}

CamomileEnvironment::CamomileEnvironment()
{
    File const plugin(File::getSpecialLocation(File::currentApplicationFile));
    if(plugin.exists())
    {
        plugin_name = plugin.getFileNameWithoutExtension().toStdString();
        plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
        patch_name = plugin_name + std::string(".pd");
#ifdef JUCE_MAC
        patch_path = plugin_path + "/" + plugin.getFileName().toStdString() + std::string("/Contents/Resources");
#else
        patch_path = plugin_path + String(File::getSeparatorString()).toStdString() + plugin_name;
#endif

        FileInputStream stream(File(String(patch_path + String(File::getSeparatorString()).toStdString() + plugin_name + ".txt")));
        std::map<std::string, std::vector<std::string>> options;
        if(stream.openedOk())
        {
            while(!stream.isExhausted())
            {
                auto entry = CamomileParser::getLine(stream.readNextLine().toStdString());
                if(!entry.first.empty())
                {
                    try
                    {
                        if(entry.first == "program")
                        {
                            programs.push_back(CamomileParser::getString(entry.second));
                        }
                        else if(entry.first == "buse")
                        {
                            buses.push_back(CamomileParser::getTwoIntegers(entry.second));
                        }
                        else if(entry.first == "midiin")
                        {
                            midi_in_support = CamomileParser::getBool(entry.second);
                        }
                        else if(entry.first == "midiout")
                        {
                            midi_out_support = CamomileParser::getBool(entry.second);
                        }
                        else if(entry.first == "playhead")
                        {
                            play_head_support = CamomileParser::getBool(entry.second);
                        }
                        else if(entry.first == "midionly")
                        {
                            midi_only = CamomileParser::getBool(entry.second);
                        }
                        else if(entry.first == "latency")
                        {
                            latency_samples = CamomileParser::getInteger(entry.second);
                        }
                        else if(entry.first == "taillength")
                        {
                            tail_length_sec = CamomileParser::getFloat(entry.second);
                        }
                        else if(entry.first == "code")
                        {
                            plugin_code = CamomileParser::getHexadecimalCode(entry.second);
                        }
                        else
                        {
                            options[entry.first].push_back(entry.second);
                        }
                    }
                    catch(const std::string& message)
                    {
                        errors.push_back(entry.first + " " + message);
                    }

                    
                }
            }
            valid = true;
        }
        else
        {
            errors.push_back("no configuration file.");
        }
        
        for(auto& it : options)
        {
            if(it.first == "param")
            {
                params = it.second;
            }
            else { errors.push_back("unknown option " + it.first + "."); }
        }
    }
    else
    {
        errors.push_back("plugin is not recognized.");
    }
    
    if(programs.empty())
    {
        programs.push_back("");
    }
    
    if(buses.empty())
    {
        buses.push_back({2, 2});
    }
}


