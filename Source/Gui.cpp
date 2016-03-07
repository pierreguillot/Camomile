/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Gui.hpp"

// ==================================================================================== //
//                                          GUI                                         //
// ==================================================================================== //

Font Gui::getFont()
{
    return Font(String("Monaco"), 13.f, juce::Font::plain);
}

int Gui::getBordersize() noexcept
{
    return 1;
}

Colour const& Gui::getColorBg() noexcept
{
    return Colours::lightgrey;
}

Colour const& Gui::getColorBd() noexcept
{
    return Colours::darkgrey;
}

Colour const& Gui::getColorTxt() noexcept
{
    return Colours::darkgrey;
}

Colour const& Gui::getColorInv() noexcept
{
    static Colour c(Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
    return c;
}






