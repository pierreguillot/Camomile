/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      BUTTON                                              //
//////////////////////////////////////////////////////////////////////////////////////////////

//! @brief The flower button
class CamomileEditorButton : public Button
{
public:
    CamomileEditorButton();
    void paintButton(Graphics& g, bool over, bool down) final {};
    void buttonStateChanged() final;
    //void clicked() final;
private:
    DrawableImage   m_center;
    DrawableImage   m_petals;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditorButton)
};

