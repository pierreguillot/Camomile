/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INSTANCE_EDITOR__
#define __CAMOMILE_INSTANCE_EDITOR__

#include "Gui.hpp"

// ==================================================================================== //
//                                  INSTANCE EDITOR                                     //
// ==================================================================================== //

class InstanceEditor : public AudioProcessorEditor, public InstanceProcessor::Listener, public Button::Listener
{
public:
    InstanceEditor(InstanceProcessor&);
    ~InstanceEditor();
    void paint(Graphics&) final;
    void buttonClicked(Button* button) final;
    void patchChanged() final;
private:
    InstanceProcessor&  m_processor;
    GuiFlowerButton     m_button;
    GuiPatcher          m_patcher;
    Toolbar             m_menu;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstanceEditor)
};



#endif
