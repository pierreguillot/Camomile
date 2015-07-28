//
//  CicmPatch.cpp
//  Camomile
//
//  Created by Guillot Pierre on 27/07/2015.
//
//

#include "CicmPatch.h"

CicmPatch::CicmPatch() :
pd::Patch(), m_controller(nullptr)
{
    
}

CicmPatch::CicmPatch(const std::string& filename, const std::string& path) :
pd::Patch(filename, path), m_controller(nullptr)
{
    loadController();
}

CicmPatch::CicmPatch(void* handle, int dollarZero, const std::string& filename, const std::string& path) :
pd::Patch(handle, dollarZero, filename, path), m_controller(nullptr)
{
    loadController();
}

CicmPatch::CicmPatch(pd::Patch const& other) :
pd::Patch(other), m_controller(nullptr)
{
    loadController();
}

CicmPatch::CicmPatch(CicmPatch const& other) :
pd::Patch(other), m_controller(other.m_controller), m_bounds(other.m_bounds)
{
    
}

CicmPatch::~CicmPatch()
{
    
}

void CicmPatch::operator =(pd::Patch const& from)
{
    Patch::operator=(from);
    loadController();
}

void CicmPatch::operator =(CicmPatch const& from)
{
    Patch::operator=(from);
    m_controller = from.m_controller;
    m_bounds = from.m_bounds;
}

bool CicmPatch::isPlugin() const noexcept
{
    return isValid() && m_controller;
}

int CicmPatch::getX() const noexcept
{
    return m_bounds.getX();
}

int CicmPatch::getY() const noexcept
{
    return m_bounds.getY();
}

Point<int> CicmPatch::getPosition() const noexcept
{
    return m_bounds.getPosition();
}

int CicmPatch::getWidth() const noexcept
{
    return m_bounds.getWidth();
}

int CicmPatch::getHeight() const noexcept
{
    return m_bounds.getHeight();
}

Point<int> CicmPatch::getSize() const noexcept
{
    return Point<int>(m_bounds.getWidth(), m_bounds.getHeight());
}

Rectangle<int> CicmPatch::getBounds() const noexcept
{
    return Rectangle<int>(0, 0, m_bounds.getX(), m_bounds.getY());
}

int CicmPatch::getNumberOfObjects() const noexcept
{
    return isPlugin() ? m_controller->f_nboxes : 0;
}

std::vector<CicmObject> CicmPatch::getObjects() const noexcept
{
    std::vector<CicmObject> objects;
    if(isPlugin())
    {
        for(int i = 0; i < m_controller->f_nboxes; i++)
        {
            objects.push_back(CicmObject(*this, m_controller->f_boxes[i]));
        }
    }
    return objects;
}

void CicmPatch::loadController()
{
    t_canvas* cnv = (t_canvas *)(pd::Patch::handle());
    if(cnv)
    {
        t_symbol* name = gensym("c.camomile");
        t_gobj *y;
        for(y = cnv->gl_list; y; y = y->g_next)
        {
            if(eobj_getclassname(y) == name)
            {
                t_rect rect;
                m_controller = (t_camomile *)y;
                ebox_get_rect_for_view((t_ebox *)m_controller, &rect);
                m_bounds.setBounds(int(((t_object *)y)->te_xpix), int(((t_object *)y)->te_ypix), int(rect.width), int(rect.height));
                return;
            }
        }
    }
}