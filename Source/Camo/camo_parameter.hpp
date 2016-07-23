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
    //                                  CAMOMILE PARAMETER                                  //
    // ==================================================================================== //

    class parameter
    {
    public:
        parameter();
        parameter(std::string const& name, std::string const& label,
                  float value, float defval, float min, float max, size_t nsteps,
                  xpd::tie receive_tie, xpd::tie send_tie);
        parameter(parameter const& other);
        ~parameter();
        parameter& operator=(parameter const& other);
        
        inline std::string name() const {return m_name;}
        inline std::string label() const {return m_label;}
        inline xpd::tie const& receive_tie() const xpd_noexcept {return m_receive_tie;}
        inline xpd::tie const& send_tie() const xpd_noexcept {return m_send_tie;}
        inline operator bool() const xpd_noexcept {return m_valid;}
        inline size_t nsteps() const xpd_noexcept {return m_nsteps != 0 ? m_nsteps : 0x7fffffff;}
        inline float get_default_value_normalized() const xpd_noexcept {return m_defval;}
        inline float get_default_value_denormalized() const xpd_noexcept {return scale(m_defval, 0.f, 1.f, m_min, m_max, 0);;}
        
        inline float get_value_normalized() const xpd_noexcept {return m_value;}
        inline float get_value_denormalized() const xpd_noexcept {return scale(m_value, 0.f, 1.f, m_min, m_max, 0);}
        inline void set_value_normalized(float const v) xpd_noexcept {m_value = scale(v, 0.f, 1.f, 0.f, 1.f, m_nsteps);}
        inline void set_value_denormalized(float const v) xpd_noexcept {m_value = scale(v, m_min, m_max, 0.f, 1.f, m_nsteps);}
        
        static float scale(const float s, float const smin, float const smax, float const dmin, float const dmax, size_t const nsteps) xpd_noexcept;

        class manager;
    private:
        std::string m_name;
        std::string m_label;
        bool        m_valid;
        
        float       m_value;
        float       m_defval;
        float       m_min;
        float       m_max;
        size_t      m_nsteps;
        
        xpd::tie    m_receive_tie;
        xpd::tie    m_send_tie;
    };
    
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
        
        std::string get_parameter_name(size_t const index) const;
        
        std::string get_parameter_label(size_t const index) const;
        
        std::string get_parameter_type(size_t const index) const;
        
        size_t get_parameter_nsteps(size_t const index) const xpd_noexcept;
        
        float get_parameter_default_value(size_t const index, bool const normalized = true) const xpd_noexcept;
        
        float get_parameter_value(size_t const index, bool const normalized = true) const xpd_noexcept;
        
        inline std::string get_parameter_text(size_t const index) const {return std::to_string(get_parameter_value(index, false));}
        
        inline  void set_parameter_value(size_t const index, const float val, bool const normalized = true) xpd_noexcept;
        
        
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
        
        static xpd::symbol      s_float;
        std::vector<parameter>  m_parameters;
    };
}


#endif // CAMO_PARAMETER_INCLUDE_HPP
