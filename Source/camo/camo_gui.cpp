/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "camo_gui.hpp"

namespace camo
{
    // ==================================================================================== //
    //                                  CAMOMILE GUI                                        //
    // ==================================================================================== //
    
    gui::gui(processor& processor, xpd::gui const& g) : m_processor(processor), m_gui(g)
    {
        setBounds(m_gui.x(), m_gui.y(), m_gui.width(), m_gui.height());
        setOpaque(true);
    }
    
    void gui::set(float value, bool normalized)
    {
        const float max = maximum();
        const float min = minimum();
        value = std::max(std::min(normalized ? (value * (max - min) + min) : value, max), min);
        m_processor.send(m_gui.receive_tie(), get_symbol_float(), {value});
    }
    
    void gui::update()
    {
        ;
    }
    
    
    // ==================================================================================== //
    //                                  CAMOMILE BANG                                       //
    // ==================================================================================== //
    
    gui::bang::bang(processor& processor, xpd::gui const& g) : gui(processor, g)
    {
        
    }
    
    void gui::bang::paint(Graphics& g)
    {
        g.fillAll(env::get_color_bg());
        g.setColour(env::get_color_bd());
        g.drawRect(getLocalBounds(), env::get_border_size());
        g.drawEllipse(getWidth() / 4, getHeight() / 4, getWidth() / 2, getHeight() / 2, env::get_border_size());
        if(get() != 0.f)
        {
            g.fillEllipse(getWidth() / 4, getHeight() / 4, getWidth() / 2, getHeight() / 2);
        }
    }
    
    void gui::bang::mouseDown(const MouseEvent& event)
    {
        int tosee;
        //startEdition();
        set(1.f);
        //stopEdition();
    }
    
    // ==================================================================================== //
    //                                  CAMOMILE TOGGLE                                     //
    // ==================================================================================== //
    
    gui::toggle::toggle(processor& processor, xpd::gui const& g) : gui(processor, g)
    {
        
    }
    
    void gui::toggle::paint(Graphics& g)
    {
        g.fillAll(env::get_color_bg());
        g.setColour(env::get_color_bd());
        g.drawRect(getLocalBounds(), env::get_border_size());
        if(get() != 0.f)
        {
            g.drawLine(0, 0, getWidth(), float(getHeight()), env::get_border_size());
            g.drawLine(getWidth(), 0, 0, getHeight(), env::get_border_size());
        }
    }
    
    void gui::toggle::mouseDown(const MouseEvent& event)
    {
        int tosee;
        //startEdition();
        set(1.f - get());
        //stopEdition();
    }
    
    // ==================================================================================== //
    //                                      JPATCH                                          //
    // ==================================================================================== //
    
    jPatch::jPatch(xpd::patch const& patch)
    {
        setSize(std::max(patch.width(), 120), std::max(patch.height(), 20));
        setInterceptsMouseClicks(false, true);
        
        std::vector<xpd::object> objects(patch.objects());
        for(size_t i = 0; i < objects.size(); ++i)
        {
            if(objects[i].is_gui())
            {
                
            }
            else
            {
                
            }
        }
        
    }
}
