/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.hpp"
#include "CamomileEditor.hpp"
//#include "LookAndFeel.hpp"

InstanceProcessor::InstanceProcessor() : m_name("Camomile")
{
    send(xpd::console::post{xpd::console::level::log, std::string("Camomile ") +
        std::string(JucePlugin_VersionString) + std::string(" for Pure Data ") +
        std::to_string(xpd::environment::version_major()) + "." +
        std::to_string(xpd::environment::version_minor()) + "." +
        std::to_string(xpd::environment::version_bug())});
    
    
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
    return static_cast<int>(get_number_of_parameters()) != 0 ? static_cast<int>(get_number_of_parameters()) : 64;
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
    return String(get_parameter_value(index));
}

String InstanceProcessor::getParameterText(int index, int size)
{
    return String(get_parameter_value(index)).substring(0, size);
}

int InstanceProcessor::getParameterNumSteps(int index)
{
    return static_cast<int>(get_parameter_nsteps(index));
}

// ==================================================================================== //
//                                          DSP                                         //
// ==================================================================================== //


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

    AudioPlayHead* playhead = getPlayHead();
    if(playhead && playhead->getCurrentPosition(m_playinfos))
    {
        set_playhead_infos(reinterpret_cast<PlayHeadInfos const&>(m_playinfos));
    }

    {
        m_midi.clear();
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

void InstanceProcessor::receive(xpd::midi::event const& event)
{
    if(event.type() == xpd::midi::event::note_t)
    {
        if(event.velocity() != 0)
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
                    String const& aname = params->getAttributeName(i);
                    for(int j = 0; j < static_cast<int>(get_number_of_parameters()); ++j)
                    {
                        if(aname == get_parameter_name(j))
                        {
                            setParameterNotifyingHost(j, params->getAttributeValue(i).getDoubleValue());
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




