/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiNumbox.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

GuiNumbox::GuiNumbox(InstanceProcessor& processor, pd::Gui const& gui) : GuiParameter(processor, gui)
{
    Rectangle<int> bounds(getLocalBounds());
    m_label = new Label(String());
    m_label->setBounds(bounds.getHeight() / 2, 0, bounds.getWidth() - bounds.getHeight() / 2, bounds.getHeight());
    m_label->setFont(GuiParameter::getFont());
    m_label->setColour(Label::textColourId, GuiParameter::getColorTxt());
    m_label->setColour(Label::backgroundColourId, GuiParameter::getColorInv());
    m_label->setColour(Label::outlineColourId, GuiParameter::getColorInv());
    m_label->setColour(Label::textWhenEditingColourId, GuiParameter::getColorTxt());
    m_label->setColour(Label::backgroundWhenEditingColourId, GuiParameter::getColorInv());
    m_label->setColour(Label::outlineWhenEditingColourId, GuiParameter::getColorInv());
    m_label->setBorderSize(BorderSize<int>(GuiParameter::getBordersize()+1, GuiParameter::getBordersize(), GuiParameter::getBordersize(), GuiParameter::getBordersize()));
    m_label->setText(String(getValue()), NotificationType::dontSendNotification);
    m_label->setEditable(false, false);
    m_label->setInterceptsMouseClicks(false, false);
    m_label->addListener(this);
    setInterceptsMouseClicks(true, false);
    addAndMakeVisible(m_label);
}

void GuiNumbox::paint(Graphics& g)
{
    g.fillAll(GuiParameter::getColorBg());
    g.setColour(GuiParameter::getColorBd());
    g.drawRect(getLocalBounds(), GuiParameter::getBordersize());
    g.drawLine(0.f, 0.f, float(getHeight()) * 0.5f, float(getHeight()) * 0.5f, GuiParameter::getBordersize());
    g.drawLine(0.f, float(getHeight()), float(getHeight()) * 0.5f, float(getHeight()) * 0.5f, GuiParameter::getBordersize());
}

void GuiNumbox::mouseDown(const MouseEvent& event)
{
    startEdition();
    m_shift = event.mods.isShiftDown();
    m_value = getValue();
}

void GuiNumbox::mouseDrag(const MouseEvent& event)
{
    if(m_shift)
    {
        setValue(m_value + float(event.getDistanceFromDragStartY()) / -100.f);
    }
    else
    {
        setValue(m_value + float(event.getDistanceFromDragStartY()) / -10.f);
    }
    
    m_label->setText(String(getValue()), NotificationType::dontSendNotification);
}

void GuiNumbox::mouseUp(const MouseEvent& event)
{
    stopEdition();
}

void GuiNumbox::mouseDoubleClick(const MouseEvent&)
{
    m_label->showEditor();
}

void GuiNumbox::labelTextChanged(Label* label)
{
    const String value = label->getText();
    if(value.isNotEmpty())
    {
        setValue(value.getDoubleValue());
        label->setText(String(getValue()), NotificationType::dontSendNotification);
    }
}

void GuiNumbox::editorShown(Label*, TextEditor&)
{
    startEdition();
}

void GuiNumbox::editorHidden(Label*, TextEditor&)
{
    stopEdition();
}

