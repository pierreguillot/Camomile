/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginEditorObject.hpp"
#include "PluginLookAndFeel.hpp"
#include <algorithm>

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     PATCH              ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiPatch::GuiPatch(CamomileEditorMouseManager& processor, pd::Patch patch) : m_processor(processor), m_patch(patch)
{
    setInterceptsMouseClicks(false, true);
    updateSize();
    updateObjects();
}

void GuiPatch::updateObjects()
{
    auto guis = m_patch.getGuis();
    auto isObjectDeprecated = [&](object_pair const& pair)
    {
        return pair.first != nullptr && std::find(guis.begin(), guis.end(), pair.first->getGUI()) == guis.end();
    };
    m_objects.erase(std::remove_if(m_objects.begin(), m_objects.end(), isObjectDeprecated), m_objects.end());
    
    for(auto& gui : guis)
    {
        auto it = std::find_if(m_objects.begin(), m_objects.end(), [&gui](object_pair const& pair)
                               {
            return pair.first != nullptr && pair.first->getGUI() == gui;
        });
        if(it == m_objects.end())
        {
            object_uptr object(PluginEditorObject::createTyped(m_processor, gui));
            if(object != nullptr)
            {
                addAndMakeVisible(object.get());
                auto label = object->getLabel();
                if(label != nullptr)
                {
                    addAndMakeVisible(label.get());
                }
                m_objects.push_back({std::move(object), std::move(label)});
            }
        }
        else
        {
            it->first->updateInterface();
            auto label = it->first->getLabel();
            if(label != nullptr)
            {
                addAndMakeVisible(label.get());
            }
            it->second = std::move(label);
        }
    }
}

void GuiPatch::updateSize()
{
    auto const bounds = m_patch.getBounds();
    int const width  = bounds[2] > 0 ? std::max(bounds[2], 100) : 400;
    int const height = bounds[3] > 0 ? std::max(bounds[3], 100) : 300;
    setSize(width, height);
}

