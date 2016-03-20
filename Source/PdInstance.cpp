/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdInstance.hpp"
#include "PdPatch.hpp"

extern "C"
{
#include "z_pd.h"
    
}

namespace pd
{
    struct Instance::Internal : public Smuggler
    {
    public:
        z_instance object;
        Instance*  ref;
        
        static void m_print(Instance::Internal* instance, const char *s)
        {
            instance->ref->receivePost(s);
        }
        
        static void m_noteon(Instance::Internal* instance, int port, int channel, int pitch, int velocity)
        {
            instance->ref->receiveMidiNoteOn(port, channel, pitch, velocity);
        }
        
        static void m_controlchange(Instance::Internal* instance, int port, int channel, int control, int value)
        {
            instance->ref->receiveMidiControlChange(port, channel, control, value);
        }
        
        static void m_programchange(Instance::Internal* instance, int port, int channel, int value)
        {
            instance->ref->receiveMidiProgramChange(port, channel, value);
        }
        
        static void m_pitchbend(Instance::Internal* instance, int port, int channel, int value)
        {
            instance->ref->receiveMidiPitchBend(port, channel, value);
        }
        
        static void m_aftertouch(Instance::Internal* instance, int port, int channel, int value)
        {
            instance->ref->receiveMidiAfterTouch(port, channel, value);
        }
        
        static void m_polyaftertouch(Instance::Internal* instance, int port, int channel, int pitch, int value)
        {
            instance->ref->receiveMidiPolyAfterTouch(port, channel, pitch, value);
        }
        
        static void m_byte(Instance::Internal* instance, int port, int value)
        {
            instance->ref->receiveMidiByte(port, value);
        }
        
        
        
        
        static void m_bang(Instance::Internal* instance, z_tie* tie)
        {
            instance->ref->receiveMessageBang(createTie(tie));
        }
        
        static void m_float(Instance::Internal* instance, z_tie* tie, z_float f)
        {
            instance->ref->receiveMessageFloat(createTie(tie), f);
        }
        
        static void m_symbol(Instance::Internal* instance, z_tie* tie, z_symbol* s)
        {
            instance->ref->receiveMessageSymbol(createTie(tie), createSymbol(s));
        }
        
        static void m_gpointer(Instance::Internal* instance, z_tie* tie, z_gpointer *g)
        {
            instance->ref->receiveMessageGpointer(createTie(tie), createGpointer(g));
        }
        
        static void m_list(Instance::Internal* instance, z_tie* tie, z_list *list)
        {
            instance->ref->receiveMessageList(createTie(tie), List(list));
        }
        
        static void m_anything(Instance::Internal* instance, z_tie* tie, z_symbol *s, z_list *list)
        {
            instance->ref->receiveMessageAnything(createTie(tie), createSymbol(s), List(list));
        }
    };
    
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    Instance::Instance(const std::string& name) noexcept
    {
        Environment::lock();
        m_ptr = z_pd_instance_new(sizeof(Instance::Internal),
                                  (z_hook_print)Instance::Internal::m_print,
                                  (z_hook_noteon)Instance::Internal::m_noteon,
                                  (z_hook_controlchange)Instance::Internal::m_controlchange,
                                  (z_hook_programchange)Instance::Internal::m_programchange,
                                  (z_hook_pitchbend)Instance::Internal::m_pitchbend,
                                  (z_hook_aftertouch)Instance::Internal::m_aftertouch,
                                  (z_hook_polyaftertouch)Instance::Internal::m_polyaftertouch,
                                  (z_hook_byte)Instance::Internal::m_byte);
        reinterpret_cast<Instance::Internal*>(m_ptr)->ref = this;
        m_count = new std::atomic<long>(1);
        Environment::unlock();
    }
    
    Instance::Instance() noexcept :
    m_ptr(nullptr),
    m_count(nullptr)
    {
        
    }
    
    
    Instance::Instance(Instance const& other) noexcept :
    m_ptr(other.m_ptr),
    m_count(other.m_count)
    {
        if(m_ptr && m_count)
        {
            ++(*m_count);
        }
    }
    
    Instance::Instance(Instance&& other) noexcept :
    m_ptr(other.m_ptr),
    m_count(other.m_count)
    {
        other.m_ptr         = nullptr;
        other.m_count       = nullptr;
    }
    
    void Instance::release() noexcept
    {
        if(m_ptr && m_count && m_count->operator--() == 0)
        {
            releaseDsp();
            lock();
            z_pd_instance_free(reinterpret_cast<z_instance *>(m_ptr));
            unlock();
            delete m_count;
            m_ptr           = nullptr;
            m_count         = nullptr;
        }
    }
    
    Instance& Instance::operator=(Instance const& other) noexcept
    {
        release();
        if(other.m_ptr && other.m_count && other.m_count->operator++() > 0)
        {
            m_ptr           = other.m_ptr;
            m_count         = other.m_count;
        }
        return *this;
    }
    
