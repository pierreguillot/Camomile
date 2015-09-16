/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "ObjectEditor.h"
#include "PatchEditor.h"

class ObjectEditor::ObjectCallBack : public ModalComponentManager::Callback
{
private:
    ObjectEditor* m_editor;
public:
    ObjectCallBack(ObjectEditor* editor) : m_editor(editor)
    {
        ;
    }
    
    void modalStateFinished(int returnValue)
    {
        m_editor->modalStateFinished(returnValue);
    }
};

class ObjectEditor::ObjectPopup : public juce::PopupMenu
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

class ObjectEditor::ObjectText : public juce::TextEditor
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

// ==================================================================================== //
//                                  OBJECT EDITOR                                       //
// ==================================================================================== //

ObjectEditor::ObjectEditor(PatchEditor& camo, Gui const& object) :
Messenger(object.getBindingName()),
m_interface(camo),
m_object(object)
{
    const std::array<int,2> bounds = m_object.getSize();
    const int offset = m_object.getBorderSize() * 2;
    Component::setSize(bounds[0] + offset, bounds[1] + offset);
    Component::setVisible(true);
    Component::setInterceptsMouseClicks(m_object.wantMouse(), m_object.wantMouse());
    Component::setMouseClickGrabsKeyboardFocus(m_object.wantKeyboard());
    Component::setWantsKeyboardFocus(m_object.wantKeyboard());
    Component::setFocusContainer(m_object.hasTextEditor());
    m_editor = nullptr;
    m_popup  = nullptr;
    startTimer(20);
}

ObjectEditor::~ObjectEditor()
{
    stopTimer();
}

// ==================================================================================== //
//                                        PAINT                                         //
// ==================================================================================== //

void ObjectEditor::paint(Graphics& g)
{
    const int offset = m_object.getBorderSize();
    const AffineTransform transform(AffineTransform::translation(offset, offset));
    g.fillAll(tojColor(m_object.getBackgroundColor()));
    std::vector<Layer> layers(m_object.paint());
    for(auto it : layers)
    {
        if(it.state() == Layer::Todraw)
        {
            for(int i = 0; i < it.size(); i++)
            {
                const Gobj obj = it[i];
                g.setColour(tojColor(obj.color()));
                if(obj.type() == Gobj::Text)
                {
                    vector<t_pt> const points(obj.points());
                    g.setFont(tojFont(obj.getFont()));
                    g.drawText(juce::String(obj.text()),
                               points[0].x + offset, points[0].y + offset, points[1].x, points[1].y,
                               juce::Justification(obj.justification()), obj.wrapText());
                }
                else if(obj.filled())
                {
                    g.fillPath(tojPath(obj), transform);
                }
                else
                {
                    g.strokePath(tojPath(obj), PathStrokeType(obj.witdh()), transform);
                }
            }
            it.close();
        }
    }
    g.setColour(tojColor(m_object.getBorderColor()));
    g.drawRect(getBounds().withZeroOrigin(), m_object.getBorderSize());
}

// ==================================================================================== //
//                                      INTERACTIONS                                    //
// ==================================================================================== //

void ObjectEditor::mouseMove(const MouseEvent& event)
{
    m_object.mouseMove({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()));
    Messenger::trigger();
}

void ObjectEditor::mouseEnter(const MouseEvent& event)
{
    m_object.mouseEnter({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()));
    Messenger::trigger();
}

void ObjectEditor::mouseExit(const MouseEvent& event)
{
    m_object.mouseExit({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()));
    Messenger::trigger();
}

void ObjectEditor::mouseDown(const MouseEvent& event)
{
    m_object.mouseDown({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()));
    Messenger::trigger();
}

void ObjectEditor::mouseDrag(const MouseEvent& event)
{
    m_object.mouseDrag({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()));
    Messenger::trigger();
}

void ObjectEditor::mouseUp(const MouseEvent& event)
{
    m_object.mouseUp({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()));
    Messenger::trigger();
}

void ObjectEditor::mouseDoubleClick(const MouseEvent& event)
{
    m_object.mouseDoubleClick({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()));
    Messenger::trigger();
}

