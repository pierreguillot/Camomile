/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.hpp"
#include "InstanceEditor.hpp"
#include "LookAndFeel.hpp"

InstanceProcessor::InstanceProcessor() : pd::Instance("Camomile")
{
    consoleLog(std::string("Camomile ") +
                         std::string(JucePlugin_VersionString) +
                         std::string(" for Pure Data ") +
                         pd::Environment::getPdVersion());
    m_parameters.resize(32);
    busArrangement.inputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(16);
    busArrangement.outputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(16);
    m_path = juce::File::getCurrentWorkingDirectory().getFullPathName();
}

InstanceProcessor::~InstanceProcessor()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.clear();
}

const String InstanceProcessor::getName() const
{
    if(m_patch.isValid())
    {
        return String(JucePlugin_Name + std::string(" ") + m_patch.getName());
    }
    return String(JucePlugin_Name);
}

int InstanceProcessor::getNumParameters()
{
    return int(m_parameters.size());
}

const String InstanceProcessor::getParameterName(int index)
{
    if(m_parameters[index].isValid())
    {
        return m_parameters[index].getName(512);
    }
    else
    {
        return String("Dummy ") + String(std::to_string(index + 1));
    }
}

float InstanceProcessor::getParameter(int index)
{
    return m_parameters[index].getValue();
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
    m_parameters[index].setValue(newValue);
}

float InstanceProcessor::getParameterDefaultValue(int index)
{
    return 0.;
}

const String InstanceProcessor::getParameterText(int index)
{
    return m_parameters[index].getText(index, 512);
}

String InstanceProcessor::getParameterText(int index, int size)
{
    return m_parameters[index].getText(index, size);
}

String InstanceProcessor::getParameterLabel(int index) const
{
    return m_parameters[index].getLabel();
}

int InstanceProcessor::getParameterNumSteps(int index)
{
    return m_parameters[index].getNumSteps();
}

bool InstanceProcessor::isParameterAutomatable(int index) const
{
    return m_parameters[index].isAutomatable();
}

bool InstanceProcessor::isParameterOrientationInverted(int index) const
{
    return m_parameters[index].isOrientationInverted();
}

bool InstanceProcessor::isMetaParameter(int index) const
{
    return m_parameters[index].isMetaParameter();
}

int InstanceProcessor::getParameterIndex(pd::Tie const& name)
{
    if(name != pd::Tie())
    {
        for(size_t i = 0; i < m_parameters.size(); i++)
        {
            if(m_parameters[i].getTie() == name)
            {
                return i;
            }
        }
    }
    return -1;
}

int InstanceProcessor::getParameterIndex(String const& name)
{
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(m_parameters[i].getName(512) == name)
        {
            return i;
        }
    }
    return -1;
}

void InstanceProcessor::parametersChanged()
{
    size_t index = 0;
    
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        m_parameters[i] = Parameter();
    }
    if(m_patch.isValid())
    {
        std::vector<pd::Gui> guis(m_patch.getGuis());
        for(auto const& gui : guis)
        {
            if(gui.isParameter())
            {
                bool ok = true;
                for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); i++)
                {
                    if(gui.getName() == m_parameters[i].getName(512))
                    {
                        consoleError("Warning in patch " + m_patch.getName() + ": "  + gui.getName() + " parameter is duplicated !");
                        ok = false;
                        break;
                    }
                    else if(gui.getReceiveTie() == m_parameters[i].getTie())
                    {
                        consoleError("Warning in patch " + m_patch.getName() + ": "  + gui.getName() + " parameter shares the same receive symbol with another parameter !");
                        ok = false;
                        break;
                    }
                }
                if(ok)
                {
                    m_parameters[index] = Parameter(gui);
                    index++;
                }
            }
        }
    }
    updateHostDisplay();
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(m_parameters[i].isValid())
        {
            setParameterNotifyingHost(i, m_parameters[i].getValue());
        }
    }
}

void InstanceProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    prepareDsp(16, 16, sampleRate, samplesPerBlock);
}

