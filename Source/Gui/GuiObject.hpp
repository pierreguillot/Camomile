/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "../Pd/PdObject.hpp"

class GuiPatch
{
public:
    virtual ~GuiPatch() {}
    virtual void startEdition() = 0;
    virtual void performEdition() = 0;
    virtual void stopEdition() = 0;
};

// ==================================================================================== //
//                                      GUI OBJECT                                      //
// ==================================================================================== //

class GuiObject : public virtual Component, private Timer, public Label::Listener
{
public:
    GuiObject(GuiPatch& p, pd::Gui& g);
    ~GuiObject() {}
    
protected:
    float getValueOriginal() const noexcept;
    void setValueOriginal(float v);
    
    float getValueScaled() const noexcept;
    void setValueScaled(float v);
    
    void startEdition() noexcept;
    void stopEdition() noexcept;
    
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
    void mouseDrag(const MouseEvent& event) final;
    void mouseUp(const MouseEvent& event) final;
    
    void mouseDoubleClick(const MouseEvent&) final;
    void labelTextChanged(Label* label) final;
    void editorShown(Label*, TextEditor&) final;
    void editorHidden(Label*, TextEditor&) final;
private:
    void timerCallback() final;
    
    typedef void (*method_paint)(GuiObject& x, Graphics& g);
    typedef void (*method_mouse)(GuiObject& x, const MouseEvent& g);
    
    pd::Gui   gui;
    GuiPatch& patch;
    bool  edited = false;
    float value  = 0;
    float min = 0;
    float max = 1;
    Font  font;
    // For number
    bool  shift;
    ScopedPointer<Label> label;
    
    method_paint metpaint = nullptr;
    method_mouse metmousedown = nullptr;
    method_mouse metmousedrag = nullptr;
    method_mouse metmouseup = nullptr;
    
    static void paintToggle(GuiObject& x, Graphics& g);
    static void mouseDownToggle(GuiObject& x, const MouseEvent& g);
    
    static void mouseUpSlider(GuiObject& x, const MouseEvent& e);
    
    static void paintSliderHorizontal(GuiObject& x, Graphics& g);
    static void mouseDownSliderHorizontal(GuiObject& x, const MouseEvent& e);
    static void mouseDragSliderHorizontal(GuiObject& x, const MouseEvent& e);
    
    static void paintSliderVertical(GuiObject& x, Graphics& g);
    static void mouseDownSliderVertical(GuiObject& x, const MouseEvent& e);
    static void mouseDragSliderVertical(GuiObject& x, const MouseEvent& e);
    
    static void paintRadioHorizontal(GuiObject& x, Graphics& g);
    static void mouseDownRadioHorizontal(GuiObject& x, const MouseEvent& e);
    
    static void paintRadioVertical(GuiObject& x, Graphics& g);
    static void mouseDownRadioVertical(GuiObject& x, const MouseEvent& e);
    
    static void paintBang(GuiObject& x, Graphics& g);
    static void mouseDownBang(GuiObject& x, const MouseEvent& e);
    static void mouseUpBang(GuiObject& x, const MouseEvent& e);
    
    static void paintPanel(GuiObject& x, Graphics& g);
    
    static void paintComment(GuiObject& x, Graphics& g);
    
    static void paintNumber(GuiObject& x, Graphics& g);
    static void mouseDownNumber(GuiObject& x, const MouseEvent& g);
    static void mouseDragNumber(GuiObject& x, const MouseEvent& g);
    static void mouseUpNumber(GuiObject& x, const MouseEvent& g);
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiObject)
};