    Instance& Instance::operator=(Instance&& other) noexcept
    {
        std::swap(m_count, other.m_count);
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }
    
    Instance::~Instance() noexcept
    {
        release();
    }
    
    void Instance::prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept
    {
        lock();
        z_pd_instance_dsp_prepare(reinterpret_cast<z_instance *>(m_ptr), nins, nouts, samplerate, nsamples);
        unlock();
    }

    void Instance::performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept
    {
        z_pd_instance_dsp_perform(reinterpret_cast<z_instance *>(m_ptr), nsamples, nins, inputs, nouts, outputs);
    }
    
    void Instance::releaseDsp() noexcept
    {
        lock();
        z_pd_instance_dsp_release(reinterpret_cast<z_instance *>(m_ptr));
        unlock();
    }
    
    
    
    
    
    void Instance::consolePost(std::string const& message) noexcept
    {
        lock();
        z_pd_console_post(message.c_str());
        unlock();
    }
    
    void Instance::consoleLog(std::string const& message) noexcept
    {
        lock();
        z_pd_console_log(message.c_str());
        unlock();
    }
    
    void Instance::consoleError(std::string const& message) noexcept
    {
        lock();
        z_pd_console_error(message.c_str());
        unlock();
    }
    
    void Instance::consoleFatal(std::string const& message) noexcept
    {
        lock();
        z_pd_console_fatal(message.c_str());
        unlock();
    }
    
    
    
    
    
    
    void Instance::sendMessageBang(Tie const& name) const
    {
        z_pd_messagesend_bang(reinterpret_cast<z_tie const *>(getTie(name)));
    }
    
    void Instance::sendMessageFloat(Tie const& name, float val) const
    {
        z_pd_messagesend_float(reinterpret_cast<z_tie const *>(getTie(name)), val);
    }
    
    void Instance::sendMessageSymbol(Tie const& name, Symbol const& s) const
    {
        z_pd_messagesend_symbol(reinterpret_cast<z_tie const *>(getTie(name)),
                                reinterpret_cast<z_symbol const *>(getSymbol(s)));
    }
    
    void Instance::sendMessageGpointer(Tie const& name, Gpointer const& g) const
    {
        z_pd_messagesend_gpointer(reinterpret_cast<z_tie const *>(getTie(name)),
                                  reinterpret_cast<z_gpointer const *>(getGpointer(g)));
    }
    
    void Instance::sendMessageList(Tie const& name, List const& list) const
    {
        z_pd_messagesend_list(reinterpret_cast<z_tie const *>(getTie(name)),
                              reinterpret_cast<z_list const *>(list.get()));
    }
    
    void Instance::sendMessageAnything(Tie const& name, Symbol const& s, List const& list) const
    {
        z_pd_messagesend_anything(reinterpret_cast<z_tie const *>(getTie(name)),
                                  reinterpret_cast<z_symbol const *>(getSymbol(s)),
                                  reinterpret_cast<z_list const *>(list.get()));
    }
    
    void Instance::sendMidiNote(int channel, int pitch, int velocity) const
    {
        z_pd_midisend_noteon(channel, pitch, velocity);
    }
    
    void Instance::sendMidiControlChange(int channel, int controller, int value) const
    {
        z_pd_midisend_controlchange(channel, controller, value);
    }
    
    void Instance::sendMidiProgramChange(int channel, int value) const
    {
        z_pd_midisend_programchange(channel, value);
    }
    
    void Instance::sendMidiPitchBend(int channel, int value) const
    {
        z_pd_midisend_pitchbend(channel, value);
    }
    
    void Instance::sendMidiAfterTouch(int channel, int value) const
    {
        z_pd_midisend_aftertouch(channel, value);
    }
    
    void Instance::sendMidiPolyAfterTouch(int channel, int pitch, int value) const
    {
        z_pd_midisend_polyaftertouch(channel, pitch, value);
    }
    
    void Instance::sendMidiByte(int port, int byte) const
    {
        z_pd_midisend_byte(port, byte);
    }
    
    void Instance::sendMidiSysEx(int port, int byte) const
    {
        z_pd_midisend_sysex(port, byte);
    }
    
    void Instance::sendMidiSysRealtime(int port, int byte) const
    {
        z_pd_midisend_sysrealtimein(port, byte);
    }
    
    void Instance::lock() noexcept
    {
        Environment::lock();
        z_pd_instance_set(reinterpret_cast<z_instance *>(m_ptr));
    }
    
    void Instance::unlock() noexcept
    {
        Environment::unlock();
    }
    
    bool Instance::isValid() const noexcept
    {
        return bool(m_ptr) && bool(m_count) && bool(m_count->load());
    }
    
    int Instance::getSampleRate() const noexcept
    {
        return z_pd_instance_get_samplerate(reinterpret_cast<z_instance *>(m_ptr));
    }
}



