/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_PROCESSOR__
#define __CAMOMILE_INTANCE_PROCESSOR__

#include "PdWrapper.h"

using namespace std;
using namespace pd;

class InstanceProcessor : public AudioProcessor, public Instance, public Messenger
{
public:
    class Listener;
private:
    Patch               m_patch;
    set<Listener*>      m_listeners;
    mutable mutex       m_mutex_list;
    vector<Parameter>   m_parameters;
    mutable mutex       m_mutex;
public:
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
    bool isParameterAutomatable(int index) const;
    bool isParameterOrientationInverted (int index) const;
    bool isMetaParameter(int index) const;
     
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
    inline const Patch getPatch() const noexcept {return m_patch;}
    inline Patch getPatch() noexcept {return m_patch;}
    void receive(std::string const& dest, std::string const& s, std::vector<Atom> const& atoms) override;
    
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
    vector<Listener*> getListeners() const noexcept;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InstanceProcessor)
};


#endif  // PLUGINPROCESSOR_H_INCLUDED
