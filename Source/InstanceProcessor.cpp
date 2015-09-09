/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.h"
#include "PatchEditor.h"
#include "LookAndFeel.h"

InstanceProcessor::InstanceProcessor() : Instance(string("camomile")), Messenger(Instance(*this))
{
    static CamoLookAndFeel lookAndFeel;
    LookAndFeel::setDefaultLookAndFeel(&lookAndFeel);
    m_parameters.resize(32);
}

InstanceProcessor::~InstanceProcessor()
{
    lock_guard<mutex> guard(m_mutex_list);
    m_listeners.clear();
    m_parameters.clear();
}

int InstanceProcessor::getNumParameters()
{
    return int(m_parameters.size());
}

const String InstanceProcessor::getParameterName(int index)
{
    if(m_parameters[index])
        return String(m_parameters[index].getName());
    else
        return String("Dummy ") + String(to_string(index + 1));
}

float InstanceProcessor::getParameter(int index)
{
    return m_parameters[index].getNormalizedValue();
}

void InstanceProcessor::setParameter(int index, float newValue)
{
    m_parameters[index].setNormalizedValue(newValue);
}

float InstanceProcessor::getParameterDefaultValue(int index)
{
    return 0.;
}

const String InstanceProcessor::getParameterText(int index)
{
    return String(m_parameters[index].getTextValue().c_str());
}

String InstanceProcessor::getParameterText(int index, int size)
{
    return String(m_parameters[index].getTextValue().c_str(), size);
}

String InstanceProcessor::getParameterLabel(int index) const
{
    return String(m_parameters[index].getLabel());
}

int InstanceProcessor::getParameterNumSteps(int index)
{
    return m_parameters[index].getNumberOfStep();
}

bool InstanceProcessor::isParameterAutomatable(int index) const
{
    return m_parameters[index].isAutomatable();
}

bool InstanceProcessor::isParameterOrientationInverted(int index) const
{
    return m_parameters[index].isInverted();
}

bool InstanceProcessor::isMetaParameter(int index) const
{
    return m_parameters[index].isMetaParameter();
}

void InstanceProcessor::receive(Message const& message)
{
    if(message.selector == "parameter")
    {
        if(message.atoms.size() == 3 && message.atoms[1].isSymbol() && message.atoms[2].isFloat())
        {
            if(message.atoms[1] == "beginchanges")
            {
                beginParameterChangeGesture(int(message.atoms[2]));
            }
            else if(message.atoms[1] == "endchanges")
            {
                endParameterChangeGesture(int(message.atoms[2]));
            }
            else if(message.atoms[1] == "value_changed")
            {
                sendParamChangeMessageToListeners(int(message.atoms[2]), m_parameters[int(message.atoms[2])].getNormalizedValue());
            }
            else if(message.atoms[1] == "attr_modified")
            {
                ;
            }
        }
    }
}

void InstanceProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    prepareDsp(getNumInputChannels(), getNumOutputChannels(), sampleRate, samplesPerBlock);
}

void InstanceProcessor::releaseResources()
{
    releaseDsp();
}

void InstanceProcessor::processBlock(AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    Instance::trigger();
    for(int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {
        buffer.clear(i, 0, buffer.getNumSamples());
    }
    performDsp(buffer.getNumSamples(),
               getNumInputChannels(), buffer.getArrayOfReadPointers(),
               getNumOutputChannels(), buffer.getArrayOfWritePointers());
}

AudioProcessorEditor* InstanceProcessor::createEditor()
{
    return new PatchEditor(*this);
}

void InstanceProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml("CamomileSettings");
    xml.setAttribute("name", m_patch.getName());
    xml.setAttribute("path", m_patch.getPath());
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

void InstanceProcessor::loadPatch(const juce::File& file)
{
    suspendProcessing(true);
    if(isSuspended())
    {
        if(true)
        {
            releaseDsp();
            vector<Gui> objects(m_patch.getGuis());
            for(auto it : objects)
            {
               // unbind(it.getBindingName());
            }
            
            if(file.exists() && file.getFileExtension() == String(".pd"))
            {
                m_patch = Patch(*this,
                                file.getFileName().toStdString(),
                                file.getParentDirectory().getFullPathName().toStdString());
            }
            else
            {
                m_patch = Patch();
            }
            
            size_t index = 0;
            if(m_patch)
            {
                vector<Gui> objects(m_patch.getGuis());
                for(auto it : objects)
                {
                    bind(it.getBindingName());
                    vector<Parameter> params = it.getParameters();
                    if(!params.empty())
                    {
                       // bind(it.getBindingName());
                        for(size_t i = 0; i < params.size(); i++)
                        {
                            if(index < m_parameters.size())
                            {
                                m_parameters[index] = params[i];
                                m_parameters[index].setIndex(index);
                                index++;
                            }
                        }
                    }
                }
                for(; index < m_parameters.size(); index++)
                {
                    m_parameters[index] = Parameter();
                }
            }
        }
        
        for(size_t i = 0; i < m_parameters.size(); i++)
        {
            if(bool(m_parameters[i]))
            {
                setParameterNotifyingHost(i+1, m_parameters[i].getNormalizedValue());
            }
        }
    
        vector<Listener*> listeners = getListeners();
        for(auto it : listeners)
        {
            it->patchChanged();
        }
        updateHostDisplay();
        prepareDsp(getNumInputChannels(), getNumOutputChannels(), getSampleRate(), getBlockSize());
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

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new InstanceProcessor();
}


