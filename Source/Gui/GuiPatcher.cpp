/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Gui.hpp"
#include "GuiPatcher.hpp"
#include "GuiRadio.hpp"
#include "GuiSlider.hpp"
#include "GuiToggle.hpp"
#include "GuiNumbox.hpp"
#include "GuiLabel.hpp"

// ==================================================================================== //
//                                      GUI LABEL                                       //
// ==================================================================================== //

GuiPatcher::GuiPatcher()
{
    setBounds(0, 20, 600, 400);
    setInterceptsMouseClicks(false, true);
}

GuiPatcher::~GuiPatcher()
{
    
}

void GuiPatcher::timerCallback()
{
    for(int i = 0; i < m_parameters.size(); i++)
    {
        m_parameters[i]->update();
    }
}

void GuiPatcher::setPatch(InstanceProcessor& processor, xpd::patch const& patch)
{
    stopTimer();
    m_comment.clear();
    m_parameters.clear();
    m_labels.clear();
    if(bool(patch))
    {
        setSize(std::max(patch.width(), 120), std::max(patch.height(), 20));
        std::vector<xpd::object> objects(patch.objects());
        for(size_t i = 0; i < objects.size(); ++i)
        {
            xpd::gui gui;
            try
            {
                gui = objects[i];
            }
            catch(...)
            {
                ;
            }
            if(bool(gui))
            {
                if(gui.type() == xpd::gui::number)
                {
                    m_parameters.add(new GuiNumbox(processor, gui));
                    addAndMakeVisible(m_parameters.getLast());
                }
                else if(gui.type() == xpd::gui::radio_horizontal ||
                        gui.type() == xpd::gui::radio_vertical)
                {
                    m_parameters.add(new GuiRadio(processor, gui));
                    addAndMakeVisible(m_parameters.getLast());
                }
                else if(gui.type() == xpd::gui::slider_horizontal ||
                        gui.type() == xpd::gui::slider_vertical)
                {
                    m_parameters.add(new GuiSlider(processor, gui));
                    addAndMakeVisible(m_parameters.getLast());
                }
                else if(gui.type() == xpd::gui::toggle)
                {
                    m_parameters.add(new GuiToggle(processor, gui));
                    addAndMakeVisible(m_parameters.getLast());
                }
                
                int todo;
                /*
                if(gui.isParameter())
                {
                    m_labels.add(new GuiLabel(processor, gui));
                    addAndMakeVisible(m_labels.getLast());
                }
                 */
            }
            else
            {
                /*
                 std::vector<xpd::Object> cmts(patch.getComments());
                 for(size_t i = 0; i < cmts.size(); ++i)
                 {
                 m_comment.add(new GuiComment(cmts[i]));
                 addAndMakeVisible(m_comment.getLast());
                 }
                 */
            }
        }
        repaint();
    }
    startTimer(25);
}