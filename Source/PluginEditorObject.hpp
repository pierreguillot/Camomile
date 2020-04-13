/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "PluginEditorInteraction.h"
#include "Pd/PdInstance.hpp"
#include <atomic>

// ==================================================================================== //
//                                  GRAPHICAL ARRAY                                     //
// ==================================================================================== //

class GraphicalArray : public Component, private Timer
{
public:
    GraphicalArray(CamomileAudioProcessor& processor, pd::Array& graph);
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& event) final;
    void mouseDrag(const MouseEvent& event) final;
    void mouseUp(const MouseEvent& event) final;
    size_t getArraySize() const noexcept;
private:
    void timerCallback() final;
    template <typename T> T clip(const T& n, const T& lower, const T& upper) {
        return std::max(std::min(n, upper), lower);
    }
    
    CamomileAudioProcessor& m_processor;
    pd::Array               m_array;
    std::vector<float>      m_vector;
    std::vector<float>      m_temp;
    std::atomic<bool>       m_edited;
    bool                    m_error = false;
    const std::string string_array = std::string("array");
};

// ==================================================================================== //
//                                      GUI OBJECT                                      //
// ==================================================================================== //

class PluginEditorObject : public virtual Component
{
public:
    PluginEditorObject(CamomileEditorMouseManager& p, pd::Gui& g);
    virtual ~PluginEditorObject();
    
    static PluginEditorObject* createTyped(CamomileEditorMouseManager& p, pd::Gui& g);
    virtual void update();
    Label* getLabel();
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PluginEditorObject)
};

class GuiBang : public PluginEditorObject
{
public:
    GuiBang(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
};

class GuiToggle : public PluginEditorObject
{
public:
    GuiToggle(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiSliderHorizontal : public PluginEditorObject
{
public:
    GuiSliderHorizontal(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
private:
    float m_temp = 0.f;
};

class GuiSliderVertical : public PluginEditorObject
{
public:
    GuiSliderVertical(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
    void mouseDrag(const MouseEvent& e) final;
    void mouseUp(const MouseEvent& e) final;
private:
    float m_temp = 0.f;
};

class GuiRadioHorizontal : public PluginEditorObject
{
public:
    GuiRadioHorizontal(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiRadioVertical : public PluginEditorObject
{
public:
    GuiRadioVertical(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g) {}
    void paint(Graphics& g) final;
    void mouseDown(const MouseEvent& e) final;
};

class GuiPanel : public PluginEditorObject
{
public:
    GuiPanel(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& g) final;
};

class GuiComment : public PluginEditorObject
{
public:
    GuiComment(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& g) final;
};

class GuiTextEditor : public PluginEditorObject, public Label::Listener
{
public:
    GuiTextEditor(CamomileEditorMouseManager& p, pd::Gui& g);
    void labelTextChanged(Label* label) override;
    void editorShown(Label*, TextEditor&) final;
    void editorHidden(Label*, TextEditor&) final;
    void update() override;
protected:
    juce::Label label;
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
    bool    shift = false;
    float   last  = 0.f;
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
    bool    shift = false;
    float   last  = 0.f;
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
    std::string last;
};

class GuiArray : public PluginEditorObject
{
public:
    GuiArray(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& ) final {}
    void resized() final;
    void update() final {}
private:
    pd::Array      m_graph;
    GraphicalArray m_array;
};


class GuiGraphOnParent : public PluginEditorObject
{
public:
    GuiGraphOnParent(CamomileEditorMouseManager& p, pd::Gui& g);
    void paint(Graphics& ) final;
    void resized() final;
    void update() final;
private:
    OwnedArray<PluginEditorObject>  m_objects;
    OwnedArray<Component>           m_labels;
};




