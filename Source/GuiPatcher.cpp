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

void GuiPatcher::setPatch(InstanceProcessor& processor, pd::Patch const& patch)
{
    m_comment.clear();
    m_parameters.clear();
    m_labels.clear();
    if(patch.isValid())
    {
        std::array<int, 2> size(patch.getSize());
        setSize(std::max(size[0], 120), std::max(size[1], 20));
        std::vector<pd::Gui> guis(patch.getGuis());
        for(size_t i = 0; i < guis.size(); ++i)
        {
            if(guis[i].getType() == pd::Gui::Type::Number)
            {
                m_parameters.add(new GuiNumbox(processor, guis[i]));
                addAndMakeVisible(m_parameters.getLast());
            }
            else if(guis[i].getType() == pd::Gui::Type::HorizontalRadio ||
                    guis[i].getType() == pd::Gui::Type::VerticalRadio)
            {
                m_parameters.add(new GuiRadio(processor, guis[i]));
                addAndMakeVisible(m_parameters.getLast());
            }
            else if(guis[i].getType() == pd::Gui::Type::HorizontalSlider ||
                    guis[i].getType() == pd::Gui::Type::VerticalSlider)
            {
                m_parameters.add(new GuiSlider(processor, guis[i]));
                addAndMakeVisible(m_parameters.getLast());
            }
            else if(guis[i].getType() == pd::Gui::Type::Toggle)
            {
                m_parameters.add(new GuiToggle(processor, guis[i]));
                addAndMakeVisible(m_parameters.getLast());
            }
            
            if(guis[i].isParameter())
            {
                m_labels.add(new GuiLabel(processor, guis[i]));
                addAndMakeVisible(m_labels.getLast());
            }
        }
        
        std::vector<pd::Comment> cmts(patch.getComments());
        for(size_t i = 0; i < cmts.size(); ++i)
        {
            m_comment.add(new GuiComment(cmts[i]));
            addAndMakeVisible(m_comment.getLast());
        }
        repaint();
    }
}