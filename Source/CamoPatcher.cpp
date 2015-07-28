/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "CamoPatcher.h"

namespace camo
{
    /*
    Patcher::Patcher() noexcept
    {
        ;
    }
    
    Patcher::Patcher(const std::string& filename, const std::string& path) :
    pd::Patch(filename, path)
    {
        loadController();
    }
    
    Patcher::Patcher(void* handle, int dollarZero, const std::string& filename, const std::string& path) :
    pd::Patch(handle, dollarZero, filename, path), m_controller(nullptr)
    {
        loadController();
    }
    
    Patcher::Patcher(pd::Patch const& other) :
    pd::Patch(other), m_controller(nullptr)
    {
        loadController();
    }
    
    Patcher::Patcher(Patcher const& other) :
    pd::Patch(other), m_controller(other.m_controller), m_bounds(other.m_bounds)
    {
        
    }
    
    Patcher::~Patcher()
    {
        
    }
    
    void Patcher::operator =(pd::Patch const& from)
    {
        Patch::operator=(from);
        loadController();
    }
    
    void Patcher::operator =(Patcher const& from)
    {
        Patch::operator=(from);
        m_controller = from.m_controller;
        m_bounds = from.m_bounds;
    }
    
    bool Patcher::isPlugin() const noexcept
    {
        return isValid() && m_controller;
    }
    
    int Patcher::getX() const noexcept
    {
        return m_bounds.getX();
    }
    
    int Patcher::getY() const noexcept
    {
        return m_bounds.getY();
    }
    
    Point<int> Patcher::getPosition() const noexcept
    {
        return m_bounds.getPosition();
    }
    
    int Patcher::getWidth() const noexcept
    {
        return m_bounds.getWidth();
    }
    
    int Patcher::getHeight() const noexcept
    {
        return m_bounds.getHeight();
    }
    
    Point<int> Patcher::getSize() const noexcept
    {
        return Point<int>(m_bounds.getWidth(), m_bounds.getHeight());
    }
    
    Rectangle<int> Patcher::getBounds() const noexcept
    {
        return Rectangle<int>(0, 0, m_bounds.getX(), m_bounds.getY());
    }
     */
}



