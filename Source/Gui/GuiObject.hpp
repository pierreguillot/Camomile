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

class GuiObject : public virtual Component, protected Timer
{
public:
    GuiObject(GuiPatch& p, pd::Gui& g);
    virtual ~GuiObject() {}
    
    static GuiObject* createTyped(GuiPatch& p, pd::Gui& g);
protected:
    float getValueOriginal() const noexcept;
    void setValueOriginal(float v);
    float getValueScaled() const noexcept;
    void setValueScaled(float v);
    
    void startEdition() noexcept;
    void stopEdition() noexcept;
    void timerCallback() override;
    
    pd::Gui     gui;
    GuiPatch&   patch;
    bool        edited  = false;
    float       value   = 0;
    float       min     = 0;
    float       max     = 1;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiObject)
};

class GuiBang : public GuiObject
{
public:
    GuiBang(GuiPatch& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
};

class GuiToggle : public GuiObject
{
public:
    GuiToggle(GuiPatch& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiSliderHorizontal : public GuiObject
{
public:
    GuiSliderHorizontal(GuiPatch& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
};

class GuiSliderVertical : public GuiObject
{
public:
    GuiSliderVertical(GuiPatch& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
};

class GuiRadioHorizontal : public GuiObject
{
public:
    GuiRadioHorizontal(GuiPatch& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiRadioVertical : public GuiObject
{
public:
    GuiRadioVertical(GuiPatch& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiPanel : public GuiObject
{
public:
    GuiPanel(GuiPatch& p, pd::Gui& g);
    void paint(Graphics& g) final;
};

class GuiComment : public GuiObject
{
public:
    GuiComment(GuiPatch& p, pd::Gui& g);
    void paint(Graphics& g) final;
};

class GuiNumber : public GuiObject, public Label::Listener
{
public:
    GuiNumber(GuiPatch& p, pd::Gui& g);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
    void mouseDoubleClick(const MouseEvent&) final;
    void labelTextChanged(Label* label) final;
    void editorShown(Label*, TextEditor&) final;
    void editorHidden(Label*, TextEditor&) final;
    void timerCallback() final;
private:
    bool                 shift;
    float                last;
    ScopedPointer<Label> label;
};

class GuiAtomNumber : public GuiObject, public Label::Listener
{
public:
    GuiAtomNumber(GuiPatch& p, pd::Gui& g);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
    void mouseDoubleClick(const MouseEvent&) final;
    void labelTextChanged(Label* label) final;
    void editorShown(Label*, TextEditor&) final;
    void editorHidden(Label*, TextEditor&) final;
    void timerCallback() final;
private:
    bool                 shift;
    float                last;
    ScopedPointer<Label> label;
};

