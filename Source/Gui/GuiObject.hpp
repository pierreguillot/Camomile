/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../PluginEditorInteraction.h"
#include "../Pd/PdObject.hpp"
#include <atomic>

// ==================================================================================== //
//                                      GUI OBJECT                                      //
// ==================================================================================== //

class GuiObject : public virtual Component
{
public:
    GuiObject(CamomileEditorMouseManager& p, pd::Gui& g);
    virtual ~GuiObject();
    
    static GuiObject* createTyped(CamomileEditorMouseManager& p, pd::Gui& g);
    virtual void update();
protected:
    float getValueOriginal() const noexcept;
    void setValueOriginal(float v);
    float getValueScaled() const noexcept;
    void setValueScaled(float v);
    
    void startEdition() noexcept;
    void stopEdition() noexcept;
    
    pd::Gui     gui;
    CamomileEditorMouseManager&   patch;
    std::atomic<bool> edited;
    float       value   = 0;
    float       min     = 0;
    float       max     = 1;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiObject)
};

class GuiBang : public GuiObject
{
public:
    GuiBang(CamomileEditorMouseManager& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
};

class GuiToggle : public GuiObject
{
public:
    GuiToggle(CamomileEditorMouseManager& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiSliderHorizontal : public GuiObject
{
public:
    GuiSliderHorizontal(CamomileEditorMouseManager& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
};

class GuiSliderVertical : public GuiObject
{
public:
    GuiSliderVertical(CamomileEditorMouseManager& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
};

class GuiRadioHorizontal : public GuiObject
{
public:
    GuiRadioHorizontal(CamomileEditorMouseManager& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiRadioVertical : public GuiObject
{
public:
    GuiRadioVertical(CamomileEditorMouseManager& p, pd::Gui& g) : GuiObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiPanel : public GuiObject
{
public:
    GuiPanel(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& g) final;
};

class GuiComment : public GuiObject
{
public:
    GuiComment(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& g) final;
};

class GuiTextEditor : public GuiObject, public Label::Listener
{
public:
    GuiTextEditor(CamomileEditorMouseManager& p, pd::Gui& g);
    void labelTextChanged(Label* label) override;
    void editorShown(Label*, TextEditor&) final;
    void editorHidden(Label*, TextEditor&) final;
    void update() override;
protected:
    ScopedPointer<Label> label;
};

class GuiNumber : public GuiTextEditor
{
public:
    GuiNumber(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
    void mouseDoubleClick(const MouseEvent&) final;
private:
    bool                 shift;
    float                last;
};

class GuiAtomNumber : public GuiTextEditor
{
public:
    GuiAtomNumber(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
    void mouseDoubleClick(const MouseEvent&) final;
private:
    bool                 shift;
    float                last;
};

class GuiAtomSymbol : public GuiTextEditor
{
public:
    GuiAtomSymbol(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& g) final;
    void mouseDoubleClick(const MouseEvent&) final;
    void labelTextChanged(Label* label) final;
    void update() final;
private:
    std::string          last;
};

