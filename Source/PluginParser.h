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
#include "PluginConfig.h"


// ======================================================================================== //
//                                      PARSER                                             //
// ======================================================================================== //

class CamomileParser
{
public:
    using bus = CamomileEnvironment::bus;
    using buses_layout = CamomileEnvironment::buses_layout;
    
    static std::pair<std::string, std::string> getLine(std::string const& line);
    static std::map<std::string, std::string> getOptions(std::string const& value);
    static std::vector<std::string> getList(std::string const& value);
    static bool getBool(std::string const& value);
    static int getInteger(std::string const& value);
    static float getFloat(std::string const& value);
    static unsigned int getHexadecimalCode(std::string const& value);
    static std::string getString(std::string const& value);
    static std::pair<int, int> getTwoIntegers(std::string const& value);
    static std::pair<size_t, size_t> getTwoUnsignedIntegers(std::string const& value);
    
    static buses_layout getBusesLayout(std::string const& value);
    
private:
    static size_t getNios(std::string const& value, size_t& pos);
    static bus getBus(std::string const& value, size_t& pos);
};

