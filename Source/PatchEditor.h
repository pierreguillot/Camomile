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
public:
    PatchEditor(InstanceProcessor&);
    ~PatchEditor();
    void handleAsyncUpdate() override;
    void paint(Graphics&) override;
    void buttonClicked(Button* button) override;
    void patchChanged() override;
    
private:
    class ImgButton;
    class PatchWin;
    class About;
    class Console;
    class GuiParameter;
    
    InstanceProcessor&                      m_processor;
    bool                                    m_dropping;
    Toolbar                                 m_menu;
    ScopedPointer<ImgButton>                m_button;
    ScopedPointer<DocumentWindow>           m_window;
    String                                  m_last_path;
    OwnedArray<GuiParameter>                m_parameters;
    
    static  Font    font;
    static  int     bordersize;
    static  Colour  color_bg;
    static  Colour  color_bd;
    static  Colour  color_txt;
    static  Colour  color_invisible;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchEditor)
};



#endif  // PLUGINEDITOR_H_INCLUDED
