/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiObject.hpp"
#include "Gui.hpp"
#include <limits>

GuiObject::GuiObject(pd::Gui& g) : gui(g), edited(false), value(g.getValue())
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
    const float min = gui.getMinimum(); const float max = gui.getMaximum();
    value = (min < max) ? std::max(std::min(v, max), min) : std::max(std::min(v, min), max);
    gui.setValue(value);
}

float GuiObject::getValueScaled() const noexcept
{
    const float min = gui.getMinimum(); const float max = gui.getMaximum();
    return (min < max) ? (value - min) / (max - min) : 1.f - (value - max) / (min - max);
}

void GuiObject::setValueScaled(float v)
{
    v = std::max(std::min(value, 1.f), 0.f);
    const float min = gui.getMinimum(); const float max = gui.getMaximum();
    value = (min < max) ? v * (max - min) + min : (1.f - v) * (min - max) + max;
    gui.setValue(value);
}

void GuiObject::startEdition() noexcept
{
    edited = true;
    stopTimer();
    value = gui.getValue();
}

void GuiObject::stopEdition() noexcept
{
    edited = false;
    startTimer(25);
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
    x.setValueScaled(static_cast<float>(std::min(std::max(e.x - 2, 0), x.getWidth() - 4)) /
                     static_cast<float>(x.getWidth() - 4));
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
    x.setValueScaled(static_cast<float>(std::min(std::max(x.getHeight() - e.y - 2, 0), x.getHeight() - 4)) /
                     static_cast<float>(x.getHeight() - 4));
    x.repaint();
}

