/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "CamoInterface.h"

namespace camo
{
    Interface::Interface(Object const& object) : m_object(object)
    {
        int remove_camo_position;
        Component::setBounds(m_object.getBounds());
        Component::setVisible(true);
    }
    
    void Interface::paint(Graphics& g)
    {
        DrawParameters parameters = m_object.getDrawParameters();
        g.fillAll(parameters.getBackgroundColor());
        g.setColour(parameters.getBorderColor());
        g.drawRect(getBounds().withZeroOrigin());
    }
}



