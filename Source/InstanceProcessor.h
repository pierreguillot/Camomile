/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_PROCESSOR__
#define __CAMOMILE_INTANCE_PROCESSOR__

#include "Pd.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class InstanceParameter : public AudioProcessorParameter
{
public:
    InstanceParameter()
    : m_valid(false), m_value (0.f), m_min(0.f), m_max(0.f),
    m_name (""), m_label(""), m_bname(nullptr), m_nsteps(0) {}
    
    InstanceParameter(InstanceParameter const& other)
    : m_valid(other.m_valid), m_value (other.m_value),
    m_min(other.m_min), m_max(other.m_max),
    m_name (other.m_name), m_label(other.m_label),
    m_bname(other.m_bname), m_nsteps(other.m_nsteps) {}
    
    InstanceParameter(pd::Gui const& gui)
    : m_valid(true), m_value (0.f),
    m_min(gui.getMinimum()),
    m_max(gui.getMaximum()),
    m_name(gui.getName()),
    m_label(gui.getLabel()),
    m_bname(gui.getBindingName()),
    m_nsteps(gui.getNumberOfSteps())
    {setValueNonNormalized(gui.getValue());}
    
    ~InstanceParameter() {}
    
    InstanceParameter& operator=(InstanceParameter const& other)
    {
        m_valid = other.m_valid;
        m_value = other.m_value;
        m_min   = other.m_min;
        m_max   = other.m_max;
        m_name  = other.m_name;
        m_label = other.m_label;
        m_bname = other.m_bname;
        m_nsteps= other.m_nsteps;
        return *this;
    }
    
    InstanceParameter& operator=(InstanceParameter&& other)
    {
        m_valid = other.m_valid;
        m_value = other.m_value;
        m_min   = other.m_min;
        m_max   = other.m_max;
        std::swap(m_name, other.m_name);
        std::swap(m_label, other.m_label);
        m_bname = other.m_bname;
        m_nsteps= other.m_nsteps;
        return *this;
    }
    
    bool isValid() const noexcept {return m_valid;}
    
    float getValue() const final {return m_value;}
    
    float getValueNonNormalized() const
    {
        if(m_min < m_max)
        {
            return m_value * (m_max - m_min) + m_min;
        }
        return m_value * (m_min - m_max) + m_max;
    }
    
    void setValue (float newValue) final {m_value = newValue;}
    
    void setValueNonNormalized (float newValue)
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
    
    String getText (float value, int size) const final {return String(getValueNonNormalized());}
    
    float getValueForText (const String& text) const final {return text.getFloatValue();}
    
    bool isOrientationInverted() const final {return m_max < m_min;}
    
    int getNumSteps() const final {return m_nsteps != 0 ? m_nsteps : AudioProcessor::getDefaultNumParameterSteps();}

    inline pd::BindingName const& getBindingName() const noexcept {return m_bname;}

private:
    bool   m_valid;
    float  m_value;
    float  m_min;
    float  m_max;
    String m_name;
    String m_label;
    pd::BindingName m_bname;
    int    m_nsteps;
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
    pd::Patch                    m_patch;
    std::set<Listener*>          m_listeners;
    std::vector<InstanceParameter> m_parameters;
    mutable std::mutex           m_mutex;
    
    void parametersChanged();
    std::vector<Listener*> getListeners() const noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstanceProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
