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
    //! @brief
    //! @details
    class camomile : public exchanger, public xpd::console::history
    {
    public:
       
        //! @brief The default constructor.
        camomile() = default;
        
        //! @brief The virutal destructor.
        virtual ~camomile();
        
        // ================================================================================ //
        //                                      PATCH                                       //
        // ================================================================================ //
 
        //! @brief Loads a patch.
        //! @details You can override the method to perform extra stuff before and after the loading of the patch.
        virtual void load_patch(std::string const& name, std::string const& path);
        
        //! @brief Closes a patch.
        //! @details You can override the method to perform extra stuff before and after the closing of the patch.
        virtual void close_patch();
        
        //! @brief Returns the current patch.
        inline xpd::patch const get_patch() const noexcept {return m_patch;}
        
        
        // ================================================================================ //
        //                                      PARAMETERS                                  //
        // ================================================================================ //

        
        
        
        // ================================================================================ //
        //                                      LISTENER                                    //
        // ================================================================================ //
        
        //! @brief The camomile listener.
        class listener
        {
        public:
            virtual ~listener() = default;
            
            //! @brief Receives the notification that the patch changed.
            //! @details You must override the method.
            virtual void patch_changed() = 0;
        };
        
        //! @brief Adds a listener to camomile.
        void add_listener(listener& l);
        
        //! @brief Removes a listener from camomile.
        void remove_listener(listener& l);
        
    private:
        
        xpd::patch              m_patch;
        xpd::tie                m_playhead_tie;
        std::set<listener*>     m_listeners;
    };
};


#endif // CAMO_INSTANCE_INCLUDE_HPP
