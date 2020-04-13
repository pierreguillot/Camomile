/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEditorConsole.hpp"
#include "PluginLookAndFeel.hpp"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          CONSOLE BUTTON                                  //
//////////////////////////////////////////////////////////////////////////////////////////////

class ConsoleButton : public Button
{
public:
    ConsoleButton(Image const& image) : Button(""), m_image()
    {
        setClickingTogglesState(false);
        setAlwaysOnTop(true);
        m_image.setImage(image);
        m_image.setTransformToFit(Rectangle<float>(0.f, 0.f, 18.f, 18.f), RectanglePlacement::stretchToFit);
        m_image.setAlpha(0.5f);
        addAndMakeVisible(m_image);
        setSize(18, 18);
    }
    
    void buttonStateChanged() final
    {
        m_image.setAlpha((isDown() || isOver()) ? 1.f : 0.5f);
    }
    
    void paintButton(Graphics& g, bool over, bool down) final {};
private:
    DrawableImage   m_image;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ConsoleButton)
};

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          CONSOLE                                         //
//////////////////////////////////////////////////////////////////////////////////////////////
    
PluginEditorConsole::PluginEditorConsole(CamomileAudioProcessor& p) :
m_history(p), m_table(),
m_level_button(new ConsoleButton(ImageCache::getFromMemory(BinaryData::settings_png, BinaryData::settings_pngSize))),
m_clear_button(new ConsoleButton(ImageCache::getFromMemory(BinaryData::garbage_png, BinaryData::garbage_pngSize))),
m_copy_button(new ConsoleButton(ImageCache::getFromMemory(BinaryData::copy_png, BinaryData::copy_pngSize))),
m_reload_button(new ConsoleButton(ImageCache::getFromMemory(BinaryData::reload_png, BinaryData::reload_pngSize))),
m_font(CamoLookAndFeel::getDefaultFont().withPointHeight(10.f))
{
    m_size  = 0;
    setWantsKeyboardFocus(true);
    m_table.setBounds(2, 2, getWidth() - 2, getHeight() - 30);
    m_table.setModel(this);
    m_table.setOutlineThickness(0);
    m_table.setWantsKeyboardFocus(true);
    m_table.setMultipleSelectionEnabled(true);
    m_table.setMouseMoveSelectsRows(false);
    m_table.setRowHeight(static_cast<int>(m_font.getHeight() + 2));
    m_table.setColour(ListBox::ColourIds::backgroundColourId, Colours::transparentWhite);
    m_table.getViewport()->setScrollBarsShown(true, true, true, true);
    m_table.getViewport()->setScrollBarThickness(4);
    addAndMakeVisible(m_table);
    
    m_clear_button->addListener(this);
    addAndMakeVisible(m_clear_button.get());
    m_copy_button->addListener(this);
    addAndMakeVisible(m_copy_button.get());
    m_level_button->addListener(this);
    addAndMakeVisible(m_level_button.get());
    m_reload_button->addListener(this);
    addAndMakeVisible(m_reload_button.get());
    startTimer(100);
}

PluginEditorConsole::~PluginEditorConsole()
{
    stopTimer();
}

void PluginEditorConsole::clearSelection()
{
    stopTimer();
    SparseSet<int> const selection = m_table.getSelectedRows();
    if(selection.isEmpty())
    {
        const size_t n = m_history.size(m_level);
        for(size_t i = n; i > 0; --i)
        {
            m_history.clear(m_level, i-1);
        }
    }
    else
    {
        const int n = selection.size();
        for(int i = n; i > 0; --i)
        {
            m_history.clear(m_level, static_cast<size_t>(selection[i-1]));
        }
    }
    m_table.deselectAllRows();
    timerCallback();
    startTimer(100);
}

void PluginEditorConsole::copySelection()
{
    String text;
    stopTimer();
    SparseSet<int> const selection = m_table.getSelectedRows();
    if(selection.isEmpty())
    {
        const size_t n = m_history.size(m_level);
        for(size_t i = 0; i < n; ++i)
        {
            text += String(m_history.get(m_level, static_cast<size_t>(i)).second + "\n");
        }
    }
    else
    {
        const int n = selection.size();
        for(int i = 0; i < n; ++i)
        {
            text += String(m_history.get(m_level, static_cast<size_t>(selection[i])).second + "\n");
        }
    }
    SystemClipboard::copyTextToClipboard(text);
    startTimer(100);
}

void PluginEditorConsole::paint(Graphics& g)
{
    g.setColour(Colours::black.withAlpha(0.5f));
    g.drawHorizontalLine(getHeight() - 28, 2.f, static_cast<float>(getWidth()) - 2.f);
}

void PluginEditorConsole::resized()
{
    const int btn_height  = getHeight() - 22;
    const int btn_width   = 26;
    const int btn_woffset = 4;
    const int tbl_height  = getHeight() - 30;
    const int tbl_wdith   = getWidth() - 2;
    m_level_button->setTopLeftPosition(btn_woffset+btn_width*0, btn_height);
    m_clear_button->setTopLeftPosition(btn_woffset+btn_width*1, btn_height);
    m_copy_button->setTopLeftPosition(btn_woffset+btn_width*2, btn_height);
    m_reload_button->setTopLeftPosition(btn_woffset+btn_width*3, btn_height);
    m_table.setSize(tbl_wdith, tbl_height);
}

bool PluginEditorConsole::keyPressed(const KeyPress& key)
{
    if(key.getModifiers() == ModifierKeys::commandModifier && key.getTextCharacter() == 'c')
    {
        copySelection();
        return true;
    }
    return false;
}

void PluginEditorConsole::deleteKeyPressed(int lastRowSelected)
{
    clearSelection();
}

void PluginEditorConsole::buttonClicked(Button* button)
{
    if(button == m_reload_button.get())
    {
        m_history.reloadPatch();
    }
    else if(button == m_clear_button.get())
    {
        clearSelection();
    }
    else if(button == m_copy_button.get())
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
        
        stopTimer();
        int const level = m.show(0, 0, static_cast<int>(m_font.getHeight() + 2));
        if(level != 0 && static_cast<ConsoleLevel>(level - 1) != m_level)
        {
            m_level = static_cast<ConsoleLevel>(level - 1);
            m_size  = m_history.size(m_level);
            m_table.updateContent();
            m_table.deselectAllRows();
        }
        startTimer(100);
    }
}

void PluginEditorConsole::paintListBoxItem(int rowNumber, Graphics& g, int width, int height, bool rowIsSelected)
{
    std::pair<size_t, std::string> const message(m_history.get(m_level, rowNumber));
    if(rowIsSelected)
    {
        g.setColour(Colours::black);
        g.fillRect(0, 0, width, height);
    }
    
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
        g.setColour(rowIsSelected ? Colours::lightgrey : Colours::black.withAlpha(0.5f));
    }
    else
    {
        g.setColour(Colours::green);
    }
    String const mess = String(message.second).trimCharactersAtEnd(" \n");
    g.setFont(m_font);
    g.drawText(mess, 2, 0, width, height, juce::Justification::centredLeft, 0);
}

void PluginEditorConsole::timerCallback()
{
    m_history.processPrints();
    const size_t size = m_history.size(m_level);
    if(m_size != size)
    {
        m_size = size;
        m_table.updateContent();
    }
}




