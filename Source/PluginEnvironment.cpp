/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEnvironment.h"
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

std::vector<std::pair<std::string, std::string>> const& CamomileEnvironment::getBuses() { return get().buses; }

std::vector<std::string> const& CamomileEnvironment::getErrors() { return get().errors; }

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          CONSTRUCTOR                                     //
//////////////////////////////////////////////////////////////////////////////////////////////


static void parse(std::string const& name, std::vector<std::string> const& values, unsigned int& def, std::vector<std::string>& errors)
{
    if(!values.empty() && !values[0].empty())
    {
        unsigned int ret = 0;
        if(values[0].size() >= 4 &&
           (isupper(static_cast<int>(values[0][0])) || isupper(static_cast<int>(values[0][1])) ||
            isupper(static_cast<int>(values[0][2])) || isupper(static_cast<int>(values[0][3]))))
        {
            for (int i = 0; i < 4; ++i)
                ret = (ret << 8U) | (static_cast<unsigned int>(values[0][i]) & 0xffU);
            def = ret;
        }
        else { errors.push_back("code must contain 4 characters with at least one upper case."); }
        if(values.size() > 1) { errors.push_back("code already defined."); }
    }
}

static void parse(std::string const& name, std::vector<std::string> const& values, bool& def, std::vector<std::string>& errors)
{
    if(!values.empty() && !values[0].empty())
    {
        if(isdigit(static_cast<int>(values[0][0])))
            def = static_cast<bool>(atoi(values[0].c_str()));
        else
        {
            if(values[0].size() >= 4 &&
               tolower(static_cast<int>(values[0][0])) == 't' &&  tolower(static_cast<int>(values[0][1])) == 'r' &&
               tolower(static_cast<int>(values[0][2])) == 'u' && tolower(static_cast<int>(values[0][3])) == 'e')
                def = true;
            else if(values[0].size() >= 5 && tolower(static_cast<int>(values[0][0])) == 'f' &&
                    tolower(static_cast<int>(values[0][1])) == 'a' &&  tolower(static_cast<int>(values[0][2])) == 'l' &&
                    tolower(static_cast<int>(values[0][3])) == 's' && tolower(static_cast<int>(values[0][4])) == 'e')
                def = false;
            else
                errors.push_back(name + " must be an boolean.");
        }
        if(values.size() > 1) { errors.push_back(name + " already defined."); }
    }
    else { errors.push_back(name + " undefined."); }
}

static void parse(std::string const& name, std::vector<std::string> const& values, int& def, std::vector<std::string>& errors)
{
    if(!values.empty() && !values[0].empty())
    {
        if(isdigit(static_cast<int>(values[0][0])))
            def = atoi(values[0].c_str());
        else
            errors.push_back(name + " must be an integer.");
        if(values.size() > 1) { errors.push_back(name + " already defined."); }
    }
    else { errors.push_back(name + " undefined."); }
}

static void parse(std::string const& name, std::vector<std::string> const& values, float& def, std::vector<std::string>& errors)
{
    if(!values.empty() && !values[0].empty())
    {
        if(isdigit(static_cast<int>(values[0][0])))
            def = atof(values[0].c_str());
        else
            errors.push_back(name + " must be a float.");
        if(values.size() > 1) { errors.push_back(name + " already defined."); }
    }
    else { errors.push_back(name + " undefined."); }
}

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

static void parse(std::string const& name, std::vector<std::string> const& values,
                  std::vector<std::string>& def, std::vector<std::string>& errors)
{
    if(!values.empty())
    {
        for(size_t i = 0; i < values.size(); ++i)
        {
            if(!values[i].empty())
            {
                if(values[i].back() == ';')
                    def.push_back(values[i].substr(0, values[i].size()-1));
                else
                    def.push_back(values[i]);
            }
            else { errors.push_back(name + " " + std::to_string(i) + " needs a name."); }
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
            String line = stream.readNextLine();
            while(line.isNotEmpty())
            {
                int const limit = line.indexOfAnyOf(StringRef(" ;\n"));
                String const name = line.substring(0, limit);
                if(name.isNotEmpty())
                {
                    line.trimEnd();
                    options[name.toStdString()].push_back(line.substring(limit+1).toStdString());
                }
                line = stream.readNextLine();
            }
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
            else if(it.first == "program")
            {
                parse("program", it.second, programs, errors);
            }
            else if(it.first == "buses")
            {
                parse("buses", it.second, buses, errors);
            }
            else if(it.first == "code")
            {
                parse("code", it.second, plugin_code, errors);
            }
            else if(it.first == "midiin")
            {
                parse("midiin", it.second, midi_in_support, errors);
            }
            else if(it.first == "midiout")
            {
                parse("midiout", it.second, midi_out_support, errors);
            }
            else if(it.first == "playhead")
            {
                parse("playhead", it.second, play_head_support, errors);
            }
            else if(it.first == "midionly")
            {
                parse("midionly", it.second, midi_only, errors);
            }
            else if(it.first == "taillength")
            {
                parse("taillength", it.second, tail_length_sec, errors);
            }
            else if(it.first == "latency")
            {
                parse("latency", it.second, latency_samples, errors);
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
        buses.push_back({"stereo", "stereo"});
    }
    
}


