/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "ObjectEditor.h"
#include "PatchEditor.h"

// ==================================================================================== //
//                                  OBJECT EDITOR                                       //
// ==================================================================================== //

ObjectEditor::ObjectEditor(PatchEditor& camo, sGui object) :
Messenger(object->getBindingName()),
m_interface(camo),
m_object(object),
m_attached(false)
{
    if(object)
    {
        const std::array<int,2> bounds = object->getSize();
        const int offset = object->getBorderSize() * 2;
        Component::setSize(bounds[0] + offset, bounds[1] + offset);
        Component::setVisible(true);
        Component::setInterceptsMouseClicks(object->wantMouse(), object->wantMouse());
        Component::setMouseClickGrabsKeyboardFocus(object->wantKeyboard());
        Component::setWantsKeyboardFocus(object->wantKeyboard());
        Component::setFocusContainer(object->hasTextEditor());
    }
}

ObjectEditor::~ObjectEditor()
{
    m_editors.clear();
}

// ==================================================================================== //
//                                        PAINT                                         //
// ==================================================================================== //

void ObjectEditor::paint(Graphics& g)
{
    sGui object = m_object.lock();
    if(object)
    {
        if(!m_attached)
        {
            //m_messenger->addListener(this);
            m_attached = true;
        }
        m_interface.lock();
        const int offset = object->getBorderSize();
        const AffineTransform transform(AffineTransform::translation(offset, offset));
        g.fillAll(tojColor(object->getBackgroundColor()));
        std::vector<Layer> layers(object->paint());
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
                        const Font f(obj.fontSize());
                        g.setFont(f);
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
        g.setColour(tojColor(object->getBorderColor()));
        g.drawRect(getBounds().withZeroOrigin(), object->getBorderSize());
        m_interface.unlock();
    }
    else
    {
        g.fillAll(Colours::whitesmoke);
    }
}

// ==================================================================================== //
//                                      INTERACTIONS                                    //
// ==================================================================================== //

void ObjectEditor::mouseMove(const MouseEvent& event)
{
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseMove({float(event.x), float(event.y)}, event.mods.getRawFlags());
    }
}

void ObjectEditor::mouseEnter(const MouseEvent& event)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseEnter({float(event.x), float(event.y)}, event.mods.getRawFlags());
    }
}

void ObjectEditor::mouseExit(const MouseEvent& event)
{
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseExit({float(event.x), float(event.y)}, event.mods.getRawFlags());
    }
}

void ObjectEditor::mouseDown(const MouseEvent& event)
{
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseDown({float(event.x), float(event.y)}, event.mods.getRawFlags());
    }
}

void ObjectEditor::mouseDrag(const MouseEvent& event)
{
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseDrag({float(event.x), float(event.y)}, event.mods.getRawFlags());
    }
}

void ObjectEditor::mouseUp(const MouseEvent& event)
{
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseUp({float(event.x), float(event.y)}, event.mods.getRawFlags());
    }
}

void ObjectEditor::mouseDoubleClick(const MouseEvent& event)
{
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseDoubleClick({float(event.x), float(event.y)}, event.mods.getRawFlags());
    }
}

void ObjectEditor::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
    sGui object = m_object.lock();
    if(object)
    {
        object->mouseWheelMove({float(event.x), float(event.y)}, event.mods.getRawFlags(), {wheel.deltaX, wheel.deltaY});
    }
}

bool ObjectEditor::keyPressed(const KeyPress& key)
{
    sGui object = m_object.lock();
    if(object)
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
                object->keyFilter(buffer[0], EKEY_DEL);
            }
            else if(key.getKeyCode() == KeyPress::returnKey)
            {
                object->keyFilter(buffer[0], EKEY_RETURN);
            }
            else if(key.getKeyCode() == KeyPress::tabKey)
            {
                object->keyFilter(buffer[0], EKEY_TAB);
            }
            else if(key.getKeyCode() == KeyPress::escapeKey)
            {
                object->keyFilter(buffer[0], EKEY_ESC);
            }
        }
        else
        {
            object->keyPressed(buffer[0], key.getModifiers().getRawFlags());
        }
        return true;
    }
    return false;
}

// ==================================================================================== //
//                                      NOTIFICATIONS                                   //
// ==================================================================================== //

