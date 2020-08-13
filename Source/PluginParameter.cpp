/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginParameter.h"
#include "PluginParser.h"
#include <cmath>

// ======================================================================================== //
//                                      PARAMETER                                           //
// ======================================================================================== //

CamomileAudioParameter::CamomileAudioParameter(const String& name, const String& label,
                                               const float min, const float max,
                                               const float def, const int nsteps,
                                               const bool automatable, const bool meta) :
RangedAudioParameter(name.toLowerCase().replaceCharacter(' ', '_'), name, label),
m_norm_range(min, max, nsteps > 1 ? (max - min) / static_cast<float>(nsteps - 1) : 0.f),
m_default(convertTo0to1(def)),
m_automatable(automatable),
m_meta(meta)
{
    m_value = convertFrom0to1(getDefaultValue());
}

CamomileAudioParameter::CamomileAudioParameter(const String& name, const String& label,
                                               StringArray const& elems, const int def,
                                               const bool automatable, const bool meta) :
RangedAudioParameter(name.toLowerCase().replaceCharacter(' ', '_'), name, label),
m_norm_range(0.f, static_cast<float>(elems.size() - 1), 1.f),
m_default(convertTo0to1(static_cast<float>(def))),
m_automatable(automatable),
m_meta(meta),
m_elements(elems)
{
    m_value = convertFrom0to1(getDefaultValue());
}

CamomileAudioParameter::~CamomileAudioParameter() {}

NormalisableRange<float> const& CamomileAudioParameter::getNormalisableRange() const
{
    return m_norm_range;
}

float CamomileAudioParameter::getValue() const
{
    return convertTo0to1(m_value);
}

void CamomileAudioParameter::setValue(float newValue)
{
    m_value = convertFrom0to1(newValue);
}

float CamomileAudioParameter::getDefaultValue() const
{
    return m_default;
}

String CamomileAudioParameter::getText(float value, int maximumStringLength) const
{
    auto const mappedValue = convertFrom0to1(value);
    if(m_elements.isEmpty())
    {
        auto const isInterger = m_norm_range.interval > 0.0 && (std::abs(m_norm_range.interval - std::floor(m_norm_range.interval)) < std::numeric_limits<float>::epsilon() && std::abs(m_norm_range.start - std::floor(m_norm_range.start))  < std::numeric_limits<float>::epsilon());
        if(isInterger)
        {
            return maximumStringLength > 0 ? String(static_cast<int>(mappedValue)).substring(0, maximumStringLength) :  String(static_cast<int>(mappedValue));
        }
        return maximumStringLength > 0 ? String(mappedValue, 2).substring(0, maximumStringLength) :  String(mappedValue, 2);
    }
    else
    {
        auto const index = std::min(std::max(static_cast<int>(floor(mappedValue)), 0), m_elements.size() - 1);
        return maximumStringLength > 0 ? m_elements[index].substring(0, maximumStringLength) : m_elements[index];
    }
}

float CamomileAudioParameter::getValueForText(const String& text) const
{
    if(m_elements.isEmpty())
    {
        return convertTo0to1(text.getFloatValue());
    }
    auto const index = std::min(std::max(m_elements.indexOf(text), 0), m_elements.size() - 1);
    return convertTo0to1(static_cast<float>(index));
}

bool CamomileAudioParameter::isDiscrete() const
{
    return !m_elements.isEmpty() || m_norm_range.interval > 0.f;
}

bool CamomileAudioParameter::isOrientationInverted() const
{
    return m_norm_range.start > m_norm_range.end;
}

bool CamomileAudioParameter::isAutomatable() const
{
    return m_automatable;
}

bool CamomileAudioParameter::isMetaParameter() const
{
    return m_meta;
}

CamomileAudioParameter* CamomileAudioParameter::parse(const std::string& definition)
{
    auto const options = CamomileParser::getOptions(definition);
    if(options.count("list"))
    {
        String name, label;
        float def = 0.f;
        bool autom = true, meta = false;
        std::vector<std::string> telems;
        for(auto const& option : options)
        {
            if(option.first == "list")
            {
                telems = CamomileParser::getList(option.second);
            }
            else if(option.first == "name")
            {
                name = CamomileParser::getString(option.second);
            }
            else if(option.first == "label")
            {
                label = CamomileParser::getString(option.second);
            }
            else if(option.first == "default")
            {
                def = CamomileParser::getFloat(option.second);
            }
            else if(option.first == "auto")
            {
                autom = CamomileParser::getBool(option.second);
            }
            else if(option.first == "meta")
            {
                meta = CamomileParser::getBool(option.second);
            }
            else if(option.first == "min" || option.first == "max" || option.first == "nsteps")
            {
                throw std::string("enumarated doesn't support the option ") + option.first;
            }
            else
            {
                throw std::string("unknown option ") + option.first;
            }
        }
        if(def >= telems.size())
            throw std::string("default value superior to list size");
        StringArray elems;
        for(auto const& el : telems) { elems.add(el); }
        return new CamomileAudioParameter(name, label, elems, static_cast<int>(def), autom, meta);
    }
    else
    {
        String name, label;
        float def = 0.f, min = 0.f, max = 1.f;
        bool autom = true,  meta = false;
        int nsteps = 0;
        for(auto const& option : options)
        {
            if(option.first == "name")
            {
                name = CamomileParser::getString(option.second);
            }
            else if(option.first == "label")
            {
                label = CamomileParser::getString(option.second);
            }
            else if(option.first == "min")
            {
                min = CamomileParser::getFloat(option.second);
                if(!options.count("default"))
                    def = min;
            }
            else if(option.first == "max")
            {
                max = CamomileParser::getFloat(option.second);
            }
            else if(option.first == "default")
            {
                def = CamomileParser::getFloat(option.second);
            }
            else if(option.first == "auto")
            {
                autom = CamomileParser::getBool(option.second);
            }
            else if(option.first == "meta")
            {
                meta = CamomileParser::getBool(option.second);
            }
            else if(option.first == "nsteps")
            {
                nsteps = CamomileParser::getInteger(option.second);
            }
            else
            {
                throw std::string("unknown option ") + option.first;
            }
        }
        if(def > max || def < min)
            throw std::string("default value out of range");
        return new CamomileAudioParameter(name, label, min, max, def, nsteps, autom, meta);
    }
}

void CamomileAudioParameter::saveStateInformation(XmlElement& xml, Array<AudioProcessorParameter*> const& parameters)
{
    XmlElement* params = xml.createNewChildElement("params");
    if(params)
    {
        for(int i = 0; i < parameters.size(); ++i)
        {
            params->setAttribute(String("param") + String(i+1), static_cast<double>(parameters[i]->getValue()));
        }
    }
}

void CamomileAudioParameter::loadStateInformation(XmlElement const& xml, Array<AudioProcessorParameter*> const& parameters)
{
    XmlElement const* params = xml.getChildByName(juce::StringRef("params"));
    if(params)
    {
        for(int i = 0; i < parameters.size(); ++i)
        {
            const float navalue = static_cast<float>(params->getDoubleAttribute(String("param") + String(i+1),
                                                                                static_cast<double>(parameters[i]->getValue())));
            parameters[i]->setValueNotifyingHost(navalue);
        }
    }
}




