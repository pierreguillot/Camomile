/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PluginEditorInteraction.h"
#include "PluginLookAndFeel.hpp"
#include <locale> // std::locale;
#include <atomic>
#include <algorithm>

template <typename T> T clip(const T& n, const T& lower, const T& upper) {
    return std::max(lower, std::min(n, upper));
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      INTERACTION                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

CamomileEditorInteractionManager::CamomileEditorInteractionManager(CamomileAudioProcessor& processor) :
CamomileEditorKeyManager(processor), CamomileEditorMouseManager(processor), CamomileEditorMessageManager(processor)
{
    
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      KEY MANAGER                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

const std::string CamomileEditorKeyManager::string_key       = std::string("#key");
const std::string CamomileEditorKeyManager::string_keyup     = std::string("#keyup");
const std::string CamomileEditorKeyManager::string_keyname   = std::string("#keyname");
const std::string CamomileEditorKeyManager::string_list      = std::string("list");
const std::string CamomileEditorKeyManager::string_float     = std::string("float");

bool CamomileEditorKeyManager::sendKey(const bool down, const int code, const juce_wchar c)
{
    std::string stringname;
    if(code == KeyPress::spaceKey) { stringname = "Space"; }
    else if(code == KeyPress::escapeKey) { stringname = "Escape"; }
    else if(code == KeyPress::returnKey) { stringname = "Return"; }
    else if(code == KeyPress::tabKey) { stringname = "Tab"; }
    else if(code == KeyPress::deleteKey) { stringname = "Delete"; }
    else if(code == KeyPress::backspaceKey) { stringname = "BackSpace"; }
    else if(code == KeyPress::insertKey) { stringname = "Insert"; }
    else if(code == KeyPress::upKey) { stringname = "Up"; }
    else if(code == KeyPress::downKey) { stringname = "Down"; }
    else if(code == KeyPress::leftKey) { stringname = "Left"; }
    else if(code == KeyPress::rightKey) { stringname = "Right"; }
    else if(code == KeyPress::pageUpKey) { stringname = "PageUp"; }
    else if(code == KeyPress::pageDownKey) { stringname = "PageDown"; }
    else if(code == KeyPress::homeKey) { stringname = "Home"; }
    else if(code == KeyPress::endKey) { stringname = "End"; }
    else {
        std::locale const loc;
        stringname = std::string(1, std::use_facet<std::ctype<juce_wchar>>(loc).narrow(c, '?' ));
    }
    m_processor.enqueueMessages(down ? string_key : string_keyup, string_float, {static_cast<float>(code)});
    m_processor.enqueueMessages(string_keyname, string_list, {static_cast<float>(down), stringname});
    if(down){ m_keys.insert(ikey{code, c}); }
    else { m_keys.erase(ikey{code, c}); }
    return true;
}

bool CamomileEditorKeyManager::keyPressed(const KeyPress& key)
{
    if(CamomileEnvironment::wantsKey() && key.isCurrentlyDown()) {
        return sendKey(true, key.getKeyCode(), key.getTextCharacter()); }
    return false;
}

bool CamomileEditorKeyManager::keyStateChanged(bool isKeyDown)
{
    if(CamomileEnvironment::wantsKey() && !isKeyDown) {
        for(auto mkey : m_keys)  {
            if(!KeyPress::isKeyCurrentlyDown(mkey.first))
                return sendKey(false, mkey.first, mkey.second);
        }
    }
    return false;
}

bool CamomileEditorKeyManager::keyModifiersChanged(const ModifierKeys& modifiers)
{
    if(CamomileEnvironment::wantsKey())
    {
        bool down;
        std::string stringname;
        const size_t mod = static_cast<size_t>(modifiers.getRawFlags());
        if(mod & ModifierKeys::shiftModifier && !m_modifiers.test(ModifierKeys::shiftModifier)) {
            m_modifiers.set(static_cast<size_t>(ModifierKeys::shiftModifier));
            stringname = "Shift_L"; down = true; }
        else if(mod & ModifierKeys::ctrlModifier && !m_modifiers.test(ModifierKeys::ctrlModifier)) {
            m_modifiers.set(static_cast<size_t>(ModifierKeys::ctrlModifier));
            stringname = "Control_L"; down = true; }
        else if(mod & ModifierKeys::altModifier && !m_modifiers.test(ModifierKeys::altModifier)) {
            m_modifiers.set(static_cast<size_t>(ModifierKeys::altModifier));
            stringname = "Alt_L"; down = true; }
        else if(mod & ModifierKeys::commandModifier && !m_modifiers.test(ModifierKeys::commandModifier)) {
            m_modifiers.set(static_cast<size_t>(ModifierKeys::commandModifier));
            stringname = "Meta_L"; down = true; }
        else if(!(mod & ModifierKeys::shiftModifier) && m_modifiers.test(ModifierKeys::shiftModifier)) {
            m_modifiers.reset(static_cast<size_t>(ModifierKeys::shiftModifier));
            stringname = "Shift_L"; down = false; }
        else if(!(mod & ModifierKeys::ctrlModifier) && m_modifiers.test(ModifierKeys::ctrlModifier)) {
            m_modifiers.reset(static_cast<size_t>(ModifierKeys::ctrlModifier));
            stringname = "Control_L"; down = false; }
        else if(!(mod & ModifierKeys::altModifier) && m_modifiers.test(ModifierKeys::altModifier)) {
            m_modifiers.reset(static_cast<size_t>(ModifierKeys::altModifier));
            stringname = "Alt_L"; down = false; }
        else if(!(mod & ModifierKeys::commandModifier) && m_modifiers.test(ModifierKeys::commandModifier)) {
            m_modifiers.reset(static_cast<size_t>(ModifierKeys::commandModifier));
            stringname = "Meta_L"; down = false; }
        else
            return false;
        
        m_processor.enqueueMessages(down ? string_key : string_keyup, string_float, {static_cast<float>(0)});
        m_processor.enqueueMessages(string_keyname, string_list, {static_cast<float>(down), stringname});
        return true;
    }
    return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      MOUSE MANAGER                                       //
//////////////////////////////////////////////////////////////////////////////////////////////

const std::string CamomileEditorMouseManager::string_gui = std::string("gui");
const std::string CamomileEditorMouseManager::string_mouse = std::string("mouse");

void CamomileEditorMouseManager::startEdition() {
    m_processor.enqueueMessages(string_gui, string_mouse, {1.f});
}

void CamomileEditorMouseManager::stopEdition() {
    m_processor.enqueueMessages(string_gui, string_mouse, {0.f});
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      PANEL MANAGER                                       //
//////////////////////////////////////////////////////////////////////////////////////////////


class CamomileEditorMessageWindow : public DocumentWindow
{
public:
    CamomileEditorMessageWindow() : DocumentWindow(String(""), Colours::lightgrey, DocumentWindow::closeButton, false)
    {
        setAlwaysOnTop(true);
        setUsingNativeTitleBar(true);
        setBounds(50, 50, 300, 120);
        setResizable(true, true);
        setDropShadowEnabled(true);
        setVisible(true);
        setWantsKeyboardFocus(true);
    }
    
    void closeButtonPressed() { removeFromDesktop(); }
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditorMessageWindow)
};

class GraphicalArray : public Component, protected Timer
{
public:
    GraphicalArray(CamomileAudioProcessor& processor, std::string const& name) :
    m_processor(processor), m_name(name), m_edited(false) {
        m_vector.reserve(8192);
        m_temp.reserve(8192);
        try { m_processor.readArray(m_name, m_vector); }
        catch(...) { m_error = true; }
        startTimer(100);
        setInterceptsMouseClicks(true, false);
    }
    
    inline void paintArray(Graphics& g, const float w, const float h)
    {
        if(!m_vector.empty())
        {
            Path p;
            const float offset = static_cast<float>(s_shift * 2);
            const float dh = (h - offset) * 0.5f;
            const float dw = (w - offset) / static_cast<float>(m_vector.size() - 1);
            p.startNewSubPath(s_shift, s_shift + (clip(-m_vector[0], -1.f, 1.f) + 1.f) * dh);
            for(size_t i = 1; i < m_vector.size(); ++i)
            {
                const float x = s_shift + static_cast<float>(i) * dw;
                const float y = s_shift + (clip(-m_vector[i], -1.f, 1.f) + 1.f) * dh;
                p.lineTo(x, y);
            }
            g.setColour(Colours::black);
            g.strokePath(p, PathStrokeType(1));
        }
    }
    
    inline void paintBackground(Graphics& g, const float w, const float h)
    {
        const float offset = static_cast<float>(s_shift * 2);
        const float hminus = h - s_shift;
        const float font2 = s_font_height * 0.5f;
        const float shift2 = s_shift * 2.f;
        
        g.setColour(Colours::darkgrey);
        g.drawLine(s_shift, h * 0.5f, w - s_shift, h * 0.5f, 1);
        g.drawLine(s_shift, h * 0.5f - (h - offset) * 0.25f, w - s_shift, h * 0.5f - (h - offset) * 0.25f, 1);
        g.drawLine(s_shift, h * 0.5f + (h - offset) * 0.25f, w - s_shift, h * 0.5f + (h - offset) * 0.25f, 1);
        
        g.drawLine(w * 0.5f, s_shift, w * 0.5f, h - s_shift, 1);
        g.drawLine(w * 0.5f - (w - offset) * 0.25f, s_shift, w * 0.5f - (w - offset) * 0.25f, h - s_shift, 1);
        g.drawLine(w * 0.5f + (w - offset) * 0.25f, s_shift, w * 0.5f + (w - offset) * 0.25f, h - s_shift, 1);
        
        g.setColour(Colours::black);
        g.setFont(CamoLookAndFeel::getDefaultFont().withHeight(s_font_height));
        g.drawText("1", 0, s_shift - font2, s_shift, s_font_height, Justification::centred);
        g.drawText("0", 0, h * 0.5f - font2, s_shift, s_font_height, Justification::centred);
        g.drawText("-1", 0, hminus - font2, s_shift, s_font_height, Justification::centred);
        
        g.drawText("0", 0, hminus, shift2, s_shift, Justification::centred);
        g.drawText(String(m_vector.size()), w - shift2, hminus, shift2, s_shift, Justification::centred);
    }
    
    void paint(Graphics& g) final
    {
        const float h = static_cast<float>(getHeight());
        const float w = static_cast<float>(getWidth());
        Rectangle<int> bd = getBounds().reduced(s_shift - 0.5f, s_shift - 0.5f);
        g.setColour(Colours::white.withAlpha(0.5f));
        g.fillRect(bd);
        if(m_error)
        {
            g.setFont(CamoLookAndFeel::getDefaultFont());
            g.drawText("array " + m_name + " is invalid", 0, 0, w, h, juce::Justification::centred);
        }
        else
        {
            paintBackground(g, w, h);
            paintArray(g, w, h);
        }
        g.setColour(Colours::black);
        g.drawRect(bd, 1.5f);
    }
    
    void mouseDown(const MouseEvent& event) final
    {
        auto const bounds = getBounds().reduced(s_shift - 0.5f, s_shift - 0.5f);
        if(bounds.contains(event.position.translated(-s_shift, -s_shift).toInt()))
        {
            m_edited = true;
            mouseDrag(event);
        }
    }
    
    void mouseDrag(const MouseEvent& event) final
    {
        if(m_edited)
        {
            const float o = static_cast<float>(s_shift * 2);
            const float s = static_cast<float>(m_vector.size() - 1);
            const float w = static_cast<float>(getWidth()) - o;
            const float h = static_cast<float>(getHeight()) - o;
            const float x = static_cast<float>(event.x - s_shift);
            const float y = static_cast<float>(event.y - s_shift);
            
            const size_t index = static_cast<size_t>(std::round(clip(x / w, 0.f, 1.f) * s));
            m_vector[index] = (1.f - clip(y / h, 0.f, 1.f)) * 2.f - 1.f;
            try { m_processor.writeArraySample(m_name, index, m_vector[index]); }
            catch(...) { m_error = true; }
            m_processor.enqueueMessages(string_array, m_name, {});
            repaint();
        }
    }
    
    void mouseUp(const MouseEvent& event) final
    {
        m_edited = false;
    }
    
    void timerCallback() final
    {
        if(!m_edited)
        {
            try { m_processor.readArray(m_name, m_temp); }
            catch(...) { m_error = true; }
            if(m_temp != m_vector)
            {
                m_vector.swap(m_temp);
                repaint();
            }
        }
    }
    
private:
    CamomileAudioProcessor& m_processor;
    std::string const       m_name;
    std::vector<float>      m_vector;
    std::vector<float>      m_temp;
    std::atomic<bool>       m_edited;
    bool                    m_error = false;
    
    static const int s_shift       = 20;
    static const int s_font_height = 12;
    const std::string string_array = std::string("array");
};

//////////////////////////////////////////////////////////////////////////////////////////////

const std::string CamomileEditorMessageManager::string_openpanel = std::string("openpanel");
const std::string CamomileEditorMessageManager::string_savepanel = std::string("savepanel");
const std::string CamomileEditorMessageManager::string_array     = std::string("array");

CamomileEditorMessageManager::CamomileEditorMessageManager(CamomileAudioProcessor& processor) : m_processor(processor), m_window(new CamomileEditorMessageWindow())
{}

bool CamomileEditorMessageManager::processMessages()
{
    CamomileAudioProcessor::MessageGui message;
    while(m_processor.dequeueGui(message))
    {
        if(message.first == string_openpanel)
        {
            FileChooser fc("Open...", File(message.second));
            if(fc.browseForFileToOpen())
            {
                File const f(fc.getResult());
                m_processor.enqueueMessages(string_openpanel, f.getFullPathName().toStdString(), {});
            }
        }
        else if(message.first == string_savepanel)
        {
            FileChooser fc("Open...", File(message.second));
            if(fc.browseForFileToSave(true))
            {
                File const f(fc.getResult());
                m_processor.enqueueMessages(string_savepanel, f.getFullPathName().toStdString(), {});
            }
        }
        else if(message.first == string_array)
        {
            GraphicalArray* garray = new GraphicalArray(m_processor, message.second);
            if(garray)
            {
                String const trackname = m_processor.getTrackProperties().name;
                String const name = CamomileEnvironment::getPluginName() + " - " + message.second
                + (trackname.isEmpty() ? "" : trackname);
                m_window->clearContentComponent();
                m_window->setName(name);
                m_window->setContentOwned(garray, false);
                if(!m_window->isVisible() || !m_window->isShowing())
                {
                    m_window->addToDesktop();
                }
                m_window->toFront(true);
                m_window->grabKeyboardFocus();
            }
        }
    }
    return true;
}



