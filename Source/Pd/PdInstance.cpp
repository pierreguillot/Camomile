/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */


#include <cassert>
#include <algorithm>

extern "C"
{
#include <z_libpd.h>
#include "x_libpd_multi.h"
}

#include "PdInstance.hpp"
#include "PdPatch.hpp"

extern "C"
{
    struct pd::Instance::internal
    {
        static void instance_multi_bang(pd::Instance* ptr, const char *recv)
        {
            std::vector<Atom> const vec;
            std::lock_guard<std::mutex> lock(ptr->m_messages_mutex);
            ptr->m_messages.push({std::string(recv), std::string("bang"), vec});
        }
        
        static void instance_multi_float(pd::Instance* ptr, const char *recv, float f)
        {
            std::vector<Atom> const vec(1, f);
            std::lock_guard<std::mutex> lock(ptr->m_messages_mutex);
            ptr->m_messages.push({std::string(recv), std::string("float"), vec});
        }
        
        static void instance_multi_symbol(pd::Instance* ptr, const char *recv, const char *sym)
        {
            std::vector<Atom> vec(1, std::string(sym));
            std::lock_guard<std::mutex> lock(ptr->m_messages_mutex);
            ptr->m_messages.push({std::string(recv), std::string("symbol"), vec});
        }
        
        static void instance_multi_list(pd::Instance* ptr, const char *recv, int argc, t_atom *argv)
        {
            std::vector<Atom> vec(argc);
            for(int i = 0; i < argc; ++i)
            {
                if(argv[i].a_type == A_FLOAT)
                    vec[i] = Atom(atom_getfloat(argv+i));
                else if(argv[i].a_type == A_SYMBOL)
                    vec[i] = Atom(std::string(atom_getsymbol(argv+i)->s_name));
            }
            std::lock_guard<std::mutex> lock(ptr->m_messages_mutex);
            ptr->m_messages.push({std::string(recv), std::string("list"), vec});
        }
        
        static void instance_multi_message(pd::Instance* ptr, const char *recv, const char *msg, int argc, t_atom *argv)
        {
            std::vector<Atom> vec(argc);
            for(int i = 0; i < argc; ++i)
            {
                if(argv[i].a_type == A_FLOAT)
                    vec[i] = Atom(atom_getfloat(argv+i));
                else if(argv[i].a_type == A_SYMBOL)
                    vec[i] = Atom(std::string(atom_getsymbol(argv+i)->s_name));
            }
            std::lock_guard<std::mutex> lock(ptr->m_messages_mutex);
            ptr->m_messages.push({std::string(recv), std::string(msg), vec});
        }

        
        static void instance_multi_noteon(pd::Instance* ptr, int channel, int pitch, int velocity)
        {
            std::lock_guard<std::mutex> lock(ptr->m_midi_mutex);
            ptr->m_midi.push({midievent::NOTEON, channel, pitch, velocity});
        }
        
        static void instance_multi_controlchange(pd::Instance* ptr, int channel, int controller, int value)
        {
            std::lock_guard<std::mutex> lock(ptr->m_midi_mutex);
            ptr->m_midi.push({midievent::CONTROLCHANGE, channel, controller, value});
        }
        
        static void instance_multi_programchange(pd::Instance* ptr, int channel, int value)
        {
            std::lock_guard<std::mutex> lock(ptr->m_midi_mutex);
            ptr->m_midi.push({midievent::PROGRAMCHANGE, channel, value, 0});
        }
        
        static void instance_multi_pitchbend(pd::Instance* ptr, int channel, int value)
        {
            std::lock_guard<std::mutex> lock(ptr->m_midi_mutex);
            ptr->m_midi.push({midievent::PITCHBEND, channel, value, 0});
        }
        
        static void instance_multi_aftertouch(pd::Instance* ptr, int channel, int value)
        {
            std::lock_guard<std::mutex> lock(ptr->m_midi_mutex);
            ptr->m_midi.push({midievent::AFTERTOUCH, channel, value, 0});
        }
        
        static void instance_multi_polyaftertouch(pd::Instance* ptr, int channel, int pitch, int value)
        {
            std::lock_guard<std::mutex> lock(ptr->m_midi_mutex);
            ptr->m_midi.push({midievent::POLYAFTERTOUCH, channel, pitch, value});
        }
        
        static void instance_multi_midibyte(pd::Instance* ptr, int port, int byte)
        {
            std::lock_guard<std::mutex> lock(ptr->m_midi_mutex);
            ptr->m_midi.push({midievent::MIDIBYTE, port, byte, 0});
        }
        
        static void instance_multi_print(pd::Instance* ptr, char* s)
        {
            std::lock_guard<std::mutex> lock(ptr->m_prints_mutex);
            ptr->m_prints.push(s);
        }
    };
    
}

