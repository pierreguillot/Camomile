/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceProcessor.h"
#include "PatchEditor.h"
#include "LookAndFeel.h"

InstanceProcessor::InstanceProcessor() : Instance(string("camomile")), Messenger()
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
            const string mess = message.atoms[1];
            const int index = std::max((int)message.atoms[2], 0);
            if(mess == "beginchanges")
            {
                beginParameterChangeGesture(index);
            }
            else if(mess == "endchanges")
            {
                endParameterChangeGesture(index);
            }
            else if(mess == "value_changed")
            {
                sendParamChangeMessageToListeners(index, m_parameters[index].getNormalizedValue());
            }
            else if(mess == "attr_modified" || mess == "create" || mess == "destroy")
            {
                updateHostDisplay();
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
    Messenger::trigger();
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

void InstanceProcessor::parametersChanged()
{
    unbind();
    size_t index = 0;
    if(m_patch)
    {
        vector<Gui> objects(m_patch.getGuis());
        for(auto it : objects)
        {
            vector<Parameter> params = it.getParameters();
            if(!params.empty())
            {
                bind(it.getBindingName());
                for(size_t i = 0; i < params.size(); i++)
                {
                    if(index < m_parameters.size())
                    {
                        m_parameters[index] = params[i];
                        index++;
                    }
                }
            }
        }
        for(; index < m_parameters.size(); index++)
        {
            m_parameters[index] = Parameter();
        }
        std::sort(m_parameters.begin(), m_parameters.end(), [] (Parameter const& p1, Parameter const& p2)
                  {
                      return p1.getIndex() < p2.getIndex();
                  });
    }
    else
    {
        for(size_t i = 0; i < m_parameters.size(); i++)
        {
            m_parameters[i] = Parameter();
        }
    }
    
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(bool(m_parameters[i]))
        {
            m_parameters[i].setIndex(i);
            setParameterNotifyingHost(i, m_parameters[i].getNormalizedValue());
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
            vector<Gui> objects(m_patch.getGuis());
            for(auto it : objects)
            {
                unbind(it.getBindingName());
            }
            
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

void InstanceProcessor::getStateInformation(MemoryBlock& destData)
{
    XmlElement xml(String("CamomileSettings"));
    xml.setAttribute(String("name"), m_patch.getName());
    xml.setAttribute(String("path"), m_patch.getPath());
    for(size_t i = 0; i < m_parameters.size(); i++)
    {
        if(bool(m_parameters[i]))
        {
            xml.setAttribute(String(string("name") + to_string(i)), double(m_parameters[i].getNormalizedValue()));
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
            
            File file(path + File::separatorString + name);
            loadPatch(file);
            for(size_t i = 0; i < m_parameters.size(); i++)
            {
                if(bool(m_parameters[i]))
                {
                    setParameterNotifyingHost(i, xml->getDoubleAttribute(String(string("name") + to_string(i))));
                }
            }
        }
    }
}

AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new InstanceProcessor();
}


