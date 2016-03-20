/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_PROCESSOR__
#define __CAMOMILE_INTANCE_PROCESSOR__

#include "Pd.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class InstanceProcessor : public AudioProcessor, public pd::Instance
{
public:
    class Listener;
    InstanceProcessor();
    ~InstanceProcessor();

    void prepareToPlay(double sampleRate, int samplesPerBlock) final;
    void releaseResources() final;
    void processBlock(AudioSampleBuffer&, MidiBuffer&) final;

    AudioProcessorEditor* createEditor() final;
    bool hasEditor() const final {return true;};
    const String getName() const final ;
    
    int getNumParameters() final;
    float getParameter(int index) final;
    void setParameter(int index, float newValue) final;
    float getParameterDefaultValue(int index) final;
    const String getParameterName(int index) final;
    const String getParameterText(int index) final;
    String getParameterText(int index, int size) final;
    String getParameterLabel (int index) const final;
    int getParameterNumSteps(int index) final;
    bool isParameterAutomatable(int index) const final;
    bool isParameterOrientationInverted (int index) const final;
    bool isMetaParameter(int index) const final;
    float getParameterNonNormalized(int index) const;
    void setParameterNonNormalized(int index, float newValue);
    void setParameterNonNormalizedNotifyingHost(int index, float newValue);
    
    const String getInputChannelName(int index) const final {return String(index + 1);}
    const String getOutputChannelName(int index) const final {return String(index + 1);}
    bool isInputChannelStereoPair(int index) const final {return true;}
    bool isOutputChannelStereoPair(int index) const final {return true;}

    bool acceptsMidi() const final {return bool(JucePlugin_WantsMidiInput);}
    bool producesMidi() const final {return bool(JucePlugin_ProducesMidiOutput);}
    bool silenceInProducesSilenceOut() const final {return false;}
    double getTailLengthSeconds() const final {return 0.0;}

    int getNumPrograms() final {return 1;}
    int getCurrentProgram() final {return 0;}
    void setCurrentProgram(int index) final {}
    const String getProgramName(int index) final {return String();}
    void changeProgramName(int index, const String& newName) final {}

    void getStateInformation(MemoryBlock& destData) final;
    void setStateInformation(const void* data, int sizeInBytes) final;
    
    void loadPatch(const juce::File& file);
    inline const pd::Patch getPatch() const noexcept {return m_patch;}
    inline pd::Patch getPatch() noexcept {return m_patch;}
    int getParameterIndex(pd::Tie const& name);
    int getParameterIndex(String const& name);
    
    void addListener(Listener* listener);
    void removeListener(Listener* listener);
    class Listener
    {
    public:
        inline constexpr Listener() {}
        inline virtual ~Listener() {}
        virtual void patchChanged() = 0;
    };

protected:
    
    void receiveMidiNoteOn(int port, int channel, int pitch, int velocity) final;
    
    //! @brief Receives midi control change.
    void receiveMidiControlChange(int port, int channel, int control, int value) final;
    
    //! @brief Receives midi program change.
    void receiveMidiProgramChange(int port, int channel, int value) final;
    
    //! @brief Receives midi pitch bend.
    void receiveMidiPitchBend(int port, int channel, int value) final;
    
    //! @brief Receives midi after touch.
    void receiveMidiAfterTouch(int port, int channel, int value) final;
    
    //! @brief Receives midi poly after touch.
    void receiveMidiPolyAfterTouch(int port, int channel, int pitch, int value) final;
    
    //! @brief Receives midi byte.
    void receiveMidiByte(int port, int value) final;
private:
    
    class Parameter : public AudioProcessorParameter
    {
    public:
        Parameter();
        Parameter(Parameter const& other);
        Parameter(pd::Gui const& gui);
        ~Parameter();
        Parameter& operator=(Parameter const& other);
        Parameter& operator=(Parameter&& other);
        bool isValid() const noexcept;
        float getValue() const final;
        float getValueNonNormalized() const;
        void setValue(float newValue) final;
        void setValueNonNormalized(float newValue);
        float getValueNormalized(float newValue);
        float getDefaultValue() const final;
        String getName(int maximumStringLength) const final;
        String getLabel() const final;
        String getText (float value, int size) const final;
        float getValueForText (const String& text) const final;
        bool isOrientationInverted() const final;
        int getNumSteps() const final;
        inline pd::Tie const& getTie() const noexcept {return m_bname;}
        
    private:
        bool   m_valid;
        float  m_value;
        float  m_min;
        float  m_max;
        String m_name;
        String m_label;
        pd::Tie m_bname;
        int    m_nsteps;
    };
    
    pd::Patch              m_patch;
    std::set<Listener*>    m_listeners;
    std::vector<Parameter> m_parameters;
    mutable std::mutex     m_mutex;
    juce::String           m_path;
    MidiBuffer             m_midi;
    AudioPlayHead::CurrentPositionInfo m_playinfos;

    void parametersChanged();
    std::vector<Listener*> getListeners() const noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstanceProcessor)
};


#endif