namespace pd
{
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    Instance::Instance()
    {
        libpd_multi_init();
        m_instance = libpd_new_instance();
        m_midi_receiver = libpd_multi_midi_new(this,
                                               reinterpret_cast<t_libpd_multi_noteonhook>(internal::instance_multi_noteon),
                                               reinterpret_cast<t_libpd_multi_controlchangehook>(internal::instance_multi_controlchange),
                                               reinterpret_cast<t_libpd_multi_programchangehook>(internal::instance_multi_programchange),
                                               reinterpret_cast<t_libpd_multi_pitchbendhook>(internal::instance_multi_pitchbend),
                                               reinterpret_cast<t_libpd_multi_aftertouchhook>(internal::instance_multi_aftertouch),
                                               reinterpret_cast<t_libpd_multi_polyaftertouchhook>(internal::instance_multi_polyaftertouch),
                                               reinterpret_cast<t_libpd_multi_midibytehook>(internal::instance_multi_midibyte));
        m_prints_receiver = libpd_multi_print_new(this,
                                                  reinterpret_cast<t_libpd_multi_printhook>(internal::instance_multi_print));
    }
    
    Instance::~Instance()
    {
        if(m_patch)
            closePatch();
        for(auto it : m_receivers)
        {
            pd_free((t_pd *)it.second);
        }
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_free_instance(static_cast<t_pdinstance *>(m_instance));
        pd_free((t_pd *)m_midi_receiver);
        pd_free((t_pd *)m_prints_receiver);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    void Instance::prepareDSP(const int nins, const int nouts, const int blksize, const double samplerate)
    {
        m_inputs.resize(blksize * nins);
        m_outputs.resize(blksize * nouts);
        
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_init_audio((int)nins, (int)nouts, (int)samplerate);
        
        libpd_start_message(1);
        libpd_add_float(1.f);
        libpd_finish_message("pd", "dsp");
    }
    
    void Instance::releaseDSP()
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_start_message(1);
        libpd_add_float(0.f);
        libpd_finish_message("pd", "dsp");
    }
    
    void Instance::performDSP(const int blksize,
                           const int nins, float const** inputs,
                           const int nouts, float** outputs)
    {
        for(int i = 0; i < nins; ++i)
        {
            for(int j = 0; j < blksize; ++j)
            {
                m_inputs[j*nins+i] = inputs[i][j];
            }
        }
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_process_float(blksize / 64, m_inputs.data(), m_outputs.data());
        for(int i = 0; i < nouts; ++i)
        {
            for(int j = 0; j < blksize; ++j)
            {
                outputs[i][j] = m_outputs[j*nouts+i];
            }
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////

    void Instance::sendNoteOn(const int channel, const int pitch, const int velocity) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_noteon(channel, pitch, velocity);
    }
    
    void Instance::sendControlChange(const int channel, const int controller, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_controlchange(channel, controller, value);
    }
    
    void Instance::sendProgramChange(const int channel, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_programchange(channel, value);
    }
    
    void Instance::sendPitchBend(const int channel, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_pitchbend(channel, value);
    }
    
    void Instance::sendAfterTouch(const int channel, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_aftertouch(channel, value);
    }
    
    void Instance::sendPolyAfterTouch(const int channel, const int pitch, const int value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_polyaftertouch(channel, pitch, value);
    }
    
    void Instance::sendSysEx(const int port, const int byte) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_sysex(port, byte);
    }
    
