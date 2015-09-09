/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_MESSENGER__
#define __CAMOMILE_PD_MESSENGER__

#include "PdAtom.h"
#include "PdInstance.h"

namespace pd
{
    // ==================================================================================== //
    //                                      MESSENGER                                       //
    // ==================================================================================== //
    
    //! @brief The Messenger class can be used to receive messages from Pure Data.
    //! @todo Later let the possibilty of synchronous trigger.
    class Messenger
    {
    public:
        struct Message
        {
            std::string         destination;
            std::string         selector;
            std::vector<Atom>   atoms;
            
            inline Message(std::string const& _dest, std::string const& _sel, std::vector<Atom> const& _atoms) :
            destination(_dest), selector(_sel), atoms(_atoms) {}
            inline Message(std::string&& _dest, std::string&& _sel, std::vector<Atom>&& _atoms) :
            destination(std::move(_dest)), selector(std::move(_sel)), atoms(std::move(_atoms)) {}
        };
    private:
        struct t_messenger;
        Instance                            m_instance;
        std::map<std::string, t_messenger*> m_messengers;
        std::vector<Message>                m_messages;
        void add(Message const& message);
        void add(Message&& message);
        
    public:
        //! @brief The constructor for a new Messenger.
        //! @details Creates a Messenger.
        Messenger(Instance const& instance);
        
        //! @brief The constructor for a new Messenger.
        //! @details Creates a Messenger and bind it to name.
        Messenger(Instance const& instance, std::string const& name);
        
        //! @brief The destructor for a Messenger.
        //! @details Deletes a Messenger and removes all the bindings.
        virtual ~Messenger();
        
        //! @brief Binds a Messenger to a name.
        void bind(std::string const& name);
        
        //! @brief Unbinds a Messenger from a name.
        void unbind(std::string const& name);
        
        //! @brief Triggers the messenger to send its messages.
        void trigger() noexcept;
        
        //! @brief Virutal method that receive the messages.
        virtual void receive(Message const& message) = 0;
    };
}

#endif