void ObjectEditor::textEditorAction(pd::TextEditor& editor, ewidget_action action)
{
    if(editor)
    {
        const MessageManagerLock thread(Thread::getCurrentThread());
        if(thread.lockWasGained())
        {
            switch(action)
            {
                case EWIDGET_CREATE:
                    m_editors.add(new ObjectText(editor));
                    break;
                case EWIDGET_DESTROY:
                {
                    for(int i = 0; i < m_editors.size(); i++)
                    {
                        if(m_editors[i]->getBindingName() == editor.getName())
                        {
                            m_editors.remove(i);
                            exitModalState(0);
                            break;
                        }
                    }
                }
                    break;
                case EWIDGET_CHANGED:
                {
                    for(int i = 0; i < m_editors.size(); i++)
                    {
                        if(m_editors[i]->getBindingName() == editor.getName())
                        {
                            m_editors[i]->setFont(juce::Font(editor.getFontSize()));
                            m_editors[i]->setText(editor.getText());
                            m_editors[i]->setColour(juce::TextEditor::backgroundColourId, tojColor(editor.getBackgroundColor()));
                            m_editors[i]->setColour(juce::TextEditor::textColourId, tojColor(editor.getTextColor()));
                            m_editors[i]->setMultiLine(editor.shouldWrap(), editor.shouldWrap());
                            break;
                        }
                    }
                }
                    break;
                case EWIDGET_POPUP:
                {
                    sGui object = m_object.lock();
                    const int offset = object->getBorderSize();
                    for(int i = 0; i < m_editors.size(); i++)
                    {
                        if(m_editors[i]->getBindingName() == editor.getName())
                        {
                            const std::array<int, 4> bounds(editor.getBounds());
                            m_editors[i]->addListener(this);
                            m_editors[i]->setInputFilter(this, false);
                            m_editors[i]->setBounds(bounds[0] + offset, bounds[1] + offset, bounds[2], bounds[3]);
                            enterModalState (false);
                            addAndMakeVisible(m_editors[i]);
                            break;
                        }
                    }
                }
                    break;
                case EWIDGET_GRABFOCUS:
                {
                    for(int i = 0; i < m_editors.size(); i++)
                    {
                        if(m_editors[i]->getBindingName() == editor.getName())
                        {
                            m_editors[i]->grabKeyboardFocus();
                            break;
                        }
                    }
                }
                    break;
                default:
                    break;
            }
            
        }
    }
}

void ObjectEditor::popupMenuAction(pd::PopupMenu& menu, ewidget_action action)
{
    if(menu)
    {
        const MessageManagerLock thread(Thread::getCurrentThread());
        if(thread.lockWasGained())
        {
            switch(action)
            {
                case EWIDGET_DESTROY:
                    m_popup.clear();
                    break;
                case EWIDGET_CHANGED:
                {
                    m_popup.clear();
                    for(int i = 0; i < menu.getNumberOfItems(); i++)
                    {
                        if(menu.isItemSeparator(i))
                        {
                            m_popup.addSeparator();
                        }
                        else
                        {
                            m_popup.addItem(menu.getItemId(i) + 1, menu.getItemLabel(i), !menu.isItemDisable(i), menu.isItemChecked(i), nullptr);
                        }
                        
                    }
                }
                    break;
                case EWIDGET_POPUP:
                {
                    sGui object = m_object.lock();
                    const int offset = object->getBorderSize();
                    const std::array<int, 4> bounds(menu.getBounds());
                    m_popup.show();
                    break;
                }
                default:
                    break;
            }
            
        }
    }
}

void ObjectEditor::receive(std::string const& dest, std::string const& s, std::vector<Atom> const& atoms)
{
    sGui object = m_object.lock();
    if(object && isShowing())
    {
        if(s == string("symbol") && !atoms.empty() && atoms[0] == string("repaint"))
        {
            const MessageManagerLock thread(Thread::getCurrentThread());
            if(thread.lockWasGained())
            {
                repaint();
            }
        }
        else if(s == string("texteditor"))
        {
            if(atoms.size() == 2 && atoms[0].isSymbol() && atoms[1].isFloat())
            {
                pd::TextEditor editor(atoms[0]);
                textEditorAction(editor, ewidget_action(float(atoms[1])));
            }
        }
        else if(s == string("popup"))
        {
            if(atoms.size() == 2 && atoms[0].isSymbol() && atoms[1].isFloat())
            {
                pd::PopupMenu menu(atoms[0]);
                popupMenuAction(menu, ewidget_action(float(atoms[1])));
            }
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
    sGui object = m_object.lock();
    if(object)
    {
        pd::TextEditor editor(reinterpret_cast<ObjectText&>(ed).getEditor());
        if(editor)
        {
            editor.setText(ed.getText().toStdString());
            object->textEditorKeyPress(editor, m_last_input);
        }
    }
}

void ObjectEditor::textEditorReturnKeyPressed(juce::TextEditor& ed)
{
    sGui object = m_object.lock();
    if(object)
    {
        pd::TextEditor editor(reinterpret_cast<ObjectText&>(ed).getEditor());
        if(editor)
        {
            object->textEditorKeyFilter(editor, EKEY_RETURN);
        }
    }
}

void ObjectEditor::textEditorEscapeKeyPressed(juce::TextEditor& ed)
{
    sGui object = m_object.lock();
    if(object)
    {
        pd::TextEditor editor(reinterpret_cast<ObjectText&>(ed).getEditor());
        if(editor)
        {
            object->textEditorKeyFilter(editor, EKEY_ESC);
        }
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
    for(int i = 0; i < m_editors.size(); i++)
    {
        textEditorReturnKeyPressed(*m_editors[i]);
    }
}

