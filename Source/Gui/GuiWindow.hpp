/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_WINDOW__
#define __CAMOMILE_GUI_WINDOW__

#include "InstanceProcessor.hpp"

// ==================================================================================== //
//                                      GUI WINDOW                                      //
// ==================================================================================== //

class GuiWindow : public DocumentWindow
{
public:
    GuiWindow();
    void closeButtonPressed() final;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiWindow)
};


#endif
