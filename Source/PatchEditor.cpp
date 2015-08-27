/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "InstanceProcessor.h"
#include "PatchEditor.h"

class PatchEditor::AboutWindow : public DocumentWindow
{
private:
    class Content : public Component
    {
    private:
        DrawableImage m_image;
        juce::TextEditor m_text;
    public:
        Content()
        {
            m_image.setImage(ImageCache::getFromMemory(BinaryData::flowerM_png, BinaryData::flowerM_pngSize));
            m_image.setBoundingBox(RelativeParallelogram(Rectangle<float>(300.f - 128.f, 320.f - 128.f, 128.f, 128.f)));
            m_image.setOpacity(0.5f);
            addAndMakeVisible(&m_image, 0);
            
            m_text.setMultiLine(true);
            m_text.setReadOnly(true);
            m_text.setScrollbarsShown(false);
            m_text.setCaretVisible(false);
            m_text.setPopupMenuEnabled (true);
            m_text.setColour(juce::TextEditor::backgroundColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
            m_text.setColour(juce::TextEditor::outlineColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
            m_text.setColour(juce::TextEditor::shadowColourId,Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
            m_text.setText("Camomile v" + String(JucePlugin_VersionString) + "\n\n"
                           "Camomile is a dynamic Plugin that allows to load and control Pure Data patches "
                           "inside a Digital Audio Work Station. Camomile uses the Cream library as framework "
                           "for the graphical user interfaces.\n\n"
                           "Author :\n"+JucePlugin_Manufacturer+"\n\n"
                           "Organizations :\nCICM | Université Paris 8 | Labex Arts H2H\n\n"
                           "Contacts :\n"+String(JucePlugin_ManufacturerEmail)+"\n"+ String(JucePlugin_ManufacturerWebsite)+"\n\n"
                           "Credits :\nPure Data by Miller Puckette\nJuce by ROLI Ltd.");
            m_text.setBounds(0, 0, 300, 320);
            addAndMakeVisible(&m_text, 1);
        }
    };
    Content m_content;
public:
    AboutWindow() : DocumentWindow("About Camomile", Colours::lightgrey, closeButton, false)
    {
        setUsingNativeTitleBar(true);
        setBounds(20, 20, 300, 320);
        setResizable(false, false);
        setAlwaysOnTop(true);
        setDropShadowEnabled(true);
        setVisible(true);
        setContentNonOwned(&m_content, false);
    }
    
    void closeButtonPressed() override
    {
        removeFromDesktop();
    }
};

class PatchEditor::ConsoleWindow : public DocumentWindow
{
private:
    class Content : public Component, public Messenger, public juce::TextEditor::Listener
    {
    private:
        juce::TextEditor m_text;
    public:
        Content() : Messenger("camo_console")
        {
            m_text.setMultiLine(true);
            m_text.setReadOnly(false);
            m_text.setScrollbarsShown(true);
            m_text.setCaretVisible(false);
            m_text.setPopupMenuEnabled (true);
            m_text.setColour(juce::TextEditor::backgroundColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
            m_text.setColour(juce::TextEditor::outlineColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
            m_text.setColour(juce::TextEditor::shadowColourId,Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
            m_text.setText(Instance::getConsole());
            
            m_text.setBounds(0, 0, 300, 320);
            addAndMakeVisible(&m_text, 1);
        }
        
        void textEditorTextChanged(juce::TextEditor& ed) override
        {
            Instance::setConsole(ed.getText().toStdString());
        }
        
        void receive(std::string const& dest, std::string const& s, std::vector<Atom> const& atoms) override
        {
            m_text.setText(Instance::getConsole());
        }
    };
    Content m_content;
public:
    ConsoleWindow() : DocumentWindow("Camomile Console", Colours::lightgrey, closeButton, false)
    {
        setUsingNativeTitleBar(true);
        setBounds(20, 20, 300, 320);
        setResizable(false, false);
        setAlwaysOnTop(true);
        setDropShadowEnabled(true);
        setVisible(true);
        setContentNonOwned(&m_content, false);
        
    }
    
    void closeButtonPressed() override
    {
        delete this;
    }
};

// ==================================================================================== //
//                                  CAMOMILE INTERFACE                                  //
// ==================================================================================== //

PatchEditor::PatchEditor(InstanceProcessor& p) :
AudioProcessorEditor(&p),
m_processor(p),
m_dropping(false),
m_color_bg(Colours::lightgrey),
m_color_bd(Colours::darkgrey)
{
    DrawableImage image;
    image.setImage(ImageCache::getFromMemory(BinaryData::flowerM_png, BinaryData::flowerM_pngSize));
    DrawableImage image2(image);
    image2.setOverlayColour(Colours::grey.withAlpha(0.2f));
    DrawableImage image3(image);
    image3.setOverlayColour(Colours::grey.withAlpha(0.5f));
    
    DrawableButton* d = new DrawableButton("CamomileButton",DrawableButton::ImageStretched);
    d->addListener(this);
    d->setClickingTogglesState(false);
    d->setAlwaysOnTop(true);
    d->setRadioGroupId(1);
    d->setImages(&image, &image2, &image3);
    d->setBounds(2, 2, 16, 16);
    d->setColour(TextButton::buttonColourId, Colours::transparentBlack);
    d->setColour(TextButton::buttonOnColourId, Colours::black);
    d->setColour(TextButton::textColourOffId, Colours::white);
    d->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    m_buttons.add(d);

    TextButton* t = new TextButton("Open");
    t->addListener(this);
    t->setClickingTogglesState(false);
    t->setRadioGroupId(2);
    t->setColour(TextButton::buttonColourId, Colours::transparentBlack);
    t->setColour(TextButton::buttonOnColourId, Colours::grey);
    t->setColour(TextButton::textColourOffId, Colours::white);
    t->setBounds(20, 1, 40, 19);
    t->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    m_buttons.add(t);
    
    t = new TextButton("Close");
    t->addListener(this);
    t->setClickingTogglesState(false);
    t->setRadioGroupId(3);
    t->setColour(TextButton::buttonColourId, Colours::transparentBlack);
    t->setColour(TextButton::buttonOnColourId, Colours::grey);
    t->setColour(TextButton::textColourOffId, Colours::white);
    t->setBounds(60, 1, 40, 19);
    t->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    m_buttons.add(t);
    
    t = new TextButton("Console");
    t->addListener(this);
    t->setClickingTogglesState(false);
    t->setRadioGroupId(4);
    t->setColour(TextButton::buttonColourId, Colours::transparentBlack);
    t->setColour(TextButton::buttonOnColourId, Colours::grey);
    t->setColour(TextButton::textColourOffId, Colours::white);
    t->setBounds(100, 1, 55, 19);
    t->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    m_buttons.add(t);

    t = new TextButton("Help");
    t->addListener(this);
    t->setClickingTogglesState(false);
    t->setRadioGroupId(5);
    t->setColour(TextButton::buttonColourId, Colours::transparentBlack);
    t->setColour(TextButton::buttonOnColourId, Colours::grey);
    t->setColour(TextButton::textColourOffId, Colours::white);
    t->setBounds(155, 1, 35, 19);
    t->setConnectedEdges(Button::ConnectedOnLeft | Button::ConnectedOnRight);
    m_buttons.add(t);
    
    Component::setWantsKeyboardFocus(true);
    m_processor.addListener(this);
    patchChanged();
    setSize(600, 420);
}

PatchEditor::~PatchEditor()
{
    m_processor.removeListener(this);
}

void PatchEditor::paint(Graphics& g)
{
    g.fillAll(m_color_bg);
    g.setColour(m_color_bd);
    g.drawRect(getBounds().withZeroOrigin());
    g.drawLine(0.f, 20.f, getWidth(), 20.f);
    const Patch patch = m_processor.getPatch();
    if(patch)
    {
        Gui camo = patch.getCamomile();
        if(!camo)
        {
            g.setFont(15.0f);
            g.drawText(juce::String("The patch is not valid !"), getBounds().withZeroOrigin(), juce::Justification::centred);
        }
    }
    else
    {
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
                return;
            }
        }
    }
}

void PatchEditor::patchChanged()
{
    removeAllChildren();
    for(int i = 0; i < m_buttons.size(); i++)
    {
        addAndMakeVisible(m_buttons[i]);
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
                    inte->setTopLeftPosition(pos[0] - ref[0] - offset, pos[1] - ref[1] - offset + 20.);
                    addChildComponent(inte);
                }
            }
            m_color_bg = tojColor(camo.getBackgroundColor());
            m_color_bd = tojColor(camo.getBorderColor());
        }
    }
    const MessageManagerLock mmLock;
    if(mmLock.lockWasGained())
    {
        if(m_window)
        {
            m_window->setBackgroundColour(m_color_bg.brighter(0.75));
        }
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

void PatchEditor::buttonClicked(Button* button)
{
    if(button->getRadioGroupId() == 1)
    {
        if(!m_window || m_window->getName() != String("About Camomile"))
        {
            m_window = new AboutWindow();
        }
        m_window->addToDesktop();
        m_window->centreAroundComponent(this, m_window->getWidth(), m_window->getHeight());
        m_window->setBackgroundColour(m_color_bg.brighter(0.75));
    }
    else if(button->getRadioGroupId() == 2)
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
                return;
            }
        }
    }
    else if(button->getRadioGroupId() == 3)
    {
        if(m_window)
        {
            m_window = nullptr;
        }
        m_processor.loadPatch(juce::File());
    }
    else if(button->getRadioGroupId() == 4)
    {
        if(!m_window || m_window->getName() != String("Camomile Console"))
        {
            m_window = new ConsoleWindow();
        }
        m_window->addToDesktop();
        m_window->centreAroundComponent(this, m_window->getWidth(), m_window->getHeight());
        m_window->setBackgroundColour(m_color_bg.brighter(0.75));
    }
    else if(button->getRadioGroupId() == 5)
    {
        if(m_window)
        {
            m_window = nullptr;
        }
        juce::URL url("https://github.com/pierreguillot/Camomile/wiki");
        if(url.isWellFormed())
            url.launchInDefaultBrowser();
    }
}

void PatchEditor::resized()
{
    
}
