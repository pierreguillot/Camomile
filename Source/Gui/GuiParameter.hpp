/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_GUI_PARAMETER__
#define __CAMOMILE_GUI_PARAMETER__

#include "../CamomileProcessor.hpp"

// ==================================================================================== //
//                                      GUI PARAMETER                                   //
// ==================================================================================== //

class GuiParameter : public virtual Component
{
public:
    GuiParameter(CamomileProcessor& processor, xpd::gui const& gui);
    ~GuiParameter() {}
    inline xpd::gui::type_t getType() const noexcept {return m_type;}
    inline float getMaximum() const noexcept {return m_maximum;}
    inline float getMinimum() const noexcept {return m_minimum;}
    inline float getValue() const noexcept {return m_value;}
    float getValueNormalized() const noexcept;
    void update();
    
protected:
    
    void startEdition() noexcept;
    void stopEdition() noexcept;
    void setValue(float value, bool redraw = true);
    void setValueNormalized(float value, bool redraw = true);
private:
    
    CamomileProcessor&      m_processor;
    const xpd::gui::type_t  m_type;
    const float             m_minimum;
    const float             m_maximum;
    const size_t            m_index;
    float                   m_value;
    bool                    m_edited;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GuiParameter)
};


#endif
