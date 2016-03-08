/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_CONSOLE__
#define __CAMOMILE_GUI_CONSOLE__

#include "InstanceProcessor.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

class GuiConsole : public juce::Component, public juce::Timer, public juce::TextEditor::Listener
{
public:
    GuiConsole();
    void textEditorTextChanged(juce::TextEditor& editor) final;
    void textEditorFocusLost(juce::TextEditor& editor) final;
    void timerCallback() final;
    
private:
    juce::TextEditor m_text;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiConsole)
};


#endif
