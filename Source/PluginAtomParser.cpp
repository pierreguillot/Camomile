/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginAtomParser.h"
#include <stdexcept>
#include <cmath>

StringArray CamomileAtomParser::parseList(const std::vector<pd::Atom>& list, const String& name)
{
    StringArray elemslist;
    String const elems = CamomileAtomParser::parseString(list, name);
    if(elems.isNotEmpty())
    {
        int start = 0, next = elems.indexOfChar(0, '/');
        while(next != -1)
        {
            String const newel = elems.substring(start, next);
            if(newel.isNotEmpty())
            {
                elemslist.add(newel);
                start = next+1;
                next = elems.indexOfChar(start, '/');
            }
        }
        String const newel = elems.substring(start);
        if(newel.isNotEmpty())
        {
            elemslist.add(newel);
        }
    }
    return elemslist;
}

String CamomileAtomParser::parseString(const std::vector<pd::Atom>& list, const String& name)
{
    String def;
    auto it = std::find(list.begin(), list.end(), name.toStdString());
    if(it != list.end())
    {
        while(++it != list.end())
        {
            if(it->isSymbol())
            {
                const String sym = it->getSymbol();
                if(sym.isNotEmpty())
                {
                    if(sym[0] == '-') {
                        return def; }
                    if(def.isEmpty()) {
                        def = sym; }
                    else {
                        def += String(" ") + sym; }
                }
            }
            else if(it->isFloat())
            {
                if(!def.isEmpty()) {
                    def += String(" "); }
                def += String(it->getFloat());
            }
        }
    }
    return def;
}

float CamomileAtomParser::parseFloat(const std::vector<pd::Atom>& list, const String& name, float const def)
{
    auto it = std::find(list.begin(), list.end(), name.toStdString());
    if(it != list.end())
    {
        if(++it != list.end() && it->isFloat())
        {
            return it->getFloat();
        }
    }
    return def;
}

int CamomileAtomParser::parseInt(const std::vector<pd::Atom>& list, const String& name, int const def)
{
    return static_cast<int>(parseFloat(list, name, static_cast<float>(def)));
}

bool CamomileAtomParser::parseBool(const std::vector<pd::Atom>& list, const String& name, bool const def)
{
    auto it = std::find(list.begin(), list.end(), name.toStdString());
    if(it != list.end())
    {
        if(++it != list.end())
        {
            if(it->isFloat())
                return static_cast<bool>(it->getFloat());
            else if(it->getSymbol() == "true")
                return true;
            else if(it->getSymbol() == "false")
                return false;
        }
    }
    return def;
}




std::pair<std::string, std::string> CamomileParser::getLine(std::string const& line)
{
    size_t const start = line.find_first_not_of(' ');
    if(start != std::string::npos)
    {
        size_t const end = line.find_first_of(' ', start+1);
        if(end != std::string::npos)
        {
            std::string const name = line.substr(start, end-start);
            size_t const start2 = line.find_first_not_of(' ', end);
            if(start2 != std::string::npos)
            {
                std::string value = line.substr(start2);
                while(value.back() == ';' || value.back() == ' ') { value.pop_back(); }
                return std::pair<std::string, std::string>(name, value);
            }
            else { return std::pair<std::string, std::string>(name, std::string()); }
        }
        else
        {
            std::string name = line.substr(start);
            while(name.back() == ';') { name.pop_back(); }
            return std::pair<std::string, std::string>(name, std::string());
        }
    }
    return std::pair<std::string, std::string>();
}

bool CamomileParser::getBool(std::string const& value)
{
    if(!value.empty())
    {
        if(isdigit(static_cast<int>(value[0])))
        {
            const int val = atoi(value.c_str());
            if(val == 0 || val ==  1)
                return static_cast<bool>(val);
            throw std::string("'") + value + std::string("' not a boolean");
        }
        else
        {
            if(value.size() == 4 &&
               tolower(static_cast<int>(value[0])) == 't' &&
               tolower(static_cast<int>(value[1])) == 'r' &&
               tolower(static_cast<int>(value[2])) == 'u' &&
               tolower(static_cast<int>(value[3])) == 'e')
                return true;
            else if(value.size() == 5 &&
                    tolower(static_cast<int>(value[0])) == 'f' &&
                    tolower(static_cast<int>(value[1])) == 'a' &&
                    tolower(static_cast<int>(value[2])) == 'l' &&
                    tolower(static_cast<int>(value[3])) == 's' &&
                    tolower(static_cast<int>(value[4])) == 'e')
                return false;
            throw std::string("'") + value + std::string("' not a boolean");
        }
    }
    throw std::string("is empty");
}

int CamomileParser::getInteger(std::string const& value)
{
    if(!value.empty())
    {
        if(isdigit(static_cast<int>(value[0])))
        {
            return atoi(value.c_str());
        }
        throw std::string("'") + value + std::string("' not an integer");
    }
    throw std::string("is empty");
}

float CamomileParser::getFloat(std::string const& value)
{
    if(!value.empty())
    {
        if(isdigit(static_cast<int>(value[0])))
        {
            return static_cast<float>(atof(value.c_str()));
        }
        throw std::string("'") + value + std::string("' not a float");
    }
    throw std::string("is empty");
}

unsigned int CamomileParser::getHexadecimalCode(std::string const& value)
{
    if(!value.empty())
    {
        if(value.size() >= 4 &&
           (isupper(static_cast<int>(value[0])) || isupper(static_cast<int>(value[1])) ||
            isupper(static_cast<int>(value[2])) || isupper(static_cast<int>(value[3]))))
        {
            unsigned int ret = 0;
            ret = (ret << 8U) | (static_cast<unsigned int>(value[0]) & 0xffU);
            ret = (ret << 8U) | (static_cast<unsigned int>(value[1]) & 0xffU);
            ret = (ret << 8U) | (static_cast<unsigned int>(value[2]) & 0xffU);
            ret = (ret << 8U) | (static_cast<unsigned int>(value[3]) & 0xffU);
            return ret;
        }
        throw std::string("'") + value + std::string("' not a hexadecimal code -  must contain 4 characters with at least one upper case");
    }
    throw std::string("is empty");
}

std::string const& CamomileParser::getString(std::string const& value)
{
    if(!value.empty())
    {
        return value;
    }
    throw std::string("is empty");
}

std::pair<int, int> CamomileParser::getTwoIntegers(std::string const& value)
{
    if(!value.empty())
    {
        if(isdigit(static_cast<int>(value[0])))
        {
            size_t next = value.find_first_of(' ');
            if(next != std::string::npos)
            {
                next = value.find_first_not_of(' ', next+1);
                if(next != std::string::npos && isdigit(static_cast<int>(value[next])))
                {
                    return std::pair<int, int>(atoi(value.c_str()),atoi(value.c_str()+next));
                }
            }
        }
        throw std::string("'") + value + std::string("' not a double integer");
    }
    throw std::string("is empty");
}







