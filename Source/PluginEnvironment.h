/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include <string>

//! @brief The class manages the global environmment for Camomile
class CamomileEnvironment
{
public:
    
    //! @brief Gets the name used by the plugin.
    static const char* getPluginNameUTF8();
    
    //! @brief Gets the name used by the plugin.
    static std::string getPluginName();
    
    //! @brief Gets the ID used by the plugin.
    static long getPluginID();
    
    //! @brief Gets the path to the Pd patch.
    static std::string getPatchPath();
    
    //! @brief Gets the name to the Pd patch.
    static std::string getPatchName();
    
    //! @brief Gets if the environment is valid.
    static bool isValid();
    
private:
    static CamomileEnvironment& get();
    CamomileEnvironment();
    
    std::string plugin_name = "Camomile";
    std::string plugin_path = "";
    long        plugin_id   = 0x4b707139;
    std::string patch_name  = "Camomile.pd";
    std::string patch_path  = "";
    bool        valid       = false;
};
