/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include "PluginProcessor.h"
#include <set>
#include <bitset>

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      INTERACTION                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      KEY MANAGER                                         //
//////////////////////////////////////////////////////////////////////////////////////////////

//! @brief The class manages the key events
//! @details The class is used to wrap and send the key events from JUCE to Pd via the objects
//! key, keyup and keyname.
//! @see CamomileAudioPluginEditor
//! @todo I didn't check all the keyname yet because it's OS dependant and pretty boring to do.
class CamomileEditorKeyManager
{
public:
    CamomileEditorKeyManager(CamomileAudioProcessor& processor);
    ~CamomileEditorKeyManager();
    
    bool keyPressed(const KeyPress& key);
    bool keyStateChanged(bool isKeyDown);
    bool keyModifiersChanged(const ModifierKeys& modifiers);
private:
    typedef std::pair<int, juce_wchar> ikey;
    CamomileAudioProcessor& m_processor;
    std::set<ikey>          m_keys;
    std::bitset<8>          m_modifiers;
    
    bool sendKey(const bool down, const int code, const juce_wchar c);
    
    static const std::string string_key;
    static const std::string string_keyup;
    static const std::string string_keyname;
    static const std::string string_list;
    static const std::string string_float;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditorKeyManager)
};

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      MOUSE MANAGER                                       //
//////////////////////////////////////////////////////////////////////////////////////////////

//! @brief The class manages the mouse events
//! @details The class is used send notifications that the mouse is pressed or released to Pd.
//! @see CamomileAudioPluginEditor
//! &todo Later see if the class can be used for other mouse events
class CamomileEditorMouseManager
{
public:
    CamomileEditorMouseManager(CamomileAudioProcessor& processor);
    ~CamomileEditorMouseManager();
    
    void startEdition();
    void stopEdition();
private:
    CamomileAudioProcessor& m_processor;
    
    static const std::string string_gui;
    static const std::string string_mouse;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditorMouseManager)
};


//////////////////////////////////////////////////////////////////////////////////////////////
//                                      PANEL MANAGER                                       //
//////////////////////////////////////////////////////////////////////////////////////////////

//! @brief The class manages the panel
//! @details The class is used to display open and receive panel and send the results to Pd
//! via the symbols openpanel and savepanel.
//! @see CamomileAudioPluginEditor
//! @todo Later this class could also manage other messages from Pd.
class CamomileEditorPanelManager
{
public:
    CamomileEditorPanelManager(CamomileAudioProcessor& processor);
    ~CamomileEditorPanelManager();
    
    bool processMessages();
private:
    CamomileAudioProcessor& m_processor;
    
    static const std::string string_openpanel;
    static const std::string string_savepanel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditorPanelManager)
};

