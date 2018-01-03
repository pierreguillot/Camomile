/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiObject.hpp"

static Font getPdFont() {
    static Font DejaVu = Font(Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansMono_ttf, BinaryData::DejaVuSansMono_ttfSize)).withHeight(12.f);
    return DejaVu;
}

GuiObject* GuiObject::createTyped(GuiPatch& p, pd::Gui& g)
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
    return new GuiObject(p, g);
}

GuiObject::GuiObject(GuiPatch& p, pd::Gui& g) : gui(g), patch(p), edited(false),
value(g.getValue()), min(g.getMinimum()), max(g.getMaximum())
{
    std::array<int, 4> const bounds(gui.getBounds());
    setBounds(bounds[0], bounds[1], bounds[2], bounds[3]);
    setOpaque(false);
    startTimer(25);
}

float GuiObject::getValueOriginal() const noexcept
{
    return value;
}

void GuiObject::setValueOriginal(float v)
{
    value = (min < max) ? std::max(std::min(v, max), min) : std::max(std::min(v, min), max);
    gui.setValue(value);
    patch.performEdition();
}

float GuiObject::getValueScaled() const noexcept
{
    return (min < max) ? (value - min) / (max - min) : 1.f - (value - max) / (min - max);
}

void GuiObject::setValueScaled(float v)
{
    value = (min < max) ? std::max(std::min(v, 1.f), 0.f) * (max - min) + min
                        : (1.f - std::max(std::min(v, 1.f), 0.f)) * (min - max) + max;
    gui.setValue(value);
    patch.performEdition();
}

void GuiObject::startEdition() noexcept
{
    patch.startEdition();
    edited = true;
    stopTimer();
    value = gui.getValue();
}

void GuiObject::stopEdition() noexcept
{
    edited = false;
    startTimer(25);
    patch.stopEdition();
}

void GuiObject::timerCallback()
{
    float const v = gui.getValue();
    if(edited == false && v != value)
    {
        value = v;
        repaint();
    }
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
    g.drawRect(getLocalBounds(), border);
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
        const float w = static_cast<float>(getWidth() - border * 2);
        g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
        g.drawLine(1.f + border, 1.f + border, w, w, border);
        g.drawLine(w, 1.f + border, 1.f + border, w, border);
    }
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), border);
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
    const float cursor = 3.f;
    const float w = static_cast<float>(getWidth() - border * 2);
    const float h = static_cast<float>(getHeight() - border * 2);
    const float pos = getValueScaled() * (w - cursor - border) + cursor;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(pos, border + 0.5f, pos, h + 0.5f, cursor);
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), border);
}

void GuiSliderHorizontal::mouseDown(const MouseEvent& e)
{
    startEdition();
    mouseDrag(e);
}

void GuiSliderHorizontal::mouseDrag(const MouseEvent& e)
{
    setValueScaled(static_cast<float>(e.x - 2) / static_cast<float>(getWidth() - 4));
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
    const float cursor = 3.f;
    const float w = static_cast<float>(getWidth() - border * 2);
    const float h = static_cast<float>(getHeight() - border * 2);
    const float pos = (1.f - getValueScaled()) * (h - cursor - border) + cursor;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(border + 0.5f, pos, w + 0.5f, pos, cursor);
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), border);
}

void GuiSliderVertical::mouseDown(const MouseEvent& e)
{
    startEdition();
    mouseDrag(e);
}

