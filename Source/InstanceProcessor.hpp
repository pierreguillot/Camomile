/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_PROCESSOR__
#define __CAMOMILE_INTANCE_PROCESSOR__

#include "Pd/Pd.hpp"
#include "../JuceLibraryCode/JuceHeader.h"


class InstanceProcessor : public AudioProcessor,
public pd::Instance, public pd::PatchManager, public pd::Console::History
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
    int getParameterIndex(pd::Tie const& name);
    int getParameterIndex(String const& name);
    
    
    void getStateInformation(MemoryBlock& destData) final;
    void setStateInformation(const void* data, int sizeInBytes) final;
    
    //! @brief Receives a normal post to the Pure Data console.
    void receiveConsolePost(std::string const& message) final;
    
    //! @brief Receives a log post to the Pure Data console.
    void receiveConsoleLog(std::string const& message) final;
    
    //! @brief Receives a error to the Pure Data console.
    void receiveConsoleError(std::string const& message) final;
    
    //! @brief Receives a fatal error to the Pure Data console.
    void receiveConsoleFatal(std::string const& message) final;

    //! @brief Loads a patch.
    void loadPatch(std::string const& name, std::string const& path) final;
    
    //! @brief Closes a patch.
    void closePatch() final;
protected:
    
     //! @brief Receives midi note on.
    void receiveMidiNoteOn(int channel, int pitch, int velocity) final;
    
    //! @brief Receives midi control change.
    void receiveMidiControlChange(int channel, int control, int value) final;
    
    //! @brief Receives midi program change.
    void receiveMidiProgramChange(int channel, int value) final;
    
    //! @brief Receives midi pitch bend.
    void receiveMidiPitchBend(int channel, int value) final;
    
    //! @brief Receives midi after touch.
    void receiveMidiAfterTouch(int channel, int value) final;
    
    //! @brief Receives midi poly after touch.
    void receiveMidiPolyAfterTouch(int channel, int pitch, int value) final;
    
    //! @brief Receives midi byte.
    void receiveMidiByte(int port, int value) final;
private:
    
    std::vector<pd::Parameter>          m_parameters;
    juce::String                        m_path;
    MidiBuffer                          m_midi;
    pd::Tie                             m_patch_tie;
    AudioPlayHead::CurrentPositionInfo  m_playinfos;

    void parametersChanged();
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstanceProcessor)
};


#endif
