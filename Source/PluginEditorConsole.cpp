/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEditorConsole.hpp"
#include "Gui/Gui.hpp"

// ==================================================================================== //
//                                      GUI CONSOLE                                     //
// ==================================================================================== //
    
GuiConsole::GuiConsole(CamomileAudioProcessor& p) :
m_history(p),
m_level_button(ImageCache::getFromMemory(BinaryData::option_png, BinaryData::option_pngSize),
               ImageCache::getFromMemory(BinaryData::flower_center_png, BinaryData::flower_center_pngSize)),
m_clear_button(ImageCache::getFromMemory(BinaryData::clear1_png, BinaryData::clear1_pngSize),
               ImageCache::getFromMemory(BinaryData::clear2_png, BinaryData::clear2_pngSize)),
m_copy_button(ImageCache::getFromMemory(BinaryData::copy1_png, BinaryData::copy1_pngSize),
              ImageCache::getFromMemory(BinaryData::copy2_png, BinaryData::copy2_pngSize))
{
    m_size  = 0;
    setWantsKeyboardFocus(true);
    m_table.setBounds(2, 2, getWidth() - 2, getHeight() - 30);
    m_table.setModel(this);
    m_table.setOutlineThickness(0);
    m_table.setWantsKeyboardFocus(true);
    m_table.setMultipleSelectionEnabled(true);
    m_table.setMouseMoveSelectsRows(false);
    m_table.setRowHeight(Gui::getFont().getHeight() + 2);
    m_table.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentWhite);
    m_table.getViewport()->setScrollBarsShown(true, true, true, true);
    m_table.getViewport()->setScrollBarThickness(4);
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

void GuiConsole::clearSelection()
{
    stopTimer();
    SparseSet<int> sels = m_table.getSelectedRows();
    for(int i = sels.size(); i > 0; --i) {
        m_history.clear(m_level, sels[i-1]); }
    m_table.deselectAllRows();
    timerCallback();
    startTimer(100);
}

void GuiConsole::copySelection()
{
    String text;
    stopTimer();
    SparseSet<int> sels = m_table.getSelectedRows();
    for(int i = 0; i < sels.size(); ++i) {
        text += m_history.get(m_level, sels[i]).second + "\n"; }
    SystemClipboard::copyTextToClipboard(text);
    startTimer(100);
}

void GuiConsole::paint(Graphics& g)
{
    g.setColour(Gui::getColorTxt().withAlpha(0.5f));
    g.drawHorizontalLine(getHeight() - 28, 2, getWidth() - 2);
}

void GuiConsole::resized()
{
    m_level_button.setTopLeftPosition(2, getHeight() - 26);
    m_clear_button.setTopLeftPosition(28, getHeight() - 26);
    m_copy_button.setTopLeftPosition(54, getHeight() - 26);
    m_table.setSize(getWidth() - 2, getHeight() - 30);
}

bool GuiConsole::keyPressed(const KeyPress& key)
{
    if(key.getModifiers() == ModifierKeys::commandModifier && key.getTextCharacter() == 'c')
    {
        copySelection();
        return true;
    }
    return false;
}

void GuiConsole::deleteKeyPressed(int lastRowSelected)
{
    clearSelection();
}

void GuiConsole::buttonClicked(Button* button)
{
    if(button == &m_clear_button)
    {
        clearSelection();
    }
    else if(button == &m_copy_button)
    {
        copySelection();
    }
    else
    {
        juce::PopupMenu m;
        m.addItem(1, "Fatal", true, m_level == ConsoleLevel::Fatal);
        m.addItem(2, "Error", true, m_level == ConsoleLevel::Error);
        m.addItem(3, "Normal", true, m_level == ConsoleLevel::Normal);
        m.addItem(4, "All", true, m_level == ConsoleLevel::Log);

        Point<int> pos = Component::getScreenPosition().translated(0, 292);
        int level = m.showAt(Rectangle<int>(pos.x, pos.y, 100, 48), 0, 0, Gui::getFont().getHeight() + 2);
        stopTimer();
        if(bool(level) && ConsoleLevel(level - 1) != m_level)
        {
            m_level = ConsoleLevel(level - 1);
            m_size = m_history.size(m_level);
            m_table.updateContent();
        }
        startTimer(100);
    }
}

void GuiConsole::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    std::pair<size_t, std::string> const message(m_history.get(m_level, rowNumber));
    if(rowIsSelected)
    {
        g.setColour(Gui::getColorTxt());
        g.fillRect(0, 0, width, height);
    }
    g.setFont(Gui::getFont());
    if(message.first == ConsoleLevel::Fatal)
    {
        g.setColour(Colours::red);
    }
    else if(message.first == ConsoleLevel::Error)
    {
        g.setColour(Colours::orange);
    }
    else if(message.first == ConsoleLevel::Normal)
    {
        g.setColour(rowIsSelected ? Gui::getColorBg() : Gui::getColorTxt().withAlpha(0.5f));
    }
    else
    {
        g.setColour(Colours::green);
    }
    String const mess = String(message.second).trimCharactersAtEnd(" \n");
    g.setFont(Gui::getFont());
    g.drawText(mess, 2, 0, width, height, juce::Justification::centredLeft, 0);
}

void GuiConsole::timerCallback()
{
    m_history.processPrints();
    const size_t size = m_history.size(m_level);
    if(m_size != size)
    {
        m_size = size;
        m_table.updateContent();
    }
}


GuiConsole::GButton::GButton(Image const& image1, Image const& image2) : Button("")
{
    setClickingTogglesState(false);
    setAlwaysOnTop(true);
    m_image1.setImage(image1);
    m_image2.setImage(image2);
    m_image1.setTransformToFit(Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image2.setTransformToFit(Rectangle<float>(0.f, 0.f, 22.f, 22.f), RectanglePlacement::stretchToFit);
    m_image1.setOverlayColour(Gui::getColorTxt());
    m_image1.setAlpha(0.5f);
    addAndMakeVisible(m_image1, -1);
    addAndMakeVisible(m_image2, 0);
    m_image1.setAlwaysOnTop(true);
    setSize(22, 22);
}

void GuiConsole::GButton::buttonStateChanged()
{
    m_image1.setAlpha((isDown() || isOver()) ? 1.f : 0.5f);
}



