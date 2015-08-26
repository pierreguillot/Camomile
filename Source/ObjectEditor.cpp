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

ObjectEditor::ObjectEditor(PatchEditor& camo, Gui const& object) :
Messenger(object.getBindingName()),
m_interface(camo),
m_object(object),
m_popup_active(false),
m_attached(false)
{
    const std::array<int,2> bounds = m_object.getSize();
    const int offset = m_object.getBorderSize() * 2;
    Component::setSize(bounds[0] + offset, bounds[1] + offset);
    Component::setVisible(true);
    Component::setInterceptsMouseClicks(m_object.wantMouse(), m_object.wantMouse());
    Component::setMouseClickGrabsKeyboardFocus(m_object.wantKeyboard());
    Component::setWantsKeyboardFocus(m_object.wantKeyboard());
    Component::setFocusContainer(m_object.hasTextEditor());
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
    g.setColour(tojColor(m_object.getBorderColor()));
    g.drawRect(getBounds().withZeroOrigin(), m_object.getBorderSize());
}

// ==================================================================================== //
//                                      INTERACTIONS                                    //
// ==================================================================================== //

void ObjectEditor::mouseMove(const MouseEvent& event)
{
    m_object.mouseMove({float(event.x), float(event.y)}, event.mods.getRawFlags());
}

void ObjectEditor::mouseEnter(const MouseEvent& event)
{
    setMouseCursor(juce::MouseCursor::NormalCursor);
    m_object.mouseEnter({float(event.x), float(event.y)}, event.mods.getRawFlags());
}

void ObjectEditor::mouseExit(const MouseEvent& event)
{
    m_object.mouseExit({float(event.x), float(event.y)}, event.mods.getRawFlags());
}

void ObjectEditor::mouseDown(const MouseEvent& event)
{
    m_object.mouseDown({float(event.x), float(event.y)}, event.mods.getRawFlags());
}

void ObjectEditor::mouseDrag(const MouseEvent& event)
{
    m_object.mouseDrag({float(event.x), float(event.y)}, event.mods.getRawFlags());
}

void ObjectEditor::mouseUp(const MouseEvent& event)
{
     m_object.mouseUp({float(event.x), float(event.y)}, event.mods.getRawFlags());
}

void ObjectEditor::mouseDoubleClick(const MouseEvent& event)
{
    m_object.mouseDoubleClick({float(event.x), float(event.y)}, event.mods.getRawFlags());
}

void ObjectEditor::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& wheel)
{
     m_object.mouseWheelMove({float(event.x), float(event.y)}, event.mods.getRawFlags(), {wheel.deltaX, wheel.deltaY});
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
    return true;
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
                    const int offset = m_object.getBorderSize();
                    for(int i = 0; i < m_editors.size(); i++)
                    {
                        if(m_editors[i]->getBindingName() == editor.getName())
                        {
                            const std::array<int, 4> bounds(editor.getBounds());
                            m_editors[i]->addListener(this);
                            m_editors[i]->setInputFilter(this, false);
                            m_editors[i]->setBounds(bounds[0] + offset, bounds[1] + offset, bounds[2], bounds[3]);
                            enterModalState(false);
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
    if(menu && !m_popup_active)
    {
        const MessageManagerLock thread(Thread::getCurrentThread());
        if(thread.lockWasGained())
        {
            switch(action)
            {
                case EWIDGET_DESTROY:
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
                    m_popup_active = true;
                    int i = m_popup.show();
                    if(i)
                    {
                        m_object.popup(menu, i-1);
                    }
                    m_popup_active = false;                    
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
    if(s == string("symbol") && !atoms.empty() && atoms[0] == string("repaint"))
    {
        const MessageManagerLock mml(Thread::getCurrentThread());
        if(mml.lockWasGained())
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
    pd::TextEditor editor(reinterpret_cast<ObjectText&>(ed).getEditor());
    if(editor)
    {
        editor.setText(ed.getText().toStdString());
        m_object.textEditorKeyPress(editor, m_last_input);
    }
}

void ObjectEditor::textEditorReturnKeyPressed(juce::TextEditor& ed)
{
    pd::TextEditor editor(reinterpret_cast<ObjectText&>(ed).getEditor());
    if(editor)
    {
        m_object.textEditorKeyFilter(editor, EKEY_RETURN);
    }
}

void ObjectEditor::textEditorEscapeKeyPressed(juce::TextEditor& ed)
{
    pd::TextEditor editor(reinterpret_cast<ObjectText&>(ed).getEditor());
    if(editor)
    {
        m_object.textEditorKeyFilter(editor, EKEY_ESC);
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

