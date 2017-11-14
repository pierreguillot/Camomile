/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginAtomParser.h"
#include <stdexcept>
#include <cmath>

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




