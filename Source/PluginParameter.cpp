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
m_name(name), m_label(label),
m_minimum(min), m_maximum(max),
m_default(def), m_nsteps(nsteps),
m_automatable(automatable), m_meta(meta) { m_value = getDefaultValue(); }

CamomileAudioParameter::CamomileAudioParameter(const String& name, const String& label,
                                               StringArray const& elems, const int def,
                                               const bool automatable, const bool meta) :
m_name(name), m_label(label),
m_minimum(0), m_maximum(elems.size() - 1),
m_default(static_cast<int>(def)), m_nsteps(elems.size()),
m_automatable(automatable), m_meta(meta),
m_elements(elems) { m_value = getDefaultValue(); }

CamomileAudioParameter::~CamomileAudioParameter() {}

String CamomileAudioParameter::getName(int maximumStringLength) const
{
    return m_name.substring(0, maximumStringLength);
}

String CamomileAudioParameter::getLabel() const
{
    return m_label;
}

float CamomileAudioParameter::getValue() const
{
    return m_value;
}

float CamomileAudioParameter::getOriginalScaledValue() const
{
    return m_value * (m_maximum - m_minimum) + m_minimum;
}

void CamomileAudioParameter::setValue(float newValue)
{
    if(isDiscrete())
    {
        newValue = floor(newValue * static_cast<float>(m_nsteps - 1)) / static_cast<float>(m_nsteps - 1);
    }
    m_value = newValue;
}

void CamomileAudioParameter::setOriginalScaledValue(float newValue)
{
    setValue((newValue - m_minimum) / (m_maximum - m_minimum));
}

void CamomileAudioParameter::setOriginalScaledValueNotifyingHost(float newValue)
{
    setValueNotifyingHost((newValue - m_minimum) / (m_maximum - m_minimum));
}

float CamomileAudioParameter::getDefaultValue() const
{
    return std::max(std::min((m_default - m_minimum) / (m_maximum - m_minimum), 1.f), 0.f);
}

int CamomileAudioParameter::getNumSteps() const
{
    return (m_nsteps > 0 && m_nsteps < 1e+37) ? m_nsteps : AudioProcessor::getDefaultNumParameterSteps();
}

bool CamomileAudioParameter::isDiscrete() const
{
    return (m_nsteps > 0 && m_nsteps < 1e+37);
}

String CamomileAudioParameter::getText(float value, int maximumStringLength) const
{
    if(m_elements.isEmpty())
    {
        value = value * (m_maximum - m_minimum) + m_minimum;
        if(isDiscrete())
        {
            value = floor(value * static_cast<float>(m_nsteps - 1)) / static_cast<float>(m_nsteps - 1);
        }
        return String(value).substring(0, maximumStringLength);
    }
    else
    {
        value = floor(std::max(std::min(value, 1.f), 0.f) * m_maximum);
        return m_elements[static_cast<int>(value)].substring(0, maximumStringLength);
    }
}

float CamomileAudioParameter::getValueForText(const String& text) const
{
    if(m_elements.isEmpty())
    {
        return text.getFloatValue();
    }
    return static_cast<float>(m_elements.indexOf(text)) / static_cast<float>(m_maximum);
}

bool CamomileAudioParameter::isOrientationInverted() const
{
    return m_minimum > m_maximum;
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
        return new CamomileAudioParameter(name, label, elems, def, autom, meta);
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

void CamomileAudioParameter::saveStateInformation(XmlElement& xml, OwnedArray<AudioProcessorParameter> const& parameters)
{
    XmlElement* params = xml.createNewChildElement("params");
    if(params)
    {
        for(int i = 0; i < parameters.size(); ++i)
        {
            params->setAttribute(String("param") + String(i+1), parameters[i]->getValue());
        }
    }
}

void CamomileAudioParameter::loadStateInformation(XmlElement const& xml, OwnedArray<AudioProcessorParameter> const& parameters)
{
    XmlElement const* params = xml.getChildByName(juce::StringRef("params"));
    if(params)
    {
        for(int i = 0; i < parameters.size(); ++i)
        {
            parameters[i]->setValue(params->getDoubleAttribute(String("param") + String(i+1), parameters[i]->getValue()));
        }
    }
}




