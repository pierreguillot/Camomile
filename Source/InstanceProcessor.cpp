/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.h"
#include "PatchEditor.h"
#include "LookAndFeel.h"

InstanceProcessor::InstanceProcessor() : Instance(string("camomile"))
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
}

InstanceProcessor::~InstanceProcessor()
{
    lock_guard<mutex> guard(m_mutex_list);
    m_listeners.clear();
}

int InstanceProcessor::getNumParameters()
{
    return 0;
}

const String InstanceProcessor::getParameterName(int index)
{
    return String("Dummy ") + String(to_string(index + 1));
}

float InstanceProcessor::getParameter(int index)
{
    return 0.f;
}

void InstanceProcessor::setParameter(int index, float newValue)
{
    ;
}

float InstanceProcessor::getParameterDefaultValue(int index)
{
    return 0.;
}

const String InstanceProcessor::getParameterText(int index)
{
    return String("");
}

String InstanceProcessor::getParameterText(int index, int size)
{
    return String("");
}

String InstanceProcessor::getParameterLabel(int index) const
{
    return String("");
}

int InstanceProcessor::getParameterNumSteps(int index)
{
    return 1.f;
}

bool InstanceProcessor::isParameterAutomatable(int index) const
{
    return false;
}

bool InstanceProcessor::isParameterOrientationInverted(int index) const
{
    return false;
}

bool InstanceProcessor::isMetaParameter(int index) const
{
    return false;
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
    performDsp(buffer.getNumSamples(),
               getTotalNumInputChannels(), buffer.getArrayOfReadPointers(),
               getTotalNumOutputChannels(), buffer.getArrayOfWritePointers());
}

AudioProcessorEditor* InstanceProcessor::createEditor()
{
    return new PatchEditor(*this);
}

void InstanceProcessor::parametersChanged()
{
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
                m_patch = Patch(*this, file.getFileName().toStdString(), file.getParentDirectory().getFullPathName().toStdString());
            }
            else
            {
                m_patch = Patch();
            }
        }
    
        vector<Listener*> listeners = getListeners();
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
        lock_guard<mutex> guard(m_mutex_list);
        m_listeners.insert(listener);
    }
}

void InstanceProcessor::removeListener(Listener* listener)
{
    if(listener)
    {
        lock_guard<mutex> guard(m_mutex_list);
        m_listeners.erase(listener);
    }
}

vector<InstanceProcessor::Listener*> InstanceProcessor::getListeners() const noexcept
{
    lock_guard<mutex> guard(m_mutex_list);
    return vector<Listener*>(m_listeners.begin(), m_listeners.end());
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
    return new InstanceProcessor();
}


