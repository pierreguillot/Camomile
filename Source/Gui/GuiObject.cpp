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

GuiObject::GuiObject(GuiPatch& p, pd::Gui& g) : gui(g), patch(p), edited(false),
value(g.getValue()), min(g.getMinimum()), max(g.getMaximum()), font(getPdFont())
{
    std::array<int, 4> const bounds(gui.getBounds());
    
    setBounds(int(bounds[0]), int(bounds[1]), int(bounds[2]), int(bounds[3]));
    if(gui.getType() == pd::Gui::Type::Toggle)
    {
        metpaint = GuiObject::paintToggle;
        metmousedown = GuiObject::mouseDownToggle;
    }
    else if(gui.getType() == pd::Gui::Type::VerticalSlider)
    {
        metpaint = GuiObject::paintSliderVertical;
        metmousedown = GuiObject::mouseDownSliderVertical;
        metmousedrag = GuiObject::mouseDragSliderVertical;
        metmouseup = GuiObject::mouseUpSlider;
    }
    else if(gui.getType() == pd::Gui::Type::HorizontalSlider)
    {
        metpaint = GuiObject::paintSliderHorizontal;
        metmousedown = GuiObject::mouseDownSliderHorizontal;
        metmousedrag = GuiObject::mouseDragSliderHorizontal;
        metmouseup = GuiObject::mouseUpSlider;
    }
    else if(gui.getType() == pd::Gui::Type::VerticalRadio)
    {
        metpaint = GuiObject::paintRadioVertical;
        metmousedown = GuiObject::mouseDownRadioVertical;
    }
    else if(gui.getType() == pd::Gui::Type::HorizontalRadio)
    {
        metpaint = GuiObject::paintRadioHorizontal;
        metmousedown = GuiObject::mouseDownRadioHorizontal;
    }
    else if(gui.getType() == pd::Gui::Type::Bang)
    {
        metpaint = GuiObject::paintBang;
        metmousedown = GuiObject::mouseDownBang;
        metmouseup = GuiObject::mouseUpBang;
    }
    else if(gui.getType() == pd::Gui::Type::Panel)
    {
        metpaint = GuiObject::paintPanel;
        setSize(gui.getPanelSize()[0], gui.getPanelSize()[1]);
    }
    else if(gui.getType() == pd::Gui::Type::Comment)
    {
        metpaint = GuiObject::paintComment;
        setBounds(int(bounds[0]), int(bounds[1]), bounds[2] < 1.f ? 360 : bounds[2] * 6, 200);
        font.setHeight(gui.getFontSize() + 2);
        setInterceptsMouseClicks(false, false);
    }
    else if(gui.getType() == pd::Gui::Type::Number)
    {
        const float border = 1.f;
        const float w = getWidth();
        const float h = getHeight();
        const float fs = gui.getFontSize() + 2;
        metpaint = GuiObject::paintNumber;
        metmousedown = GuiObject::mouseDownNumber;
        metmousedrag = GuiObject::mouseDragNumber;
        metmouseup = GuiObject::mouseUpNumber;
        
        Font const tf = font.withHeight(fs);
        label = new Label();
        label->setBounds(h * 0.5f, 0.5f, w - h * 0.5f, h);
        label->setFont(tf);
        label->setJustificationType(Justification::centredLeft);
        label->setBorderSize(BorderSize<int>(border+1, border, border, border));
        label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
        label->setEditable(false, false);
        label->setInterceptsMouseClicks(false, false);
        label->addListener(this);
        label->setColour(Label::textColourId, Colour(static_cast<uint32>(gui.getForegroundColor())));
        setInterceptsMouseClicks(true, false);
        addAndMakeVisible(label);
    }
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

void GuiObject::paint(Graphics& g)
{
    if(metpaint)
    {
        metpaint(*this, g);
    }
}

void GuiObject::mouseDown(const MouseEvent& e)
{
    if(metmousedown)
    {
        metmousedown(*this, e);
    }
}

void GuiObject::mouseDrag(const MouseEvent& e)
{
    if(metmousedrag)
    {
        metmousedrag(*this, e);
    }
}

void GuiObject::mouseUp(const MouseEvent& e)
{
    if(metmouseup)
    {
        metmouseup(*this, e);
    }
}

void GuiObject::timerCallback()
{
    float const v = gui.getValue();
    if(edited == false && v != value)
    {
        value = v;
        if(label)
        {
            label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
        }
        else
        {
            repaint();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::mouseDoubleClick(const MouseEvent&)
{
    if(gui.getType() == pd::Gui::Type::Number)
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
}

void GuiObject::labelTextChanged(Label* label)
{
    const String value = label->getText();
    if(value.isNotEmpty())
    {
        setValueOriginal(value.getDoubleValue());
        label->setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    }
}

void GuiObject::editorShown(Label*, TextEditor&)
{
    startEdition();
}

void GuiObject::editorHidden(Label*, TextEditor&)
{
    stopEdition();
}

void GuiObject::paintNumber(GuiObject& x, Graphics& g)
{
    const float border = 1.f;
    const float h = static_cast<float>(x.getHeight());
    const float w = static_cast<float>(x.getWidth());
    Path p;
    p.startNewSubPath(0.5f, 0.5f);
    p.lineTo(0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h * 0.25f);
    p.lineTo(w - (h * 0.25f), 0.5f);
    p.closeSubPath();
    g.setColour(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
    g.fillPath(p);
    g.setColour(Colour(static_cast<uint32>(x.gui.getForegroundColor())));
    g.drawLine(0.f, 0.f, h * 0.5f, h * 0.5f, border);
    g.drawLine(0.f, h, h * 0.5f, h * 0.5f, border);
    g.setColour(Colours::black);
    g.strokePath(p, PathStrokeType(border));
}

void GuiObject::mouseDownNumber(GuiObject& x, const MouseEvent& event)
{
    if(!x.label->hasKeyboardFocus(true))
    {
        x.startEdition();
        x.shift = event.mods.isShiftDown();
    }
}

void GuiObject::mouseUpNumber(GuiObject& x, const MouseEvent& e)
{
    if(!x.label->hasKeyboardFocus(true))
    {
        x.stopEdition();
    }
}

void GuiObject::mouseDragNumber(GuiObject& x, const MouseEvent& e)
{
    if(x.shift)
    {
        x.setValueOriginal(x.getValueOriginal() + float(e.getDistanceFromDragStartY()) / -100.f);
    }
    else
    {
        x.setValueOriginal(x.getValueOriginal() + float(e.getDistanceFromDragStartY()) / -10.f);
    }
    x.label->setText(String(x.getValueOriginal()), NotificationType::dontSendNotification);
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintToggle(GuiObject& x, Graphics& g)
{
    const float border = 1.f;
    g.fillAll(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
    if(x.getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        const float w = static_cast<float>(x.getWidth() - border * 2);
        g.setColour(Colour(static_cast<uint32>(x.gui.getForegroundColor())));
        g.drawLine(1.f + border, 1.f + border, w, w, border);
        g.drawLine(w, 1.f + border, 1.f + border, w, border);
    }
    g.setColour(Colours::black);
    g.drawRect(x.getLocalBounds(), border);
}

void GuiObject::mouseDownToggle(GuiObject& x, const MouseEvent& event)
{
    x.startEdition();
    x.setValueOriginal(1.f - x.getValueOriginal());
    x.repaint();
    x.stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::mouseUpSlider(GuiObject& x, const MouseEvent& e)
{
    x.stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintSliderHorizontal(GuiObject& x, Graphics& g)
{
    const float border = 1.f;
    const float cursor = 3.f;
    const float w = static_cast<float>(x.getWidth() - border * 2);
    const float h = static_cast<float>(x.getHeight() - border * 2);
    const float pos = x.getValueScaled() * (w - cursor - border) + cursor;
    g.fillAll(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(x.gui.getForegroundColor())));
    g.drawLine(pos, border + 0.5f, pos, h + 0.5f, cursor);
    
    g.setColour(Colours::black);
    g.drawRect(x.getLocalBounds(), border);
}

void GuiObject::mouseDownSliderHorizontal(GuiObject& x, const MouseEvent& e)
{
    x.startEdition();
    mouseDragSliderHorizontal(x, e);
}

void GuiObject::mouseDragSliderHorizontal(GuiObject& x, const MouseEvent& e)
{
    x.setValueScaled(static_cast<float>(e.x - 2) / static_cast<float>(x.getWidth() - 4));
    x.repaint();
}


//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintSliderVertical(GuiObject& x, Graphics& g)
{
    const float border = 1.f;
    const float cursor = 3.f;
    const float w = static_cast<float>(x.getWidth() - border * 2);
    const float h = static_cast<float>(x.getHeight() - border * 2);
    const float pos = (1.f - x.getValueScaled()) * (h - cursor - border) + cursor;
    g.fillAll(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(x.gui.getForegroundColor())));
    g.drawLine(border + 0.5f, pos, w + 0.5f, pos, cursor);
    g.setColour(Colours::black);
    g.drawRect(x.getLocalBounds(), border);
}

void GuiObject::mouseDownSliderVertical(GuiObject& x, const MouseEvent& e)
{
    x.startEdition();
    mouseDragSliderVertical(x, e);
}

void GuiObject::mouseDragSliderVertical(GuiObject& x, const MouseEvent& e)
{
    x.setValueScaled(static_cast<float>(x.getHeight() - e.y - 2) / static_cast<float>(x.getHeight() - 4));
    x.repaint();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintRadioHorizontal(GuiObject& x, Graphics& g)
{
    const float border = 1.f;
    const float extra  = 2.f;
    const float h  = static_cast<float>(x.getHeight());
    const float hs = h - 2.f * (border + extra);
    const float w = static_cast<float>(x.getWidth()) / static_cast<float>(x.max + 1);
    const float ws = w - 2.f * (border + extra);
    g.fillAll(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(x.gui.getForegroundColor())));
    g.fillRect(w * x.getValueOriginal() + border + extra, border + extra, ws, hs);
    g.setColour(Colours::black);
    for(size_t i = 1; i < size_t(x.max) + 1; ++i)
    {
        g.drawLine(w * static_cast<float>(i), 0.f, w * static_cast<float>(i), w, border);
    }
    g.drawRect(x.getLocalBounds(), border);
}

void GuiObject::mouseDownRadioHorizontal(GuiObject& x, const MouseEvent& e)
{
    x.startEdition();
    x.setValueOriginal(std::floor(static_cast<float>(e.x * (x.max + 1)) / static_cast<float>(x.getWidth())));
    x.repaint();
    x.stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintRadioVertical(GuiObject& x, Graphics& g)
{
    const float border = 1.f;
    const float extra  = 2.f;
    const float h  = static_cast<float>(x.getHeight()) / static_cast<float>(x.max + 1);
    const float hs = h - 2.f * (border + extra);
    const float w = static_cast<float>(x.getWidth());
    const float ws = w - 2.f * (border + extra);
    g.fillAll(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(x.gui.getForegroundColor())));
    g.fillRect(border + extra, h * x.getValueOriginal() + border + extra, ws, hs);
    g.setColour(Colours::black);
    for(size_t i = 1; i < static_cast<size_t>(x.max) + 1; ++i)
    {
        g.drawLine(0.f, h * static_cast<float>(i), h, h * static_cast<float>(i), border);
    }
    g.drawRect(x.getLocalBounds(), border);
}

void GuiObject::mouseDownRadioVertical(GuiObject& x, const MouseEvent& e)
{
    x.startEdition();
    x.setValueOriginal(std::floor(static_cast<float>(e.y * (x.max + 1)) / static_cast<float>(x.getHeight())));
    x.repaint();
    x.stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintBang(GuiObject& x, Graphics& g)
{
    const float border = 1.f;
    const float w = static_cast<float>(x.getWidth() - border * 2);
    g.fillAll(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
    if(x.getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        g.setColour(Colour(static_cast<uint32>(x.gui.getForegroundColor())));
        g.fillEllipse(border, border, w, w);
    }
    g.setColour(Colours::black);
    g.drawEllipse(border, border, w, w, border);
    g.drawRect(x.getLocalBounds(), border);
}

void GuiObject::mouseDownBang(GuiObject& x, const MouseEvent& e)
{
    x.startEdition();
    x.setValueOriginal(1);
    x.repaint();
    x.stopEdition();
}

void GuiObject::mouseUpBang(GuiObject& x, const MouseEvent& e)
{
    if(x.getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        x.repaint();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintPanel(GuiObject& x, Graphics& g)
{
    g.fillAll(Colour(static_cast<uint32>(x.gui.getBackgroundColor())));
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintComment(GuiObject& x, Graphics& g)
{
    g.setFont(x.font);
    g.setColour(Colours::black);
    g.drawMultiLineText(x.gui.getText(), 0, x.gui.getFontSize(), x.getWidth());
}


