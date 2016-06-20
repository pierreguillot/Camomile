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

InstanceProcessor::InstanceProcessor() : xpd::instance(),
//m_parameters(64),
m_playing_list(2), m_measure_list(5), m_name("Camomile")
{
    send(xpd::console::post{xpd::console::level::log, std::string("Camomile ") +
        std::string(JucePlugin_VersionString) + std::string(" for Pure Data ") +
        std::to_string(xpd::environment::version_major()) + "." +
        std::to_string(xpd::environment::version_minor()) + "." +
        std::to_string(xpd::environment::version_bug())});
    
    s_playing           = xpd::symbol("playing");
    s_measure           = xpd::symbol("measure");
    s_float             = xpd::symbol("float");
    busArrangement.inputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(16);
    busArrangement.outputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(16);
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

/*
int InstanceProcessor::getNumParameters()
{
    return int(m_parameters.size());
}

const String InstanceProcessor::getParameterName(int index)
{
    if(m_parameters[index].isValid())
    {
        return m_parameters[index].getName();
    }
    else
    {
        return String("Dummy ") + String(std::to_string(index + 1));
    }
}

float InstanceProcessor::getParameter(int index)
{
    return m_parameters[index].getValueNormalized();
}

float InstanceProcessor:: getParameterNonNormalized(int index) const
{
    return m_parameters[index].getValueNonNormalized();
}

void InstanceProcessor::setParameterNonNormalized(int index, float newValue)
{
    m_parameters[index].setValueNonNormalized(newValue);
}

void InstanceProcessor::setParameterNonNormalizedNotifyingHost(int index, float newValue)
{
    setParameterNotifyingHost(index, m_parameters[index].getValueNormalized(newValue));
}


void InstanceProcessor::setParameter(int index, float newValue)
{
    m_parameters[index].setValueNormalized(newValue);
}

float InstanceProcessor::getParameterDefaultValue(int index)
{
    return 0.;
}

const String InstanceProcessor::getParameterText(int index)
{
    return m_parameters[index].getTextForValue();
}

String InstanceProcessor::getParameterText(int index, int size)
{
    return m_parameters[index].getTextForValue();
}

String InstanceProcessor::getParameterLabel(int index) const
{
    return m_parameters[index].getLabel();
}

int InstanceProcessor::getParameterNumSteps(int index)
{
    return m_parameters[index].getNumberOfSteps();
}

bool InstanceProcessor::isParameterAutomatable(int index) const
{
    return true;
}

bool InstanceProcessor::isParameterOrientationInverted(int index) const
{
    return m_parameters[index].isOrientationInverted();
}

bool InstanceProcessor::isMetaParameter(int index) const
{
    return false;
}

int InstanceProcessor::getParameterIndex(xpd::tie const& name)
{
    if(name != xpd::tie())
    {
        for(size_t i = 0; i < m_parameters.size(); i++)
        {
            if(m_parameters[i].gettie() == name)
            {
                return int(i);
            }
        }
    }
    return -1;
}

int InstanceProcessor::getParameterIndex(String const& name)
{
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(m_parameters[i].getName() == name)
        {
            return int(i);
        }
    }
    return -1;
}

*/
void InstanceProcessor::parametersChanged()
{
    size_t index = 0;
    /*
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        m_parameters[i] = xpd::Parameter();
    }
    */
    
    if(m_patch)
    {
        int todo;
        /*
        std::vector<xpd::gui> guis(m_patch->getGuis());
        for(auto const& gui : guis)
        {
            if(gui.isParameter())
            {
                bool ok = true;
                for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); i++)
                {
                    if(gui.getName() == m_parameters[i].getName())
                    {
                        send({xpd::console::level::error, "Warning in patch " + m_patch->name() + ": "  + gui.getName() + " parameter is duplicated !"});
                        ok = false;
                        break;
                    }
                    else if(gui.getReceivetie() == m_parameters[i].gettie())
                    {
                        send({xpd::console::level::error, "Warning in patch " + m_patch->name() + ": "  + gui.getName() + " parameter shares the same receive symbol with another parameter !"});
                        ok = false;
                        break;
                    }
                }
                if(ok)
                {
                    m_parameters[index] = xpd::Parameter(gui);
                    index++;
                }
            }
        }
         */
    }
    updateHostDisplay();
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
        for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); ++i)
        {
            send(m_parameters[i].gettie(), s_float, std::vector<xpd::atom>(1, m_parameters[i].getValueNonNormalized()));
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

AudioProcessorEditor* InstanceProcessor::createEditor()
{
    int todo;
    return nullptr; //new InstanceEditor(*this);
}

void InstanceProcessor::loadPatch(std::string const& name, std::string const& path)
{
    suspendProcessing(true);
    if(isSuspended())
    {
        xpd::instance::release();
        if(static_cast<bool>(m_patch))
        {
            close(m_patch);
        }
        m_patch = xpd::instance::load(name, path);
        if(static_cast<bool>(m_patch))
        {
            m_patch_tie = xpd::tie(std::to_string(m_patch.unique_id()) + "-playhead");
        }
        else
        {
            send(xpd::console::post(xpd::console::error, std::string("Camomile can't find the patch : ") + name));
        }
        parametersChanged();
        prepare(getTotalNumInputChannels(), getTotalNumOutputChannels(), AudioProcessor::getSampleRate(), getBlockSize());
        
        int todo_notify_listeners;
        //
    }
    suspendProcessing(false);
}

void InstanceProcessor::closePatch()
{
    suspendProcessing(true);
    if(isSuspended())
    {
        xpd::instance::release();
        if(static_cast<bool>(m_patch))
        {
            close(m_patch);
            m_patch_tie = xpd::tie();
        }
        
        parametersChanged();
        prepare(getTotalNumInputChannels(), getTotalNumOutputChannels(), AudioProcessor::getSampleRate(), getBlockSize());
        
        int todo_notify_listeners;
        //
    }
    suspendProcessing(false);
}

void InstanceProcessor::getStateInformation(MemoryBlock& destData)
{
    juce::XmlElement xml(String("CamomileSettings"));
    /*
    xpd::Patch patch(getPatch());
    if(patch.isValid())
    {
        xml.setAttribute(String("name"), patch.getName());
        xml.setAttribute(String("path"), patch.getPath());
    }
    XmlElement* params = xml.createNewChildElement("params");
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(m_parameters[i].isValid())
        {
            params->setAttribute(String(m_parameters[i].getName()), double(m_parameters[i].getValueNormalized()));
        }
    }
    copyXmlToBinary(xml, destData);
     */
}

void InstanceProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    /*
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
                loadPatch(name.toStdString(), path.toStdString());
            }
            
            XmlElement* params = xml->getChildByName(juce::StringRef("params"));
            if(params)
            {
                for(int i = 0; i < params->getNumAttributes(); i++)
                {
                    int index = getParameterIndex(params->getAttributeName(i));
                    if(index >= 0)
                    {
                        setParameterNotifyingHost(index, params->getAttributeValue(i).getDoubleValue());
                    }
                }
            }
        }
    }
     */
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    int todo;
    //static CamoLookAndFeel lookAndFeel;
    //LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    return new InstanceProcessor();
}




