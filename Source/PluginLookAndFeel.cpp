/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PluginLookAndFeel.hpp"
#include "PluginEnvironment.h"

CamoLookAndFeel::CamoLookAndFeel()
{    
    setColour(PopupMenu::backgroundColourId, Colours::black);
    setColour(PopupMenu::highlightedBackgroundColourId, Colours::grey);
    setColour(PopupMenu::textColourId, Colours::grey);
    setColour(PopupMenu::highlightedTextColourId, Colours::black);
    
    setColour(TextEditor::backgroundColourId, Colours::lightgrey);
    setColour(TextEditor::outlineColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    setColour(TextEditor::shadowColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    setColour(TextEditor::textColourId, Colours::black.withAlpha(0.5f));
    setColour(TextEditor::highlightColourId,  Colours::black.withAlpha(0.5f));
    setColour(TextEditor::highlightedTextColourId, Colours::black);
    
    setColour(ScrollBar::thumbColourId, Colours::black.withAlpha(0.5f));
    setColour(ScrollBar::trackColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    setColour(ScrollBar::backgroundColourId, Colours::lightgrey);
    
    setColour(Label::textColourId, Colours::black);
    setColour(Label::backgroundColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    setColour(Label::outlineColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    setColour(Label::textWhenEditingColourId, Colours::black);
    setColour(Label::backgroundWhenEditingColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    setColour(Label::outlineWhenEditingColourId, Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    
    setColour(CaretComponent::caretColourId, Colours::black);
}

CamoLookAndFeel::~CamoLookAndFeel()  {}


Font CamoLookAndFeel::getPopupMenuFont()
{
    return getDefaultFont().withHeight(13);
}

Font CamoLookAndFeel::getTabButtonFont(TabBarButton&, float height)
{
    return getDefaultFont().withHeight(height);
}

void CamoLookAndFeel::drawPopupMenuBackground (Graphics& g, int width, int height)
{
    ;
}

void CamoLookAndFeel::drawLabel (Graphics& g, Label& label)
{
    g.fillAll (label.findColour (Label::backgroundColourId));
    
    if (! label.isBeingEdited())
    {
        auto alpha = label.isEnabled() ? 1.0f : 0.5f;
        const Font font (getLabelFont (label));
        
        g.setColour (label.findColour (Label::textColourId).withMultipliedAlpha (alpha));
        g.setFont (font);
        
        Rectangle<int> const textArea (label.getBorderSize().subtractedFrom (label.getLocalBounds()));
        g.drawText (label.getText(), textArea, label.getJustificationType(), false);
        g.setColour (label.findColour (Label::outlineColourId).withMultipliedAlpha (alpha));
    }
    else if (label.isEnabled())
    {
        g.setColour (label.findColour (Label::outlineColourId));
    }
    
    g.drawRect (label.getLocalBounds());
}

Font CamoLookAndFeel::getDefaultFont()
{
    static Font DejaVu = Font(Typeface::createSystemTypefaceFor(BinaryData::DejaVuSansMono_ttf, BinaryData::DejaVuSansMono_ttfSize)).withHeight(12.f);
    return DejaVu;
}

Image const& CamoLookAndFeel::getImage()
{
    static bool loaded = false;
    static Image img;
    if(!loaded && !CamomileEnvironment::getImageName().empty())
    {
        File const f(CamomileEnvironment::getPatchPath() + File::getSeparatorString() + String(CamomileEnvironment::getImageName()));
        if(f.exists())
        {
            img = ImageFileFormat::loadFrom(f);
        }
        loaded = true;
    }
    return img;
}

String const& CamoLookAndFeel::getDescription()
{
    static bool loaded = false;
    static String desc;
    if(!loaded)
    {
        if(CamomileEnvironment::getPatchName() == "Camomile")
        {
            desc = "Hey! Are you in a hurry? You're not supposed to use the plugin like this! The Camomile plugin is a meta plugins. It means that the plugin of the Camomile distribution can't be directly loaded in a digital audio workstation but must be used to generate new plugins associated with Pure Data patches that will be loadable in the digital audio workstations. Please Read the documentation to generate your first plugins.";
        }
        else if(CamomileEnvironment::getPatchDescription().empty())
        {
            desc = "No documentation provided for this patch.";
        }
        else
        {
            File const f(CamomileEnvironment::getPatchPath() + File::getSeparatorString() + String(CamomileEnvironment::getPatchDescription()));
            if(f.exists())
            {
                desc = f.loadFileAsString();
            }
            else
            {
                desc = CamomileEnvironment::getPatchDescription();
            }
        }
        loaded = true;
    }
    return desc;
}

