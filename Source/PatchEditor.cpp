/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "InstanceProcessor.h"
#include "PatchEditor.h"

// ==================================================================================== //
//                                      IMAGE BUTTON                                    //
// ==================================================================================== //

class PatchEditor::ImgButton : public Button
{
private:
    DrawableImage   m_image1;
    DrawableImage   m_image2;
    DrawableImage   m_image3;
    PatchEditor*    m_editor;
public:
    ImgButton(PatchEditor* editor, const String& name, int rid) : Button(name), m_editor(editor)
    {
        addListener(editor);
        setClickingTogglesState(false);
        setAlwaysOnTop(true);
        setRadioGroupId(rid);
        m_image1.setImage(ImageCache::getFromMemory(BinaryData::flower1_png, BinaryData::flower1_pngSize));
        m_image2.setImage(ImageCache::getFromMemory(BinaryData::flower1_png, BinaryData::flower1_pngSize));
        m_image3.setImage(ImageCache::getFromMemory(BinaryData::flower2_png, BinaryData::flower2_pngSize));
        m_image1.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
        m_image2.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
        m_image3.setTransformToFit(Rectangle<float>(0.f, 0.f, 15.f, 15.f), RectanglePlacement::stretchToFit);
        m_image1.setOverlayColour(m_editor->m_color_txt);
        m_image2.setOverlayColour(m_editor->m_color_txt.interpolatedWith(m_editor->m_color_bg, 0.5f));
        addAndMakeVisible(m_image1, 0);
        addChildComponent(m_image2, 0);
        addAndMakeVisible(m_image3, -1);
        m_image3.setAlwaysOnTop(true);
    }
    void paintButton(Graphics& g, bool over, bool down) override {}
    
    void editorChanged()
    {
        const int size = 2 + ceil(m_editor->m_bd_size * 0.5f);
        setBounds(size, size, 15, 15);
        m_image1.setOverlayColour(m_editor->m_color_txt);
        m_image2.setOverlayColour(m_editor->m_color_txt.interpolatedWith(m_editor->m_color_bg, 0.5f));
    }
    
    void buttonStateChanged() override
    {
        if(isDown() || isOver())
        {
            m_image1.setVisible(false);
            m_image2.setVisible(true);
        }
        else
        {
            m_image1.setVisible(true);
            m_image2.setVisible(false);
        }
    }
};

// ==================================================================================== //
//                                          ABOUT                                       //
// ==================================================================================== //