void ObjectEditor::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    m_object.mouseWheelMove({float(event.x), float(event.y)}, toCicmMod(event.mods.getRawFlags()), {wheel.deltaX, wheel.deltaY});
    Messenger::trigger();
}

bool ObjectEditor::keyPressed(const KeyPress& key)
{
    char buffer[MB_CUR_MAX];
    wctomb(buffer, key.getTextCharacter());
    if(key.getKeyCode() == KeyPress::deleteKey ||
       key.getKeyCode() == KeyPress::returnKey ||
       key.getKeyCode() == KeyPress::tabKey ||
       key.getKeyCode() == KeyPress::escapeKey)
    {
        
        if(key.getKeyCode() == KeyPress::deleteKey)
        {
            m_object.keyFilter(buffer[0], EKEY_DEL);
        }
        else if(key.getKeyCode() == KeyPress::returnKey)
        {
            m_object.keyFilter(buffer[0], EKEY_RETURN);
        }
        else if(key.getKeyCode() == KeyPress::tabKey)
        {
            m_object.keyFilter(buffer[0], EKEY_TAB);
        }
        else if(key.getKeyCode() == KeyPress::escapeKey)
        {
            m_object.keyFilter(buffer[0], EKEY_ESC);
        }
    }
    else
    {
        m_object.keyPressed(buffer[0], key.getModifiers().getRawFlags());
    }
    Messenger::trigger();
    return true;
}

// ==================================================================================== //
//                                      NOTIFICATIONS                                   //
// ==================================================================================== //

void ObjectEditor::textEditorAction(pd::TextEditor& editor, std::string const& action)
{
    if(editor && action == "create")
    {
        exitModalState(0);
        const MessageManagerLock thread(Thread::getCurrentThread());
        if(thread.lockWasGained())
        {
            if(m_editor)
            {
                removeChildComponent(m_editor);
                m_editor = nullptr;
            }
            m_editor = new ObjectText(editor);
        }
    }
    else if(m_editor)
    {
        if(action == "destroy")
        {
            const MessageManagerLock thread(Thread::getCurrentThread());
            if(thread.lockWasGained())
            {
                exitModalState(0);
                removeChildComponent(m_editor);
                m_editor = nullptr;
            }
        }
        else if(m_editor && action == "attr_modified")
        {
            const MessageManagerLock thread(Thread::getCurrentThread());
            if(thread.lockWasGained())
            {
                m_editor->setFont(juce::Font(editor.getFontSize()));
                m_editor->setText(editor.getText());
                m_editor->setColour(juce::TextEditor::backgroundColourId, tojColor(editor.getBackgroundColor()));
                m_editor->setColour(juce::TextEditor::textColourId, tojColor(editor.getTextColor()));
                m_editor->setMultiLine(editor.shouldWrap(), editor.shouldWrap());
            }
        }
        else if(m_editor && action == "popup")
        {
            const int offset = m_object.getBorderSize();
            const MessageManagerLock thread(Thread::getCurrentThread());
            if(thread.lockWasGained())
            {
                const std::array<int, 4> bounds(editor.getBounds());
                m_editor->addListener(this);
                m_editor->setInputFilter(this, false);
                m_editor->setBounds(bounds[0] + offset, bounds[1] + offset, bounds[2], bounds[3]);
                enterModalState(false);
                addAndMakeVisible(m_editor);
            }
        }
        else if(m_editor && action == "grabfocus")
        {
            const MessageManagerLock thread(Thread::getCurrentThread());
            if(thread.lockWasGained())
            {
                m_editor->grabKeyboardFocus();
            }
        }
    }
}