void InstanceProcessor::releaseResources()
{
    releaseDsp();
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
        int todo;
        //post to pd
    }
    lock();
    {
        m_midi.clear();
        MidiMessage message;
        MidiBuffer::Iterator it(midiMessages);
        int position = buffer.getNumSamples();
        while(it.getNextEvent(message, position))
        {
            if(message.isNoteOnOrOff())
            {
                sendMidiNote(message.getChannel(), message.getNoteNumber(), message.getVelocity());
            }
            else if(message.isController())
            {
                sendMidiControlChange(message.getChannel(), message.getControllerNumber(), message.getControllerValue());
            }
            else if(message.isPitchWheel())
            {
                sendMidiPitchBend(message.getChannel(), message.getPitchWheelValue());
            }
            else if(message.isChannelPressure())
            {
                sendMidiAfterTouch(message.getChannel(), message.getChannelPressureValue());
            }
            else if(message.isAftertouch())
            {
                sendMidiPolyAfterTouch(message.getChannel(), message.getNoteNumber(), message.getAfterTouchValue());
            }
            else if(message.isProgramChange())
            {
                sendMidiProgramChange(message.getChannel(), message.getProgramChangeNumber());
            }
        }
    }
   
    
    for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); ++i)
    {
        sendMessageFloat(m_parameters[i].getTie(), m_parameters[i].getValueNonNormalized());
    }
    
    performDsp(buffer.getNumSamples(),
               getTotalNumInputChannels(), buffer.getArrayOfReadPointers(),
               getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
    
    midiMessages.clear();
    midiMessages.swapWith(m_midi);
    unlock();
}

void InstanceProcessor::receivePost(std::string const& message)
{
    int notifi_gui;
}

void InstanceProcessor::receiveMidiNoteOn(int port, int channel, int pitch, int velocity)
{
    if(velocity)
    {
        m_midi.addEvent(MidiMessage::noteOn(channel+1, pitch, uint8(velocity)), 1);
    }
    else
    {
        m_midi.addEvent(MidiMessage::noteOff(channel+1, pitch, uint8(velocity)), 1);
    }
}

void InstanceProcessor::receiveMidiControlChange(int port, int channel, int control, int value)
{
    m_midi.addEvent(MidiMessage::controllerEvent(channel+1, control, value), 1);
}

void InstanceProcessor::receiveMidiProgramChange(int port, int channel, int value)
{
    m_midi.addEvent(MidiMessage::programChange(channel+1, value), 1);
}

void InstanceProcessor::receiveMidiPitchBend(int port, int channel, int value)
{
    m_midi.addEvent(MidiMessage::pitchWheel(channel+1, value), 1);
}

void InstanceProcessor::receiveMidiAfterTouch(int port, int channel, int value)
{
    m_midi.addEvent(MidiMessage::channelPressureChange(channel+1, value), 1);
}

void InstanceProcessor::receiveMidiPolyAfterTouch(int port, int channel, int pitch, int value)
{
    m_midi.addEvent(MidiMessage::aftertouchChange(channel+1, pitch, value), 1);
}

void InstanceProcessor::receiveMidiByte(int port, int value)
{
    m_midi.addEvent(MidiMessage(port, value), 1);
}

AudioProcessorEditor* InstanceProcessor::createEditor()
{
    return new InstanceEditor(*this);
}

void InstanceProcessor::loadPatch(const juce::File& file)
{
    suspendProcessing(true);
    if(isSuspended())
    {
        if(true)
        {
            releaseDsp();
            if(file.exists() && file.getFileExtension() == String(".pd"))
            {
                m_patch = pd::Patch(*this,
                                file.getFileName().toStdString(),
                                file.getParentDirectory().getFullPathName().toStdString());
            }
            else
            {
                m_patch = pd::Patch();
                consoleError("Camomile can't find the patch : " + file.getFullPathName().toStdString());
            }
        }
        parametersChanged();
        prepareDsp(getTotalNumInputChannels(), getTotalNumOutputChannels(), AudioProcessor::getSampleRate(), getBlockSize());
        
        std::vector<Listener*> listeners = getListeners();
        for(auto it : listeners)
        {
            it->patchChanged();
        }
    }
    
    suspendProcessing(false);
}

void InstanceProcessor::addListener(Listener* listener)
{
    if(listener)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_listeners.insert(listener);
    }
}

void InstanceProcessor::removeListener(Listener* listener)
{
    if(listener)
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_listeners.erase(listener);
    }
}

