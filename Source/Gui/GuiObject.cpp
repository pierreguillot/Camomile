/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiObject.hpp"
#include "Gui.hpp"
#include <limits>

GuiObject::GuiObject(GuiPatch& p, pd::Gui& g) : gui(g), patch(p), edited(false),
value(g.getValue()), min(g.getMinimum()), max(g.getMaximum())
{
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
    }
    else if(gui.getType() == pd::Gui::Type::Panel)
    {
        metpaint = GuiObject::paintPanel;
    }
    
    std::array<int, 4> const bounds(gui.getBounds());
    setBounds(int(bounds[0]), int(bounds[1]), int(bounds[2]), int(bounds[3]));
    setOpaque(true);
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
        repaint();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintToggle(GuiObject& x, Graphics& g)
{
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(x.getLocalBounds(), Gui::getBorderSize());
    if(x.getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        g.drawLine(0.f, 0.f, static_cast<float>(x.getWidth()), static_cast<float>(x.getHeight()), Gui::getBorderSize());
        g.drawLine(static_cast<float>(x.getWidth()), 0.f, 0.f, static_cast<float>(x.getHeight()), Gui::getBorderSize());
    }
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
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(x.getLocalBounds(), Gui::getBorderSize());
    const float pos = x.getValueScaled() * static_cast<float>(x.getWidth() - 4) + 2.f;
    g.drawLine(pos, 0.f, pos, static_cast<float>(x.getHeight()), Gui::getBorderSize());
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
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(x.getLocalBounds(), Gui::getBorderSize());
    const float pos = (1.f - x.getValueScaled())* static_cast<float>(x.getHeight() - 4) + 2.f;
    g.drawLine(0.f, pos, static_cast<float>(x.getWidth()), pos, Gui::getBorderSize());
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
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(x.getLocalBounds(), Gui::getBorderSize());
    const float w = static_cast<float>(x.getHeight());
    for(size_t i = 1; i < size_t(x.max) + 1; ++i)
    {
        g.drawLine(w * float(i), 0.f, w * float(i), w, Gui::getBorderSize());
    }
    const float o = std::max(w * 0.125f, Gui::getBorderSize() + 1.f);
    const float l = w - o * 2.f;
    g.fillRect(w * x.getValueOriginal() + o, o, l, l);
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
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(x.getLocalBounds(), Gui::getBorderSize());
    const float w = static_cast<float>(x.getWidth());
    for(size_t i = 1; i < size_t(x.max) + 1; ++i)
    {
        g.drawLine(0.f, w * float(i), w, w * float(i), Gui::getBorderSize());
    }
    const float o = std::max(w * 0.125f, Gui::getBorderSize() + 1.f);
    const float l = w - o * 2.f;
    g.fillRect(o, w * x.getValueOriginal() + o, l, l);
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
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(x.getLocalBounds(), Gui::getBorderSize());
    const float w = static_cast<float>(x.getWidth() - Gui::getBorderSize() * 2);
    const float o = w * 0.125f;
    if(x.getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        g.fillEllipse(o + Gui::getBorderSize(), o + Gui::getBorderSize(), o * 6.f, o * 6.f);
    }
    else
    {
        
        g.drawEllipse(o + Gui::getBorderSize(), o + Gui::getBorderSize(), o * 6.f, o * 6.f, Gui::getBorderSize());
    }
}

void GuiObject::mouseDownBang(GuiObject& x, const MouseEvent& g)
{
    x.startEdition();
    x.setValueOriginal(1);
    x.repaint();
    x.stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiObject::paintPanel(GuiObject& x, Graphics& g)
{
    g.fillAll(Gui::getColorBg());
}



