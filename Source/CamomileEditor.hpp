/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INSTANCE_EDITOR__
#define __CAMOMILE_INSTANCE_EDITOR__

#include "Gui/Gui.hpp"
#include "InstanceProcessor.hpp"

// ==================================================================================== //
//                                  CAMOMILE EDITOR                                     //
// ==================================================================================== //

class CamomileEditor : public AudioProcessorEditor, public camo::camomile::listener, public Button::Listener
{
public:
    CamomileEditor(InstanceProcessor&);
    ~CamomileEditor();
    void paint(Graphics&) final;
    void buttonClicked(Button* button) final;
    void patch_changed() final;
private:
    InstanceProcessor&  m_processor;
    GuiPatcher          m_patcher;
    GuiFlowerButton     m_button;
    GuiWindow           m_window;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditor)
};

#endif
