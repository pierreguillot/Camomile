/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginParameter.h"

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
m_automatable(automatable), m_meta(meta) {}

CamomileAudioParameter::CamomileAudioParameter(const String& name, const String& label,
                                               StringArray const& elems, const String& def,
                                               const bool automatable, const bool meta) :
m_name(name), m_label(label),
m_minimum(0), m_maximum(elems.size()),
m_default(static_cast<float>(elems.indexOf(def)) / static_cast<float>(elems.size())), m_nsteps(elems.size()+1),
m_automatable(automatable), m_meta(meta),
m_elements(elems) {}

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

float CamomileAudioParameter::getDefaultValue() const
{
    return m_default;
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


