/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.hpp"
#include "InstanceEditor.hpp"
#include "LookAndFeel.hpp"

pd::Symbol InstanceProcessor::s_playing;
pd::Symbol InstanceProcessor::s_measure;

InstanceProcessor::InstanceProcessor() : pd::Instance("Camomile"),
m_parameters(32), m_playing_list(2), m_measure_list(5)
{
    sendConsolePost(std::string("Camomile ") +
                         std::string(JucePlugin_VersionString) +
                         std::string(" for Pure Data ") +
                         pd::Environment::getPdVersion());
    s_playing           = pd::Symbol("playing");
    s_measure           = pd::Symbol("measure");
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
        if(m_parameters[i].getName() == name)
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
        m_parameters[i] = pd::Parameter();
    }
    pd::Patch patch(getPatch());
    if(patch.isValid())
    {
        std::vector<pd::Gui> guis(patch.getGuis());
        for(auto const& gui : guis)
        {
            if(gui.isParameter())
            {
                bool ok = true;
                for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); i++)
                {
                    if(gui.getName() == m_parameters[i].getName())
                    {
                        sendConsoleError("Warning in patch " + patch.getName() + ": "  + gui.getName() + " parameter is duplicated !");
                        ok = false;
                        break;
                    }
                    else if(gui.getReceiveTie() == m_parameters[i].getTie())
                    {
                        sendConsoleError("Warning in patch " + patch.getName() + ": "  + gui.getName() + " parameter shares the same receive symbol with another parameter !");
                        ok = false;
                        break;
                    }
                }
                if(ok)
                {
                    m_parameters[index] = pd::Parameter(gui);
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
            setParameterNotifyingHost(i, m_parameters[i].getValueNormalized());
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
    bool infos = false;
    
    AudioPlayHead* playhead = getPlayHead();
    if(playhead && m_patch_tie)
    {
        infos = playhead->getCurrentPosition(m_playinfos);
    }
    lock();
    {
        m_midi.clear();
        if(infos)
        {
            m_playing_list.setFloat(0, m_playinfos.isPlaying);
            m_playing_list.setFloat(1, m_playinfos.timeInSeconds);
            sendMessageAnything(m_patch_tie, s_playing, m_playing_list);
            m_measure_list.setFloat(0, m_playinfos.bpm);
            m_measure_list.setFloat(1, m_playinfos.timeSigNumerator);
            m_measure_list.setFloat(2, m_playinfos.timeSigDenominator);
            m_measure_list.setFloat(3, m_playinfos.ppqPosition);
            m_measure_list.setFloat(4, m_playinfos.ppqPositionOfLastBarStart);
            sendMessageAnything(m_patch_tie, s_measure, m_measure_list);
        }
        for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); ++i)
        {
            sendMessageFloat(m_parameters[i].getTie(), m_parameters[i].getValueNonNormalized());
        }
        
        MidiMessage message;
        MidiBuffer::Iterator it(midiMessages);
        int position = midiMessages.getFirstEventTime();
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
    midiMessages.clear();
    performDsp(buffer.getNumSamples(),
               getTotalNumInputChannels(), buffer.getArrayOfReadPointers(),
               getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
    midiMessages.swapWith(m_midi);
    unlock();
}

void InstanceProcessor::receiveConsolePost(std::string const& message)
{
    pd::Console::History::addPost(message);
}

void InstanceProcessor::receiveConsoleLog(std::string const& message)
{
    pd::Console::History::addLog(message);
}

void InstanceProcessor::receiveConsoleError(std::string const& message)
{
    pd::Console::History::addError(message);
}

void InstanceProcessor::receiveConsoleFatal(std::string const& message)
{
    pd::Console::History::addFatal(message);
}

void InstanceProcessor::receiveMidiNoteOn(int channel, int pitch, int velocity)
{
    if(velocity)
    {
        m_midi.addEvent(MidiMessage::noteOn(channel+1, pitch, uint8(velocity)), 0);
    }
    else
    {
        m_midi.addEvent(MidiMessage::noteOff(channel+1, pitch, uint8(velocity)), 0);
    }
}

void InstanceProcessor::receiveMidiControlChange(int channel, int control, int value)
{
    m_midi.addEvent(MidiMessage::controllerEvent(channel+1, control, value), 0);
}

void InstanceProcessor::receiveMidiProgramChange(int channel, int value)
{
    m_midi.addEvent(MidiMessage::programChange(channel+1, value), 0);
}

void InstanceProcessor::receiveMidiPitchBend(int channel, int value)
{
    m_midi.addEvent(MidiMessage::pitchWheel(channel+1, value), 0);
}

void InstanceProcessor::receiveMidiAfterTouch(int channel, int value)
{
    m_midi.addEvent(MidiMessage::channelPressureChange(channel+1, value), 0);
}

void InstanceProcessor::receiveMidiPolyAfterTouch(int channel, int pitch, int value)
{
    m_midi.addEvent(MidiMessage::aftertouchChange(channel+1, pitch, value), 0);
}

void InstanceProcessor::receiveMidiByte(int port, int value)
{
    m_midi.addEvent(MidiMessage(port, value), 0);
}

AudioProcessorEditor* InstanceProcessor::createEditor()
{
    return new InstanceEditor(*this);
}

void InstanceProcessor::loadPatch(std::string const& name, std::string const& path)
{
    suspendProcessing(true);
    if(isSuspended())
    {
        {
            releaseDsp();
            m_patch = pd::Patch(*this, name, path);
            pd::Patch patch(getPatch());
            if(patch.isValid())
            {
                m_patch_tie = pd::Tie(std::to_string(patch.getDollarZero()) + "-playhead");
            }
            else
            {
                m_patch_tie = pd::Tie();
                sendConsoleError("Camomile can't find the patch : " + name);
            }
        }
        parametersChanged();
        prepareDsp(getTotalNumInputChannels(), getTotalNumOutputChannels(),
                   AudioProcessor::getSampleRate(), getBlockSize());
        
        pd::PatchManager::notifyListeners();
    }
    
    suspendProcessing(false);
}

void InstanceProcessor::closePatch()
{
    suspendProcessing(true);
    if(isSuspended())
    {
        {
            releaseDsp();
            m_patch = pd::Patch();
            m_patch_tie = pd::Tie();
        }
        
        parametersChanged();
        prepareDsp(getTotalNumInputChannels(), getTotalNumOutputChannels(),
                   AudioProcessor::getSampleRate(), getBlockSize());
        
        pd::PatchManager::notifyListeners();
    }
    suspendProcessing(false);
}

void InstanceProcessor::getStateInformation(MemoryBlock& destData)
{
    juce::XmlElement xml(String("CamomileSettings"));
    
    pd::Patch patch(getPatch());
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
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    return new InstanceProcessor();
}




