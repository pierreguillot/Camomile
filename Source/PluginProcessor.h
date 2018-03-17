/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginEnvironment.h"
#include "PluginConsole.h"
#include "Pd/PdInstance.hpp"

// ======================================================================================== //
//                                      PROCESSOR                                           //
// ======================================================================================== //


class CamomileAudioProcessor : public AudioProcessor, public pd::Instance, public CamomileConsole<4>
{
public:
    CamomileAudioProcessor();
    ~CamomileAudioProcessor() {}

    bool isBusesLayoutSupported (const BusesLayout& layouts) const final;
    
    void prepareToPlay (double sampleRate, int samplesPerBlock) final;
    void releaseResources() final;
    void processBlock (AudioSampleBuffer&, MidiBuffer&) final;
    void processBlockBypassed (AudioBuffer<float>&, MidiBuffer&) final;
    
    AudioProcessorEditor* createEditor() final;
    bool hasEditor() const final;

    const String getName() const final { return CamomileEnvironment::getPluginName(); }
    bool acceptsMidi() const final { return CamomileEnvironment::wantsMidi(); }
    bool producesMidi() const final { return CamomileEnvironment::producesMidi(); }
    bool isMidiEffect () const final { return CamomileEnvironment::isMidiOnly(); }
    double getTailLengthSeconds() const final { return static_cast<float>(CamomileEnvironment::getTailLengthSeconds()); }
    
    int getNumPrograms() final { return static_cast<int>(m_programs.size()); };
    int getCurrentProgram() final { return m_program_current; }
    void setCurrentProgram (int index) final;
    const String getProgramName (int index) final;
    void changeProgramName (int index, const String& newName) final;

    void getStateInformation (MemoryBlock& destData) final;
    void setStateInformation (const void* data, int sizeInBytes) final;
    
    void receiveMessage(const std::string& dest, const std::string& msg, const std::vector<pd::Atom>& list) final;
    void receiveNoteOn(const int channel, const int pitch, const int velocity) final;
    void receiveControlChange(const int channel, const int controller, const int value) final;
    void receiveProgramChange(const int channel, const int value) final;
    void receivePitchBend(const int channel, const int value) final;
    void receiveAftertouch(const int channel, const int value) final;
    void receivePolyAftertouch(const int channel, const int pitch, const int value) final;
    void receiveMidiByte(const int port, const int byte) final;
    void receivePrint(const std::string& message) final;
    
    void messageEnqueued() final;
    void updateTrackProperties(const TrackProperties& properties) final;
    const TrackProperties& getTrackProperties() const { return m_track_properties; }
    
    typedef std::array<std::string, 3> MessageGui;
    bool dequeueGui(MessageGui& message);

    enum ConsoleLevel
    {
        Fatal   = 0,
        Error   = 1,
        Normal  = 2,
        Log     = 3,
        All     = 4
        
    };
private:
    static BusesProperties getBusesProperties();
    void sendBusInformation(Bus const *bus);
    void loadInformation(XmlElement const& xml);
    
    void parseSaveInformation(const std::vector<pd::Atom>& list);
    void parseOpenPanel(const std::vector<pd::Atom>& list);
    void parseSavePanel(const std::vector<pd::Atom>& list);
    void parseArray(const std::vector<pd::Atom>& list);
    void parseGui(const std::vector<pd::Atom>& list);
    void parseAudio(const std::vector<pd::Atom>& list);
    
    
    void processInternal();
    
    typedef moodycamel::ReaderWriterQueue<MessageGui> QueueGui;
    
    std::vector<pd::Atom>    m_atoms_param;
    std::vector<pd::Atom>    m_atoms_playhead;
    int                      m_audio_advancement;
    std::vector<float>       m_audio_buffer_in;
    std::vector<float>       m_audio_buffer_out;
    
    MidiBuffer               m_midi_buffer;
    int m_program_current    = 0;
    std::vector<std::string> m_programs;
    std::vector<bool>        m_params_states;
    QueueGui                 m_queue_gui = QueueGui(64);
    TrackProperties          m_track_properties;
    XmlElement*              m_temp_xml;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CamomileAudioProcessor)
};
