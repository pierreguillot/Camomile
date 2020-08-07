/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


// ======================================================================================== //
//                                      PARAMETER                                           //
// ======================================================================================== //

class CamomileAudioParameter : public AudioProcessorParameterWithID
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
    
    float getValue() const override;
    float getOriginalScaledValue() const;
    
    void setValue(float newValue) override;
    void setOriginalScaledValue(float newValue);
    void setOriginalScaledValueNotifyingHost(float newValue);
    
    float getDefaultValue() const override;
    int getNumSteps() const override;
    
    bool isDiscrete() const override;
    String getText(float value, int maximumStringLength) const override;
    float getValueForText(const String& text) const override;
    
    bool isOrientationInverted() const override;
    bool isAutomatable() const override;
    bool isMetaParameter() const override;
    
    bool isNumeric() const { return m_elements.isEmpty(); }
    bool isList() const { return !m_elements.isEmpty(); }
    
    static CamomileAudioParameter* parse(const std::string& definition);
    static void saveStateInformation(XmlElement& xml, Array<AudioProcessorParameter*> const& parameters);
    static void loadStateInformation(XmlElement const& xml, Array<AudioProcessorParameter*> const& parameters);
private:
    std::atomic<float> m_value;
    
    float const m_minimum;
    float const m_maximum;
    float const m_default;
    int   const m_nsteps;
    
    bool const  m_automatable;
    bool const  m_meta;
    
    StringArray const m_elements;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileAudioParameter)
};

