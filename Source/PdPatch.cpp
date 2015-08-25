/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdPatch.h"
#include "PdObject.h"
#include "PdGui.h"

#include <iomanip>

namespace pd
{    
    // ==================================================================================== //
    //                                          PATCHER                                     //
    // ==================================================================================== //
    
    Patch::Patch()
    {
        m_internal = new Internal();
        m_internal->counter++;
        m_internal->canvas = NULL;
    }
    
    Patch::Patch(Instance const& instance, std::string const& name, std::string const& path)
    {
        
    }
    
    Patch::~Patch()
    {
        
    }
    
    std::vector<Object> Patch::getObjects() const noexcept
    {
        std::vector<Object> objects;
        /*
        for(t_gobj *y = m_cnv->gl_list; y; y = y->g_next)
        {
            if(eobj_iscicm(y))
            {
                objects.push_back(Object(y));
            }
        }*/
        return objects;
    }
    
    std::vector<Gui> Patch::getGuis() const noexcept
    {
        std::vector<Gui> guis;
        /*
        for(auto it : m_objects)
        {
            if(it->isGui())
            {
                sGui gui = std::dynamic_pointer_cast<Gui>(it);
                if(gui)
                {
                    guis.push_back(gui);
                }
            }
        }*/
        return guis;
    }
    
    Gui Patch::getCamomile() const noexcept
    {
        /*
        auto it = std::find_if(m_objects.begin(), m_objects.end(), [] (sObject const& obj)
                               {
                                   return obj->getName() == "c.camomile";
                               });
        if(it != m_objects.end())
        {
            return std::dynamic_pointer_cast<Gui>(*it);
        }
        else
        {
            return nullptr;
        }*/
        return Gui();
    }
    
    }



