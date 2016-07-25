/*
 // Copyright (c) 2016 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef CAMO_INSTANCE_INCLUDE_HPP
#define CAMO_INSTANCE_INCLUDE_HPP

#include <set>
#include <vector>
#include "../ThirdParty/zpd/xpd/xpd.hpp"

namespace camo
{
    // ==================================================================================== //
    //                                  CAMOMILE INSTANCE                                   //
    // ==================================================================================== //
    
    //! @brief A usefull class that override an instance.
    class camomile : protected xpd::instance, public xpd::console::history
    {
    public:
       
        // ================================================================================ //
        //                                      DEFAULT                                     //
        // ================================================================================ //
        
        //! @brief The default constructor.
        camomile();
        
        //! @brief The virutal destructor.
        virtual ~camomile() = default;
        
        // ================================================================================ //
        //                                      INSTANCE                                    //
        // ================================================================================ //
 
    protected:
        
        //! @brief Receives a message from a tie.
        //! @param name The tie that received the vector of atoms.
        //! @param selector The selector.
        //! @param atoms The vector of atoms.
        void receive(xpd::tie name, xpd::symbol selector, std::vector<xpd::atom> const& atoms) override;
        
        //! @brief Receives a post from the console.
        //! @param post The console post received.
        void receive(xpd::console::post const& post) override;
        
        // ================================================================================ //
        //                                      PATCH                                       //
        // ================================================================================ //
 
    public:
        
        //! @brief Loads a patch.
        //! @details You can override the method to perform extra stuff before and after the loading of the patch.
        virtual void load_patch(std::string const& name, std::string const& path);
        
        //! @brief Closes a patch.
        //! @details You can override the method to perform extra stuff before and after the closing of the patch.
        virtual void close_patch();
        
        //! @brief Returns the current patch.
        inline xpd::patch const get_patch() const noexcept {return m_patch;}
        
        // ================================================================================ //
        //                                      PLAY HEAD                                   //
        // ================================================================================ //

        
        // ================================================================================ //
        //                                      PARAMETERS                                  //
        // ================================================================================ //

        struct parameter
        {
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
        
        //! @brief Removes all the parameters.
        void clear_parameters();

        //! @brief Adds a new parameter.
        //! @details The method can throw exceptions.
        void add_parameter(parameter const& param);
        
        //! @brief Gets the number of parameters.
        inline size_t get_number_of_parameters() const xpd_noexcept {return m_parameters.size();}
        
        //! @brief Gets the name of a parameter.
        //! @param index The index of the parameter.
        inline std::string get_parameter_name(size_t const index) const {return m_parameters[index].name;}
        
        //! @brief Gets the label of a parameter.
        //! @param index The index of the parameter.
        inline std::string get_parameter_label(size_t const index) const {return m_parameters[index].label;}
        
        //! @brief Gets the number of steps of a parameter.
        //! @param index The index of the parameter.
        inline size_t get_parameter_nsteps(size_t const index) const xpd_noexcept {return m_parameters[index].nsteps;}
        
        //! @brief Gets the default value of a parameter.
        //! @param index The index of the parameter.
        //! @param normalized If the value should be normalized berween 0 and 1.
        float get_parameter_default_value(size_t const index, bool const normalized = true) const xpd_noexcept;
        
        //! @brief Gets the current value of a parameter.
        //! @param index The index of the parameter.
        //! @param normalized If the value should be normalized berween 0 and 1.
        float get_parameter_value(size_t const index, bool const normalized = true) const xpd_noexcept;
        
        //! @brief Sets the value of a parameter.
        //! @param index The index of the parameter.
        //! @param val The new value.
        //! @param normalized If the value is normalized berween 0 and 1.
        void set_parameter_value(size_t const index, float val, bool const normalized = true);
        
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
        
        static xpd::symbol get_symbol_float();
        static xpd::symbol get_symbol_playing();
        static xpd::symbol get_symbol_measure();
        
        xpd::patch              m_patch;
        xpd::tie                m_playhead_tie;
        std::vector<parameter>  m_parameters;
        std::vector<xpd::atom>  m_playing_list;
        std::vector<xpd::atom>  m_measure_list;
        std::set<listener*>     m_listeners;
    };
};


#endif // CAMO_INSTANCE_INCLUDE_HPP
