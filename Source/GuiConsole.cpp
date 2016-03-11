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
    
GuiConsole::GuiConsole() : m_button("Clear")
{
    m_text.setMultiLine(true);
    m_text.setReadOnly(true);
    m_text.setScrollbarsShown(true);
    m_text.setScrollBarThickness(5);
    m_text.setCaretVisible(false);
    m_text.setPopupMenuEnabled (true);
    m_text.setColour(juce::TextEditor::backgroundColourId, Gui::getColorInv());
    m_text.setColour(juce::TextEditor::outlineColourId, Gui::getColorInv());
    m_text.setColour(juce::TextEditor::shadowColourId,Gui::getColorInv());
    m_text.setColour(juce::TextEditor::textColourId, Gui::getColorTxt());
    m_text.setFont(Gui::getFont());
    m_text.setBounds(0, 0, 300, 350);
    m_text.moveCaretToEnd();
    std::vector<pd::Post> messages(pd::Pd::getConsole());
    for(size_t i = 0; i < messages.size(); ++i)
    {
        m_text.moveCaretToEnd();
        m_text.setColour(juce::TextEditor::textColourId, Gui::getColorTxt());
        m_text.insertTextAtCaret(messages[i].message);
    }
    addAndMakeVisible(&m_text, 1);
    
    m_button.setBounds(0, 350, 40, 16);
    m_button.setRadioGroupId(5);
    m_button.addListener(this);
    m_button.setClickingTogglesState(false);
    m_button.setColour(juce::TextButton::buttonColourId, Gui::getColorBg());
    m_button.setColour(juce::TextButton::buttonOnColourId, Gui::getColorBg());
    m_button.setColour(juce::TextButton::textColourOffId, Gui::getColorTxt());
    m_button.setColour(juce::TextButton::textColourOnId,Gui::getColorTxt().interpolatedWith(Gui::getColorBg(), 0.5f));
    m_button.addListener(this);
    addAndMakeVisible(&m_button);
    
    setOpaque(true);
    startTimer(100);
}

void GuiConsole::paint(Graphics& g)
{
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawLine(0, 350, getWidth(), 350, Gui::getBorderSize());
}

GuiConsole::~GuiConsole()
{
    stopTimer();
}

void GuiConsole::buttonClicked(Button* button)
{
     pd::Pd::clearConsole();
}

void GuiConsole::timerCallback()
{
    if(pd::Pd::hasConsoleChanged())
    {
        m_text.clear();
        std::vector<pd::Post> messages(pd::Pd::getConsole());
        for(size_t i = 0; i < messages.size(); ++i)
        {
            m_text.moveCaretToEnd();
            m_text.setColour(juce::TextEditor::textColourId, Gui::getColorTxt());
            m_text.insertTextAtCaret(messages[i].message);
        }
    }
}



