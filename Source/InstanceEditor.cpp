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
    m_processor.listener_add(this);
    addAndMakeVisible(m_patcher);
    addAndMakeVisible(m_button);
    setOpaque(true);
    setSize(600, 420);
    setWantsKeyboardFocus(true);
    
    int todo;
    //patchChanged();
}

InstanceEditor::~InstanceEditor()
{
    m_processor.listener_remove(this);
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
    xpd::patch const* patch = m_processor.getPatch();
    if(patch)
    {
        g.drawText(String(patch->get_name()).upToLastOccurrenceOf(StringRef(".pd"), false, false),
                   0, 0, getWidth(), 20, juce::Justification::centred);
    }
    else
    {
        g.drawText(String("No Patch"), 0, 0, getWidth(), 20, juce::Justification::centred);
    }
}

/*
void InstanceEditor::patchChanged()
{
    const xpd::Patch patch = m_processor.getPatch();
    if(patch.isValid())
    {
        m_patcher.setPatch(m_processor, patch);
        setSize(m_patcher.getWidth(), m_patcher.getHeight() + 20);
    }
}
 */

void InstanceEditor::buttonClicked(Button* button)
{
    if(button)
    {
        juce::PopupMenu m;
        m.addItem(1, "About");
        m.addItem(2, "Open");
        m.addItem(3, "Close");
        m.addItem(4, "Reload");
        m.addItem(5, "Export");
        m.addItem(6, "Console");
        m.addItem(7, "Help");
        const int result = m.showAt(button->getScreenBounds().translated(-2, 3));
        if(result == 1)
        {
            m_window.setContentOwned(new GuiAbout(), false);
            m_window.setName("About Camomile " + String(JucePlugin_VersionString));
            m_window.addToDesktop();
            m_window.toFront(false);
            m_window.setAlwaysOnTop(true);
        }
        else if(result == 2)
        {
            xpd::patch const* patch = m_processor.getPatch();
            if(patch)
            {
                FileChooser fc("Open a patch...", File(patch->get_path()), "*.pd", true);
                if(fc.browseForFileToOpen())
                {
                    juce::File file(fc.getResult());
                    if(file.getFileExtension() == juce::String(".pd"))
                    {
                        m_processor.loadPatch(file.getFileName().toStdString(),
                                              file.getParentDirectory().getFullPathName().toStdString());
                    }
                }
            }
            else
            {
                FileChooser fc("Open a patch...", File::getSpecialLocation(File::userDocumentsDirectory), "*.pd", true);
                if(fc.browseForFileToOpen())
                {
                    juce::File file(fc.getResult());
                    if(file.exists() && file.getFileExtension() == juce::String(".pd"))
                    {
                        m_processor.loadPatch(file.getFileName().toStdString(),
                                              file.getParentDirectory().getFullPathName().toStdString());
                    }
                }
            }
        }
        else if(result == 3)
        {
            m_processor.closePatch();
        }
        else if(result == 4)
        {
            xpd::patch const* patch = m_processor.getPatch();
            if(patch)
            {
                m_processor.loadPatch(patch->get_name(), patch->get_path());
            }
        }
        else if(result == 5)
        {
            ;
        }
        else if(result == 6)
        {
            m_window.setContentOwned(new GuiConsole(m_processor), false);
            m_window.setName("Camomile Console");
            m_window.addToDesktop();
            m_window.grabKeyboardFocus();
            m_window.toFront(true);
            m_window.setAlwaysOnTop(true);
        }
        else if(result == 7)
        {
            juce::URL url("https://github.com/pierreguillot/Camomile/wiki");
            if(url.isWellFormed())
            {
                url.launchInDefaultBrowser();
            }
        }
    }
}

