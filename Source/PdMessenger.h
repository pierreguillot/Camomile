/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_MESSENGER__
#define __CAMOMILE_PD_MESSENGER__

#include "PdAtom.h"

namespace pd
{
    // ==================================================================================== //
    //                                      MESSENGER                                       //
    // ==================================================================================== //
    
    class Messenger
    {
    private:
        typedef struct _messenger
        {
            t_eobj      obj;
            std::string name;
            Messenger*  messenger;
            static void messenger_bang(_messenger* x);
            static void messenger_float(_messenger* x, float f);
            static void messenger_symbol(_messenger* x, t_symbol* s);
            static void messenger_list(_messenger* x, t_symbol* s, int argc, t_atom* argv);
            static void messenger_anything(_messenger* x, t_symbol* s, int argc, t_atom* argv);
        }t_messenger;
        
        std::map<std::string, t_messenger*> m_messengers;
    public:
        Messenger();
        Messenger(std::string const& name);
        virtual ~Messenger();
        
        void bind(std::string const& name);
        void unbind(std::string const& name);
        virtual void receive(std::string const& dest, std::string const& s, std::vector<Atom> const& atoms) = 0;
    };
}

#endif