void ObjectEditor::popupMenuAction(pd::PopupMenu& menu, std::string const& action)
{
    if(menu && action == "create")
    {
        const MessageManagerLock thread(Thread::getCurrentThread());
        if(thread.lockWasGained())
        {
            m_popup = nullptr;
            m_popup = new ObjectPopup(menu);
        }
    }
    if(m_popup)
    {
        if(action == "destroy")
        {
            const MessageManagerLock thread(Thread::getCurrentThread());
            if(thread.lockWasGained())
            {
                m_popup = nullptr;
            }
        }
        else if(action == "attr_modified")
        {
            const MessageManagerLock thread(Thread::getCurrentThread());
            if(thread.lockWasGained())
            {
                m_popup->clear();
                for(int i = 0; i < menu.getNumberOfItems(); i++)
                {
                    if(menu.isItemSeparator(i))
                    {
                        m_popup->addSeparator();
                    }
                    else
                    {
                        m_popup->addItem(menu.getItemId(i) + 1, menu.getItemLabel(i), !menu.isItemDisable(i), menu.isItemChecked(i), nullptr);
                    }
                }
            }
            
        }
        else if(action == "popup")
        {
            m_popup->showMenuAsync(juce::PopupMenu::Options().withTargetComponent(this), new ObjectCallBack(this));
        }
    }
}

void ObjectEditor::modalStateFinished(int returnValue)
{
    if(m_popup && returnValue)
    {
        pd::PopupMenu menu(m_popup->getPopup());
        m_object.popup(menu, returnValue - 1);
    }
    else
    {
        const MessageManagerLock thread(Thread::getCurrentThread());
        if(thread.lockWasGained())
        {
            m_popup = nullptr;
        }
    }
}

void ObjectEditor::handleAsyncUpdate()
{
    const MessageManagerLock mml(Thread::getCurrentThread());
    if(mml.lockWasGained())
    {
        repaint();
    }
}

void ObjectEditor::receive(Message const& message)
{
    if(message.selector == string("symbol") && !message.atoms.empty() && message.atoms[0] == string("repaint"))
    {
        AsyncUpdater::triggerAsyncUpdate();
    }
    else if(message.selector == string("texteditor"))
    {
        if(message.atoms.size() == 2 && message.atoms[0].isSymbol() && message.atoms[1].isSymbol())
        {
            pd::TextEditor editor(message.atoms[0]);
            textEditorAction(editor, std::string(message.atoms[1]));
        }
    }
    else if(message.selector == string("popup"))
    {
        if(message.atoms.size() == 2 && message.atoms[0].isSymbol() && message.atoms[1].isSymbol())
        {
            pd::PopupMenu menu(message.atoms[0]);
            popupMenuAction(menu, std::string(message.atoms[1]));
        }
    }
}

// ==================================================================================== //
//                                      TEXT EDITORS                                    //
// ==================================================================================== //

void ObjectEditor::textEditorTextChanged(juce::TextEditor& ed)
{
    if(!(hasKeyboardFocus(true) || isCurrentlyBlockedByAnotherModalComponent()))
    {
        textEditorReturnKeyPressed(ed);
        return;
    }
    else if(m_editor)
    {
        pd::TextEditor editor = m_editor->getEditor();
        editor.setText(m_editor->getText().toStdString());
        m_object.textEditorKeyPress(editor, m_last_input);
        Messenger::trigger();
    }
}

void ObjectEditor::textEditorReturnKeyPressed(juce::TextEditor& ed)
{
    if(m_editor)
    {
        pd::TextEditor editor = m_editor->getEditor();
        m_object.textEditorKeyFilter(editor, EKEY_RETURN);
        Messenger::trigger();
    }
}

void ObjectEditor::textEditorEscapeKeyPressed(juce::TextEditor& ed)
{
    if(m_editor)
    {
        pd::TextEditor editor = m_editor->getEditor();
        m_object.textEditorKeyFilter(editor, EKEY_ESC);
        Messenger::trigger();
    }
}

void ObjectEditor::textEditorFocusLost(juce::TextEditor& ed)
{
    textEditorTextChanged(ed);
}

String ObjectEditor::filterNewText(juce::TextEditor& editor, const String& newInput)
{
    if(!newInput.isEmpty())
    {
        m_last_input = newInput.toRawUTF8()[0];
    }
    return newInput;
}

void ObjectEditor::inputAttemptWhenModal()
{
    if(m_editor)
    {
        textEditorReturnKeyPressed(*m_editor);
    }
}

