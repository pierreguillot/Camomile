/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "InstanceProcessor.hpp"
#include "InstanceEditor.hpp"

// ==================================================================================== //
//                                  INSTANCE EDITOR                                     //
// ==================================================================================== //

InstanceEditor::InstanceEditor(InstanceProcessor& p) : AudioProcessorEditor(&p), m_processor(p)
{
    m_button.addListener(this);
    m_processor.addListener(this);
    addAndMakeVisible(m_patcher);
    addAndMakeVisible(m_button);
    setOpaque(true);
    setSize(600, 420);
    setWantsKeyboardFocus(true);
    patchChanged();
}

InstanceEditor::~InstanceEditor()
{
    m_processor.removeListener(this);
}

void InstanceEditor::paint(Graphics& g)
{
    String text;
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(getBounds().withZeroOrigin(), Gui::getBorderSize());
    g.drawLine(0.f, 20.f, getWidth(), 20.f, Gui::getBorderSize());
    g.setFont(Gui::getFont());
    g.setColour(Gui::getColorTxt());
    const pd::Patch patch = m_processor.getPatch();
    if(patch.isValid())
    {
        g.drawText(String(patch.getName()).upToLastOccurrenceOf(StringRef(".pd"), false, false),
                   0, 0, getWidth(), 20, juce::Justification::centred);
    }
    else
    {
        g.drawText(String("No Patch"), 0, 0, getWidth(), 20, juce::Justification::centred);
    }
}

void InstanceEditor::patchChanged()
{
    const pd::Patch patch = m_processor.getPatch();
    if(patch.isValid())
    {
        m_patcher.setPatch(m_processor, patch);
        setSize(m_patcher.getWidth(), m_patcher.getHeight() + 20);
    }
}

void InstanceEditor::buttonClicked(Button* button)
{
    if(button)
    {
        juce::PopupMenu m;
        m.addItem(1, "About");
        m.addItem(2, "Open");
        m.addItem(3, "Close");
        m.addItem(4, "Reload");
        m.addItem(5, "Console");
        m.addItem(6, "Help");
        const int result = m.showAt(button->getScreenBounds().translated(-2, 3));
        if(result == 1)
        {
            m_window.setContentOwned(new GuiAbout(), false);
            m_window.setName("About Camomile " + String(JucePlugin_VersionString));
            m_window.addToDesktop();
            m_window.grabKeyboardFocus();
        }
        else if(result == 2)
        {
            const pd::Patch patch = m_processor.getPatch();
            if(patch.isValid())
            {
                FileChooser fc("Open a patch...", File(patch.getPath()), "*.pd", true);
                if(fc.browseForFileToOpen())
                {
                    juce::File file(fc.getResult());
                    if(file.getFileExtension() == juce::String(".pd"))
                    {
                        m_processor.loadPatch(file);
                    }
                }
            }
            else
            {
                FileChooser fc("Open a patch...", File::getSpecialLocation(File::userDocumentsDirectory), "*.pd", true);
                if(fc.browseForFileToOpen())
                {
                    juce::File file(fc.getResult());
                    if(file.getFileExtension() == juce::String(".pd"))
                    {
                        m_processor.loadPatch(file);
                    }
                }
            }
            
        }
        else if(result == 3)
        {
            m_processor.loadPatch(juce::File());
        }
        else if(result == 4)
        {
            const pd::Patch patch = m_processor.getPatch();
            if(patch.isValid())
            {
                File file(patch.getPath() + File::separatorString.toStdString() + patch.getName());
                if(file.exists())
                {
                    m_processor.loadPatch(file);
                }
            }
        }
        else if(result == 5)
        {
            m_window.setContentOwned(new GuiConsole(), false);
            m_window.setName("Camomile Console");
            m_window.addToDesktop();
            m_window.grabKeyboardFocus();
        }
        else if(result == 6)
        {
            juce::URL url("https://github.com/pierreguillot/Camomile/wiki");
            if(url.isWellFormed())
            {
                url.launchInDefaultBrowser();
            }
        }
    }
}

