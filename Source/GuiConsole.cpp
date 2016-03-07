/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiConsole.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI CONSOLE                                     //
// ==================================================================================== //

GuiConsole::GuiConsole()
{
    m_text.setMultiLine(true);
    m_text.setReadOnly(false);
    m_text.setScrollbarsShown(true);
    m_text.setScrollBarThickness(5);
    m_text.setCaretVisible(false);
    m_text.setPopupMenuEnabled (true);
    m_text.setColour(juce::TextEditor::backgroundColourId, Gui::getColorInv());
    m_text.setColour(juce::TextEditor::outlineColourId, Gui::getColorInv());
    m_text.setColour(juce::TextEditor::shadowColourId,Gui::getColorInv());
    m_text.setColour(juce::TextEditor::textColourId, Gui::getColorTxt());
    m_text.setFont(Gui::getFont());
    m_text.setText(pd::Pd::getConsole());
    m_text.setBounds(0, 0, 300, 370);
    m_text.moveCaretToEnd();
    addAndMakeVisible(&m_text, 1);
    startTimer(25);
}

void GuiConsole::textEditorTextChanged(juce::TextEditor& ed)
{
    pd::Pd::setConsole(ed.getText().toStdString());
}

void GuiConsole::textEditorFocusLost(juce::TextEditor& editor)
{
    ;
}

void GuiConsole::timerCallback()
{
    auto range = m_text.getHighlightedRegion();
    auto caret = m_text.getCaretPosition();
    m_text.setText(pd::Pd::getConsole(), false);
    m_text.setCaretPosition(caret);
    m_text.setHighlightedRegion(range);
}



