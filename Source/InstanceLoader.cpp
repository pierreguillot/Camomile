/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "InstanceLoader.hpp"

InstanceLoader::InstanceLoader() : m_name("Camomile"), m_ninputs(16), m_noutputs(16), m_parameters(64)
{
    File file(File::getSpecialLocation(File::SpecialLocationType::currentExecutableFile).getParentDirectory().getFullPathName() + File::separatorString + String("Camomile.json"));
    if(file.exists())
    {
        juce::var infos(juce::JSON::parse(file));
        if(infos.isObject())
        {
            DynamicObject* main = infos.getDynamicObject();
            if(main)
            {
                if(main->hasProperty("Camomile"))
                {
                    var properties(main->getProperty("Camomile"));
                    if(properties.isObject())
                    {
                        DynamicObject* current = properties.getDynamicObject();
                        if(current->hasProperty("name"))
                        {
                            var namep =  current->getProperty("name");
                            if(namep.isString())
                            {
                                m_name = namep.toString();
                            }
                        }
                        if(current->hasProperty("ninputs"))
                        {
                            var ninputs = current->getProperty("ninputs");
                            if(ninputs.isInt() && ninputs.isInt64())
                            {
                                m_ninputs = int(ninputs);
                            }
                        }
                        if(current->hasProperty("noutputs"))
                        {
                            var noutputs = current->getProperty("noutputs");
                            if(noutputs.isInt())
                            {
                                m_noutputs = int(noutputs);
                            }
                        }
                        if(current->hasProperty("parameters"))
                        {
                            var params = current->getProperty("parameters");
                            if(params.isArray())
                            {
                                Array<var>* params_array = params.getArray();
                                if(params_array)
                                {
                                    m_parameters.resize(params_array->size());
                                }
                            }
                            
                        }
                    }
                }
            }
        }
    }
}






