/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_PARAMETER_HPP
#define Z_PD_PARAMETER_HPP

#include "PdObject.hpp"

namespace pd
{
    //! @brief A class that manages a parameter
    class Parameter
    {
    public:
        
        //! @brief The default constructor.
        Parameter();
        
        //! @brief The copy constructor.
        Parameter(Parameter const& other);
        
        //! @brief The real constructor.
        Parameter(Gui const& gui);
        
         //! @brief The destructor.
        ~Parameter();
        
        //! @brief The copy operator.
        Parameter& operator=(Parameter const& other);
        
        //! @brief The move operator.
        Parameter& operator=(Parameter&& other);
        
        //! @brief Gets if the parameter is valid.
        inline bool isValid() const noexcept {return m_valid;}
        
        //! @brief Gets the normalized value.
        inline float getValueNormalized() const noexcept {return m_value;}
        
        //! @brief Gets the non normalized value.
        inline float getValueNonNormalized() const noexcept {
            return (m_min < m_max) ? m_value * (m_max - m_min) + m_min : (1.f - m_value) * (m_min - m_max) + m_max;}
        
        //! @brief Sets the normalized value.
        void setValueNormalized(float value);
        
        //! @brief Sets the non normalized value.
        inline void setValueNonNormalized(float value) {m_value = getValueNormalized(value);}
        
        //! @brief Sets the normalized value of a non normalized value.
        float getValueNormalized(float value);
        
        //! @brief Gets the default value of the parameter.
        inline float getDefaultValue() const noexcept {return 0.f;}
        
        //! @brief Gets the name of the parameter.
        inline std::string getName() const {return m_name;}
        
        //! @brief Gets the label of the parameter.
        inline std::string getLabel() const {return m_label;}
        
        //! @brief Gets the text for the value of the parameter.
        inline std::string getTextForValue() const {return std::to_string(getValueNonNormalized());}
        
        //! @brief Gets if the value for a text.
        inline float getValueForText(std::string const& text) const noexcept {return std::atof(text.c_str());}
        
        //! @brief Gets if the orientation of the parameter is inverted.
        inline bool isOrientationInverted() const noexcept {return false;}
        
        //! @brief Gets the number of steps of the parameter.
        inline int getNumberOfSteps() const noexcept {return m_nsteps != 0 ? m_nsteps : 0x7fffffff;}
        
        //! @brief Gets the tie of the parameter.
        inline pd::Tie const& getTie() const noexcept {return m_bname;}
        
    private:
        bool        m_valid;
        float       m_value;
        float       m_min;
        float       m_max;
        std::string m_name;
        std::string m_label;
        pd::Tie     m_bname;
        int         m_nsteps;
    };
}

#endif