void GuiPatch::updateObjectsValues()
{
    for(auto const& object : m_objects)
    {
        if(object.first != nullptr)
        {
            object.first->updateValue();
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     Object              ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

PluginEditorObject* PluginEditorObject::createTyped(CamomileEditorMouseManager& p, pd::Gui& g)
{
    if(g.getType() == pd::Gui::Type::Bang)
    {
        return new GuiBang(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Toggle)
    {
        return new GuiToggle(p, g);
    }
    else if(g.getType() == pd::Gui::Type::HorizontalSlider)
    {
        return new GuiSliderHorizontal(p, g);
    }
    else if(g.getType() == pd::Gui::Type::VerticalSlider)
    {
        return new GuiSliderVertical(p, g);
    }
    else if(g.getType() == pd::Gui::Type::HorizontalRadio)
    {
        return new GuiRadioHorizontal(p, g);
    }
    else if(g.getType() == pd::Gui::Type::VerticalRadio)
    {
        return new GuiRadioVertical(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Panel)
    {
        return new GuiPanel(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Comment)
    {
        return new GuiComment(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Number)
    {
        return new GuiNumber(p, g);
    }
    else if(g.getType() == pd::Gui::Type::AtomNumber)
    {
        return new GuiAtomNumber(p, g);
    }
    else if(g.getType() == pd::Gui::Type::AtomSymbol)
    {
        return new GuiAtomSymbol(p, g);
    }
    else if(g.getType() == pd::Gui::Type::Array)
    {
        return new GuiArray(p, g);
    }
    else if(g.getType() == pd::Gui::Type::GraphOnParent)
    {
        return new GuiGraphOnParent(p, g);
    }
    return new PluginEditorObject(p, g);
}

PluginEditorObject::PluginEditorObject(CamomileEditorMouseManager& p, pd::Gui& g) : gui(g), patch(p), edited(false),
value(g.getValue()), min(g.getMinimum()), max(g.getMaximum())
{
    setOpaque(false);
    updateInterface();
}

PluginEditorObject::~PluginEditorObject() {}

float PluginEditorObject::getValueOriginal() const noexcept
{
    return value;
}

void PluginEditorObject::setValueOriginal(float v)
{
    value = (min < max) ? std::max(std::min(v, max), min) : std::max(std::min(v, min), max);
    gui.setValue(value);
}

float PluginEditorObject::getValueScaled() const noexcept
{
    return (min < max) ? (value - min) / (max - min) : 1.f - (value - max) / (min - max);
}

void PluginEditorObject::setValueScaled(float v)
{
    value = (min < max) ? std::max(std::min(v, 1.f), 0.f) * (max - min) + min
                        : (1.f - std::max(std::min(v, 1.f), 0.f)) * (min - max) + max;
    gui.setValue(value);
}

void PluginEditorObject::startEdition() noexcept
{
    edited = true;
    patch.startEdition();
    value = gui.getValue();
}

void PluginEditorObject::stopEdition() noexcept
{
    edited = false;
    patch.stopEdition();
}

void PluginEditorObject::updateValue()
{
    if(edited == false)
    {
        float const v = gui.getValue();
        if(v != value)
        {
            value = v;
            repaint();
        }
    }
}

void PluginEditorObject::updateInterface()
{
    min = gui.getMinimum();
    max = gui.getMaximum();
    std::array<int, 4> const bounds(gui.getBounds());
    setBounds(bounds[0], bounds[1], bounds[2], bounds[3]);
    repaint();
}

std::unique_ptr<Label> PluginEditorObject::getLabel()
{
    pd::Label const lbl = gui.getLabel();
    const String text = String(lbl.getText());
    if(text.isNotEmpty())
    {
        auto label = std::make_unique<Label>();
        if(label == nullptr)
        {
            return nullptr;
        }
        const Font ft = CamoLookAndFeel::getFont(lbl.getFontName()).withPointHeight(static_cast<float>(lbl.getFontHeight()));
        const int width = ft.getStringWidth(text) + 1;
        const int height = ft.getHeight();
        const std::array<int, 2> position = lbl.getPosition();
        label->setBounds(position[0], position[1] - height / 2, width, height);
        label->setFont(ft);
        label->setJustificationType(Justification::centredLeft);
        label->setBorderSize(BorderSize<int>(0, 0, 0, 0));
        label->setMinimumHorizontalScale(1.f);
        label->setText(text, NotificationType::dontSendNotification);
        label->setEditable(false, false);
        label->setInterceptsMouseClicks(false, false);
        label->setColour(Label::textColourId, Colour(static_cast<uint32>(lbl.getColor())));
        return label;
    }
    return nullptr;
}

pd::Gui PluginEditorObject::getGUI()
{
    return gui;
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     BANG        /////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiBang::paint(Graphics& g)
{
    const float border = 1.f;
    const float w = static_cast<float>(getWidth() - border * 2);
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    if(getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
        g.fillEllipse(border, border, w, w);
    }
    g.setColour(Colours::black);
    g.drawEllipse(border, border, w, w, border);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiBang::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(1);
    repaint();
    stopEdition();
}

void GuiBang::mouseUp(const MouseEvent& e)
{
    if(getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        repaint();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     TOGGLE        ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiToggle::paint(Graphics& g)
{
    const float border = 1.f;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    if(getValueOriginal() > std::numeric_limits<float>::epsilon())
    {
        const float w = static_cast<float>(getWidth()) - border * 2.f;
        g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
        g.drawLine(1.f + border, 1.f + border, w, w, border);
        g.drawLine(w, 1.f + border, 1.f + border, w, border);
    }
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiToggle::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(1.f - getValueOriginal());
    repaint();
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     SLIDER HORIZONTAL   /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiSliderHorizontal::paint(Graphics& g)
{
    const float border = 1.f;
    const float crsor  = 3.f;
    const float w = static_cast<float>(getWidth()) - border * 2.f;
    const float h = static_cast<float>(getHeight()) - border * 2.f;
    const float val = gui.isLogScale() ? log(getValueOriginal() / min) / log(max / min) : getValueScaled();
    const float pos = val * (w - crsor - border) + crsor;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(pos, border + 0.5f, pos, h + 0.5f, crsor);
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiSliderHorizontal::mouseDown(const MouseEvent& e)
{
    startEdition();
    if(!gui.jumpOnClick())
    {
        if(gui.isLogScale())
        {
            m_temp = log(getValueOriginal() / min) / log(max / min);
        }
        else
        {
            m_temp = getValueScaled();
        }
    }
    mouseDrag(e);
}

void GuiSliderHorizontal::mouseDrag(const MouseEvent& e)
{
    if(gui.jumpOnClick())
    {
        const float val = static_cast<float>(e.x - 2) / static_cast<float>(getWidth() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp(val * log(max / min)) * min);
        }
        else
        {
            setValueScaled(val);
        }
    }
    else
    {
        const float val = static_cast<float>(e.x - e.getMouseDownX()) / static_cast<float>(getWidth() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp((m_temp + val) * log(max / min)) * min);
        }
        else
        {
            setValueScaled(m_temp + val);
        }
    }
    repaint();
}

void GuiSliderHorizontal::mouseUp(const MouseEvent& e)
{
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     SLIDER VERTICAL     /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
    
void GuiSliderVertical::paint(Graphics& g)
{
    const float border = 1.f;
    const float crsor = 3.f;
    const float w = static_cast<float>(getWidth() - border * 2);
    const float h = static_cast<float>(getHeight() - border * 2);
    const float val = gui.isLogScale() ? log(getValueOriginal() / min) / log(max / min) : getValueScaled();
    const float pos = (1.f - val) * (h - crsor - border) + crsor;
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(border + 0.5f, pos, w + 0.5f, pos, crsor);
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiSliderVertical::mouseDown(const MouseEvent& e)
{
    startEdition();
    if(!gui.jumpOnClick())
    {
        if(gui.isLogScale())
        {
            m_temp = log(getValueOriginal() / min) / log(max / min);
        }
        else
        {
            m_temp = getValueScaled();
        }
    }
    mouseDrag(e);
}

void GuiSliderVertical::mouseDrag(const MouseEvent& e)
{
    if(gui.jumpOnClick())
    {
        const float val = static_cast<float>(getHeight() - e.y - 2) / static_cast<float>(getHeight() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp(val * log(max /min)) * min);
        }
        else
        {
            setValueScaled(val);
        }
    }
    else
    {
        const float val = static_cast<float>(e.getMouseDownY() - e.y) / static_cast<float>(getHeight() - 4);
        if(gui.isLogScale())
        {
            setValueOriginal(exp((m_temp + val) * log(max / min)) * min);
        }
        else
        {
            setValueScaled(m_temp + val);
        }
    }
    repaint();
}

void GuiSliderVertical::mouseUp(const MouseEvent& e)
{
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     RADIO HORIZONTAL    /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiRadioHorizontal::paint(Graphics& g)
{
    const float border = 1.f;
    const float extra  = 2.f;
    const float h  = static_cast<float>(getHeight());
    const float hs = h - 2.f * (border + extra);
    const float w = static_cast<float>(getWidth()) / static_cast<float>(max + 1);
    const float ws = w - 2.f * (border + extra);
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.fillRect(w * getValueOriginal() + border + extra, border + extra, ws, hs);
    g.setColour(Colours::black);
    for(size_t i = 1; i < size_t(max) + 1; ++i)
    {
        g.drawLine(w * static_cast<float>(i), 0.f, w * static_cast<float>(i), w, border);
    }
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiRadioHorizontal::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(std::floor(static_cast<float>(e.x * (max + 1)) / static_cast<float>(getWidth())));
    repaint();
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     RADIO VERTICAL      /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

void GuiRadioVertical::paint(Graphics& g)
{
    const float border = 1.f;
    const float extra  = 2.f;
    const float h  = static_cast<float>(getHeight()) / static_cast<float>(max + 1);
    const float hs = h - 2.f * (border + extra);
    const float w = static_cast<float>(getWidth());
    const float ws = w - 2.f * (border + extra);
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.setColour(Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.fillRect(border + extra, h * getValueOriginal() + border + extra, ws, hs);
    g.setColour(Colours::black);
    for(size_t i = 1; i < static_cast<size_t>(max) + 1; ++i)
    {
        g.drawLine(0.f, h * static_cast<float>(i), h, h * static_cast<float>(i), border);
    }
    g.drawRect(getLocalBounds(), static_cast<int>(border));
}

void GuiRadioVertical::mouseDown(const MouseEvent& e)
{
    startEdition();
    setValueOriginal(std::floor(static_cast<float>(e.y * (max + 1)) / static_cast<float>(getHeight())));
    repaint();
    stopEdition();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     PANEL               /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiPanel::GuiPanel(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g)
{
    setInterceptsMouseClicks(false, false);
    edited = true;
}

void GuiPanel::paint(Graphics& g)
{
    g.fillAll(Colour(static_cast<uint32>(gui.getBackgroundColor())));
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     COMMENT             /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiComment::GuiComment(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g)
{
    setInterceptsMouseClicks(false, false);
    edited = true;
}

void GuiComment::paint(Graphics& g)
{
    const auto fheight = gui.getFontHeight();
    auto const ft = CamoLookAndFeel::getFont(gui.getFontName()).withPointHeight(fheight);
    g.setFont(ft);
    g.setColour(Colours::black);
    g.drawMultiLineText(gui.getText(), 0, static_cast<int>(ft.getAscent()), getWidth());
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     TEXT EDITOR         /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiTextEditor::GuiTextEditor(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g)
{
    static const int border = 1;
    const float fs = static_cast<float>(gui.getFontHeight());
    Font const tf = CamoLookAndFeel::getDefaultFont().withPointHeight(fs);
    
    label.setBounds(2, 0, getWidth() - 2, getHeight() - 1);
    label.setFont(tf);
    label.setMinimumHorizontalScale(1.f);
    label.setJustificationType(Justification::centredLeft);
    label.setBorderSize(BorderSize<int>(border+2, border, border, border));
    label.setText(String(getValueOriginal()), NotificationType::dontSendNotification);
    label.setEditable(false, false);
    label.setInterceptsMouseClicks(false, false);
    label.setColour(Label::textColourId, Colour(static_cast<uint32>(gui.getForegroundColor())));
    setInterceptsMouseClicks(true, false);
    addAndMakeVisible(label);
    
    label.onEditorHide = [this]()
    {
        auto const newValue = label.getText().getFloatValue();
        if(std::abs(newValue - getValueOriginal()) > std::numeric_limits<float>::epsilon())
        {
            startEdition();
            setValueOriginal(newValue);
            stopEdition();
            label.setText(juce::String(getValueOriginal()), juce::NotificationType::dontSendNotification);
        }
    };
    
    label.onEditorShow = [this]()
    {
        auto* editor = label.getCurrentTextEditor();
        if(editor != nullptr)
        {
            editor->setIndents(1, 2);
            editor->setBorder(juce::BorderSize<int>(0));
        }
    };
    
    updateValue();
}

void GuiTextEditor::mouseDoubleClick(const juce::MouseEvent&)
{
    label.showEditor();
}

void GuiTextEditor::updateValue()
{
    if(edited == false && !label.isBeingEdited())
    {
        value = gui.getValue();
        label.setText(juce::String(value), juce::NotificationType::dontSendNotification);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     NUMBER              /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiNumber::GuiNumber(CamomileEditorMouseManager& p, pd::Gui& g) : GuiTextEditor(p, g)
{
    const float w = static_cast<float>(getWidth());
    const float h = static_cast<float>(getHeight());
    label.setBounds(static_cast<int>(h * 0.5f), static_cast<int>(0.5f),
                    static_cast<int>(w - h * 0.5f), static_cast<int>(h));
    
    label.onEditorShow = [this]()
    {
        auto* editor = label.getCurrentTextEditor();
        if(editor != nullptr)
        {
            editor->setIndents(0, 2);
            editor->setBorder(juce::BorderSize<int>(0));
        }
    };
}

void GuiNumber::paint(Graphics& g)
{
    static auto const border = 1.0f;
    const float h = static_cast<float>(getHeight());
    const float w = static_cast<float>(getWidth());
    juce::Path p;
    p.startNewSubPath(0.5f, 0.5f);
    p.lineTo(0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h * 0.25f);
    p.lineTo(w - (h * 0.25f), 0.5f);
    p.closeSubPath();
    g.setColour(juce::Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.fillPath(p);
    g.setColour(juce::Colour(static_cast<uint32>(gui.getForegroundColor())));
    g.drawLine(0.f, 0.f, h * 0.5f, h * 0.5f, border);
    g.drawLine(0.f, h, h * 0.5f, h * 0.5f, border);
    g.setColour(juce::Colours::black);
    g.strokePath(p, juce::PathStrokeType(border));
}

void GuiNumber::mouseDown(const juce::MouseEvent& event)
{
    if(!label.isBeingEdited())
    {
        startEdition();
        shift = event.mods.isShiftDown();
        last  = getValueOriginal();
        setValueOriginal(last);
    }
}

void GuiNumber::mouseUp(const juce::MouseEvent& e)
{
    if(!label.isBeingEdited())
    {
        stopEdition();
    }
}

void GuiNumber::mouseDrag(const juce::MouseEvent& e)
{
    // Dragging mode
    if(!label.isBeingEdited())
    {
        auto const inc = static_cast<float>(-e.getDistanceFromDragStartY());
        if(std::abs(inc) < 1.0f)
        {
            return;
        }
        setValueOriginal(last + inc * (shift ? 0.01f : 1.0f));
        label.setText(juce::String(getValueOriginal()), juce::NotificationType::dontSendNotification);
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GATOM NUMBER        /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiAtomNumber::GuiAtomNumber(CamomileEditorMouseManager& p, pd::Gui& g) : GuiTextEditor(p, g)
{
}

void GuiAtomNumber::paint(juce::Graphics& g)
{
    static auto const border = 1.0f;
    const float h = static_cast<float>(getHeight());
    const float w = static_cast<float>(getWidth());
    const float o = h * 0.25f;
    juce::Path p;
    p.startNewSubPath(0.5f, 0.5f);
    p.lineTo(0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, o);
    p.lineTo(w - o, 0.5f);
    p.closeSubPath();
    g.setColour(juce::Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.fillPath(p);
    g.setColour(juce::Colours::black);
    g.strokePath(p, juce::PathStrokeType(border));
}

void GuiAtomNumber::mouseDown(const juce::MouseEvent& event)
{
    if(label.isBeingEdited())
    {
        return;
    }
    startEdition();
    if(gui.getNumberOfSteps() == 1) // Toggle mode
    {
        setValueOriginal(static_cast<float>(getValueOriginal() <= std::numeric_limits<float>::epsilon()));
        stopEdition();
        label.setText(juce::String(getValueOriginal()), juce::NotificationType::dontSendNotification);
    }
    else // Dragging mode
    {
        shift = event.mods.isShiftDown();
        last  = getValueOriginal();
        setValueOriginal(last);
    }
}

void GuiAtomNumber::mouseDrag(const juce::MouseEvent& e)
{
    // Toggle mode is off and dragging mode
    if(gui.getNumberOfSteps() == 0 && !label.isBeingEdited())
    {
        auto const inc = static_cast<float>(-e.getDistanceFromDragStartY());
        if(std::abs(inc) < 1.0f)
        {
            return;
        }
        setValueOriginal(last + inc * (shift ? 0.01f : 1.0f));
        label.setText(juce::String(getValueOriginal()), juce::NotificationType::dontSendNotification);
    }
}

void GuiAtomNumber::mouseUp(const juce::MouseEvent&)
{
    // Toggle mode is off and dragging mode
    if(gui.getNumberOfSteps() == 0 || !label.isBeingEdited())
    {
        stopEdition();
    }
}

void GuiAtomNumber::mouseDoubleClick(const juce::MouseEvent&)
{
    // Toggle mode is off
    if(gui.getNumberOfSteps() == 0)
    {
        label.showEditor();
    }
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GATOM SYMBOL        /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiAtomSymbol::GuiAtomSymbol(CamomileEditorMouseManager& p, pd::Gui& g) : GuiTextEditor(p, g)
{
    label.onEditorHide = [this]()
    {
        auto const strval = label.getText().toStdString();
        if(strval != gui.getSymbol())
        {
            startEdition();
            gui.setSymbol(strval);
            stopEdition();
            label.setText(juce::String(gui.getSymbol()), juce::NotificationType::dontSendNotification);
        }
    };
    
    label.onEditorShow = [this]()
    {
        auto* editor = label.getCurrentTextEditor();
        if(editor != nullptr)
        {
            editor->setIndents(1, 2);
            editor->setBorder(juce::BorderSize<int>(0));
        }
    };
    
    updateValue();
}

void GuiAtomSymbol::paint(juce::Graphics& g)
{
    static auto const border = 1.0f;
    const float h = static_cast<float>(getHeight());
    const float w = static_cast<float>(getWidth());
    const float o = h * 0.25f;
    juce::Path p;
    p.startNewSubPath(0.5f, 0.5f);
    p.lineTo(0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, h - 0.5f);
    p.lineTo(w - 0.5f, o);
    p.lineTo(w - o, 0.5f);
    p.closeSubPath();
    g.setColour(juce::Colour(static_cast<uint32>(gui.getBackgroundColor())));
    g.fillPath(p);
    g.setColour(juce::Colours::black);
    g.strokePath(p, juce::PathStrokeType(border));
}

void GuiAtomSymbol::updateValue()
{
    if(edited == false && !label.isBeingEdited())
    {
        label.setText(juce::String(gui.getSymbol()), juce::NotificationType::dontSendNotification);
    }
}

GuiArray::GuiArray(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g),
m_graph(gui.getArray()), m_array(p.getProcessor(), m_graph)
{
    setInterceptsMouseClicks(false, true);
    m_array.setBounds(getLocalBounds());
    addAndMakeVisible(&m_array);
}

void GuiArray::resized()
{
    m_array.setBounds(getLocalBounds());
}
    
//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GOP               /////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GuiGraphOnParent::GuiGraphOnParent(CamomileEditorMouseManager& p, pd::Gui& g) : PluginEditorObject(p, g), m_patch(p, g.getPatch())
{
    setInterceptsMouseClicks(false, true);
    edited = true;
    addAndMakeVisible(m_patch);
}

void GuiGraphOnParent::paint(Graphics& g)
{
    g.setColour(Colours::black);
    g.drawRect(getLocalBounds(), 1);
}

void GuiGraphOnParent::updateValue()
{
    m_patch.updateObjectsValues();
}

void GuiGraphOnParent::updateInterface()
{
    PluginEditorObject::updateInterface();
    m_patch.updateObjects();
}

//////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////     GRAPHICAL ARRAY      ////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

GraphicalArray::GraphicalArray(CamomileAudioProcessor& processor, pd::Array& graph) :
m_processor(processor), m_array(graph), m_edited(false)
{
    m_vector.reserve(8192);
    m_temp.reserve(8192);
    try { m_array.read(m_vector); }
    catch(...) { m_error = true; }
    startTimer(100);
    setInterceptsMouseClicks(true, false);
    setOpaque(false);
}

void GraphicalArray::paint(Graphics& g)
{
    if(m_error)
    {
        g.setFont(CamoLookAndFeel::getDefaultFont());
        g.drawText("array " + m_array.getName() + " is invalid", 0, 0, getWidth(), getHeight(), juce::Justification::centred);
        return;
    }
    if(m_vector.empty())
    {
        return;
    }
    
    auto const height = static_cast<float>(getHeight());
    auto const width = static_cast<float>(getWidth());
    auto const clipBounds = g.getClipBounds();
    auto const scale = m_array.getScale();
    auto const dh = height / (scale[1] - scale[0]);
    auto const wRadio = static_cast<float>(m_vector.size()) / width;
    g.setColour(juce::Colours::black);
    
    if(m_array.isDrawingCurve())
    {
        juce::Path p;
        for(int i = clipBounds.getX() + 1; i < clipBounds.getRight() - 1; i += 2)
        {
            auto const x1 = static_cast<float>(i);
            auto const previousIndex = static_cast<size_t>((x1 - 1.0f) * wRadio);
            auto const currentIndex = static_cast<size_t>(x1 * wRadio);
            auto const nextIndex = static_cast<size_t>((x1 + 1.0f) * wRadio);
            auto const y1 = height - (m_vector[previousIndex] - scale[0]) * dh;
            auto const y2 = height - (m_vector[currentIndex] - scale[0]) * dh;
            auto const y3 = height - (m_vector[nextIndex] - scale[0]) * dh;
            p.cubicTo(x1 - 1.0f, y1, x1, y2, x1 + 1.0f, y3);
        }
        g.strokePath(p, juce::PathStrokeType(1));
    }
    else if(m_array.isDrawingLine())
    {
        juce::Path p;
        for(int i = clipBounds.getX(); i < clipBounds.getRight(); i++)
        {
            auto const x1 = static_cast<float>(i);
            auto const currentIndex = static_cast<size_t>(x1 * wRadio);
            auto const nextIndex = static_cast<size_t>((x1 + 1.0f) * wRadio);
            auto const max = std::max_element(m_vector.cbegin()+currentIndex, m_vector.cbegin()+nextIndex, [](float const lhs, float const rhs) { return std::abs(lhs) < std::abs(rhs); });
            if(max != m_vector.cend())
            {
                auto const y = std::floor(height - (*max - scale[0]) * dh);
                p.lineTo(x1, y);
            }
        }
        g.strokePath(p, juce::PathStrokeType(1));
    }
    else
    {
        juce::RectangleList<float> rectangles;
        for(int i = clipBounds.getX(); i < clipBounds.getRight(); i++)
        {
            auto const x1 = static_cast<float>(i);
            auto const currentIndex = static_cast<size_t>(x1 * wRadio);
            auto const nextIndex = static_cast<size_t>((x1 + 1.0f) * wRadio);
            auto const minmax = std::minmax_element(m_vector.cbegin()+currentIndex, m_vector.cbegin()+nextIndex);
            if(minmax.first != m_vector.cend() && minmax.first != m_vector.cend())
            {
                auto const y1 = std::floor(height - (*minmax.second - scale[0]) * dh);
                auto const y2 = std::floor(height - (*minmax.first - scale[0]) * dh);
                rectangles.add(x1, y1, 1.0f , std::max(y2 - y1, 1.0f));
            }
        }
        g.fillRectList(rectangles);
    }
    
    g.drawRect(getLocalBounds(), 1);
}

void GraphicalArray::mouseDown(const MouseEvent& event)
{
    if(m_error)
        return;
    m_edited = true;
    mouseDrag(event);
}

void GraphicalArray::mouseDrag(const MouseEvent& event)
{
    if(m_error)
        return;
    const float s = static_cast<float>(m_vector.size() - 1);
    const float w = static_cast<float>(getWidth());
    const float h = static_cast<float>(getHeight());
    const float x = static_cast<float>(event.x);
    const float y = static_cast<float>(event.y);
    
    const std::array<float, 2> scale = m_array.getScale();
    const size_t index = static_cast<size_t>(std::round(clip(x / w, 0.f, 1.f) * s));
    m_vector[index] = (1.f - clip(y / h, 0.f, 1.f)) * (scale[1] - scale[0]) + scale[0];
    const CriticalSection& cs = m_processor.getCallbackLock();
    if(cs.tryEnter())
    {
        try { m_array.write(index, m_vector[index]); }
        catch(...) { m_error = true; }
        cs.exit();
    }
    m_processor.enqueueMessages(string_array, m_array.getName(), {});
    repaint();
}

void GraphicalArray::mouseUp(const MouseEvent& event)
{
    if(m_error)
        return;
    m_edited = false;
}

void GraphicalArray::timerCallback()
{
    if(!m_edited)
    {
        m_error = false;
        try { m_array.read(m_temp); }
        catch(...) { m_error = true; }
        if(m_temp != m_vector)
        {
            m_vector.swap(m_temp);
            repaint();
        }
    }
}

size_t GraphicalArray::getArraySize() const noexcept
{
    return m_vector.size();
}


