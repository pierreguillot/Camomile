/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_PROCESSOR__
#define __CAMOMILE_INTANCE_PROCESSOR__

#include "Pd.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class SliderParameter : public AudioProcessorParameter
{
public:
    SliderParameter()
    : m_valid(false), m_value (0.f), m_min(0.f), m_max(0.f),
    m_name (""), m_label(""), m_ptr(nullptr) {}
    
    SliderParameter(SliderParameter const& other)
    : m_valid(other.m_valid), m_value (other.m_value),
    m_min(other.m_min), m_max(other.m_max),
    m_name (other.m_name), m_label(other.m_label),
    m_ptr(other.m_ptr) {}
    
    SliderParameter(pd::Slider const& slider)
    :
    m_valid(true), m_value (0.f),
    m_min(slider.getMinimum()),
    m_max(slider.getMaximum()),
    m_name(slider.getName()),
    m_label(slider.getLabel()),
    m_ptr(slider.getBindingPtr())
    {setValueUnormalized(slider.getValue());}
    
    ~SliderParameter() {}
    
    SliderParameter& operator=(SliderParameter const& other)
    {
        m_valid = other.m_valid;
        m_value = other.m_value;
        m_min   = other.m_min;
        m_max   = other.m_max;
        m_name  = other.m_name;
        m_label = other.m_label;
        m_ptr   = other.m_ptr;
        return *this;
    }
    
    SliderParameter& operator=(SliderParameter&& other)
    {
        m_valid = other.m_valid;
        m_value = other.m_value;
        m_min   = other.m_min;
        m_max   = other.m_max;
        std::swap(m_name, other.m_name);
        std::swap(m_label, other.m_label);
        m_ptr   = other.m_ptr;
        return *this;
    }
    
    bool isValid() const noexcept {return m_valid;}
    
    float getValue() const final {return m_value;}
    
    float getValueUnormalized() const
    {
        if(m_min < m_max)
        {
            return m_value * (m_max - m_min) + m_min;
        }
        return m_value * (m_min - m_max) + m_max;
    }
    
    void setValue (float newValue) final {m_value = newValue;}
    
    void setValueUnormalized (float newValue)
    {
        if(m_min < m_max)
        {
            m_value = (newValue - m_min) / (m_max - m_min);
        }
        else
        {
            m_value = (newValue - m_max) / (m_min - m_max);
        }
    }
    
    float getDefaultValue() const final {return 0.f;}
    
    String getName(int maximumStringLength) const final {return m_name;}
    
    String getLabel() const final {return m_label;}
    
    String getText (float value, int size) const final {return String(getValueUnormalized());}
    
    float getValueForText (const String& text) const final {return text.getFloatValue();}
    
    bool isOrientationInverted() const final {return m_max < m_min;}

    inline void* getBindingPtr() const noexcept {return m_ptr;}

private:
    bool   m_valid;
    float  m_value;
    float  m_min;
    float  m_max;
    String m_name;
    String m_label;
    void*  m_ptr;
};

class InstanceProcessor : public AudioProcessor, public pd::Instance
{
public:
    class Listener;
    InstanceProcessor();
    ~InstanceProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(AudioSampleBuffer&, MidiBuffer&) override;

    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override {return true;};
    const String getName() const override {return String(JucePlugin_Name);};
    
    int getNumParameters() override;
    float getParameter(int index) override;
    void setParameter(int index, float newValue) override;
    float getParameterDefaultValue(int index) override;
    const String getParameterName(int index) override;
    const String getParameterText(int index) override;
    String getParameterText(int index, int size) override;
    String getParameterLabel (int index) const override;
    int getParameterNumSteps(int index) override;
    bool isParameterAutomatable(int index) const override;
    bool isParameterOrientationInverted (int index) const override;
    bool isMetaParameter(int index) const override;
     
    const String getInputChannelName(int index) const override {return String(index + 1);}
    const String getOutputChannelName(int index) const override {return String(index + 1);}
    bool isInputChannelStereoPair(int index) const override {return true;}
    bool isOutputChannelStereoPair(int index) const override {return true;}

    bool acceptsMidi() const override {return bool(JucePlugin_WantsMidiInput);}
    bool producesMidi() const override {return bool(JucePlugin_ProducesMidiOutput);}
    bool silenceInProducesSilenceOut() const override {return false;}
    double getTailLengthSeconds() const override {return 0.0;}

    int getNumPrograms() override {return 1;}
    int getCurrentProgram() override {return 0;}
    void setCurrentProgram(int index) override {}
    const String getProgramName(int index) override {return String();}
    void changeProgramName(int index, const String& newName) override {}

    void getStateInformation(MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;
    
    void loadPatch(const juce::File& file);
    inline const pd::Patch getPatch() const noexcept {return m_patch;}
    inline pd::Patch getPatch() noexcept {return m_patch;}
    
    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    
    class Listener
    {
    public:
        inline constexpr Listener() {}
        inline virtual ~Listener() {}
        virtual void patchChanged() = 0;
    };

private:
    pd::Patch                       m_patch;
    std::set<Listener*>             m_listeners;
    std::vector<SliderParameter>    m_parameters;
    mutable std::mutex              m_mutex;
    
    void parametersChanged();
    std::vector<Listener*> getListeners() const noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstanceProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
