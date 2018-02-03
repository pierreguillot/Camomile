/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "LookAndFeel.hpp"
#include "Gui.hpp"

CamoLookAndFeel::CamoLookAndFeel()
{    
    setColour(PopupMenu::backgroundColourId, Colours::black);
    setColour(PopupMenu::highlightedBackgroundColourId, Colours::grey);
    setColour(PopupMenu::textColourId, Colours::grey);
    setColour(PopupMenu::highlightedTextColourId, Colours::black);
    
    setColour(TextEditor::backgroundColourId, Gui::getColorBg());
    setColour(TextEditor::outlineColourId, Gui::getColorInv());
    setColour(TextEditor::shadowColourId,Gui::getColorInv());
    setColour(TextEditor::textColourId, Gui::getColorTxt().withAlpha(0.5f));
    setColour(TextEditor::highlightColourId,  Gui::getColorTxt().withAlpha(0.5f));
    setColour(TextEditor::highlightedTextColourId, Gui::getColorTxt());
    
    setColour(ScrollBar::thumbColourId, Gui::getColorTxt().withAlpha(0.5f));
    setColour(ScrollBar::trackColourId,Gui::getColorInv());
    setColour(ScrollBar::backgroundColourId, Gui::getColorBg());
    
    setColour(Label::textColourId, Gui::getColorTxt());
    setColour(Label::backgroundColourId, Gui::getColorInv());
    setColour(Label::outlineColourId, Gui::getColorInv());
    setColour(Label::textWhenEditingColourId, Gui::getColorTxt());
    setColour(Label::backgroundWhenEditingColourId, Gui::getColorInv());
    setColour(Label::outlineWhenEditingColourId, Gui::getColorInv());
    
    setColour(CaretComponent::caretColourId, Gui::getColorTxt());
}

CamoLookAndFeel::~CamoLookAndFeel()  {}


Font CamoLookAndFeel::getPopupMenuFont()
{
    return Gui::getFont().withHeight(13);
}

Font CamoLookAndFeel::getTabButtonFont(TabBarButton&, float height)
{
    return Gui::getFont().withHeight(height);
}

void CamoLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    ;
}


