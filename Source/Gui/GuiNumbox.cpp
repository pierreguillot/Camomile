/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiNumbox.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

GuiNumbox::GuiNumbox(InstanceProcessor& processor, xpd::Gui const& gui) : GuiParameter(processor, gui)
{
    Rectangle<int> bounds(getLocalBounds());
    m_label.setBounds(bounds.getHeight() / 2, 0, bounds.getWidth() - bounds.getHeight() / 2, bounds.getHeight());
    m_label.setFont(Gui::getFont());
    m_label.setColour(Label::textColourId, Gui::getColorTxt());
    m_label.setColour(Label::backgroundColourId, Gui::getColorInv());
    m_label.setColour(Label::outlineColourId, Gui::getColorInv());
    m_label.setColour(Label::textWhenEditingColourId, Gui::getColorTxt());
    m_label.setColour(Label::backgroundWhenEditingColourId, Gui::getColorInv());
    m_label.setColour(Label::outlineWhenEditingColourId, Gui::getColorInv());
    m_label.setBorderSize(BorderSize<int>(Gui::getBorderSize()+1,Gui::getBorderSize(),Gui::getBorderSize(),Gui::getBorderSize()));
    m_label.setText(String(getValue()), NotificationType::dontSendNotification);
    m_label.setEditable(false, false);
    m_label.setInterceptsMouseClicks(false, false);
    m_label.addListener(this);
    setInterceptsMouseClicks(true, false);
    addAndMakeVisible(m_label);
}

void GuiNumbox::paint(Graphics& g)
{
    g.fillAll(Gui::getColorBg());
    g.setColour(Gui::getColorBd());
    g.drawRect(getLocalBounds(), Gui::getBorderSize());
    g.drawLine(0.f, 0.f, float(getHeight()) * 0.5f, float(getHeight()) * 0.5f, Gui::getBorderSize());
    g.drawLine(0.f, float(getHeight()), float(getHeight()) * 0.5f, float(getHeight()) * 0.5f, Gui::getBorderSize());
    if(!m_label.hasKeyboardFocus(true))
    {
        m_label.setText(String(getValue()), NotificationType::dontSendNotification);        
    }
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
    
    m_label.setText(String(getValue()), NotificationType::dontSendNotification);
}

void GuiNumbox::mouseUp(const MouseEvent& event)
{
    if(m_label.isBeingEdited() && !m_label.hasKeyboardFocus(true))
    {
        stopEdition();
    }
}

void GuiNumbox::mouseDoubleClick(const MouseEvent&)
{
    startEdition();
    m_label.grabKeyboardFocus();
    m_label.showEditor();
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

