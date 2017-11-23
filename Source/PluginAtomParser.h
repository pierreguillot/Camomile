/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PdInstance.h"

// ======================================================================================== //
//                                      PARSER                                             //
// ======================================================================================== //

class CamomileAtomParser
{
public:
    static StringArray parseList(const std::vector<pd::Atom>& list, const String& name);
    static String parseString(const std::vector<pd::Atom>& list, const String& name);
    static float parseFloat(const std::vector<pd::Atom>& list, const String& name, float const def);
    static int parseInt(const std::vector<pd::Atom>& list, const String& name, int const def);
    static bool parseBool(const std::vector<pd::Atom>& list, const String& name, bool const def);
};


class CamomileParser
{
public:
    
    static std::pair<std::string, std::string> getLine(std::string const& line);
    static bool getBool(std::string const& value);
    static int getInteger(std::string const& value);
    static float getFloat(std::string const& value);
    static unsigned int getHexadecimalCode(std::string const& value);
    static std::string const& getString(std::string const& value);
    static std::pair<int, int> getTwoIntegers(std::string const& value);
    
    /*
    static template<typename T> T perform(std::string const& name, std::vector<std::string> const& values, T const def, std::vector<std::string>& errors)
    {
        T res = def;
        if(!values.empty())
        {
            res = perform(values[0], def);
            if(values.size() > 1) { errors.push_back(name + " already defined."); }
        }
        else { errors.push_back(name + " undefined."); }
    }
    
    static void parse(std::string const& name, std::vector<std::string> const& values, unsigned int& def, std::vector<std::string>& errors)
    {
        if(!values.empty() && !value.empty())
        {
            unsigned int ret = 0;
            if(value.size() >= 4 &&
               (isupper(static_cast<int>(value[0])) || isupper(static_cast<int>(value[1])) ||
                isupper(static_cast<int>(value[2])) || isupper(static_cast<int>(value[3]))))
            {
                for (int i = 0; i < 4; ++i)
                    ret = (ret << 8U) | (static_cast<unsigned int>(value[i]) & 0xffU);
                def = ret;
            }
            else { errors.push_back("code must contain 4 characters with at least one upper case."); }
            if(values.size() > 1) { errors.push_back("code already defined."); }
        }
    }
    
    static template <typename T> void parse(std::string const& name, std::vector<std::string> const& values, bool& def, std::vector<std::string>& errors)
    {
        if(!values.empty() && !value.empty())
        {
            if(isdigit(static_cast<int>(value[0])))
                def = static_cast<bool>(atoi(value.c_str()));
            else
            {
                if(value.size() >= 4 &&
                   tolower(static_cast<int>(value[0])) == 't' &&  tolower(static_cast<int>(value[1])) == 'r' &&
                   tolower(static_cast<int>(value[2])) == 'u' && tolower(static_cast<int>(value[3])) == 'e')
                    def = true;
                else if(value.size() >= 5 && tolower(static_cast<int>(value[0])) == 'f' &&
                        tolower(static_cast<int>(value[1])) == 'a' &&  tolower(static_cast<int>(value[2])) == 'l' &&
                        tolower(static_cast<int>(value[3])) == 's' && tolower(static_cast<int>(value[4])) == 'e')
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
        if(!values.empty() && !value.empty())
        {
            if(isdigit(static_cast<int>(value[0])))
                def = atoi(value.c_str());
            else
                errors.push_back(name + " must be an integer.");
            if(values.size() > 1) { errors.push_back(name + " already defined."); }
        }
        else { errors.push_back(name + " undefined."); }
    }
    
    static void parse(std::string const& name, std::vector<std::string> const& values, float& def, std::vector<std::string>& errors)
    {
        if(!values.empty() && !value.empty())
        {
            if(isdigit(static_cast<int>(value[0])))
                def = atof(value.c_str());
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
                const size_t separator = value.find_first_of(" ");
                if(separator != std::string::npos)
                {
                    std::string const input = value.substr(0, separator);
                    std::string const output = value.substr(separator+1);
                    
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
     */
};

