/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEnvironment.h"
#include "../JuceLibraryCode/JuceHeader.h"



CamomileEnvironment& CamomileEnvironment::get()
{
    static CamomileEnvironment env;
    return env;
}

const char* CamomileEnvironment::getPluginNameUTF8()
{
    return get().plugin_name.c_str();
}

std::string CamomileEnvironment::getPluginName()
{
    return get().plugin_name;
}

long CamomileEnvironment::getPluginID()
{
    return get().plugin_id;
}

std::string CamomileEnvironment::getPatchPath()
{
    return get().patch_path;
}

std::string CamomileEnvironment::getPatchName()
{
    return get().patch_name;
}

bool CamomileEnvironment::isValid()
{
    return get().valid;
}

CamomileEnvironment::CamomileEnvironment()
{
    juce::File const plugin(juce::File::getSpecialLocation(juce::File::currentApplicationFile));
    if(plugin.exists())
    {
        plugin_name = plugin.getFileNameWithoutExtension().toStdString();
        plugin_path = plugin.getParentDirectory().getFullPathName().toStdString();
        patch_name = plugin_name + std::string(".pd");
#ifdef JUCE_MAC
        patch_path = plugin_name + std::string("/Contents/Resources");
#else
        patch_path = plugin_name + std::string("/") + plugin_name;
#endif
        juce::File const patch(String(patch_path + patch_name));
        if(patch.exists())
        {
            valid = patch.exists();
        }
    }
}

