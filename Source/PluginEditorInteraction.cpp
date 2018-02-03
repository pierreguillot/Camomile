/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditorInteraction.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      KEY MANAGER                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

const std::string CamomileEditorKeyManager::string_key       = std::string("#key");
const std::string CamomileEditorKeyManager::string_keyup     = std::string("#keyup");
const std::string CamomileEditorKeyManager::string_keyname   = std::string("#keyname");
const std::string CamomileEditorKeyManager::string_list      = std::string("list");
const std::string CamomileEditorKeyManager::string_float     = std::string("float");

CamomileEditorKeyManager::CamomileEditorKeyManager(CamomileAudioProcessor& processor) : m_processor(processor)
{
    
}

CamomileEditorKeyManager::~CamomileEditorKeyManager()
{
    ;
}

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

CamomileEditorMouseManager::CamomileEditorMouseManager(CamomileAudioProcessor& processor) : m_processor(processor) {}

CamomileEditorMouseManager::~CamomileEditorMouseManager() {}

void CamomileEditorMouseManager::startEdition() {
    m_processor.enqueueMessages(string_gui, string_mouse, {1.f});
}

void CamomileEditorMouseManager::stopEdition() {
    m_processor.enqueueMessages(string_gui, string_mouse, {0.f});
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      PANEL MANAGER                                       //
//////////////////////////////////////////////////////////////////////////////////////////////

const std::string CamomileEditorPanelManager::string_openpanel = std::string("openpanel");
const std::string CamomileEditorPanelManager::string_savepanel = std::string("savepanel");

CamomileEditorPanelManager::CamomileEditorPanelManager(CamomileAudioProcessor& processor) : m_processor(processor)
{
    
}

CamomileEditorPanelManager::~CamomileEditorPanelManager()
{
    ;
}

bool CamomileEditorPanelManager::processMessages()
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
    }
    return true;
}



