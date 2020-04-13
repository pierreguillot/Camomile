/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include "PluginProcessor.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                      BUTTON                                              //
//////////////////////////////////////////////////////////////////////////////////////////////

//! @brief The flower button
//! The only button of the editor that's not a Pd object.
class CamomileEditorButton : public Button
{
public:
    CamomileEditorButton(CamomileAudioProcessor& processor);
    ~CamomileEditorButton();
    void paintButton(Graphics& g, bool over, bool down) final {};
    void buttonStateChanged() final;
    void clicked() final;
private:
    CamomileAudioProcessor& m_processor;
    DrawableImage           m_center;
    DrawableImage           m_petals;
    std::unique_ptr<DocumentWindow> m_window;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamomileEditorButton)
};