std::vector<InstanceProcessor::Listener*> InstanceProcessor::getListeners() const noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    return std::vector<Listener*>(m_listeners.begin(), m_listeners.end());
}

void InstanceProcessor::getStateInformation(MemoryBlock& destData)
{
    juce::XmlElement xml(String("CamomileSettings"));
    if(m_patch.isValid())
    {
        xml.setAttribute(String("name"), m_patch.getName());
        xml.setAttribute(String("path"), m_patch.getPath());
    }
    XmlElement* params = xml.createNewChildElement("params");
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(m_parameters[i].isValid())
        {
            params->setAttribute(String(m_parameters[i].getName(512)), double(m_parameters[i].getValue()));
        }
    }
    copyXmlToBinary(xml, destData);
}

void InstanceProcessor::setStateInformation (const void* data, int sizeInBytes)
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
                loadPatch(file);
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
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    return new InstanceProcessor();
}

// ==================================================================================== //
//                                  PARAMETERS                                          //
// ==================================================================================== //


InstanceProcessor::Parameter::Parameter()
: m_valid(false), m_value (0.f), m_min(0.f), m_max(0.f),
m_name (""), m_label(""), m_bname(), m_nsteps(0)
{
    
}

InstanceProcessor::Parameter::Parameter(Parameter const& other)
: m_valid(other.m_valid), m_value (other.m_value),
m_min(other.m_min), m_max(other.m_max),
m_name (other.m_name), m_label(other.m_label),
m_bname(other.m_bname), m_nsteps(other.m_nsteps)
{
    
}

InstanceProcessor::Parameter::Parameter(pd::Gui const& gui)
: m_valid(true), m_value (0.f),
m_min(gui.getMinimum()),
m_max(gui.getMaximum()),
m_name(gui.getName()),
m_label(gui.getLabel()),
m_bname(gui.getReceiveTie()),
m_nsteps(gui.getNumberOfSteps())
{
    setValueNonNormalized(gui.getValue());
}

InstanceProcessor::Parameter::~Parameter()
{
    
}

InstanceProcessor::Parameter& InstanceProcessor::Parameter::operator=(InstanceProcessor::Parameter const& other)
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

InstanceProcessor::Parameter& InstanceProcessor::Parameter::operator=(InstanceProcessor::Parameter&& other)
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

bool InstanceProcessor::Parameter::isValid() const noexcept
{
    return m_valid;
}

float InstanceProcessor::Parameter::getValue() const
{
    return m_value;
}

float InstanceProcessor::Parameter::getValueNonNormalized() const
{
    if(m_min < m_max)
    {
        return m_value * (m_max - m_min) + m_min;
    }
    return (1.f - m_value) * (m_min - m_max) + m_max;
}

void InstanceProcessor::Parameter::setValue(float newValue)
{
    newValue = std::min(std::max(newValue, 0.f), 1.f);
    if(m_nsteps)
    {
        const float step = (1.f/ float(m_nsteps - 1));
        m_value = std::round(newValue / step) * step;
    }
    else
    {
        m_value = newValue;
    }
}

void InstanceProcessor::Parameter::setValueNonNormalized(float newValue)
{
    m_value = getValueNormalized(newValue);
}

float InstanceProcessor::Parameter::getValueNormalized(float newValue)
{
    if(m_min < m_max)
    {
        return std::min(std::max((newValue - m_min) / (m_max - m_min), 0.f), 1.f);
    }
    return std::min(std::max(1.f  - ((newValue - m_max) / (m_min - m_max)), 0.f), 1.f);
}

float InstanceProcessor::Parameter::getDefaultValue() const {return 0.f;}

String InstanceProcessor::Parameter::getName(int maximumStringLength) const {return m_name;}

String InstanceProcessor::Parameter::getLabel() const {return m_label;}

String InstanceProcessor::Parameter::getText (float value, int size) const {return String(getValueNonNormalized());}

float InstanceProcessor::Parameter::getValueForText (const String& text) const {return text.getFloatValue();}

bool InstanceProcessor::Parameter::isOrientationInverted() const {return false;}

int InstanceProcessor::Parameter::getNumSteps() const
{
    return m_nsteps != 0 ? m_nsteps : AudioProcessor::getDefaultNumParameterSteps();
}



