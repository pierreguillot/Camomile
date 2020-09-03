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

class CamomileAudioParameter : public RangedAudioParameter
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
    
    NormalisableRange<float> const& getNormalisableRange() const override;
    
    float getValue() const override;
    void setValue(float newValue) override;
    float getDefaultValue() const override;
    String getText(float value, int maximumStringLength) const override;
    float getValueForText(const String& text) const override;
    bool isDiscrete() const override;
    bool isOrientationInverted() const override;
    bool isAutomatable() const override;
    bool isMetaParameter() const override;
    
    static CamomileAudioParameter* parse(const std::string& definition);
    static void saveStateInformation(XmlElement& xml, Array<AudioProcessorParameter*> const& parameters);
    static void loadStateInformation(XmlElement const& xml, Array<AudioProcessorParameter*> const& parameters);
private:
    std::atomic<float> m_value;
    NormalisableRange<float> const m_norm_range;
    
    float const m_default;
    bool const  m_automatable;
    bool const  m_meta;
    
    StringArray const m_elements;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileAudioParameter)
};

