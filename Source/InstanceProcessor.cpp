/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.hpp"
#include "CamomileEditor.hpp"
//#include "LookAndFeel.hpp"

xpd::symbol InstanceProcessor::s_playing;
xpd::symbol InstanceProcessor::s_measure;
xpd::symbol InstanceProcessor::s_float;

InstanceProcessor::InstanceProcessor() :
m_playing_list(2),
m_measure_list(5),
m_name("Camomile")
{
    send(xpd::console::post{xpd::console::level::log, std::string("Camomile ") +
        std::string(JucePlugin_VersionString) + std::string(" for Pure Data ") +
        std::to_string(xpd::environment::version_major()) + "." +
        std::to_string(xpd::environment::version_minor()) + "." +
        std::to_string(xpd::environment::version_bug())});
    
    s_playing           = xpd::symbol("playing");
    s_measure           = xpd::symbol("measure");
    s_float             = xpd::symbol("float");
    busArrangement.inputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(32);
    busArrangement.outputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(32);
    m_path = juce::File::getCurrentWorkingDirectory().getFullPathName();
}

InstanceProcessor::~InstanceProcessor()
{
    ;
}

const String InstanceProcessor::getName() const
{
    return m_name;
}


// ==================================================================================== //
//                                          PARAMETERS                                  //
// ==================================================================================== //

int InstanceProcessor::getNumParameters()
{
    return get_number_of_parameters() != 0 ? get_number_of_parameters() : 64;
}

const String InstanceProcessor::getParameterName(int index)
{
    return get_parameter_name(index);
}

String InstanceProcessor::getParameterLabel(int index) const
{
    return get_parameter_label(index);
}

float InstanceProcessor::getParameter(int index)
{
    return get_parameter_value(index);
}

void InstanceProcessor::setParameter(int index, float newValue)
{
    set_parameter_value(index, newValue);
}

float InstanceProcessor::getParameterDefaultValue(int index)
{
    return get_parameter_default_value(index);
}

const String InstanceProcessor::getParameterText(int index)
{
    return get_parameter_text(index);
}

String InstanceProcessor::getParameterText(int index, int size)
{
    return String(get_parameter_text(index)).substring(0, size);
}

int InstanceProcessor::getParameterNumSteps(int index)
{
    return static_cast<int>(get_parameter_nsteps(index));
}








void InstanceProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    prepare(getTotalNumInputChannels(), getTotalNumOutputChannels(), sampleRate, samplesPerBlock);
}

void InstanceProcessor::releaseResources()
{
    release();
}

void InstanceProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for(int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    bool infos = false;
    
    AudioPlayHead* playhead = getPlayHead();
    if(playhead && m_patch_tie)
    {
        infos = playhead->getCurrentPosition(m_playinfos);
    }

    {
        m_midi.clear();
        if(infos)
        {
            m_playing_list[0] = m_playinfos.isPlaying;
            m_playing_list[1] = m_playinfos.timeInSeconds;
            send(m_patch_tie, s_playing, m_playing_list);
            m_measure_list[0] = m_playinfos.bpm;
            m_measure_list[1] = m_playinfos.timeSigNumerator;
            m_measure_list[2] = m_playinfos.timeSigDenominator;
            m_measure_list[3] = m_playinfos.ppqPosition;
            m_measure_list[4] = m_playinfos.ppqPositionOfLastBarStart;
            send(m_patch_tie, s_measure, m_measure_list);
        }
        
        /*
        for(size_t i = 0; i < m_parameters.size() && bool(m_parameters[i]); ++i)
        {
            send(m_parameters[i].receive_tie(), s_float, std::vector<xpd::atom>(1, m_parameters[i].get_value_denormalized()));
        }
        */
        
        MidiMessage message;
        MidiBuffer::Iterator it(midiMessages);
        int position = midiMessages.getFirstEventTime();
        while(it.getNextEvent(message, position))
        {
            if(message.isNoteOn())
            {
                send(xpd::midi::event::note(message.getChannel(), message.getNoteNumber(), message.getVelocity()));
            }
            if(message.isNoteOff())
            {
                send(xpd::midi::event::note(message.getChannel(), message.getNoteNumber(), 0));
            }
            else if(message.isController())
            {
                send(xpd::midi::event::control_change(message.getChannel(), message.getControllerNumber(), message.getControllerValue()));
            }
            else if(message.isPitchWheel())
            {
                send(xpd::midi::event::program_change(message.getChannel(), message.getPitchWheelValue()));
            }
            else if(message.isChannelPressure())
            {
                send(xpd::midi::event::after_touch(message.getChannel(), message.getChannelPressureValue()));
            }
            else if(message.isAftertouch())
            {
                send(xpd::midi::event::poly_after_touch(message.getChannel(), message.getNoteNumber(), message.getAfterTouchValue()));
            }
            else if(message.isProgramChange())
            {
                send(xpd::midi::event::program_change(message.getChannel(), message.getProgramChangeNumber()));
            }
        }
    }
    midiMessages.clear();
    perform(buffer.getNumSamples(), getTotalNumInputChannels(), buffer.getArrayOfReadPointers(), getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
    midiMessages.swapWith(m_midi);
}

void InstanceProcessor::receive(xpd::console::post const& post)
{
    xpd::console::history::add(std::move(post));
}

void InstanceProcessor::receive(xpd::midi::event const& event)
{
    if(event.type() == xpd::midi::event::note_t)
    {
        if(event.velocity())
        {
            m_midi.addEvent(MidiMessage::noteOn(event.channel()+1, event.pitch(), uint8(event.velocity())), 0);
        }
        else
        {
            m_midi.addEvent(MidiMessage::noteOff(event.channel()+1, event.pitch(), uint8(0)), 0);
        }
    }
    else if(event.type() == xpd::midi::event::control_change_t)
    {
        m_midi.addEvent(MidiMessage::controllerEvent(event.channel()+1, event.controller(), event.value()), 0);
    }
    else if(event.type() == xpd::midi::event::program_change_t)
    {
        m_midi.addEvent(MidiMessage::programChange(event.channel()+1, event.program()), 0);
    }
    else if(event.type() == xpd::midi::event::pitch_bend_t)
    {
        m_midi.addEvent(MidiMessage::pitchWheel(event.channel()+1, event.bend()), 0);
    }
    else if(event.type() == xpd::midi::event::after_touch_t)
    {
        m_midi.addEvent(MidiMessage::channelPressureChange(event.channel()+1, event.value()), 0);
    }
    else if(event.type() == xpd::midi::event::poly_after_touch_t)
    {
        m_midi.addEvent(MidiMessage::aftertouchChange(event.channel()+1, event.pitch(), event.value()), 0);
    }
}

// ================================================================================ //
//                                      PATCH                                       //
// ================================================================================ //

void InstanceProcessor::load_patch(std::string const& name, std::string const& path)
{
    suspendProcessing(true);
    if(isSuspended())
    {
        camo::camomile::load_patch(name, path);
        updateHostDisplay();
        camo::camomile::prepare(getTotalNumInputChannels(), getTotalNumOutputChannels(), AudioProcessor::getSampleRate(), getBlockSize());
    }
    suspendProcessing(false);
}

void InstanceProcessor::close_patch()
{
    suspendProcessing(true);
    if(isSuspended())
    {
        camo::camomile::close_patch();
        updateHostDisplay();
        camo::camomile::prepare(getTotalNumInputChannels(), getTotalNumOutputChannels(), AudioProcessor::getSampleRate(), getBlockSize());
    }
    suspendProcessing(false);
}


// ================================================================================ //
//                                  STATE INFORMATION                               //
// ================================================================================ //

void InstanceProcessor::getStateInformation(MemoryBlock& destData)
{
    juce::XmlElement xml(String("CamomileSettings"));
    xpd::patch patch(get_patch());
    if(static_cast<bool>(patch))
    {
        xml.setAttribute(String("name"), patch.name());
        xml.setAttribute(String("path"), patch.path());
    }
    XmlElement* params = xml.createNewChildElement("params");
    for(size_t i = 0; i < get_number_of_parameters(); ++i)
    {
        params->setAttribute(String(get_parameter_name(i)), static_cast<double>(get_parameter_value(i, true)));
    }
    copyXmlToBinary(xml, destData);
}

void InstanceProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    ScopedPointer<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if(xml != nullptr)
    {
        if(xml->hasTagName("CamomileSettings"))
        {
            String name = xml->getStringAttribute("name");
            String path = xml->getStringAttribute("path");
            if(File::isAbsolutePath(path))
            {
                File file(path + File::separatorString + name);
                if(!file.exists())
                {
                    file = File(m_path + File::separatorString + name);
                    if(!file.exists())
                    {
                        file = File(File::getCurrentWorkingDirectory().getFullPathName() + File::separatorString + name);
                        if(!file.exists())
                        {
                            file = File(File::getSpecialLocation(juce::File::SpecialLocationType::userDocumentsDirectory).getFullPathName() + File::separatorString + name);
                            if(!file.exists())
                            {
                                file = File(path + File::separatorString + name);
                            }
                        }
                    }
                }
                this->load_patch(name.toStdString(), path.toStdString());
            }
            
            XmlElement* params = xml->getChildByName(juce::StringRef("params"));
            if(params)
            {
                for(int i = 0; i < params->getNumAttributes(); i++)
                {
                    String const& name = params->getAttributeName(i);
                    for(size_t i = 0; i < get_number_of_parameters(); ++i)
                    {
                        if(name == get_parameter_name(i))
                        {
                            setParameterNotifyingHost(i, params->getAttributeValue(i).getDoubleValue());
                        }
                    }
                }
            }
        }
    }
}


AudioProcessorEditor* InstanceProcessor::createEditor()
{
    return new CamomileEditor(*this);
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    int todo;
    //static CamoLookAndFeel lookAndFeel;
    //LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    return new InstanceProcessor();
}




