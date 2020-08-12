/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEditorObject.hpp"
#include "PluginLookAndFeel.hpp"

PluginEditorObject* PluginEditorObject::createTyped(CamomileEditorMouseManager& p, pd::Gui& g)
{
    if(g.getType() == pd::Gui::Type::Bang)
    {
        return new GuiBang(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Toggle)
    {
        return new GuiToggle(p, g);
    }
    else if(g.getType() == pd::Gui::Type::HorizontalSlider)
    {
        return new GuiSliderHorizontal(p, g);
    }
    else if(g.getType() == pd::Gui::Type::VerticalSlider)
    {
        return new GuiSliderVertical(p, g);
    }
    else if(g.getType() == pd::Gui::Type::HorizontalRadio)
    {
        return new GuiRadioHorizontal(p, g);
    }
    else if(g.getType() == pd::Gui::Type::VerticalRadio)
    {
        return new GuiRadioVertical(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Panel)
    {
        return new GuiPanel(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Comment)
    {
        return new GuiComment(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Number)
    {
        return new GuiNumber(p, g);
    }
    else if(g.getType() == pd::Gui::Type::AtomNumber)
    {
        return new GuiAtomNumber(p, g);
    }
    else if(g.getType() == pd::Gui::Type::AtomSymbol)
    {
        return new GuiAtomSymbol(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Array)
    {
        return new GuiArray(p, g);
    }
    else if(g.getType() == pd::Gui::Type::GraphOnParent)
    {
        return new GuiGraphOnParent(p, g);
    }
    return new PluginEditorObject(p, g);
}

PluginEditorObject::PluginEditorObject(CamomileEditorMouseManager& p, pd::Gui& g) : gui(g), patch(p), edited(false),
value(g.getValue()), min(g.getMinimum()), max(g.getMaximum())
{
    std::array<int, 4> const bounds(gui.getBounds());
    setBounds(bounds[0], bounds[1], bounds[2], bounds[3]);
    setOpaque(false);
}

PluginEditorObject::~PluginEditorObject() {}

float PluginEditorObject::getValueOriginal() const noexcept
{
    return value;
}

void PluginEditorObject::setValueOriginal(float v)
{
    value = (min < max) ? std::max(std::min(v, max), min) : std::max(std::min(v, min), max);
    gui.setValue(value);
}

float PluginEditorObject::getValueScaled() const noexcept
{
    return (min < max) ? (value - min) / (max - min) : 1.f - (value - max) / (min - max);
}

void PluginEditorObject::setValueScaled(float v)
{
    value = (min < max) ? std::max(std::min(v, 1.f), 0.f) * (max - min) + min
                        : (1.f - std::max(std::min(v, 1.f), 0.f)) * (min - max) + max;
    gui.setValue(value);
}

void PluginEditorObject::startEdition() noexcept
{
    edited = true;
    patch.startEdition();
    value = gui.getValue();
}

void PluginEditorObject::stopEdition() noexcept
{
    edited = false;
    patch.stopEdition();
}

void PluginEditorObject::updateValue()
{
    if(edited == false)
    {
        float const v = gui.getValue();
        if(v != value)
        {
            value = v;
            repaint();
        }
    }
}

void PluginEditorObject::updateInterface()
{
    std::array<int, 4> const bounds(gui.getBounds());
    setBounds(bounds[0], bounds[1], bounds[2], bounds[3]);
    repaint();
}

Label* PluginEditorObject::getLabel()
{
    pd::Label const lbl = gui.getLabel();
    const String text = String(lbl.getText());
    if(text.isNotEmpty())
    {
        Label* label = new Label();
        const Font ft = CamoLookAndFeel::getFont(lbl.getFontName()).withPointHeight(static_cast<float>(lbl.getFontHeight()));
        const int width = ft.getStringWidth(text) + 1;
        const int height = ft.getHeight();
        const std::array<int, 2> position = lbl.getPosition();
        label->setBounds(position[0], position[1] - height / 2, width, height);
        label->setFont(ft);
        label->setJustificationType(Justification::centredLeft);
        label->setBorderSize(BorderSize<int>(0, 0, 0, 0));
        label->setMinimumHorizontalScale(1.f);
        label->setText(text, NotificationType::dontSendNotification);
        label->setEditable(false, false);
        label->setInterceptsMouseClicks(false, false);
        label->setColour(Label::textColourId, Colour(static_cast<uint32>(lbl.getColor())));
        return label;
    }
    return nullptr;
}

pd::Gui PluginEditorObject::getGUI()
{
    return gui;
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     BANG        /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiBang::paint(Graphics& g)
{
    const float border = 1.f;
    const float w = static_cast<float>(getWidth() - border * 2);
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    if(getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
        g.fillEllipse(border, border, w, w);
    }
    g.setColour(Colours::black);
    g.drawEllipse(border, border, w, w, border);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiBang::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(1);
    repaint();
    stopEdition();
}

void GuiBang::mouseUp(const MouseEvent& e)
{
    if(getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        repaint();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     TOGGLE        ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiToggle::paint(Graphics& g)
{
    const float border = 1.f;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    if(getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        const float w = static_cast<float>(getWidth()) - border * 2.f;
        g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
        g.drawLine(1.f + border, 1.f + border, w, w, border);
        g.drawLine(w, 1.f + border, 1.f + border, w, border);
    }
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiToggle::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(1.f - getValueOriginal());
    repaint();
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     SLIDER HORIZONTAL   /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiSliderHorizontal::paint(Graphics& g)
{
    const float border = 1.f;
    const float crsor  = 3.f;
    const float w = static_cast<float>(getWidth()) - border * 2.f;
    const float h = static_cast<float>(getHeight()) - border * 2.f;
    const float val = gui.isLogScale() ? log(getValueOriginal() / min) / log(max / min) : getValueScaled();
    const float pos = val * (w - crsor - border) + crsor;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(pos, border + 0.5f, pos, h + 0.5f, crsor);
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiSliderHorizontal::mouseDown(const MouseEvent& e)
{
    startEdition();
    if(gui.jumpOnClick())
    {
        mouseDrag(e);
    }
    else
    {
        if(gui.isLogScale())
        {
            m_temp = log(getValueOriginal() / min) / log(max / min);
        }
        else
        {
            m_temp = getValueScaled();
        }
    }
}

void GuiSliderHorizontal::mouseDrag(const MouseEvent& e)
{
    if(gui.jumpOnClick())
    {
        const float val = static_cast<float>(e.x - 2) / static_cast<float>(getWidth() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp(val * log(max / min)) * min);
        }
        else
        {
            setValueScaled(val);
        }
    }
    else
    {
        const float val = static_cast<float>(e.x - e.getMouseDownX()) / static_cast<float>(getWidth() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp((m_temp + val) * log(max / min)) * min);
        }
        else
        {
            setValueScaled(m_temp + val);
        }
    }
    repaint();
}

void GuiSliderHorizontal::mouseUp(const MouseEvent& e)
{
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     SLIDER VERTICAL     /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    
void GuiSliderVertical::paint(Graphics& g)
{
    const float border = 1.f;
    const float crsor = 3.f;
    const float w = static_cast<float>(getWidth() - border * 2);
    const float h = static_cast<float>(getHeight() - border * 2);
    const float val = gui.isLogScale() ? log(getValueOriginal() / min) / log(max / min) : getValueScaled();
    const float pos = (1.f - val) * (h - crsor - border) + crsor;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(border + 0.5f, pos, w + 0.5f, pos, crsor);
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiSliderVertical::mouseDown(const MouseEvent& e)
{
    startEdition();
    if(gui.jumpOnClick())
    {
        mouseDrag(e);
    }
    else
    {
        if(gui.isLogScale())
        {
            m_temp = log(getValueOriginal() / min) / log(max / min);
        }
        else
        {
            m_temp = getValueScaled();
        }
    }
}

void GuiSliderVertical::mouseDrag(const MouseEvent& e)
{
    if(gui.jumpOnClick())
    {
        const float val = static_cast<float>(getHeight() - e.y - 2) / static_cast<float>(getHeight() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp(val * log(max /min)) * min);
        }
        else
        {
            setValueScaled(val);
        }
    }
    else
    {
        const float val = static_cast<float>(e.getMouseDownY() - e.y) / static_cast<float>(getHeight() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp((m_temp + val) * log(max / min)) * min);
        }
        else
        {
            setValueScaled(m_temp + val);
        }
    }
    repaint();
}

void GuiSliderVertical::mouseUp(const MouseEvent& e)
{
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     RADIO HORIZONTAL    /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiRadioHorizontal::paint(Graphics& g)
{
    const float border = 1.f;
    const float extra  = 2.f;
    const float h  = static_cast<float>(getHeight());
    const float hs = h - 2.f * (border + extra);
    const float w = static_cast<float>(getWidth()) / static_cast<float>(max + 1);
    const float ws = w - 2.f * (border + extra);
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.fillRect(w * getValueOriginal() + border + extra, border + extra, ws, hs);
    g.setColour(Colours::black);
    for(size_t i = 1; i < size_t(max) + 1; ++i)
    {
        g.drawLine(w * static_cast<float>(i), 0.f, w * static_cast<float>(i), w, border);
    }
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiRadioHorizontal::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(std::floor(static_cast<float>(e.x * (max + 1)) / static_cast<float>(getWidth())));
    repaint();
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     RADIO VERTICAL      /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiRadioVertical::paint(Graphics& g)
{
    const float border = 1.f;
    const float extra  = 2.f;
    const float h  = static_cast<float>(getHeight()) / static_cast<float>(max + 1);
    const float hs = h - 2.f * (border + extra);
    const float w = static_cast<float>(getWidth());
    const float ws = w - 2.f * (border + extra);
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.fillRect(border + extra, h * getValueOriginal() + border + extra, ws, hs);
    g.setColour(Colours::black);
    for(size_t i = 1; i < static_cast<size_t>(max) + 1; ++i)
    {
        g.drawLine(0.f, h * static_cast<float>(i), h, h * static_cast<float>(i), border);
    }
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiRadioVertical::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(std::floor(static_cast<float>(e.y * (max + 1)) / static_cast<float>(getHeight())));
    repaint();
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     PANEL               /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiPanel::GuiPanel(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g)
{
    setInterceptsMouseClicks(false, false);
    edited = true;
}

void GuiPanel::paint(Graphics& g)
{
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     COMMENT             /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiComment::GuiComment(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g)
{
    setInterceptsMouseClicks(false, false);
    edited = true;
}

void GuiComment::paint(Graphics& g)
{
    const auto fheight = gui.getFontHeight();
    auto const ft = CamoLookAndFeel::getFont(gui.getFontName()).withPointHeight(fheight);
    g.setFont(ft);
    g.setColour(Colours::black);
    g.drawMultiLineText(gui.getText(), 0, static_cast<int>(ft.getAscent()), getWidth());
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     TEXT EDITOR         /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiTextEditor::GuiTextEditor(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g)
{
    const int border = 1;
    const float fs = static_cast<float>(gui.getFontHeight());
    Font const tf = CamoLookAndFeel::getDefaultFont().withPointHeight(fs);
    
    label.setBounds(2, 0, getWidth() - 2, getHeight() - 1);
    label.setFont(tf);
    label.setMinimumHorizontalScale(1.f);
    label.setJustificationType(Justification::centredLeft);
    label.setBorderSize(BorderSize<int>(border+2, border, border, border));
    label.setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    label.setEditable(false, false);
    label.setInterceptsMouseClicks(false, false);
    label.addListener(this);
    label.setColour(Label::textColourId, Colour(static_cast<uint32>(gui.getForegroundColor())));
    setInterceptsMouseClicks(true, false);
    addAndMakeVisible(label);
}

void GuiTextEditor::labelTextChanged(Label* lbl)
{
    const String strval = lbl->getText();
    if(strval.isNotEmpty())
    {
        startEdition();
        setValueOriginal(static_cast<float>(strval.getDoubleValue()));
        lbl->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
        stopEdition();
    }
}

void GuiTextEditor::editorShown(Label*, TextEditor&)
{
    startEdition();
}

void GuiTextEditor::editorHidden(Label*, TextEditor&)
{
    stopEdition();
}

void GuiTextEditor::updateValue()
{
    if(edited == false)
    {
        float const v = gui.getValue();
        if(v != value)
        {
            value = v;
            label.setText(String(getValueOriginal()), NotificationType::dontSendNotification);
        }
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     NUMBER              /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiNumber::GuiNumber(CamomileEditorMouseManager& p, pd::Gui& g) : GuiTextEditor(p, g)
{
    const float w = static_cast<float>(getWidth());
    const float h = static_cast<float>(getHeight());
    label.setBounds(static_cast<int>(h * 0.5f), static_cast<int>(0.5f),
                    static_cast<int>(w - h * 0.5f), static_cast<int>(h));
}

void GuiNumber::paint(Graphics& g)
{
    const float border = 1.f;
    const float h = static_cast<float>(getHeight());
    const float w = static_cast<float>(getWidth());
    Path p;
    p.startNewSubPath(0.5f, 0.5f);
    p.lineTo(0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h * 0.25f);
    p.lineTo(w - (h * 0.25f), 0.5f);
    p.closeSubPath();
    g.setColour(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.fillPath(p);
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(0.f, 0.f, h * 0.5f, h * 0.5f, border);
    g.drawLine(0.f, h, h * 0.5f, h * 0.5f, border);
    g.setColour(Colours::black);
    g.strokePath(p, PathStrokeType(border));
}

void GuiNumber::mouseDown(const MouseEvent& event)
{
    if(!label.hasKeyboardFocus(true))
    {
        startEdition();
        shift = event.mods.isShiftDown();
        last  = getValueOriginal();
    }
}

void GuiNumber::mouseUp(const MouseEvent& e)
{
    if(!label.hasKeyboardFocus(true))
    {
        stopEdition();
    }
}

void GuiNumber::mouseDrag(const MouseEvent& e)
{
    const float inc = static_cast<float>(-e.getDistanceFromDragStartY());
    if(std::abs(inc) < 1)
    {
        return;
    }
    if(shift)
    {
        setValueOriginal(last + inc * 0.01f);
    }
    else
    {
        setValueOriginal(last + inc);
    }
    label.setText(String(getValueOriginal()), NotificationType::dontSendNotification);
}

void GuiNumber::mouseDoubleClick(const MouseEvent&)
{
    startEdition();
    label.grabKeyboardFocus();
    label.showEditor();
    TextEditor* editor = label.getCurrentTextEditor();
    if(editor)
    {
        editor->setIndents(0, 2);
        editor->setBorder(BorderSize<int>(0));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GATOM NUMBER        /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiAtomNumber::GuiAtomNumber(CamomileEditorMouseManager& p, pd::Gui& g) : GuiTextEditor(p, g)
{
    ;
}

void GuiAtomNumber::paint(Graphics& g)
{
    const float border = 1.f;
    const float h = static_cast<float>(getHeight());
    const float w = static_cast<float>(getWidth());
    const float o = h * 0.25f;
    Path p;
    p.startNewSubPath(0.5f, 0.5f);
    p.lineTo(0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, o);
    p.lineTo(w - o, 0.5f);
    p.closeSubPath();
    g.setColour(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.fillPath(p);
    g.setColour(Colours::black);
    g.strokePath(p, PathStrokeType(border));
}

void GuiAtomNumber::mouseDown(const MouseEvent& event)
{
    if(gui.getNumberOfSteps() == 1)
    {
        startEdition();
        setValueOriginal(static_cast<float>(getValueOriginal() <= std::numeric_limits<float>::epsilon()));
        label.setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    }
    else if(!label.hasKeyboardFocus(true))
    {
        startEdition();
        shift = event.mods.isShiftDown();
        last  = getValueOriginal();
    }
}

void GuiAtomNumber::mouseUp(const MouseEvent& e)
{
    if(gui.getNumberOfSteps() == 1 || !label.hasKeyboardFocus(true))
    {
        stopEdition();
    }
}

void GuiAtomNumber::mouseDrag(const MouseEvent& e)
{
    if(!gui.getNumberOfSteps())
    {
        const float inc = static_cast<float>(-e.getDistanceFromDragStartY());
        if(std::abs(inc) < 1)
        {
            return;
        }
        if(shift)
        {
            setValueOriginal(last + inc * 0.01f);
        }
        else
        {
            setValueOriginal(last + inc);
        }
        label.setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    }
}

void GuiAtomNumber::mouseDoubleClick(const MouseEvent&)
{
    if(!gui.getNumberOfSteps())
    {
        startEdition();
        label.grabKeyboardFocus();
        label.showEditor();
        TextEditor* editor = label.getCurrentTextEditor();
        if(editor)
        {
            editor->setIndents(1, 2);
            editor->setBorder(BorderSize<int>(0));
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GATOM SYMBOL        /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiAtomSymbol::GuiAtomSymbol(CamomileEditorMouseManager& p, pd::Gui& g) : GuiTextEditor(p, g), last(gui.getSymbol())
{
    label.setText(String(last), NotificationType::dontSendNotification);
}

void GuiAtomSymbol::paint(Graphics& g)
{
    const float border = 1.f;
    const float h = static_cast<float>(getHeight());
    const float w = static_cast<float>(getWidth());
    const float o = h * 0.25f;
    Path p;
    p.startNewSubPath(0.5f, 0.5f);
    p.lineTo(0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, o);
    p.lineTo(w - o, 0.5f);
    p.closeSubPath();
    g.setColour(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.fillPath(p);
    g.setColour(Colours::black);
    g.strokePath(p, PathStrokeType(border));
}

void GuiAtomSymbol::mouseDoubleClick(const MouseEvent&)
{
    startEdition();
    label.grabKeyboardFocus();
    label.showEditor();
    TextEditor* editor = label.getCurrentTextEditor();
    if(editor)
    {
        editor->setIndents(1, 2);
        editor->setBorder(BorderSize<int>(0));
    }
}

void GuiAtomSymbol::labelTextChanged(Label* lbl)
{
    const String strval = lbl->getText();
    if(strval.isNotEmpty())
    {
        gui.setSymbol(strval.toStdString());
        lbl->setText(String(gui.getSymbol()), NotificationType::dontSendNotification);
        last = gui.getSymbol();
    }
}

void GuiAtomSymbol::updateValue()
{
    if(edited == false)
    {
        std::string const v = gui.getSymbol();
        if(v != last)
        {
            last = v;
            label.setText(String(last), NotificationType::dontSendNotification);
        }
    }
}

GuiArray::GuiArray(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g),
m_graph(gui.getArray()), m_array(p.getProcessor(), m_graph)
{
    setInterceptsMouseClicks(false, true);
    m_array.setBounds(getLocalBounds());
    addAndMakeVisible(&m_array);
}

void GuiArray::resized()
{
    m_array.setBounds(getLocalBounds());
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GOP               /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiGraphOnParent::GuiGraphOnParent(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g)
{
    setInterceptsMouseClicks(false, true);
    edited = true;
    resized();
}

void GuiGraphOnParent::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), 1);
}

void GuiGraphOnParent::resized()
{
    m_labels.clear();
    m_objects.clear();
    const auto bounds = getLocalBounds().expanded(1);
    for(auto& g : gui.getPatch().getGuis())
    {
        PluginEditorObject* obj = PluginEditorObject::createTyped(patch, g);
        if(obj && bounds.contains(obj->getBounds()))
        {
            Component* label = obj->getLabel();
            addAndMakeVisible(m_objects.add(obj));
            if(label)
            {
                addAndMakeVisible(m_labels.add(label));
            }
        }
    }
}

void GuiGraphOnParent::updateValue()
{
    for(auto object : m_objects) {
        object->updateValue(); }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GRAPHICAL ARRAY      ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GraphicalArray::GraphicalArray(CamomileAudioProcessor& processor, pd::Array& graph) :
m_processor(processor), m_array(graph), m_edited(false)
{
    m_vector.reserve(8192);
    m_temp.reserve(8192);
    try { m_array.read(m_vector); }
    catch(...) { m_error = true; }
    startTimer(100);
    setInterceptsMouseClicks(true, false);
    setOpaque(false);
}

void GraphicalArray::paint(Graphics& g)
{
    if(m_error)
    {
        g.setFont(CamoLookAndFeel::getDefaultFont());
        g.drawText("array " + m_array.getName() + " is invalid", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
    }
    else
    {
        const float h = static_cast<float>(getHeight());
        const float w = static_cast<float>(getWidth());
        if(!m_vector.empty())
        {
            const std::array<float, 2> scale = m_array.getScale();
            if(m_array.isDrawingCurve())
            {
                const float dh = h / (scale[1] - scale[0]);
                const float dw = w / static_cast<float>(m_vector.size() - 1);
                Path p;
                p.startNewSubPath(0, h - (clip(m_vector[0], scale[0], scale[1]) - scale[0]) * dh);
                for(size_t i = 1; i < m_vector.size() - 1; i += 2)
                {
                    const float y1 = h - (clip(m_vector[i-1], scale[0], scale[1]) - scale[0]) * dh;
                    const float y2 = h - (clip(m_vector[i], scale[0], scale[1]) - scale[0]) * dh;
                    const float y3 = h - (clip(m_vector[i+1], scale[0], scale[1]) - scale[0]) * dh;
                    p.cubicTo(static_cast<float>(i-1) * dw, y1,
                              static_cast<float>(i) * dw, y2,
                              static_cast<float>(i+1) * dw, y3);
                }
                g.setColour(Colours::black);
                g.strokePath(p, PathStrokeType(1));
            }
            else if(m_array.isDrawingLine())
            {
                const float dh = h / (scale[1] - scale[0]);
                const float dw = w / static_cast<float>(m_vector.size() - 1);
                Path p;
                p.startNewSubPath(0, h - (clip(m_vector[0], scale[0], scale[1]) - scale[0]) * dh);
                for(size_t i = 1; i < m_vector.size(); ++i)
                {
                    const float y = h - (clip(m_vector[i], scale[0], scale[1]) - scale[0]) * dh;
                    p.lineTo(static_cast<float>(i) * dw, y);
                }
                g.setColour(Colours::black);
                g.strokePath(p, PathStrokeType(1));
            }
            else
            {
                const float dh = h / (scale[1] - scale[0]);
                const float dw = w / static_cast<float>(m_vector.size());
                g.setColour(Colours::black);
                for(size_t i = 0; i < m_vector.size(); ++i)
                {
                    const float y = h - (clip(m_vector[i], scale[0], scale[1]) - scale[0]) * dh;
                    g.drawLine(static_cast<float>(i) * dw, y, static_cast<float>(i+1) * dw, y);
                }
            }
        }
    }
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), 1);
}

void GraphicalArray::mouseDown(const MouseEvent& event)
{
    if(m_error)
        return;
    m_edited = true;
    mouseDrag(event);
}

void GraphicalArray::mouseDrag(const MouseEvent& event)
{
    if(m_error)
        return;
    const float s = static_cast<float>(m_vector.size() - 1);
    const float w = static_cast<float>(getWidth());
    const float h = static_cast<float>(getHeight());
    const float x = static_cast<float>(event.x);
    const float y = static_cast<float>(event.y);
    
    const std::array<float, 2> scale = m_array.getScale();
    const size_t index = static_cast<size_t>(std::round(clip(x / w, 0.f, 1.f) * s));
    m_vector[index] = (1.f - clip(y / h, 0.f, 1.f)) * (scale[1] - scale[0]) + scale[0];
    const CriticalSection& cs = m_processor.getCallbackLock();
    if(cs.tryEnter())
    {
        try { m_array.write(index, m_vector[index]); }
        catch(...) { m_error = true; }
        cs.exit();
    }
    m_processor.enqueueMessages(string_array, m_array.getName(), {});
    repaint();
}

void GraphicalArray::mouseUp(const MouseEvent& event)
{
    if(m_error)
        return;
    m_edited = false;
}

void GraphicalArray::timerCallback()
{
    if(!m_edited)
    {
        m_error = false;
        try { m_array.read(m_temp); }
        catch(...) { m_error = true; }
        if(m_temp != m_vector)
        {
            m_vector.swap(m_temp);
            repaint();
        }
    }
}

size_t GraphicalArray::getArraySize() const noexcept
{
    return m_vector.size();
}


