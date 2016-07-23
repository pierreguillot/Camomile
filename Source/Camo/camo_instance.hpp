/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef CAMO_INSTANCE_INCLUDE_HPP
#define CAMO_INSTANCE_INCLUDE_HPP

#include "camo_parameter.hpp"

namespace camo
{
    // ==================================================================================== //
    //                                  CAMOMILE INSTANCE                                   //
    // ==================================================================================== //

    class instance : public exchanger, public xpd::console::history
    {
    public:
       
        virtual ~instance();
        
        // ================================================================================ //
        //                                      PATCH                                       //
        // ================================================================================ //
 
        virtual void load_patch(std::string const& name, std::string const& path);
        
        virtual void close_patch();
        
        inline xpd::patch const get_patch() const noexcept {return m_patch;}
        
        
        // ================================================================================ //
        //                                      LISTENER                                    //
        // ================================================================================ //
        
        class listener
        {
        public:
            virtual ~listener() {}
            virtual void patch_changed() = 0;
        };
        
        void add_listener(listener& l);
        
        void remove_listener(listener& l);
        
    private:
        
        xpd::patch              m_patch;
        xpd::tie                m_playhead_tie;
        std::set<listener*>     m_listeners;
    };
};


#endif // CAMO_INSTANCE_INCLUDE_HPP
