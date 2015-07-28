//
//  CicmObject.cpp
//  Camomile
//
//  Created by Guillot Pierre on 27/07/2015.
//
//

#include "CicmObject.h"
#include "CicmPatch.h"

CicmObject::CicmObject() : m_box(nullptr)
{
    
}

CicmObject::CicmObject(CicmPatch const& patch, t_ebox* box) : m_box(box)
{
    t_rect rect;
    ebox_get_rect_for_view(box, &rect);
    const int _x = int(((t_object *)box)->te_xpix);
    const int _y = int(((t_object *)box)->te_ypix);
    m_bounds.setBounds(int(_x - patch.getX()), int(_y - patch.getY()), int(rect.width), int(rect.height));
}

CicmObject::CicmObject(CicmObject const& other) : m_box(other.m_box), m_bounds(other.m_bounds)
{
    
}

void CicmObject::operator=(CicmObject const& from)
{
    m_box = from.m_box;
    m_bounds = from.m_bounds;
}

CicmObject::~CicmObject()
{
    
}

int CicmObject::getX() const noexcept
{
    return m_bounds.getX();
}

int CicmObject::getY() const noexcept
{
    return m_bounds.getY();
}

Point<int> CicmObject::getPosition() const noexcept
{
    return m_bounds.getPosition();
}

int CicmObject::getWidth() const noexcept
{
    return m_bounds.getWidth();
}

int CicmObject::getHeight() const noexcept
{
    return m_bounds.getHeight();
}

Point<int> CicmObject::getSize() const noexcept
{
    return Point<int>(m_bounds.getWidth(), m_bounds.getHeight());
}

Rectangle<int> CicmObject::getBounds() const noexcept
{
    return Rectangle<int>(0, 0, m_bounds.getX(), m_bounds.getY());
}

Colour CicmObject::getBackgroundColor() const noexcept
{
    t_eclass* c = eobj_getclass(m_box);
    if(c && c->c_widget.w_getdrawparameters)
    {
        t_edrawparams params;
        c->c_widget.w_getdrawparameters(m_box, NULL, &params);
        return camo::toJuce(params.d_boxfillcolor);
    }
    return Colours::white;
}

Colour CicmObject::getBorderColor() const noexcept
{
    t_eclass* c = eobj_getclass(m_box);
    if(c && c->c_widget.w_getdrawparameters)
    {
        t_edrawparams params;
        c->c_widget.w_getdrawparameters(m_box, NULL, &params);
        return camo::toJuce(params.d_bordercolor);
    }
    return Colours::white;
}

int CicmObject::getBorderSize() const noexcept
{
    t_eclass* c = eobj_getclass(m_box);
    if(c && c->c_widget.w_getdrawparameters)
    {
        t_edrawparams params;
        c->c_widget.w_getdrawparameters(m_box, NULL, &params);
        return (int)params.d_borderthickness;
    }
    return 0;
}


