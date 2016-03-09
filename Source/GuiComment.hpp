/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_COMMENT__
#define __CAMOMILE_GUI_COMMENT__

#include "GuiParameter.hpp"

// ==================================================================================== //
//                                      GUI COMMENT                                     //
// ==================================================================================== //

class GuiComment : public Component
{
public:
    GuiComment(pd::Comment const& cmt);
    void paint(Graphics& g) final;
private:
    const std::string m_text;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiComment)
};


#endif
