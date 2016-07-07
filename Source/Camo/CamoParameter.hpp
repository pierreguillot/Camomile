/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef CAMO_PARAMETER_INCLUDE_HPP
#define CAMO_PARAMETER_INCLUDE_HPP

#include <string>
#include <cstdlib>
#include "../ThirdParty/zpd/xpd/xpd.hpp"

// ==================================================================================== //
//                                  CAMOMILE PARAMETER                                  //
// ==================================================================================== //

namespace camo
{
    class Parameter
    {
    public:
        Parameter();
        Parameter(Parameter const& other);
        ~Parameter();
        
        Parameter& operator=(Parameter const& other);
        Parameter& operator=(Parameter&& other);
        
        inline bool isValid() const noexcept {return m_valid;}
        
        inline float getValueNormalized() const noexcept {return m_value;}
        inline float getValueNonNormalized() const noexcept {return (m_min < m_max) ? m_value * (m_max - m_min) + m_min : (1.f - m_value) * (m_min - m_max) + m_max;}
        inline void setValueNonNormalized(float value) {m_value = getValueNormalized(value);}
        void setValueNormalized(float value);
        float getValueNormalized(float value);
        inline float getDefaultValue() const noexcept {return 0.f;}
        inline std::string getName() const {return m_name;}
        inline std::string getLabel() const {return m_label;}
        inline std::string getTextForValue() const {return std::to_string(getValueNonNormalized());}
        inline float getValueForText(std::string const& text) const noexcept {return std::atof(text.c_str());}
        inline bool isOrientationInverted() const noexcept {return false;}
        inline int getNumberOfSteps() const noexcept {return m_nsteps != 0 ? m_nsteps : 0x7fffffff;}
        inline xpd::tie const& getTie() const noexcept {return m_bname;}
        
    private:
        bool        m_valid;
        float       m_value;
        float       m_min;
        float       m_max;
        std::string m_name;
        std::string m_label;
        int         m_nsteps;
        xpd::tie    m_bname;
    };
}


#endif // CAMO_PARAMETER_INCLUDE_HPP
