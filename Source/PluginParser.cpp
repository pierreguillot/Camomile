/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginParser.h"
#include <iostream>

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
            {
                return static_cast<bool>(val == 1);
            }
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
        if(isdigit(static_cast<int>(value[0])) ||
           (value.size() > 1 && value[0] == '-'  && isdigit(static_cast<int>(value[1]))))
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
        if(isdigit(static_cast<int>(value[0])) ||
           (value.size() > 1 && value[0] == '-'  && isdigit(static_cast<int>(value[1]))))
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
        if(isdigit(static_cast<int>(value[0])) ||
           (value.size() > 1 && value[0] == '-'  && isdigit(static_cast<int>(value[1]))))
        {
            size_t next = value.find_first_of(' ');
            if(next != std::string::npos)
            {
                next = value.find_first_not_of(' ', next+1);
                if(next != std::string::npos &&
                   (isdigit(static_cast<int>(value[next])) ||
                    (value.size() > next+1 && value[next] == '-'  && isdigit(static_cast<int>(value[next+1])))) )
                {
                    return std::pair<int, int>(atoi(value.c_str()),atoi(value.c_str()+next));
                }
            }
        }
        throw std::string("'") + value + std::string("' not a double integer");
    }
    throw std::string("is empty");
}

std::pair<size_t, size_t> CamomileParser::getTwoUnsignedIntegers(std::string const& value)
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
                    return std::pair<size_t, size_t>(static_cast<size_t>(atol(value.c_str())), static_cast<size_t>(atol(value.c_str()+next)));
                }
            }
        }
        throw std::string("'") + value + std::string("' not a double unsigned integer");
    }
    throw std::string("is empty");
}

std::map<std::string, std::string> CamomileParser::getOptions(std::string const& value)
{
    std::map<std::string, std::string> options;
    size_t key1 = value.find_first_of('-');
    while(key1 != std::string::npos && ++key1 != std::string::npos)
    {
        size_t const key2 = value.find_first_of(' ', key1);
        if(key2 != std::string::npos)
        {
            std::string const name = value.substr(key1, key2-key1);
            if(!options.count(name))
            {
                const size_t value1 = value.find_first_not_of(' ', key2);
                if(value1 != std::string::npos)
                {
                    size_t value2 = value.find_first_of('-', key2);
                    while(value2+1 < value.size() && isdigit(static_cast<int>(value[value2+1])))
                    {
                        value2 = value.find_first_of('-', value2+1);
                    }
                    if(value2 == value1) { throw std::string("option '" + name + "' is empty"); }
                    else if(value2 != std::string::npos)
                    {
                        key1 = value2;
                        value2 = value.find_last_not_of(' ', value2-1)+1;
                        std::string const val = value.substr(value1, value2-value1);
                        options[name] = val;
                    }
                    else
                    {
                        key1 = value2;
                        std::string const val = value.substr(value1);
                        options[name] = val;
                    }
                }
                else { throw std::string("option '" + name + "' is empty"); }
            }
            else { throw std::string("option '" + name + "' aleady defined"); }
        }
        else { throw std::string("option '" + value.substr(key1) + "' is empty"); }
    }
    return options;
}

std::vector<std::string> CamomileParser::getList(std::string const& value)
{
    std::vector<std::string> list;
    size_t start = 0;
    if(!value.empty())
    {
        while(start != std::string::npos)
        {
            size_t const next = value.find_first_of('/', start);
            if(next != std::string::npos)
            {
                size_t end = next;
                while(value[end-1] == ' ' && (end-1) > start) { --end; }
                std::string const val = value.substr(start, end-start);
                if(val.empty())
                {
                    throw std::string("'") + value + std::string("' list has an invalid argument");
                }
                list.push_back(val);
                start = value.find_first_not_of(" ", next+1);
            }
            else
            {
                size_t end = value.size();
                while(value[end-1] == ' ' && (end-1) > start) { --end; }
                std::string const val = value.substr(start, end-start);
                if(val.empty())
                {
                    throw std::string("'") + value + std::string("' list has an invalid argument");
                }
                list.push_back(val);
                start = std::string::npos;
            }
        }
        return list;
    }
    throw std::string("is empty");
}