    void Instance::sendSysRealTime(const int port, const int byte) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_sysrealtime(port, byte);
    }
    
    void Instance::sendMidiByte(const int port, const int byte) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_midibyte(port, byte);
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void Instance::sendBang(std::string const& receiver) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_bang(receiver.c_str());
    }
    
    void Instance::sendFloat(std::string const& receiver, float const value) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_float(receiver.c_str(), value);
    }
    
    void Instance::sendSymbol(std::string const& receiver, std::string const& symbol) const
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_symbol(receiver.c_str(), symbol.c_str());
    }
    
    void Instance::sendList(std::string const& receiver, const std::vector<Atom>& list) const
    {
        t_atom* argv = (t_atom *)getbytes(sizeof(t_atom) * list.size());
        if(argv)
        {
            libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
            for(size_t i = 0; i < list.size(); ++i)
            {
                if(list[i].isFloat())
                    libpd_set_float(argv+i, list[i].getFloat());
                else
                    libpd_set_symbol(argv+i, list[i].getSymbol().c_str());
            }
            libpd_list(receiver.c_str(), (int)list.size(), argv);
            freebytes(argv, sizeof(t_atom) * list.size());
        }
    }
    
    void Instance::sendMessage(std::string const& receiver, const std::string& msg, const std::vector<Atom>& list) const
    {
        t_atom* argv = (t_atom *)getbytes(sizeof(t_atom) * list.size());
        if(argv)
        {
            libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
            for(size_t i = 0; i < list.size(); ++i)
            {
                if(list[i].isFloat())
                    libpd_set_float(argv+i, list[i].getFloat());
                else
                    libpd_set_symbol(argv+i, list[i].getSymbol().c_str());
            }
            libpd_message(receiver.c_str(), msg.c_str(), (int)list.size(), argv);
            freebytes(argv, sizeof(t_atom) * list.size());
        }
    }
    
    void Instance::processMessages()
    {
        m_messages_mutex.lock();
        while (!m_messages.empty())
        {
            message const mess = m_messages.front();
            m_messages.pop();
            m_messages_mutex.unlock();
            if(mess.selector == std::string("bang"))
            {
                receiveBang(mess.destination);
            }
            else if(mess.selector == std::string("float"))
            {
                receiveFloat(mess.destination, mess.list[0].getFloat());
            }
            else if(mess.selector == std::string("symbol"))
            {
                receiveSymbol(mess.destination, mess.list[0].getSymbol());
            }
            else if(mess.selector == std::string("list"))
            {
                receiveList(mess.destination, mess.list);
            }
            else
            {
                receiveMessage(mess.destination, mess.selector, mess.list);
            }
            m_messages_mutex.lock();
        }
        m_messages_mutex.unlock();
    }
    
    void Instance::processMidi()
    {
        m_midi_mutex.lock();
        while (!m_midi.empty())
        {
            midievent const event = m_midi.front();
            m_midi.pop();
            m_midi_mutex.unlock();
            if(event.type == midievent::NOTEON)
            {
                receiveNoteOn(event.midi1, event.midi2, event.midi3);
            }
            else if(event.type == midievent::CONTROLCHANGE)
            {
                receiveControlChange(event.midi1, event.midi2, event.midi3);
            }
            else if(event.type == midievent::PROGRAMCHANGE)
            {
                receiveProgramChange(event.midi1, event.midi2);
            }
            else if(event.type == midievent::PITCHBEND)
            {
                receivePitchBend(event.midi1, event.midi2);
            }
            else if(event.type == midievent::AFTERTOUCH)
            {
                receiveAftertouch(event.midi1, event.midi2);
            }
            else if(event.type == midievent::POLYAFTERTOUCH)
            {
                receivePolyAftertouch(event.midi1, event.midi2, event.midi3);
            }
            else if(event.type == midievent::MIDIBYTE)
            {
                receiveMidiByte(event.midi1, event.midi2);
            }
            m_midi_mutex.lock();
        }
        m_midi_mutex.unlock();
    }
    
    void Instance::processPrints()
    {
        m_prints_mutex.lock();
        while (!m_prints.empty())
        {
            auto const message = m_prints.front();
            m_prints.pop();
            m_prints_mutex.unlock();
            receivePrint(message);
            m_prints_mutex.lock();
        }
        m_prints_mutex.unlock();
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void Instance::bind(std::string const& symbol)
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        if(m_receivers.find(symbol) == m_receivers.end())
        {
            void* receiver = libpd_multi_receiver_new(this, symbol.c_str(),
                                                      reinterpret_cast<t_libpd_multi_banghook>(internal::instance_multi_bang),
                                                      reinterpret_cast<t_libpd_multi_floathook>(internal::instance_multi_float),
                                                      reinterpret_cast<t_libpd_multi_symbolhook>(internal::instance_multi_symbol),
                                                      reinterpret_cast<t_libpd_multi_listhook>(internal::instance_multi_list),
                                                      reinterpret_cast<t_libpd_multi_messagehook>(internal::instance_multi_message));
            m_receivers[symbol] = receiver;
        }
    }
    
    void Instance::unbind(std::string const& symbol)
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        auto it = m_receivers.find(symbol);
        if(it != m_receivers.end())
        {
            sys_lock();
            pd_free((t_pd *)it->second);
            sys_unlock();
            m_receivers.erase(it);
        }
    }
    
    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    
    void Instance::openPatch(std::string const& path, std::string const& name)
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        m_patch = libpd_openfile(name.c_str(), path.c_str());
    }
    
    void Instance::closePatch()
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
        libpd_closefile(m_patch);
    }
    
    Patch Instance::getPatch()
    {
        return Patch(m_patch, this);
    }
    
    void Instance::setThis()
    {
        libpd_set_instance(static_cast<t_pdinstance *>(m_instance));
    }
}

