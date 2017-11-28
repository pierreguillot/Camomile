/*
  ==============================================================================

   This file is part of the JUCE library.
   Copyright (c) 2015 - ROLI Ltd.

   Permission is granted to use this software under the terms of either:
   a) the GPL v2 (or any later version)
   b) the Affero GPL v3

   Details of these licenses can be found at: www.gnu.org/licenses

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

   ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.juce.com for more information.

  ==============================================================================
*/

#include "LookAndFeel.hpp"
#include "Gui.hpp"

CamoLookAndFeel::CamoLookAndFeel()
{    
    setColour(PopupMenu::backgroundColourId, Gui::getColorBg());
    setColour(PopupMenu::highlightedBackgroundColourId, Gui::getColorBg());
    setColour(PopupMenu::textColourId, Gui::getColorTxt().withAlpha(0.5f));
    setColour(PopupMenu::highlightedTextColourId, Gui::getColorTxt());
    
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

void CamoLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    g.fillAll(Gui::getColorBg());
}


