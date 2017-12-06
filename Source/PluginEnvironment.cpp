/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEnvironment.h"
#include "PluginParser.h"
#include "../JuceLibraryCode/JuceHeader.h"
#include <cctype>
#include <string>
extern "C"
{
#include <m_pd.h>
}
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

std::string CamomileEnvironment::getPdVersion() {
    return std::to_string(PD_MAJOR_VERSION) + "." + std::to_string(PD_MINOR_VERSION) + "." + std::to_string(PD_BUGFIX_VERSION); }

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          OPTIONS                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

bool CamomileEnvironment::wantsMidi() { return get().midi_in_support; }

bool CamomileEnvironment::producesMidi() { return get().midi_out_support; }

int CamomileEnvironment::getPlayHeadLevel() { return get().play_head_level; }

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

bool CamomileEnvironment::localize()
{
#ifdef JUCE_MAC
    File plugin(File::getSpecialLocation(File::currentApplicationFile));
    if(plugin.exists() && (plugin.hasFileExtension("component") ||
                           plugin.hasFileExtension("vst") ||
                           plugin.hasFileExtension("vst3")))
    {
        
        plugin_name = plugin.getFileNameWithoutExtension().toStdString();
        plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
        patch_name = plugin_name + std::string(".pd");
        patch_path = plugin_path + "/" + plugin.getFileName().toStdString() + std::string("/Contents/Resources");
        return true;
    }
    else
    {
        errors.push_back("can't localize the plugin: ");
        errors.push_back(plugin.getFullPathName().toStdString());
        
        plugin = File::getSpecialLocation(File::currentExecutableFile);
        if(plugin.exists() && (plugin.hasFileExtension("component") ||
                               plugin.hasFileExtension("vst") ||
                               plugin.hasFileExtension("vst3")))
        {
            errors.clear();
            plugin_name = plugin.getFileNameWithoutExtension().toStdString();
            plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
            patch_name = plugin_name + std::string(".pd");
            patch_path = plugin_path;
            return true;
        }
        else
        {
            errors.push_back(plugin.getFullPathName().toStdString());
        }
    }
#elif LINUX
    File plugin(File::getSpecialLocation(File::currentExecutableFile));
    if(plugin.exists() && plugin.hasFileExtension("so"))
    {
        plugin_name = plugin.getFileNameWithoutExtension().toStdString();
        plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
        patch_name = plugin_name + std::string(".pd");
        patch_path = plugin_path;
        return true;
    }
    else
    {
        errors.push_back("can't localize the plugin: ");
        errors.push_back(plugin.getFullPathName().toStdString());
        
        plugin = File::getSpecialLocation(File::currentApplicationFile);
        if(plugin.exists() && plugin.hasFileExtension("so"))
        {
            errors.clear();
            plugin_name = plugin.getFileNameWithoutExtension().toStdString();
            plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
            patch_name = plugin_name + std::string(".pd");
            patch_path = plugin_path;
            return true;
        }
        else
        {
            errors.push_back(plugin.getFullPathName().toStdString());
        }
    }
#else // WIN32
    File plugin(File::getSpecialLocation(File::currentExecutableFile));
    if(plugin.exists() && (plugin.hasFileExtension("dll") || plugin.hasFileExtension("vst3")))
    {
        plugin_name = plugin.getFileNameWithoutExtension().toStdString();
        plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
        patch_name = plugin_name + std::string(".pd");
        patch_path = plugin_path;
        return true;
    }
    else
    {
        errors.push_back("can't localize the plugin: ");
        errors.push_back(plugin.getFullPathName().toStdString());
        
        plugin = File::getSpecialLocation(File::currentApplicationFile);
        if(plugin.exists() && (plugin.hasFileExtension("dll") || plugin.hasFileExtension("vst3")))
        {
            errors.clear();
            plugin_name = plugin.getFileNameWithoutExtension().toStdString();
            plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
            patch_name = plugin_name + std::string(".pd");
            patch_path = plugin_path;
            return true;
        }
        else
        {
            errors.push_back(plugin.getFullPathName().toStdString());
        }
    }
#endif
    return false;
}

CamomileEnvironment::CamomileEnvironment()
{
    if(localize())
    {
        FileInputStream stream(File(String(patch_path + String(File::getSeparatorString()).toStdString() + plugin_name + ".txt")));
        if(stream.openedOk())
        {
            while(!stream.isExhausted())
            {
                auto entry = CamomileParser::getLine(stream.readNextLine().toStdString());
                if(!entry.first.empty())
                {
                    try
                    {
                        if(entry.first == "param")
                        {
                            params.push_back(CamomileParser::getString(entry.second));
                        }
                        else if(entry.first == "program")
                        {
                            programs.push_back(CamomileParser::getString(entry.second));
                        }
                        else if(entry.first == "buse")
                        {
                            buses.push_back(CamomileParser::getTwoIntegers(entry.second));
                        }
                        else if(entry.first == "midiin")
                        {
                            if(state.test(init_midi_in))
                                throw std::string("already defined");
                            midi_in_support = CamomileParser::getBool(entry.second);
                            state.set(init_midi_in);
                        }
                        else if(entry.first == "midiout")
                        {
                            if(state.test(init_midi_out))
                                throw std::string("already defined");
                            midi_out_support = CamomileParser::getBool(entry.second);
                            state.set(init_midi_out);
                        }
                        else if(entry.first == "playhead")
                        {
                            if(state.test(init_play_head))
                                throw std::string("already defined");
                            play_head_level = static_cast<int>(CamomileParser::getBool(entry.second));
                            state.set(init_play_head);
                        }
                        else if(entry.first == "midionly")
                        {
                            if(state.test(init_midi_only))
                                throw std::string("already defined");
                            midi_only = CamomileParser::getBool(entry.second);
                            state.set(init_midi_only);
                        }
                        else if(entry.first == "latency")
                        {
                            if(state.test(init_latency))
                                throw std::string("already defined");
                            latency_samples = CamomileParser::getInteger(entry.second);
                            state.set(init_latency);
                        }
                        else if(entry.first == "taillength")
                        {
                            if(state.test(init_tail_length))
                                throw std::string("already defined");
                            tail_length_sec = CamomileParser::getFloat(entry.second);
                            state.set(init_tail_length);
                        }
                        else if(entry.first == "code")
                        {
                            if(state.test(init_code))
                                throw std::string("already defined");
                            plugin_code = CamomileParser::getHexadecimalCode(entry.second);
                            state.set(init_code);
                        }
                        else
                        {
                            errors.push_back(entry.first + " unknown option");
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
            errors.push_back("can't find the configuration file.");
        }
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


