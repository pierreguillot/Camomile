/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PATCH_EDITOR__
#define __CAMOMILE_PATCH_EDITOR__

#include "../JuceLibraryCode/JuceHeader.h"
#include "InstanceProcessor.h"
#include "ObjectEditor.h"

// ==================================================================================== //
//                                  CAMOMILE INTERFACE                                  //
// ==================================================================================== //

class PatchEditor  :
public AsyncUpdater,
public AudioProcessorEditor,
public InstanceProcessor::Listener,
public FileDragAndDropTarget,
public Button::Listener
{
private:
    class AboutWindow;
    class ConsoleWindow;
    InstanceProcessor&              m_processor;
    OwnedArray<ObjectEditor>        m_objects;
    bool                            m_dropping;
    ScopedPointer<DrawableButton>   m_button_infos;
    OwnedArray<Component>           m_buttons;
    ScopedPointer<DocumentWindow>   m_window;
    Colour                          m_color_bg;
    Colour                          m_color_bd;
    String                          m_last_path;
public:
    PatchEditor(InstanceProcessor&);
    ~PatchEditor();
    void handleAsyncUpdate() override;
    void paint(Graphics&) override;

    bool isInterestedInFileDrag(const StringArray& files) override;
    void filesDropped(const StringArray& files, int x, int y) override;
    void fileDragEnter(const StringArray& files, int x, int y) override;
    void fileDragExit(const StringArray& files) override;
    void buttonClicked(Button* button) override;
    void patchChanged() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchEditor)
};



#endif  // PLUGINEDITOR_H_INCLUDED
