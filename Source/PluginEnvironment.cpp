/*
 // Copyright (c) 2015-2018 Pierre Guillot.
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

std::string CamomileEnvironment::getPatchDescription() { return get().plugin_desc; }

std::string CamomileEnvironment::getImageName() { return get().image_name; }

std::string CamomileEnvironment::getPluginDescriptionUTF8() { return get().plugin_desc.c_str(); }

std::string CamomileEnvironment::getPluginDescription() { return get().plugin_desc; }

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

bool CamomileEnvironment::wantsKey() { return get().key_support; }

bool CamomileEnvironment::isLatencyInitialized() { return get().state.test(init_latency); }

bool CamomileEnvironment::isTailLengthInitialized() { return get().state.test(init_tail_length); }

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
        std::string const sep = String(File::getSeparatorString()).toStdString();
        std::string const ext = std::string(".txt");
        File file(patch_path + sep + plugin_name + ext);
        if(!file.exists())
        {
#ifdef JUCE_MAC
            errors.push_back("can't find the configuration file \"" + patch_path + sep + plugin_name + ext + "\"");
            return;
#else
            file = File(patch_path + sep + plugin_name + sep + plugin_name + ext);
            if(!file.exists())
            {
                errors.push_back("can't find the configuration file \"" + patch_path + sep + plugin_name + ext + "\"");
                errors.push_back("can't find the configuration file \"" + patch_path + sep + plugin_name + sep  + plugin_name + ext + "\"");
                return;
            }
#endif
        }
        FileInputStream stream(file);
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
                        else if(entry.first == "bus")
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
                        else if(entry.first == "key")
                        {
                            if(state.test(init_key))
                                throw std::string("already defined");
                            key_support = CamomileParser::getBool(entry.second);
                            state.set(init_key);
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
                        else if(entry.first == "image")
                        {
                            if(state.test(init_image))
                                throw std::string("already defined");
                            image_name = CamomileParser::getString(entry.second);
                            state.set(init_image);
                        }
                        else if(entry.first == "description")
                        {
                            if(state.test(init_desc))
                                throw std::string("already defined");
                            plugin_desc = CamomileParser::getString(entry.second);
                            state.set(init_desc);
                        }
                        else if(entry.first == "compatibility")
                        {
                            if(state.test(init_compatibilty))
                                throw std::string("already defined");
                            plugin_version = CamomileParser::getString(entry.second);
                            state.set(init_compatibilty);
                        }
                        else if(entry.first == "type")
                        {
                            if(state.test(init_type))
                                throw std::string("already defined");
                            state.set(init_type);
                            std::string const type = CamomileParser::getString(entry.second);
                            if(type == "instrument")
                            {
                                if(!JucePlugin_IsSynth)
                                    throw std::string("wrong: effect binary expected.");
                            }
                            else if(type == "effect")
                            {
                                if(JucePlugin_IsSynth)
                                    throw std::string("wrong: instrument binary expected.");
                            }
                            else
                            {
                                throw std::string("\"") + type + std::string(" \"unknown.");
                            }
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
            errors.push_back("can't open the stream \"" + patch_path + sep + "\"");
        }
    }
    
    if(!state.test(init_code)) {
        errors.push_back("code not defined."); }
    if(!state.test(init_type)) {
        errors.push_back("type not defined."); }
    if(!state.test(init_compatibilty)) {
        errors.push_back("compatibility not defined."); }
    else
    {
        size_t vpatch = 0, vplugin = 0;
        try {
            vpatch = get_version(plugin_version);
            vplugin = get_version(JucePlugin_VersionString);
        }
        catch(...) {
            errors.push_back("compatibility version wrong syntax, should be \"major.minor.bug\".");
        }
        if(vpatch > vplugin)
        {
            errors.push_back("patch has been created for a newer version of the plugin v" + plugin_version);
        }
    }
    if(buses.empty())
    {
        buses.push_back({2, 2});
        errors.push_back("no bus defined, add default bus 2 2");
    }
    if(programs.empty())
    {
        programs.push_back("");
    }
}

size_t CamomileEnvironment::get_version(std::string const& v)
{
    size_t index;
    std::string temp = v;
    const int vmajor = std::stoi(temp, &index);
    temp.erase(temp.begin(), temp.begin()+index+1);
    const int vminor = std::stoi(temp, &index);
    temp.erase(temp.begin(), temp.begin()+index+1);
    const int vbug = std::stoi(temp);
    return vmajor*100+vminor*10+vbug;
}


