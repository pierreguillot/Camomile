/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_NUMBOX__
#define __CAMOMILE_GUI_NUMBOX__

#include "GuiParameter.hpp"

// ==================================================================================== //
//                                      GUI NUMBOX                                      //
// ==================================================================================== //

class GuiNumbox : public GuiParameter, public Label::Listener
{
public:
    GuiNumbox(InstanceProcessor& processor, pd::Gui const& gui);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
    void mouseDrag(const MouseEvent& event) final;
    void mouseUp(const MouseEvent& event) final;
    void mouseDoubleClick(const MouseEvent&) final;
    
    void labelTextChanged(Label* label);
    void editorShown(Label*, TextEditor&) final;
    void editorHidden(Label*, TextEditor&) final;
private:
    bool  m_shift;
    float m_value;
    Label m_label;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiNumbox)
};


#endif
