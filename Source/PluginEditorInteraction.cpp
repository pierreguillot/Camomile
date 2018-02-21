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
        try {
            m_processor.readArray(m_name, m_vector);
        }
        catch(...)
        {
            m_error = true;
        }
        startTimer(100);
        setInterceptsMouseClicks(true, false);
    }
    
    static inline float toHeight(const float value, const float h, const float s)
    {
        return (std::min(std::max(-value, -1.f), 1.f) + 1.f) * h * 0.5f + s;
    }
    
    void paint(Graphics& g) final
    {
        g.setColour(Colours::black);
        if(m_error)
        {
            g.setFont(CamoLookAndFeel::getDefaultFont());
            g.drawText("array " + m_name + " invalid or empty",
                       0, 0, getWidth(), getHeight(), juce::Justification::centred);
        }
        else
        {
            if(!m_vector.empty())
            {
                const float h = static_cast<float>(getHeight() - offset);
                const float w = static_cast<float>(getWidth() - offset) / static_cast<float>(m_vector.size() - 1);
                Path p;
                p.startNewSubPath(std::ceil(shift), toHeight(m_vector[0], h, shift));
                for(size_t i = 1; i < m_vector.size(); ++i)
                {
                    p.lineTo(std::ceil(shift) + static_cast<float>(i) * w, toHeight(m_vector[i], h, shift));
                }
                g.strokePath(p, PathStrokeType(border));
            }
            g.setFont(CamoLookAndFeel::getDefaultFont().withHeight(fheight));
            g.drawText("1", 0, shift - fheight * 0.5f, shift, fheight, juce::Justification::centred);
            g.drawText("-1", 0, getHeight() - shift - fheight * 0.5f, shift, fheight, juce::Justification::centred);
            g.drawText("0", 0, getHeight() - shift, shift * 2.f, shift, juce::Justification::centred);
            g.drawText(String(m_vector.size()), getWidth() - shift * 2.f, getHeight() - shift, shift * 2.f, shift, juce::Justification::centred);
        }
        g.drawRect(shift - 0.5f, shift - 0.5f, getWidth() - offset + 0.5f, getHeight() - offset + 1.f, float(border));
    }
    
    void mouseDown(const MouseEvent& event) final
    {
        auto const bounds = getBounds().reduced(shift - 0.5f, shift - 0.5f);
        if(bounds.contains(event.position.translated(-shift + 0.5f, -shift + 0.5f).toInt()))
        {
            m_edited = true;
            mouseDrag(event);
        }
    }
    
    void mouseDrag(const MouseEvent& event) final
    {
        if(m_edited)
        {
            const float s = static_cast<float>(m_vector.size() - 1);
            const float w = static_cast<float>(getWidth() - offset);
            const float h = static_cast<float>(getHeight() - offset);
            const float x = static_cast<float>(event.x - shift);
            const float y = static_cast<float>(event.y - shift);
            
            const int index = static_cast<int>(std::max(std::min(x / w, 1.f), 0.f) * s);
            m_vector[index] = (1.f - std::max(std::min(y / h, 1.f), 0.f)) * 2.f - 1.f;
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
            try {
                m_processor.readArray(m_name, m_temp);
            }
            catch(...)
            {
                m_error = true;
            }
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
    
    static const int border  = 1;
    static const int offset  = 40;
    static const int shift   = 20;
    static const int fheight = 12;
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



