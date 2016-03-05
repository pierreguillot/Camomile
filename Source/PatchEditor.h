/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PATCH_EDITOR__
#define __CAMOMILE_PATCH_EDITOR__

#include "../JuceLibraryCode/JuceHeader.h"
#include "InstanceProcessor.h"

// ==================================================================================== //
//                                  CAMOMILE INTERFACE                                  //
// ==================================================================================== //

class PatchEditor  :
public AsyncUpdater,
public AudioProcessorEditor,
public InstanceProcessor::Listener,
public Button::Listener
{
private:
    class ImgButton;
    class PatchWin;
    class About;
    class Console;
    
    InstanceProcessor&              m_processor;
    bool                            m_dropping;
    Toolbar                         m_menu;
    ScopedPointer<ImgButton>        m_button;
    ScopedPointer<DocumentWindow>   m_window;
    Colour                          m_color_bg;
    Colour                          m_color_bd;
    Colour                          m_color_txt;
    int                             m_bd_size;
    Font                            m_font;
    String                          m_last_path;
public:
    PatchEditor(InstanceProcessor&);
    ~PatchEditor();
    void handleAsyncUpdate() override;
    void paint(Graphics&) override;
    void buttonClicked(Button* button) override;
    void patchChanged() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchEditor)
};



#endif  // PLUGINEDITOR_H_INCLUDED
