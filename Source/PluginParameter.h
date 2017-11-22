/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "xpd/PdInstance.h"

// ======================================================================================== //
//                                      PARAMETER                                           //
// ======================================================================================== //

class CamomileAudioParameter : public AudioProcessorParameter
{
public:
    CamomileAudioParameter(const String& name, const String& label,
                           const float min, const float max,
                           const float def, const int nsteps,
                           const bool automatable = true, const bool meta = false);
    
    CamomileAudioParameter(const String& name, const String& label,
                           StringArray const& elemen, const int def,
                           const bool automatable = true, const bool meta = false);
    
    ~CamomileAudioParameter();
    
    String getName(int maximumStringLength) const final;
    String getLabel() const final;
    
    float getValue() const final;
    float getOriginalScaledValue() const;
    
    void setValue(float newValue) final;
    void setOriginalScaledValue(float newValue);
    void setOriginalScaledValueNotifyingHost(float newValue);
    
    float getDefaultValue() const final;
    int getNumSteps() const final;
    
    bool isDiscrete() const final;
    String getText(float value, int maximumStringLength) const final;
    float getValueForText(const String& text) const final;
    
    bool isOrientationInverted() const final;
    bool isAutomatable() const final;
    bool isMetaParameter() const final;
    
    bool isNumeric() const { return m_elements.isEmpty(); }
    bool isList() const { return !m_elements.isEmpty(); }
    
    static CamomileAudioParameter* parse(const std::vector<pd::Atom>& list);
    static void saveStateInformation(XmlElement& xml, OwnedArray<AudioProcessorParameter> const& parameters);
    static void loadStateInformation(XmlElement const& xml, OwnedArray<AudioProcessorParameter> const& parameters);
private:
    float m_value;
    String const m_name;
    String const m_label;
    
    float const m_minimum;
    float const m_maximum;
    float const m_default;
    int   const m_nsteps;
    
    bool const  m_automatable;
    bool const  m_meta;
    
    StringArray const m_elements;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileAudioParameter)
};

