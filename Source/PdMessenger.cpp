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

    struct Messenger::t_messenger
    {
        t_eobj      obj;
        std::string name;
        Messenger*  messenger;
        
    public:
        static void messenger_bang(t_messenger* x)
        {
            x->messenger->add(Message(std::string(x->name), std::string("bang"), std::vector<Atom>()));
        }
        
        static void messenger_float(t_messenger* x, float f)
        {
            x->messenger->add(Message(std::string(x->name), std::string("float"), {Atom(f)}));
        }
        
        static void messenger_symbol(t_messenger* x, t_symbol* s)
        {
            x->messenger->add(Message(std::string(x->name), std::string("symbol"), {Atom(std::string(s->s_name))}));
        }
        
        static void messenger_list(t_messenger* x, t_symbol* s, int argc, t_atom* argv)
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
            x->messenger->add(Message(std::string(x->name), std::string("list"), std::move(vec)));
        }
        
        static void messenger_anything(t_messenger* x, t_symbol* s, int argc, t_atom* argv)
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
            x->messenger->add(Message(std::string(x->name), std::string(s->s_name), std::move(vec)));
        }
    };
    
    Messenger::Messenger(Instance const& instance) : m_instance(instance)
    {
        if(m_instance)
        {
            m_instance.addMessenger(this);
        }
    }
    
    Messenger::Messenger(Instance const& instance, std::string const& name) : m_instance(instance)
    {
        if(m_instance)
        {
            m_instance.addMessenger(this);
        }
        bind(name);
    }
    
    Messenger::~Messenger()
    {
        unbind();
        if(m_instance)
        {
            m_instance.removeMessenger(this);
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
                c = eclass_new("c.messenger", (method)NULL, (method)NULL, (short)sizeof(t_messenger), CLASS_PD, A_GIMME, 0);
                eclass_addmethod(c, (method) t_messenger::messenger_bang,      "bang",             A_NULL,  0);
                eclass_addmethod(c, (method) t_messenger::messenger_float,     "float",            A_FLOAT, 0);
                eclass_addmethod(c, (method) t_messenger::messenger_symbol,    "symbol",           A_SYMBOL,0);
                eclass_addmethod(c, (method) t_messenger::messenger_list,      "list",             A_GIMME, 0);
                eclass_addmethod(c, (method) t_messenger::messenger_anything,  "anything",         A_GIMME, 0);
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
    
    void Messenger::unbind()
    {
        for(auto it : m_messengers)
        {
            pd_unbind((t_pd *)(it.second), gensym(it.first.c_str()));
            eobj_free(it.second);
        }
    }
    
    void Messenger::add(Message const& message)
    {
        m_messages.push_back(message);
    }
    
    void Messenger::add(Message&& message)
    {
        m_messages.push_back(std::move(message));
    }
    
    void Messenger::trigger() noexcept
    {
        for(size_t i = 0; i < m_messages.size(); i++)
        {
            receive(m_messages[i]);
        }
        m_messages.clear();
    }
}