class PatchEditor::About : public Component
{
private:
    DrawableImage    m_image1;
    juce::TextEditor m_text;
public:
    About()
    {
        m_image1.setImage(ImageCache::getFromMemory(BinaryData::flowerG_png, BinaryData::flowerG_pngSize));
        m_image1.setBoundingBox(RelativeParallelogram(Rectangle<float>(300.f - 128.f, 370.f - 128.f, 128.f, 128.f)));
        m_image1.setOpacity(0.5f);
        addAndMakeVisible(&m_image1);
        
        m_text.setMultiLine(true);
        m_text.setReadOnly(true);
        m_text.setScrollbarsShown(false);
        m_text.setCaretVisible(false);
        m_text.setPopupMenuEnabled(true);
        m_text.setColour(juce::TextEditor::backgroundColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        m_text.setColour(juce::TextEditor::outlineColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        m_text.setColour(juce::TextEditor::shadowColourId,Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        m_text.setColour(juce::TextEditor::textColourId, Colours::darkgrey);
        m_text.setFont(juce::Font(String("Futura"), 16.f, juce::Font::plain));
        m_text.setText("Camomile is a dynamic plugin that allows to load and control Pure Data patches "
                       "inside a digital audio workstation. Camomile translates the Cream library's user"
                       " graphical interfaces into Juce components for creating a modular plugin editor "
                       "and retrieves the parameters of this graphical objects in order to associate"
                       " them with the plugin host.\n\n"
                       "Author :\n"+ String(JucePlugin_Manufacturer) + "\n\n"
                       "Organizations :\nCICM | Université Paris 8 | Labex Arts H2H\n\n"
                       "Contacts :\n"+String(JucePlugin_ManufacturerEmail)+"\n"+ String(JucePlugin_ManufacturerWebsite)+"\n\n"
                       "Credits :\nPure Data by Miller Puckette\nJuce by ROLI Ltd.");
        m_text.setBounds(0, 0, 300, 370);
        addAndMakeVisible(&m_text, -1);
    }
};

// ==================================================================================== //
//                                          CONSOLE                                     //
// ==================================================================================== //

class PatchEditor::Console : public Component, public Messenger, public juce::Timer, public juce::TextEditor::Listener
{
private:
    juce::TextEditor m_text;
public:
    Console() : Messenger("camo-console")
    {
        m_text.setMultiLine(true);
        m_text.setReadOnly(false);
        m_text.setScrollbarsShown(true);
        m_text.setCaretVisible(false);
        m_text.setPopupMenuEnabled (true);
        m_text.setColour(juce::TextEditor::backgroundColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        m_text.setColour(juce::TextEditor::outlineColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        m_text.setColour(juce::TextEditor::shadowColourId,Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        m_text.setColour(juce::TextEditor::textColourId, Colours::darkgrey);
        m_text.setFont(juce::Font(String("Futura"), 16.f, juce::Font::plain));
        m_text.setText(Instance::getConsole());
        m_text.setBounds(0, 0, 300, 370);
        addAndMakeVisible(&m_text, 1);
        startTimer(20);
    }
    
    void textEditorTextChanged(juce::TextEditor& ed) override
    {
        Instance::setConsole(ed.getText().toStdString());
    }
    
    void receive(Message const& message) override
    {
        m_text.setText(Instance::getConsole());
    }
    
    void timerCallback() override
    {
        Messenger::trigger();
    }
};

// ==================================================================================== //
//                                          WINDOW                                      //
// ==================================================================================== //

class PatchEditor::PatchWin : public DocumentWindow
{
public:
    PatchWin(String const& name) :
    DocumentWindow(name, Colours::lightgrey, DocumentWindow::closeButton, false)
    {
        setUsingNativeTitleBar(true);
        setBounds(50, 50, 300, 370);
        setResizable(false, false);
        setAlwaysOnTop(true);
        setDropShadowEnabled(true);
        setVisible(true);
        setBackgroundColour(Colours::lightgrey);
    }

    void closeButtonPressed() override
    {
        removeFromDesktop();
    }
};

// ==================================================================================== //
//                                  PATCHER EDITOR                                  //
// ==================================================================================== //

PatchEditor::PatchEditor(InstanceProcessor& p) :
AudioProcessorEditor(&p), m_processor(p),
m_dropping(false), m_window(nullptr),
m_color_bg(Colours::lightgrey),
m_color_bd(Colours::darkgrey),
m_color_txt(Colours::darkgrey),
m_bd_size(2), m_font(22)
{
    Component::setWantsKeyboardFocus(true);
    m_processor.addListener(this);
    m_button = new ImgButton(this, "CamomileButton", 1);
    m_window = new PatchWin("");
    addAndMakeVisible(m_button);
    setSize(600, 420);
    patchChanged();
}

PatchEditor::~PatchEditor()
{
    m_processor.removeListener(this);
}

void PatchEditor::paint(Graphics& g)
{
    String text;
    g.fillAll(m_color_bg);
    g.setColour(m_color_bd);
    g.drawRect(getBounds().withZeroOrigin(), m_bd_size);
    g.drawLine(0.f, 20.f + round(m_bd_size * 0.5f), getWidth(), 20.f, m_bd_size);
    g.setFont(m_font);
    g.setColour(m_color_txt);
    const Patch patch = m_processor.getPatch();
    if(patch)
    {
        Gui camo = patch.getCamomile();
        if(!camo)
        {
            text = "Invalid patch.";
        }
        else
        {
            const vector<Atom> name(camo.getAttr("name"));
            if(!name.empty() && name[0].isSymbol())
            {
                text = String(std::string(name[0]));
            }
        }
    }
    else
    {
        text = "No patch.";
    }
    g.drawText(text, 20, 0, getWidth() - 20, 20, juce::Justification::centred);
    if(m_dropping)
    {
        g.fillAll(Colours::white.withAlpha(0.2f));
    }
}

void PatchEditor::handleAsyncUpdate()
{
    const MessageManagerLock mml(Thread::getCurrentThread());
    if(mml.lockWasGained())
    {
        repaint();
    }
}

void PatchEditor::patchChanged()
{
    for(int i = 0; i < m_objects.size(); i++)
    {
        removeChildComponent(m_objects[i]);
    }
    m_objects.clear(true);
    
    const Patch patch = m_processor.getPatch();
    if(patch)
    {
        const Gui camo = patch.getCamomile();
        if(camo)
        {
            const std::vector<Gui> objects = patch.getGuis();
            const std::array<int,2> ref = camo.getPosition();
            for(auto it : objects)
            {
                if(it != camo)
                {
                    ObjectEditor* inte = m_objects.add(new ObjectEditor(*this, it));
                    const std::array<int,2> pos = it.getPosition();
                    const int offset = it.getBorderSize();
                    inte->setTopLeftPosition(pos[0] - ref[0] - offset + 2, pos[1] - ref[1] - offset + 4);
                    addChildComponent(inte);
                }
            }
            m_color_bg = tojColor(camo.getBackgroundColor());
            m_color_bd = tojColor(camo.getBorderColor());
            m_color_txt= tojColor(camo.getTextColor());
            m_font     = tojFont(camo.getFont());
            m_bd_size  = camo.getBorderSize();
            setSize(std::max(camo.getWidth() + m_bd_size * 2, 20), std::max(camo.getHeight()  + m_bd_size * 2, 40));
        }
        m_last_path = patch.getPath() + File::separatorString + patch.getName();
    }
    
    if(m_button)
    {
        m_button->editorChanged();
    }
    AsyncUpdater::triggerAsyncUpdate();
}

void PatchEditor::buttonClicked(Button* button)
{
    if(button->getRadioGroupId() == 1)
    {
        juce::PopupMenu m;
        m.addItem(1, "About");
        m.addItem(2, "Open");
        m.addItem(3, "Close");
        m.addItem(4, "Reload");
        m.addItem(5, "Console");
        m.addItem(6, "Help");
        const int result = m.showAt(button->getScreenBounds().translated(-2, 2));
        if(result == 1)
        {
            m_window->setContentOwned(new About(), false);
            m_window->setName("About Camomile v" + String(JucePlugin_VersionString));
            m_window->addToDesktop();
        }
        else if(result == 2)
        {
            if(m_window)
            {
                m_window = nullptr;
            }
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
        else if(result == 3)
        {
            if(m_window)
            {
                m_window = nullptr;
            }
            m_processor.loadPatch(juce::File());
        }
        else if(result == 4)
        {
            File file(m_last_path);
            if(file.exists())
            {
                m_processor.loadPatch(file);
            }
        }
        else if(result == 5)
        {
            m_window->setContentOwned(new Console(), false);
            m_window->setName("Camomile Console");
            m_window->addToDesktop();
        }
        else if(result == 6)
        {
            if(m_window)
            {
                m_window = nullptr;
            }
            juce::URL url("https://github.com/pierreguillot/Camomile/wiki");
            if(url.isWellFormed())
            {
                url.launchInDefaultBrowser();
            }
        }
    }
}

