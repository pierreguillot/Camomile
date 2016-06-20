/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiComment.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI COMMENT                                      //
// ==================================================================================== //

GuiComment::GuiComment(xpd::object const& cmt) : m_text(cmt.text())
{
    setInterceptsMouseClicks(false, false);
    setWantsKeyboardFocus(false);
    setBounds(cmt.x(), cmt.y(), cmt.width() < 1 ? 360 : cmt.width() * 6, 200);
}

void GuiComment::paint(Graphics& g)
{
    g.setFont(Gui::getFont().withHeight(12));
    g.setColour(Gui::getColorTxt());
    g.drawMultiLineText(m_text, 0, 12, getWidth());
}



