/*
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


/*******************************************************************************
 The block below describes the properties of this module, and is read by
 the Projucer to automatically generate project code that uses it.
 For details about the syntax and how to create or use a module, see the
 JUCE Module Format.txt file.


 BEGIN_JUCE_MODULE_DECLARATION

  ID:               juce_audio_plugin_client_LV2
  vendor:
  version:          0.0.1
  name:             JUCE audio plugin client LV2 classes
  description:      Classes for building LV2 plugins.
  website:
  license:          

  searchpaths: LV2/lv2
  dependencies:    juce_audio_plugin_client

 END_JUCE_MODULE_DECLARATION

*******************************************************************************/


#pragma once
#define JUCE_AUDIO_PLUGIN_CLIENT_LV2_H_INCLUDED

#include <juce_audio_plugin_client/juce_audio_plugin_client.h>

/** Config: JUCE_LV2_WANTS_FIXED_BLOCK_SIZE
 
 Enable this if  your LV2 plug-in requires a fixed block size.
 */
#ifndef JUCE_LV2_WANTS_FIXED_BLOCK_SIZE
#define JUCE_LV2_WANTS_FIXED_BLOCK_SIZE 0
#endif

/** Config: JUCE_LV2_SUPPORTS_PRESETS
 
 Enable this if  your LV2 plug-in supports presets.
 */
#ifndef JUCE_LV2_SUPPORTS_PRESETS
#define JUCE_LV2_SUPPORTS_PRESETS 1
#endif
