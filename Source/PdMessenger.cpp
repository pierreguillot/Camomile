/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdMessenger.h"

namespace pd
{
    
    // ==================================================================================== //
    //                                      MESSENGER                                       //
    // ==================================================================================== //


    void Messenger::_messenger::messenger_bang(Messenger::t_messenger* x)
    {
        x->messenger->receive(x->name, std::string("bang"), std::vector<Atom>());
    }
    
    void Messenger::_messenger::messenger_float(Messenger::t_messenger* x, float f)
    {
        x->messenger->receive(x->name, std::string("float"), std::vector<Atom>({Atom(f)}));
    }
    
    void Messenger::_messenger::messenger_symbol(Messenger::t_messenger* x, t_symbol* s)
    {
        x->messenger->receive(x->name, std::string("symbol"), std::vector<Atom>({Atom(std::string(s->s_name))}));
    }
    
    void Messenger::_messenger::messenger_list(Messenger::t_messenger* x, t_symbol* s, int argc, t_atom* argv)
    {
        std::vector<Atom> vec(argc);
        for(size_t i = 0; i < vec.size(); i++)
        {
            if(atom_gettype(argv+i) == A_FLOAT)
            {
                vec[i] = atom_getfloat(argv+i);
            }
            if(atom_gettype(argv+i) == A_SYMBOL)
            {
                vec[i] = std::string(atom_getsymbol(argv+i)->s_name);
            }
        }
        x->messenger->receive(x->name, std::string("list"), vec);
    }
    
    void Messenger::_messenger::messenger_anything(Messenger::t_messenger* x, t_symbol* s, int argc, t_atom* argv)
    {
        std::vector<Atom> vec(argc);
        for(size_t i = 0; i < vec.size(); i++)
        {
            if(atom_gettype(argv+i) == A_FLOAT)
            {
                vec[i] = atom_getfloat(argv+i);
            }
            if(atom_gettype(argv+i) == A_SYMBOL)
            {
                vec[i] = std::string(atom_getsymbol(argv+i)->s_name);
            }
        }
        x->messenger->receive(x->name, std::string(s->s_name), vec);
    }
    
    Messenger::Messenger(std::string const& name)
    {
        bind(name);
    }
    
    Messenger::~Messenger()
    {
        for(auto it : m_messengers)
        {
            pd_unbind((t_pd *)(it.second), gensym(it.first.c_str()));
            eobj_free(it.second);
        }
    }
    
    void Messenger::bind(std::string const& name)
    {
        static t_eclass *c = NULL;
        auto it = m_messengers.find(name);
        if(it == m_messengers.end())
        {
            if(!c)
            {
                c = eclass_new("c.messenger", (method)NULL, (method)NULL, (short)sizeof(t_messenger), 0L, A_GIMME, CLASS_PD);
                eclass_addmethod(c, (method) _messenger::messenger_bang,      "bang",             A_NULL,  0);
                eclass_addmethod(c, (method) _messenger::messenger_float,     "float",            A_FLOAT, 0);
                eclass_addmethod(c, (method) _messenger::messenger_symbol,    "symbol",           A_SYMBOL,0);
                eclass_addmethod(c, (method) _messenger::messenger_list,      "list",             A_GIMME, 0);
                eclass_addmethod(c, (method) _messenger::messenger_anything,  "anything",         A_GIMME, 0);
                eclass_register(CLASS_OBJ, c);
            }
            if(c)
            {
                t_messenger* mess = (t_messenger *)eobj_new(c);
                mess->name = name;
                mess->messenger = this;
                m_messengers[name] = mess;
                pd_bind((t_pd *)(mess), gensym(name.c_str()));
            }
        }
    }
    
    void Messenger::unbind(std::string const& name)
    {
        auto it = m_messengers.find(name);
        if(it != m_messengers.end())
        {
            pd_unbind((t_pd *)(it->second), gensym(it->first.c_str()));
            eobj_free(it->second);
            m_messengers.erase(it);
        }
    }
}



