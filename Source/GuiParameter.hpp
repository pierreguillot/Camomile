/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_PARAMETER__
#define __CAMOMILE_GUI_PARAMETER__

#include "InstanceProcessor.h"

// ==================================================================================== //
//                                      GUI PARAMETER                                   //
// ==================================================================================== //

class GuiParameter : public virtual Component, private Timer
{
public:
    GuiParameter(InstanceProcessor& processor, pd::Gui const& gui);
    ~GuiParameter();
    
    pd::Gui::Type getType() const noexcept;
    float getMaximum() const noexcept;
    float getMinimum() const noexcept;
    
    static Font getFont(){return Font(String("Monaco"), 13.f, juce::Font::plain);}
    static int getBordersize() noexcept {return 1;}
    static Colour const& getColorBg() noexcept {return Colours::lightgrey;}
    static Colour const& getColorBd() noexcept {return Colours::darkgrey;}
    static Colour const& getColorTxt() noexcept {return Colours::darkgrey;}
    static Colour const& getColorInv() noexcept {
        static Colour c(Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        return c;}
protected:
    
    void startEdition() noexcept;
    void stopEdition() noexcept;
    float getValue() const noexcept;
    float getValueNormalized() const noexcept;
    void setValue(float value, bool redraw = true);
    void setValueNormalized(float value, bool redraw = true);
    
private:
    void timerCallback() final;
    
    InstanceProcessor&  m_processor;
    const pd::Gui::Type m_type;
    const float         m_minimum;
    const float         m_maximum;
    const size_t        m_index;
    float               m_value;
    bool                m_edited;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiParameter)
};


#endif
