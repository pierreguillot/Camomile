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
    
    typedef struct
    {
        size_t inputs;
        size_t outputs;
        std::string name;
    } bus;
    typedef std::vector<bus> buses_layout;
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
    static const char* getPluginDescriptionUTF8();

    //! @brief Gets the manufacturer of the plugin.
    static std::string getPluginManufacturer();
    
    //! @brief Gets the manufacturer of the plugin.
    static const char* getPluginManufacturerUTF8();
    
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
    
    //! @brief Gets if the plugin wants to auto reload the patch.
    static bool wantsAutoReload();
    
    //! @brief Gets if the plugin wants to store the parameters within the programs.
    static bool wantsAutoProgram();
    
    //! @brief Gets if the plugin wants to auto bypass the process.
    static bool wantsAutoBypass();
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                      PROGRAMS                                        //
    //////////////////////////////////////////////////////////////////////////////////////////
    
    //! @brief Gets the programs.
    static std::vector<std::string> const& getPrograms();
    
    //! @brief Gets the parameters.
    static std::vector<std::string> const& getParams();
    
    //! @brief Gets the channels buses layouts supported.
    static std::vector<buses_layout> const& getBusesLayouts();
    
    //! @brief Gets the parsing errors.
    static std::vector<std::string> const& getErrors();
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //                                      INITIALIZED                                     //
    //////////////////////////////////////////////////////////////////////////////////////////
    
    static bool isLatencyInitialized();
    
    static bool isTailLengthInitialized();
    
private:
    static CamomileEnvironment& get();
    bool localize();
    static size_t get_version(std::string const& v);
    CamomileEnvironment();
    
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
        init_key        = 10,
        init_compatibilty = 11,
        init_auto_reload  = 12,
        init_auto_program = 13,
        init_auto_bypass  = 14,
        init_manufacturer = 15,
        all = 16
    };
    
    std::string     plugin_name = "Camomile";
    std::string     plugin_path = "";
    std::string     plugin_desc = "";
    std::string     plugin_manufacturer = "Undefined";
    unsigned int    plugin_code = 0x4b707139;
    std::string     plugin_version  = "";
    std::string     patch_name  = "Camomile.pd";
    std::string     patch_path  = "";
    std::string     image_name  = "";
    bool            valid       = false;
    std::bitset<init_flags::all>  state;
    
    bool    midi_in_support   = false;
    bool    midi_out_support  = false;
    bool    key_support       = false;
    int     play_head_level   = 0;
    bool    midi_only         = false;
    float   tail_length_sec   = 0.f;
    int     latency_samples   = 0;
    bool    m_auto_reload     = false;
    bool    m_auto_program    = true;
    bool    m_auto_bypass     = true;
    
    std::vector<std::string>    m_programs;
    std::vector<std::string>    m_params;
    std::vector<bus>            m_buses;
    std::vector<buses_layout>   m_buses_layouts;
    
    std::vector<std::string> errors;
};
