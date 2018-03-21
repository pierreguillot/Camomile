/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginEnvironment.h"

// ======================================================================================== //
//                                      FILE WATCHER                                        //
// ======================================================================================== //

class CamomileFileWatcher : public Timer
{
public:
    CamomileFileWatcher() :
    m_file(CamomileEnvironment::getPatchPath() + File::getSeparatorString() + CamomileEnvironment::getPatchName())
    {
        if(CamomileEnvironment::wantsAutoReload())
        {
            if(m_file.exists())
            {
                m_time = m_file.getLastModificationTime();
                startTimer(100);
            }
        }
    }
    
    virtual ~CamomileFileWatcher() {}
    
    void timerCallback()
    {
        if(m_file.exists())
        {
            Time const ntime = m_file.getLastModificationTime();
            if(ntime != m_time)
            {
                m_time = ntime;
                fileChanged();
            }
        }
    }
    
    virtual void fileChanged() = 0;
    
private:
    File const m_file;
    Time m_time;
};

