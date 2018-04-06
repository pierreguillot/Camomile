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


// ======================================================================================== //
//                                      PARSER                                             //
// ======================================================================================== //

class CamomileParser
{
public:
    static std::pair<std::string, std::string> getLine(std::string const& line);
    static std::map<std::string, std::string> getOptions(std::string const& value);
    static std::vector<std::string> getList(std::string const& value);
    static bool getBool(std::string const& value);
    static int getInteger(std::string const& value);
    static float getFloat(std::string const& value);
    static unsigned int getHexadecimalCode(std::string const& value);
    static std::string const& getString(std::string const& value);
    static std::pair<int, int> getTwoIntegers(std::string const& value);
    static std::pair<size_t, size_t> getTwoUnsignedIntegers(std::string const& value);
};

