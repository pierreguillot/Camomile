/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_PROCESSOR__
#define __CAMOMILE_INTANCE_PROCESSOR__

#include "../ThirdParty/zpd/xpd/xpd.hpp"
#include "Camo/camo.hpp"
#include "../JuceLibraryCode/JuceHeader.h"


// ==================================================================================== //
//                                  INSTANCE EDITOR                                     //
// ==================================================================================== //

class InstanceProcessor :
public AudioProcessor,
public camo::camomile
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
    
    
    // ==================================================================================== //
    //                                          PARAMETERS                                  //
    // ==================================================================================== //

    int getNumParameters() final;
    float getParameter(int index) final;
    void setParameter(int index, float newValue) final;
    float getParameterDefaultValue(int index) final;
    const String getParameterName(int index) final;
    const String getParameterText(int index) final;
    String getParameterText(int index, int size) final;
    String getParameterLabel (int index) const final;
    int getParameterNumSteps(int index) final;

    
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
    
    // ================================================================================ //
    //                                      PATCH                                       //
    // ================================================================================ //
 
    void load_patch(std::string const& name, std::string const& path);
    void close_patch();

    // ================================================================================ //
    //                                  STATE INFORMATION                               //
    // ================================================================================ //

    void getStateInformation(MemoryBlock& destData) final;
    void setStateInformation(const void* data, int sizeInBytes) final;
    
protected:
    
    //! @brief Receives a midi event.
    //! @param event The midi event received.
    void receive(xpd::midi::event const& event) final;
    
private:
    static xpd::symbol s_playing;
    static xpd::symbol s_measure;
    static xpd::symbol s_float;


    juce::String                        m_path;
    MidiBuffer                          m_midi;
    xpd::tie                            m_patch_tie;
    std::vector<xpd::atom>              m_playing_list;
    std::vector<xpd::atom>              m_measure_list;
    AudioPlayHead::CurrentPositionInfo  m_playinfos;
    
    juce::String    m_name;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstanceProcessor)
};


#endif
