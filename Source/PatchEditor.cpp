/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PatchEditor.h"

// ==================================================================================== //
//                                  CAMOMILE INTERFACE                                  //
// ==================================================================================== //

PatchEditor::PatchEditor(CamomileAudioProcessor& p) : AudioProcessorEditor(&p),
    m_processor(p),
    m_dropping(false)
{
    m_processor.addListener(this);
    patchChanged();
    setSize(600, 400);
    Component::setWantsKeyboardFocus(true);
}

PatchEditor::~PatchEditor()
{
    m_processor.removeListener(this);
}

void PatchEditor::paint(Graphics& g)
{
    m_processor.lock();
    const Patch patch = m_processor.getPatch();
    if(patch)
    {
        Gui camo = patch.getCamomile();
        if(camo)
        {
            g.fillAll(tojColor(camo.getBackgroundColor()));
            g.setColour(tojColor(camo.getBorderColor()));
            g.drawRect(getBounds().withZeroOrigin());
        }
        else
        {
            g.fillAll(Colours::white);
            g.setColour(Colours::black);
            g.setFont (15.0f);
            g.drawText(juce::String("The patch is not valid !"), getBounds().withZeroOrigin(), juce::Justification::centred);
        }
        m_processor.unlock();
    }
    else
    {
        m_processor.unlock();
        g.fillAll(Colours::white);
        g.setColour(Colours::black);
        g.setFont (15.0f);
        g.drawText(juce::String("Drag & Drop your patch..."), getBounds().withZeroOrigin(), juce::Justification::centred);
    }
    
    if(m_dropping)
    {
        g.fillAll(Colours::lightblue.withAlpha(0.2f));
    }
}

bool PatchEditor::isInterestedInFileDrag(const StringArray& files)
{
    if(files.size())
    {
        for(int i = 0; i < files.size(); i++)
        {
            if(files[i].endsWith(juce::StringRef(".pd")))
            {
                return true;
            }
        }
    }
    return false;
}

void PatchEditor::filesDropped(const StringArray& files, int x, int y)
{
    if(files.size())
    {
        for(int i = 0; i < files.size(); i++)
        {
            juce::File file(files[i]);
            if(file.getFileExtension() == juce::String(".pd"))
            {
                m_processor.loadPatch(file);
            }
        }
    }
}

void PatchEditor::patchChanged()
{
    removeAllChildren();
    m_objects.clear(true);
    m_processor.lock();
    const Patch patch = m_processor.getPatch();
    if(!patch.getName().empty())
    {
        const Gui camo = patch.getCamomile();
        if(camo)
        {
            const std::vector<Gui> objects = patch.getGuis();
            const std::array<int,2> ref = camo.getPosition();
            for(auto it : objects)
            {
                ObjectEditor* inte = m_objects.add(new ObjectEditor(*this, it));
                const std::array<int,2> pos = it.getPosition();
                const int offset = it.getBorderSize();
                inte->setTopLeftPosition(pos[0] - ref[0] - offset, pos[1] - ref[1] - offset);
                addChildComponent(inte);
            }
        }
    }
    m_processor.unlock();
    const MessageManagerLock mmLock;
    if(mmLock.lockWasGained())
    {
        repaint();
    }
}

void PatchEditor::fileDragEnter(const StringArray& files, int x, int y)
{
    const MessageManagerLock mmLock;
    if(mmLock.lockWasGained())
    {
        m_dropping = true;
        repaint();
    }
}

void PatchEditor::fileDragExit(const StringArray& files)
{
    m_dropping = false;
    repaint();
}

void PatchEditor::resized()
{
    
}
