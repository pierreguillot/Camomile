/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiConsole.hpp"
#include "Gui.hpp"
#include <iostream>
// ==================================================================================== //
//                                      GUI CONSOLE                                     //
// ==================================================================================== //
    
GuiConsole::GuiConsole(CamomileAudioProcessor& p) : m_history(p)
{
    m_size  = 0;
    setWantsKeyboardFocus(true);
    TableHeaderComponent* header = new TableHeaderComponent();
    header->addColumn(String("ID"), 1, 300, 300, 300, TableHeaderComponent::notResizableOrSortable, -1);
    header->setStretchToFitActive(false);
    header->setColumnVisible(1, true);
    
    m_table.setBounds(2, 2, 298, 340);
    m_table.setModel(this);
    m_table.setOutlineThickness(0);
    m_table.setWantsKeyboardFocus(true);
    m_table.setMultipleSelectionEnabled(false);
    m_table.setMouseMoveSelectsRows(false);
    m_table.setHeaderHeight(0);
    m_table.setRowHeight(Gui::getFont().getHeight() + 2);
    m_table.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentWhite);
    m_table.getViewport()->setScrollBarsShown(true, false, true, false);
    m_table.getViewport()->setScrollBarThickness(4);
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

void GuiConsole::paint(Graphics& g)
{
    g.setColour(Gui::getColorTxt().withAlpha(0.5f));
    g.drawHorizontalLine(342, 2, 298);
}

void GuiConsole::buttonClicked(Button* button)
{
    if(button == &m_clear_button)
    {
        stopTimer();
        m_history.clear();
        startTimer(100);
    }
    else if(button == &m_copy_button)
    {
        stopTimer();
        String text;
        for(size_t i = 0; i < m_size && i < 1000; i++)
        {
            text += m_history.getMessageUntilLevel(m_level, i).text + "\n";
        }
        SystemClipboard::copyTextToClipboard(text);
        startTimer(100);
    }
    else
    {
        juce::PopupMenu m;
        m.addItem(1, "Fatal", true, m_level == Message::Level::Fatal);
        m.addItem(2, "Error", true, m_level == Message::Level::Error);
        m.addItem(3, "Normal", true, m_level == Message::Level::Normal);
        m.addItem(4, "All", true, m_level == Message::Level::Log);

        Point<int> pos = Component::getScreenPosition().translated(0, 292);
        int level = m.showAt(Rectangle<int>(pos.x, pos.y, 100, 48), 0, 0, Gui::getFont().getHeight() + 2);
        stopTimer();
        if(bool(level) && Message::Level(level) != m_level)
        {
            m_level = Message::Level(level);
            m_size = m_history.getNumberOfMessageUntilLevel(m_level);
            m_table.updateContent();
        }
        startTimer(100);
    }
}

void GuiConsole::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    Message message(m_history.getMessageUntilLevel(m_level, rowNumber));
    if(rowIsSelected)
    {
        g.setColour(Gui::getColorTxt());
        g.fillRect(0, 0, width, height);
    }
    g.setFont(Gui::getFont());
    if(message.level == Message::Level::Fatal)
    {
        g.setColour(Colours::red);
    }
    else if(message.level == Message::Level::Error)
    {
        g.setColour(Colours::orange);
    }
    else if(message.level == Message::Level::Normal)
    {
        g.setColour(rowIsSelected ? Gui::getColorBg() : Gui::getColorTxt().withAlpha(0.5f));
    }
    else
    {
        g.setColour(Colours::green);
    }
    
    g.setFont(Gui::getFont());
    g.drawText(String(message.text).trimCharactersAtEnd(" \n"), 2, 0, width, height, juce::Justification::centredLeft);
}

void GuiConsole::timerCallback()
{
    m_history.processPrints();
    const size_t size = m_history.getNumberOfMessageUntilLevel(m_level);
    if(m_size != size)
    {
        m_size = size;
        m_table.updateContent();
    }
}


GuiConsole::LevelButton::LevelButton() : Button("LevelButton")
{
    setClickingTogglesState(false);
    setAlwaysOnTop(true);
    m_image1.setImage(ImageCache::getFromMemory(BinaryData::option_png, BinaryData::option_pngSize));
    m_image2.setImage(ImageCache::getFromMemory(BinaryData::flower_center_png, BinaryData::flower_center_pngSize));
    m_image1.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image2.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image1.setOverlayColour(Gui::getColorTxt());
    m_image1.setAlpha(0.5f);
    addAndMakeVisible(m_image1, -1);
    addAndMakeVisible(m_image2, 0);
    m_image1.setAlwaysOnTop(true);
    setBounds(2, 344, 22, 22);
}

void GuiConsole::LevelButton::buttonStateChanged()
{
    m_image1.setAlpha((isDown() || isOver()) ? 1.f : 0.5f);
}


GuiConsole::ClearButton::ClearButton() : Button("ClearButton")
{
    setClickingTogglesState(false);
    setAlwaysOnTop(true);
    m_image1.setImage(ImageCache::getFromMemory(BinaryData::clear1_png, BinaryData::clear1_pngSize));
    m_image2.setImage(ImageCache::getFromMemory(BinaryData::clear2_png, BinaryData::clear2_pngSize));
    m_image1.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image2.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image2.setOverlayColour(Gui::getColorTxt());
    m_image2.setAlpha(0.5f);
    addAndMakeVisible(m_image1, -1);
    addAndMakeVisible(m_image2, 0);
    m_image2.setAlwaysOnTop(true);
    setBounds(28, 344, 22, 22);
}

void GuiConsole::ClearButton::buttonStateChanged()
{
    m_image2.setAlpha((isDown() || isOver()) ? 1.f : 0.5f);
}


GuiConsole::CopyButton::CopyButton() : Button("CopyButton")
{
    setClickingTogglesState(false);
    setAlwaysOnTop(true);
    m_image1.setImage(ImageCache::getFromMemory(BinaryData::copy1_png, BinaryData::copy1_pngSize));
    m_image2.setImage(ImageCache::getFromMemory(BinaryData::copy2_png, BinaryData::copy2_pngSize));
    m_image1.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image2.setTransformToFit(juce::Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image1.setOverlayColour(Gui::getColorTxt());
    m_image1.setAlpha(0.5f);
    addAndMakeVisible(m_image1, -1);
    addAndMakeVisible(m_image2, 0);
    m_image1.setAlwaysOnTop(true);
    setBounds(52, 344, 22, 22);
}

void GuiConsole::CopyButton::buttonStateChanged()
{
    m_image1.setAlpha((isDown() || isOver()) ? 1.f : 0.5f);
}





