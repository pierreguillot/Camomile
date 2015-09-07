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
public juce::TextEditor::Listener,
public juce::TextEditor::InputFilter,
public ModalComponentManager::Callback
{
private:
    class ObjectText;
    class ObjectPopup;
    PatchEditor&                    m_interface;
    Gui                             m_object;
    ScopedPointer<ObjectText>       m_editor;
    ScopedPointer<ObjectPopup>      m_popup;
    atomic_int                      m_popup_item;
    bool                            m_attached;
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
    
    void modalStateFinished(int returnValue) override;
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

    void receive(std::string const& dest, std::string const& s, std::vector<Atom> const& atoms) override;
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
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ObjectEditor)
    
    class ObjectPopup : public juce::PopupMenu
    {
    private:
        const pd::PopupMenu m_popup;
    public:
        ObjectPopup(pd::PopupMenu const& popup) : juce::PopupMenu(), m_popup(popup)
        {
            ;
        }
        inline std::string getBindingName() const noexcept {return m_popup.getName();}
        inline pd::PopupMenu getPopup() const noexcept {return m_popup;}
    };
    
    class ObjectText : public juce::TextEditor
    {
    private:
        const pd::TextEditor m_editor;
    public:
        ObjectText(pd::TextEditor const& editor) : juce::TextEditor(), m_editor(editor)
        {
            setBorder(BorderSize<int>(0));
            setReturnKeyStartsNewLine(true);
            setTabKeyUsedAsCharacter(true);
            setKeyboardType(juce::TextEditor::textKeyboard);
        }
        inline std::string getBindingName() const noexcept {return m_editor.getName();}
        inline pd::TextEditor getEditor() const noexcept {return m_editor;}
    };
};

#endif
