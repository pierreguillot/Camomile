/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/


#ifndef __CAMOMILE_OBJECT_EDITOR__
#define __CAMOMILE_OBJECT_EDITOR__

#include "../JuceLibraryCode/JuceHeader.h"
#include "InstanceProcessor.h"

class PatchEditor;

// ==================================================================================== //
//                                  OBJECT EDITOR                                       //
// ==================================================================================== //

class ObjectEditor :
public AsyncUpdater,
public Component,
public Messenger,
public juce::Timer,
public juce::TextEditor::Listener,
public juce::TextEditor::InputFilter,
public ModalComponentManager::Callback
{
private:
    class ObjectText;
    class ObjectPopup;
    class ObjectCallBack;
    PatchEditor&                    m_interface;
    Gui                             m_object;
    ScopedPointer<ObjectText>       m_editor;
    ScopedPointer<ObjectPopup>      m_popup;
    char                            m_last_input;
public:
    
    // ==================================================================================== //
    //                              CONSTRUCTOR & DESTRUCTOR                                //
    // ==================================================================================== //
    
    ObjectEditor(PatchEditor& camo, Gui const& object);
    virtual ~ObjectEditor();
    
    // ==================================================================================== //
    //                                        PAINT                                         //
    // ==================================================================================== //

    void handleAsyncUpdate() override;
    void paint(Graphics& g) override;
    
    // ==================================================================================== //
    //                                      INTERACTIONS                                    //
    // ==================================================================================== //
    
    void mouseMove(const MouseEvent& event) override;
    void mouseEnter(const MouseEvent& event) override;
    void mouseExit(const MouseEvent& event) override;
    void mouseDown(const MouseEvent& event) override;
    void mouseDrag(const MouseEvent& event) override;
    void mouseUp(const MouseEvent& event) override;
    void mouseDoubleClick(const MouseEvent& event) override;
    void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel) override;
    bool keyPressed(const KeyPress& key) override;
    
    // ==================================================================================== //
    //                                      NOTIFICATIONS                                   //
    // ==================================================================================== //

    void timerCallback() override {Messenger::trigger();}
    void receive(Message const& message) override;
    void textEditorAction(pd::TextEditor& editor, std::string const& action);
    void popupMenuAction(pd::PopupMenu& menu, std::string const& action);
    // ==================================================================================== //
    //                                      TEXT EDITORS                                    //
    // ==================================================================================== //
    
    void textEditorNotify(juce::TextEditor&);
    void textEditorTextChanged(juce::TextEditor&) override;
    void textEditorReturnKeyPressed(juce::TextEditor&) override;
    void textEditorEscapeKeyPressed(juce::TextEditor&) override;
    void textEditorFocusLost(juce::TextEditor&) override;
    String filterNewText(juce::TextEditor& editor, const String& newInput) override;
    void inputAttemptWhenModal() override;
    
    void modalStateFinished(int returnValue) override;
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ObjectEditor)
};

#endif
