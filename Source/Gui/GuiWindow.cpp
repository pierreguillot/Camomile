/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiWindow.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI WINDOW                                      //
// ==================================================================================== //

GuiWindow::GuiWindow() :
DocumentWindow(String(""), Gui::getColorBg(), DocumentWindow::closeButton, false)
{
    setUsingNativeTitleBar(true);
    setBounds(50, 50, 300, 370);
    setResizable(false, false);
    setAlwaysOnTop(false);
    setDropShadowEnabled(true);
    setVisible(true);
    setBackgroundColour(Gui::getColorBg());
}

void GuiWindow::closeButtonPressed()
{
    removeFromDesktop();
}
