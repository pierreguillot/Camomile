/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PluginEditorInteraction.h"
#include "PluginLookAndFeel.hpp"
#include "PluginEditorObject.hpp"
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

class GraphicalArrayOwner : public Component
{
public:
    GraphicalArrayOwner(CamomileAudioProcessor& processor, std::string const& name) :
    m_array(processor, name)
    {
        setInterceptsMouseClicks(false, true);
        m_array.setBounds(getLocalBounds().reduced(20));
        m_array.setDrawBackground(true);
        m_array.setDrawCurve(true);
        addAndMakeVisible(&m_array);
    }

    void paint(Graphics& g) final
    {
        g.setColour(Colours::black);
        g.setFont(CamoLookAndFeel::getDefaultFont().withHeight(12));
        g.drawText("1", 0, 10, 20, 30, Justification::centred);
        g.drawText("0", 0, getHeight() / 2 - 10, 20, getHeight() / 2 + 10, Justification::centred);
        g.drawText("-1", 0, getHeight() - 30, 20, getHeight() - 10, Justification::centred);
        
        g.drawText("0", 10, getHeight() - 20, 30, getHeight(), Justification::centred);
        g.drawText(String(m_array.getArraySize()), getWidth() - 30, getHeight() - 20, getWidth() - 10, getHeight(), Justification::centred);
    }
    
    void resized() final
    {
        m_array.setBounds(getLocalBounds().reduced(20));
    }
    
private:
    GraphicalArray m_array;
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
            GraphicalArrayOwner* garray = new GraphicalArrayOwner(m_processor, message.second);
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



