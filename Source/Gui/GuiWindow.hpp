/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

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

