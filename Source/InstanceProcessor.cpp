/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.h"
#include "PatchEditor.h"
#include "LookAndFeel.h"

InstanceProcessor::InstanceProcessor() : pd::Instance(pd::Pd::createInstance())
{
    m_parameters.resize(32);
}

InstanceProcessor::~InstanceProcessor()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_listeners.clear();
}

int InstanceProcessor::getNumParameters()
{
    return int(m_parameters.size());
}

const String InstanceProcessor::getParameterName(int index)
{
    if(m_parameters[index].isValid())
        return m_parameters[index].getName(512);
    else
        return String("Dummy ") + String(std::to_string(index + 1));
}

float InstanceProcessor::getParameter(int index)
{
    return m_parameters[index].getValue();
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

void InstanceProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    lock();
    prepareDsp(getTotalNumInputChannels(), getTotalNumOutputChannels(), sampleRate, samplesPerBlock);
    unlock();
}

void InstanceProcessor::releaseResources()
{
    lock();
    releaseDsp();
    unlock();
}

void InstanceProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    for(int i = getTotalNumInputChannels(); i < getTotalNumOutputChannels(); ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    lock();
    for(size_t i = 0; i < m_parameters.size() && m_parameters[i].isValid(); i++)
    {
        send(m_parameters[i].getBindingPtr(), m_parameters[i].getValueNonNormalized());
    }
    
    performDsp(buffer.getNumSamples(),
               getTotalNumInputChannels(), buffer.getArrayOfReadPointers(),
               getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
    unlock();
}

AudioProcessorEditor* InstanceProcessor::createEditor()
{
    return new PatchEditor(*this);
}

void InstanceProcessor::parametersChanged()
{
    size_t index = 0;
    if(m_patch.isValid())
    {
        std::vector<pd::Gui> guis(m_patch.getGuis());
        for(auto const& gui : guis)
        {
            m_parameters[index] = SliderParameter(gui);
            index++;
        }
        for(; index < m_parameters.size(); index++)
        {
            m_parameters[index] = SliderParameter();
        }
    }
    else
    {
        for(size_t i = 0; i < m_parameters.size(); i++)
        {
            m_parameters[i] = SliderParameter();
        }
    }
    
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(m_parameters[i].isValid())
        {
            setParameterNotifyingHost(i, m_parameters[i].getValue());
        }
    }
    
    updateHostDisplay();
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
            }
        }
    
        std::vector<Listener*> listeners = getListeners();
        for(auto it : listeners)
        {
            it->patchChanged();
        }
        parametersChanged();
        prepareDsp(getTotalNumInputChannels(), getTotalNumOutputChannels(), getSampleRate(), getBlockSize());
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
    XmlElement xml(String("CamomileSettings"));
    xml.setAttribute(String("name"), m_patch.getName());
    xml.setAttribute(String("path"), m_patch.getPath());
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
            File file(path + File::separatorString + name);
            loadPatch(file);
        }
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    return new InstanceProcessor();
}


