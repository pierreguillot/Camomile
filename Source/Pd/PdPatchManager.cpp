/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdPatchManager.hpp"

namespace pd
{
    PatchManager::PatchManager()
    {
        
    }
    
    PatchManager::~PatchManager()
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_listeners.clear();
    }
    
    void PatchManager::addListener(Listener* listener)
    {
        if(listener)
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            m_listeners.insert(listener);
        }
    }
    
    void PatchManager::removeListener(Listener* listener)
    {
        if(listener)
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            m_listeners.erase(listener);
        }
    }
    
    void PatchManager::notifyListeners()
    {
        std::vector<Listener*> listeners;
        {
            std::lock_guard<std::mutex> guard(m_mutex);
            listeners.reserve(listeners.size());
            listeners.insert(listeners.begin(), m_listeners.begin(), m_listeners.end());
        }
        for(size_t i = 0; i < listeners.size(); ++i)
        {
            listeners[i]->patchChanged();
        }
    }
}