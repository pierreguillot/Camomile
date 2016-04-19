/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_PROCESSOR__
#define __CAMOMILE_INTANCE_PROCESSOR__

#include "../ThirdParty/zpd/xpd/Pd.hpp"
#include "../JuceLibraryCode/JuceHeader.h"


class InstanceProcessor : public AudioProcessor, public xpd::instance, public xpd::console::history
{
public:
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
    int getParameterIndex(xpd::tie const& name);
    int getParameterIndex(String const& name);
    
    void getStateInformation(MemoryBlock& destData) final;
    void setStateInformation(const void* data, int sizeInBytes) final;

    //! @brief Loads a patch.
    void loadPatch(std::string const& name, std::string const& path);
    
    //! @brief Closes a patch.
    void closePatch();
    
    //! @brief Closes a patch.
    inline xpd::patch const* getPatch() const noexcept {return m_patch;}
    
protected:
    
    //! @brief Receives a post from the console.
    void receive(xpd::console::post post) final;
    
    //! @brief Receives a midi event.
    void receive(xpd::midi::event event) final;
    
private:
    static xpd::symbol s_playing;
    static xpd::symbol s_measure;
    static xpd::symbol s_float;
    xpd::patch*                 m_patch;
    std::vector<xpd::Parameter>         m_parameters;
    juce::String                        m_path;
    MidiBuffer                          m_midi;
    xpd::tie                            m_patch_tie;
    std::vector<xpd::atom>              m_playing_list;
    std::vector<xpd::atom>              m_measure_list;
    AudioPlayHead::CurrentPositionInfo  m_playinfos;
    
    juce::String    m_name;

    void parametersChanged();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstanceProcessor)
};


#endif