void GuiSliderVertical::mouseDrag(const MouseEvent& e)
{
    setValueScaled(static_cast<float>(getHeight() - e.y - 2) / static_cast<float>(getHeight() - 4));
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
    g.drawRect(getLocalBounds(), border);
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
    g.drawRect(getLocalBounds(), border);
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

GuiPanel::GuiPanel(GuiPatch& p, pd::Gui& g) : GuiObject(p, g)
{
    setInterceptsMouseClicks(false, false);
    stopTimer();
}

void GuiPanel::paint(Graphics& g)
{
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     COMMENT             /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiComment::GuiComment(GuiPatch& p, pd::Gui& g) : GuiObject(p, g)
{
    setInterceptsMouseClicks(false, false);
    stopTimer();
}

void GuiComment::paint(Graphics& g)
{
    g.setFont(getPdFont().withHeight(gui.getFontSize()));
    g.setColour(Colours::black);
    g.drawMultiLineText(gui.getText(), 0, gui.getFontSize(), getWidth());
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     TEXT EDITOR         /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiTextEditor::GuiTextEditor(GuiPatch& p, pd::Gui& g) : GuiObject(p, g)
{
    const float border = 1.f;
    const float fs = gui.getFontSize();
    Font const tf = getPdFont().withHeight(fs);
    
    label = new Label();
    label->setBounds(2.5f, 0.5f, getWidth() - 2.5f, getHeight() - 1.f);
    label->setFont(tf);
    label->setJustificationType(Justification::centredLeft);
    label->setBorderSize(BorderSize<int>(border+2, border, border, border));
    label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    label->setEditable(false, false);
    label->setInterceptsMouseClicks(false, false);
    label->addListener(this);
    label->setColour(Label::textColourId, Colour(static_cast<uint32>(gui.getForegroundColor())));
    setInterceptsMouseClicks(true, false);
    addAndMakeVisible(label);
}

void GuiTextEditor::labelTextChanged(Label* label)
{
    const String value = label->getText();
    if(value.isNotEmpty())
    {
        setValueOriginal(value.getDoubleValue());
        label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
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

void GuiTextEditor::timerCallback()
{
    float const v = gui.getValue();
    if(edited == false && v != value)
    {
        value = v;
        label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     NUMBER              /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiNumber::GuiNumber(GuiPatch& p, pd::Gui& g) : GuiTextEditor(p, g)
{
    const float w = getWidth();
    const float h = getHeight();
    label->setBounds(h * 0.5f, 0.5f, w - h * 0.5f, h);
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
    if(!label->hasKeyboardFocus(true))
    {
        startEdition();
        shift = event.mods.isShiftDown();
        last  = getValueOriginal();
    }
}

void GuiNumber::mouseUp(const MouseEvent& e)
{
    if(!label->hasKeyboardFocus(true))
    {
        stopEdition();
    }
}

void GuiNumber::mouseDrag(const MouseEvent& e)
{
    const float inc = static_cast<float>(-e.getDistanceFromDragStartY());
    if(shift)
    {
        setValueOriginal(last + inc * 0.1f);
    }
    else
    {
        setValueOriginal(last + inc);
    }
    label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
}

void GuiNumber::mouseDoubleClick(const MouseEvent&)
{
    startEdition();
    label->grabKeyboardFocus();
    label->showEditor();
    TextEditor* editor = label->getCurrentTextEditor();
    if(editor)
    {
        editor->setIndents(0, 2);
        editor->setBorder(BorderSize<int>(0));
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GATOM NUMBER        /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiAtomNumber::GuiAtomNumber(GuiPatch& p, pd::Gui& g) : GuiTextEditor(p, g)
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
        label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    }
    else if(!label->hasKeyboardFocus(true))
    {
        startEdition();
        shift = event.mods.isShiftDown();
        last  = getValueOriginal();
    }
}

void GuiAtomNumber::mouseUp(const MouseEvent& e)
{
    if(gui.getNumberOfSteps() == 1 || !label->hasKeyboardFocus(true))
    {
        stopEdition();
    }
}

void GuiAtomNumber::mouseDrag(const MouseEvent& e)
{
    if(!gui.getNumberOfSteps())
    {
        const float inc = static_cast<float>(-e.getDistanceFromDragStartY());
        if(shift)
        {
            setValueOriginal(last + inc * 0.1f);
        }
        else
        {
            setValueOriginal(last + inc);
        }
        label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    }
}

void GuiAtomNumber::mouseDoubleClick(const MouseEvent&)
{
    if(!gui.getNumberOfSteps())
    {
        startEdition();
        label->grabKeyboardFocus();
        label->showEditor();
        TextEditor* editor = label->getCurrentTextEditor();
        if(editor)
        {
            editor->setIndents(0.5, 2);
            editor->setBorder(BorderSize<int>(0));
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GATOM SYMBOL        /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiAtomSymbol::GuiAtomSymbol(GuiPatch& p, pd::Gui& g) : GuiTextEditor(p, g)
{
    last = gui.getSymbol();
    label->setText(String(last), NotificationType::dontSendNotification);
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
    label->grabKeyboardFocus();
    label->showEditor();
    TextEditor* editor = label->getCurrentTextEditor();
    if(editor)
    {
        editor->setIndents(0.5, 2);
        editor->setBorder(BorderSize<int>(0));
    }
}

void GuiAtomSymbol::labelTextChanged(Label* label)
{
    const String value = label->getText();
    if(value.isNotEmpty())
    {
        gui.setSymbol(value.toStdString());
        patch.performEdition();
        label->setText(String(gui.getSymbol()), NotificationType::dontSendNotification);
        last = gui.getSymbol();
    }
}

void GuiAtomSymbol::timerCallback()
{
    std::string const v = gui.getSymbol();
    if(edited == false && v != last)
    {
        last = v;
        label->setText(String(last), NotificationType::dontSendNotification);
    }
}




