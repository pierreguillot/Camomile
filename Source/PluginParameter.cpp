/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginParameter.h"
#include <stdexcept>
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
                                               StringArray const& elems, const String& def,
                                               const bool automatable, const bool meta) :
m_name(name), m_label(label),
m_minimum(0), m_maximum(elems.size() - 1),
m_default(static_cast<float>((elems.indexOf(def) != -1) ? elems.indexOf(def) : 0) / m_maximum),
m_nsteps(elems.size()),
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
        m_value = round(newValue * static_cast<float>(m_maximum)) / static_cast<float>(m_maximum);
    }
    else
    {
        m_value = newValue;
    }
}

void CamomileAudioParameter::setOriginalScaledValue(float newValue)
{
    m_value = (newValue - m_minimum) / (m_maximum - m_minimum);
}

void CamomileAudioParameter::setOriginalScaledValueNotifyingHost(float newValue)
{
    setValueNotifyingHost((newValue - m_minimum) / (m_maximum - m_minimum));
}

float CamomileAudioParameter::getDefaultValue() const
{
    return (m_default - m_minimum) / (m_maximum - m_minimum);
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
        return String(value * (m_maximum - m_minimum) + m_minimum).substring(0, maximumStringLength);
    }
    else
    {
        value = (value > 1.f) ? 1.f : value;
        value = (value < 0.f) ? 0.f : value;
        return m_elements[static_cast<int>(round(value * m_maximum))].substring(0, maximumStringLength);
    }
}

float CamomileAudioParameter::getValueForText(const String& text) const
{
    if(m_elements.isEmpty())
    {
        return text.getFloatValue();
    }
    else
    {
        return static_cast<float>(m_elements.indexOf(text)) / static_cast<float>(m_maximum);
    }
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

String CamomileAudioParameter::parseString(const std::vector<pd::Atom>& list, const String& name)
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

float CamomileAudioParameter::parseFloat(const std::vector<pd::Atom>& list, const String& name, float const def)
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

int CamomileAudioParameter::parseInt(const std::vector<pd::Atom>& list, const String& name, int const def)
{
    return static_cast<int>(parseFloat(list, name, static_cast<float>(def)));
}

bool CamomileAudioParameter::parseBool(const std::vector<pd::Atom>& list, const String& name, bool const def)
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


CamomileAudioParameter* CamomileAudioParameter::parse(const std::vector<pd::Atom>& list)
{
    String const name = parseString(list, "-name");
    if(!name.isEmpty())
    {
        String const label = parseString(list, "-label");
        String const elems = parseString(list, "-list");
        if(elems.isNotEmpty())
        {
            StringArray elems_l;
            int start = 0, next = elems.indexOfChar(1, '/');
            while(next != -1)
            {
                elems_l.add(elems.substring(start, next));
                start = next+1;
                next = elems.indexOfChar(start, '/');
            }
            elems_l.add(elems.substring(start));
            const String def = parseString(list, "-default");
            const bool autom = parseBool(list, "-auto", true);
            const bool meta = parseBool(list, "-meta", false);
            return new CamomileAudioParameter(name, label, elems_l, def, autom, meta);
        }
        else
        {
            const float min = parseFloat(list, "-min", 0);
            const float max = parseFloat(list, "-max", 1);
            const float def = parseFloat(list, "-default", min);
            const int nsteps = static_cast<int>(parseFloat(list, "-nsteps", 0));
            const bool autom = parseBool(list, "-auto", true);
            const bool meta = parseBool(list, "-meta", false);
            return new CamomileAudioParameter(name, label, min, max, def, nsteps, autom, meta);
        }
    }
    else
    {
        throw std::runtime_error("Wrong parameter definition.");
    }
    return nullptr;
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




