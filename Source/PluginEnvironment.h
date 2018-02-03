/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <bitset>

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      ENVIRONMENT                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

//! @brief The class manages the global environmment for Camomile
class CamomileEnvironment
{
public:
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                      GLOBAL                                          //
    //////////////////////////////////////////////////////////////////////////////////////////
    
    //! @brief Initialize the environment (only if you want to do it in advance).
    static bool initialize();
    
    //! @brief Gets the name used by the plugin.
    static const char* getPluginNameUTF8();
    
    //! @brief Gets the name used by the plugin.
    static std::string getPluginName();
    
    //! @brief Gets the code used by the plugin.
    static unsigned int getPluginCode();
    
    //! @brief Gets the path to the Pd patch.
    static std::string getPatchPath();
    
    //! @brief Gets the name of the Pd patch.
    static std::string getPatchName();
    
    //! @brief Gets a description of the Pd patch.
    static std::string getPatchDescription();
    
    //! @brief Gets the name to the Pd patch.
    static std::string getImageName();
    
    //! @brief Gets if the Pd version.
    static std::string getPdVersion();
    
    //! @brief Gets a description of the plugin.
    static std::string getPluginDescription();
    
    //! @brief Gets a description of the plugin.
    static std::string getPluginDescriptionUTF8();
    
    //! @brief Gets a description of the plugin.
    static std::string getPatchCredits();
    
    //! @brief Gets if the environment is valid.
    static bool isValid();
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                      OPTIONS                                         //
    //////////////////////////////////////////////////////////////////////////////////////////
    
    //! @brief Gets if the patch wants MIDI events.
    static bool wantsMidi();
    
    //! @brief Gets if the patch produces MIDI events.
    static bool producesMidi();
    
    //! @brief Gets if the patch wants play head information.
    static int getPlayHeadLevel();
    
    //! @brief Gets if the patch is valid (no audio).
    static bool isMidiOnly();
    
    //! @brief Gets the tail length in seconds.
    static float getTailLengthSeconds();
    
    //! @brief Gets the latency in samples.
    static int getLatencySamples();
    
    //! @brief Gets if the patch wants Key events.
    static bool wantsKey();
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                      PROGRAMS                                        //
    //////////////////////////////////////////////////////////////////////////////////////////
    
    //! @brief Gets the programs.
    static std::vector<std::string> const& getPrograms();
    
    //! @brief Gets the parameters.
    static std::vector<std::string> const& getParams();
    
    //! @brief Gets the channels buses supported.
    static std::vector<std::pair<int, int>> const& getBuses();
    
    //! @brief Gets the parsing errors.
    static std::vector<std::string> const& getErrors();
    
private:
    static CamomileEnvironment& get();
    bool localize();
    CamomileEnvironment();
    
    std::string     plugin_name = "Camomile";
    std::string     plugin_path = "";
    std::string     plugin_desc = "A plugin that loads Pure Data patches";
    unsigned int    plugin_code = 0x4b707139;
    std::string     patch_name  = "Camomile.pd";
    std::string     patch_path  = "";
    std::string     image_name  = "";
    bool            valid       = false;
    std::bitset<11>  state;
    
    bool    midi_in_support   = false;
    bool    midi_out_support  = false;
    bool    key_support       = false;
    int     play_head_level   = 0;
    bool    midi_only         = false;
    float   tail_length_sec   = 0.f;
    int     latency_samples   = 0;
    
    std::vector<std::string> programs;
    std::vector<std::string> params;
    std::vector<std::pair<int, int>> buses;
    
    std::vector<std::string> errors;
    
    enum init_flags
    {
        init_midi_in    = 0,
        init_midi_out   = 1,
        init_play_head  = 2,
        init_midi_only  = 3,
        init_tail_length= 4,
        init_latency    = 5,
        init_code       = 6,
        init_image      = 7,
        init_type       = 8,
        init_desc       = 9,
        init_key        = 10
    };
};
