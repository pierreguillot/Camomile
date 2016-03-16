/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.hpp"
#include "InstanceEditor.hpp"
#include "LookAndFeel.hpp"

InstanceProcessor::InstanceProcessor() : pd::Instance(pd::Pd::createInstance())
{
    static bool initialzed = false;
    if(!initialzed)
    {
        pd::Pd::logToConsole(std::string("Camomile ") +
                              std::string(JucePlugin_VersionString) +
                              std::string(" for Pure Data ") +
                              pd::Pd::getPdVersion());
        initialzed = true;
    }
    Gui::addInstance();
    m_parameters.resize(32);
    busArrangement.inputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(16);
    busArrangement.outputBuses.getReference(0).channels = AudioChannelSet::discreteChannels(16);
    m_path = juce::File::getCurrentWorkingDirectory().getFullPathName();
}

InstanceProcessor::~InstanceProcessor()
{
    Gui::removeInstance();
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

int InstanceProcessor::getParameterIndex(pd::BindingName const& name)
{
    if(name != nullptr)
    {
        for(size_t i = 0; i < m_parameters.size(); i++)
        {
            if(m_parameters[i].getBindingName() == name)
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
                        pd::Pd::errorToConsole("Warning in patch " + m_patch.getName() + ": "  + gui.getName() + " parameter is duplicated !");
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
    prepareDsp(getTotalNumInputChannels(), getTotalNumOutputChannels(), sampleRate, samplesPerBlock);
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
    
    MidiMessage message;
    MidiBuffer::Iterator it(midiMessages);
    int samplePosition = buffer.getNumSamples();
    lock();
    while(it.getNextEvent(message, samplePosition))
    {
        if(message.isNoteOnOrOff())
        {
            sendNote(message.getChannel(), message.getNoteNumber(), message.getVelocity());
        }
        else if(message.isController())
        {
            sendControlChange(message.getChannel(), message.getControllerNumber(), message.getControllerValue());
        }
        else if(message.isPitchWheel())
        {
            sendPitchBend(message.getChannel(), message.getPitchWheelValue());
        }
        else if(message.isAftertouch())
        {
            sendAfterTouch(message.getChannel(), message.getAfterTouchValue());
        }
        else if(message.isProgramChange())
        {
            sendProgramChange(message.getChannel(), message.getProgramChangeNumber());
        }
    }
    midiMessages.clear();
    for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); ++i)
    {
        send(m_parameters[i].getBindingName(), m_parameters[i].getValueNonNormalized());
    }
    
    //midiMessages.addEvent(
    performDsp(buffer.getNumSamples(),
               getTotalNumInputChannels(), buffer.getArrayOfReadPointers(),
               getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
    unlock();
    
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
                m_patch = createPatch(file.getFileName().toStdString(), file.getParentDirectory().getFullPathName().toStdString());
            }
            else
            {
                m_patch = pd::Patch();
                pd::Pd::errorToConsole("Camomile can't find the patch : " + file.getFullPathName().toStdString());
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
m_name (""), m_label(""), m_bname(nullptr), m_nsteps(0)
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
m_bname(gui.getBindingName()),
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



