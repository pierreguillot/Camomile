/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginParameter.h"
#include <stdexcept>

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
m_minimum(0), m_maximum(elems.size()),
m_default(static_cast<float>(elems.indexOf(def)) / static_cast<float>(elems.size())), m_nsteps(elems.size()+1),
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
     m_value = newValue;
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
        return m_elements[int(value * m_elements.size())];
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
        return static_cast<float>(m_elements.indexOf(text)) / static_cast<float>(m_elements.size());
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

CamomileAudioParameter* CamomileAudioParameter::parse(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 2 && list[0].isSymbol() && list[1].isSymbol())
    {
        String const name = (list.size() > 0 && list[0].isSymbol()) ? list[0].getSymbol() : String("");
        String const label = (list.size() > 1 && list[1].isSymbol()) ? list[1].getSymbol() : String("");
        if(list.size() >= 4 && list[2].isSymbol() && list[3].isSymbol())
        {
            const float min = (list.size() > 2 && list[2].isFloat()) ? list[2].getFloat() : 0;
            const float max = (list.size() > 3 && list[3].isFloat()) ? list[3].getFloat() : 1;
            const float def = (list.size() > 4 && list[4].isFloat()) ? list[4].getFloat() : min;
            const int nsteps = (list.size() > 5 && list[5].isFloat()) ? static_cast<int>(list[5].getFloat()) : 0;
            const int autom = (list.size() > 6 && list[6].isFloat()) ? static_cast<bool>(list[6].getFloat()) : true;
            const int meta = (list.size() > 7 && list[7].isFloat()) ? static_cast<bool>(list[7].getFloat()) : false;
            return new CamomileAudioParameter(name, label, min, max, def, nsteps, autom, meta);
        }
        else
        {
            const float min = (list.size() > 2 && list[2].isFloat()) ? list[2].getFloat() : 0;
            const float max = (list.size() > 3 && list[3].isFloat()) ? list[3].getFloat() : 1;
            const float def = (list.size() > 4 && list[4].isFloat()) ? list[4].getFloat() : min;
            const int nsteps = (list.size() > 5 && list[5].isFloat()) ? static_cast<int>(list[5].getFloat()) : 0;
            const int autom = (list.size() > 6 && list[6].isFloat()) ? static_cast<bool>(list[6].getFloat()) : true;
            const int meta = (list.size() > 7 && list[7].isFloat()) ? static_cast<bool>(list[7].getFloat()) : false;
            return new CamomileAudioParameter(name, label, min, max, def, nsteps, autom, meta);
        }
    }
    else
    {
        throw std::runtime_error("Parameter definition requires a least a name and a label.");
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




