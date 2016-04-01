/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_ABOUT__
#define __CAMOMILE_GUI_ABOUT__

#include "../InstanceProcessor.hpp"

// ==================================================================================== //
//                                      GUI ABOUT                                       //
// ==================================================================================== //

class GuiAbout : public Component
{
public:
    GuiAbout();
private:
    juce::TextEditor m_text;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiAbout)
};


#endif
