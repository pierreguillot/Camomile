/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_PATCHER__
#define __CAMOMILE_GUI_PATCHER__

#include "GuiParameter.hpp"
#include "GuiLabel.hpp"

// ==================================================================================== //
//                                      GUI PATCHER                                      //
// ==================================================================================== //

class GuiPatcher : public Component
{
public:
    GuiPatcher();
    ~GuiPatcher();
    
    void setPatch(InstanceProcessor& processor, pd::Patch const& patch);
private:
    OwnedArray<GuiParameter>    m_parameters;
    OwnedArray<GuiLabel>        m_labels;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiPatcher)
};


#endif
