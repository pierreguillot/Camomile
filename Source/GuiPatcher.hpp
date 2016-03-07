/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_PATCHER__
#define __CAMOMILE_GUI_PATCHER__

#include "GuiRadio.hpp"
#include "GuiSlider.hpp"
#include "GuiToggle.hpp"
#include "GuiNumbox.hpp"
#include "GuiLabel.hpp"

// ==================================================================================== //
//                                      GUI PATCHER                                      //
// ==================================================================================== //

class GuiPatcher : public Component
{
public:
    GuiPatcher(InstanceProcessor& processor);
    ~GuiPatcher();
    
    void setPatch(pd::Patch const& patch);
private:
    InstanceProcessor&          m_processor;
    OwnedArray<GuiParameter>    m_parameters;
    OwnedArray<GuiLabel>        m_labels;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiPatcher)
};


#endif
