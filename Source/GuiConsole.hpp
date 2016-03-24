/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_CONSOLE__
#define __CAMOMILE_GUI_CONSOLE__

#include "InstanceProcessor.hpp"
#include "GuiFlowerButton.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

class GuiConsole : public juce::Component, public juce::Timer,
public juce::Button::Listener, juce::TableListBoxModel
{
public:
    GuiConsole(pd::Console::History& history);
    ~GuiConsole();
    void timerCallback() final;
    void buttonClicked(Button* button) final;
    
    int getNumRows() final;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) final;
    void paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) final;
    bool keyPressed(const KeyPress& key) final;
private:
    typedef pd::Console::History        History;
    typedef pd::Console::Message::Level Level;
    
    History&        m_history;
    Level           m_level;
    size_t          m_size;
    TableListBox    m_table;
    GuiClearButton  m_clear_button;
    GuiCopyButton   m_copy_button;
    GuiLevelButton  m_level_button;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiConsole)
};


#endif
