/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef CAMO_PARAMETER_INCLUDE_HPP
#define CAMO_PARAMETER_INCLUDE_HPP

#include <string>
#include <vector>
#include <set>
#include <cmath>
#include <cstdlib>
#include "../ThirdParty/zpd/xpd/xpd.hpp"

namespace camo
{    
    // ==================================================================================== //
    //                                      EXCHANGER                                       //
    // ==================================================================================== //
    //! @brief A class that manages the exchange of value with a patch.
    //! @details The class stores a set of parameters and presets, when you changes their...
    class exchanger : public virtual xpd::instance
    {
    public:
        exchanger();
        
        ~exchanger();
        
        void clear();
        
        void add_parameter(std::string const& name, std::string const& label,
                           float value, float defval, float min, float max, size_t nsteps,
                           xpd::tie receive_tie, xpd::tie send_tie);
        
        inline size_t get_number_of_parameters() const xpd_noexcept {return m_parameters.size();}
        
        inline std::string get_parameter_name(size_t const index) const {return m_parameters[index].name;}
        
        inline std::string get_parameter_label(size_t const index) const {return m_parameters[index].label;}
        
        inline size_t get_parameter_nsteps(size_t const index) const xpd_noexcept {return m_parameters[index].nsteps;}
        
        inline float get_parameter_default_value(size_t const index, bool const normalized = true) const xpd_noexcept {return 0;}
        
        inline float get_parameter_value(size_t const index, bool const normalized = true) const xpd_noexcept {return m_parameters[index].get(normalized);}
        
        inline std::string get_parameter_text(size_t const index) const {return std::to_string(get_parameter_value(index, false));}
        
        inline void set_parameter_value(size_t const index, const float val, bool const normalized = true) xpd_noexcept {m_parameters[index].set(val, normalized);}
        
        
    protected:
        
        bool evaluate(xpd::tie name, xpd::symbol selector, std::vector<xpd::atom> const& atoms) xpd_noexcept;
        
    private:
        class parameter
        {
        public:
            
            static float scale(const float s, float const smin, float const smax, float const dmin, float const dmax, size_t const nsteps) xpd_noexcept
            {
                int check_if_step_is_one;
                if(nsteps)
                {
                    const float step = (1.f / float(nsteps - 1));
                    return std::round(((s - smin) * (smax - smin) * (dmax - dmin) + dmin) / step) * step;
                }
                return (s - smin) * (smax - smin) * (dmax - dmin) + dmin;
            }
            
            inline float get(const bool normalized = true) const xpd_noexcept
            {
                return normalized ? value : scale(value, 0.f, 1.f, min, max, 0);
            }
            
            inline void set(float const v, const bool normalized = true) xpd_noexcept
            {
                value = normalized ? scale(v, 0.f, 1.f, 0.f, 1.f, nsteps) : scale(v, min, max, 0.f, 1.f, nsteps);
            }
            
            std::string name;
            std::string label;
            
            float       value;
            float       defval;
            float       min;
            float       max;
            size_t      nsteps;
            
            xpd::tie    receive_tie;
            xpd::tie    send_tie;
        };
        
        std::vector<parameter>  m_parameters;
    };
}


#endif // CAMO_PARAMETER_INCLUDE_HPP
