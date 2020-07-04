/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "PluginEnvironment.h"
#define JUCE_DISPLAY_SPLASH_SCREEN 0
#define JUCE_REPORT_APP_USAGE 0
#define JucePlugin_Name CamomileEnvironment::getPluginNameUTF8()
#define JucePlugin_PluginCode CamomileEnvironment::getPluginCode()
#define JucePlugin_Desc CamomileEnvironment::getPluginDescriptionUTF8()
#define JucePlugin_LV2URI (juce::String("http://github.com/pierreguillot/Camomile/") + juce::String(JucePlugin_Name)).toUTF8()
#define JucePlugin_Manufacturer CamomileEnvironment::getPluginManufacturerUTF8()
#ifndef JucePlugin_Build_LV2
#define JucePlugin_Build_LV2 0
#endif
