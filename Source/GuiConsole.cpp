/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiConsole.hpp"
#include "GuiFlowerButton.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI CONSOLE                                     //
// ==================================================================================== //
    
GuiConsole::GuiConsole(pd::Console::History& history) : m_history(history)
{
    m_level = Level::Post;
    m_size  = 0;
    setWantsKeyboardFocus(true);
    TableHeaderComponent* header = new TableHeaderComponent();
    header->addColumn(String("ID"), 1, 300, 300, 300, TableHeaderComponent::notResizableOrSortable, -1);
    header->setStretchToFitActive(false);
    header->setColumnVisible(1, true);
    
    m_table.setBounds(0, 0, 300, 350);
    m_table.setModel(this);
    m_table.setOutlineThickness(0);
    m_table.setWantsKeyboardFocus(true);
    m_table.setMultipleSelectionEnabled(true);
    m_table.setMouseMoveSelectsRows(false);
    m_table.setHeaderHeight(0);
    m_table.setRowHeight(Gui::getFont().getHeight() + 2);
    m_table.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentWhite);
    m_table.getViewport()->setScrollBarsShown(true, false, true, false);
    m_table.getViewport()->setScrollBarThickness(1);
    m_table.setModel(this);
    m_table.setHeader(header);
    addAndMakeVisible(m_table);
    
    m_clear_button.addListener(this);
    addAndMakeVisible(&m_clear_button);
    m_copy_button.addListener(this);
    addAndMakeVisible(&m_copy_button);
    m_level_button.addListener(this);
    addAndMakeVisible(&m_level_button);
    startTimer(100);
}

GuiConsole::~GuiConsole()
{
    stopTimer();
}

void GuiConsole::buttonClicked(Button* button)
{
    if(button == &m_clear_button)
    {
        m_history.clear();
    }
    else if(button == &m_copy_button)
    {
        String text;
        SparseSet<int> selection = m_table.getSelectedRows();
        for(size_t i = 0; i < selection.size(); i++)
        {
            pd::Console::Message message(m_history.getMessageUntilLevel(m_level, i));
            if(!message.text.empty())
            {
                text += message.text + "\n";
            }
        }
        SystemClipboard::copyTextToClipboard(text);
    }
    else
    {
        juce::PopupMenu m;
        m.addItem(1, "Fatal", true, m_level == Level::Fatal);
        m.addItem(2, "Error", true, m_level == Level::Error);
        m.addItem(3, "Normal", true, m_level == Level::Post);
        m.addItem(4, "All", true, m_level == Level::Log);
        int level = m.showAt(getScreenBounds().translated(222, -6 * (Gui::getFont().getHeight() + 2) - 2),
                             0, 78, Gui::getFont().getHeight() + 2);
        if(level && level != int(m_level)+1)
        {
            m_level = Level(level-1);
            m_size = m_history.getNumberOfMessageUntilLevel(m_level);
            m_table.updateContent();
            if(m_level == Level::Fatal)
            {
                m_level_button.setLevelColor(Colours::red);
            }
            else if(m_level == Level::Error)
            {
                m_level_button.setLevelColor(Colours::orange);
            }
            else if(m_level == Level::Post)
            {
                m_level_button.setLevelColor(Gui::getColorTxt());
            }
            else
            {
                m_level_button.setLevelColor(Colours::green);
            }
            
        }
    }
}

bool GuiConsole::keyPressed(const KeyPress& key)
{
    if(key.getModifiers().isCommandDown() && key.getTextCharacter() == 'c')
    {
        SparseSet<int> selection = m_table.getSelectedRows();
        if(!selection.isEmpty())
        {
            String text;
            for(size_t i = 0; i < selection.size(); i++)
            {
                pd::Console::Message message(m_history.getMessageUntilLevel(m_level, i));
                if(!message.text.empty())
                {
                    text += message.text + "\n";
                }
            }
            SystemClipboard::copyTextToClipboard(text);
            return true;
        }
    }
    return false;
}

int GuiConsole::getNumRows()
{
    return m_size;
}

void GuiConsole::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    
}

void GuiConsole::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    pd::Console::Message message(m_history.getMessageUntilLevel(m_level, rowNumber));
    if(rowIsSelected)
    {
        g.setColour(Gui::getColorTxt());
        g.fillRect(0, 0, width, height);
    }
    g.setFont(Gui::getFont());
    if(message.level == Level::Fatal)
    {
        g.setColour(Colours::red);
    }
    else if(message.level == Level::Error)
    {
        g.setColour(Colours::orange);
    }
    else if(message.level == Level::Post)
    {
        g.setColour(rowIsSelected ? Gui::getColorBg() : Gui::getColorTxt());
    }
    else
    {
        g.setColour(Colours::green);
    }
    g.drawText(message.text, 2, 0, width, height, juce::Justification::centredLeft);
}

void GuiConsole::timerCallback()
{
    const size_t size = m_history.getNumberOfMessageUntilLevel(m_level);
    if(m_size != size)
    {
        m_size = size;
        m_table.updateContent();
    }
}



