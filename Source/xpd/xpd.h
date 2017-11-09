/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include <vector>
#include <queue>
#include <utility>
#include <string>
#include <mutex>

namespace pd
{
    // ==================================================================================== //
    //                                      INSTANCE                                        //
    // ==================================================================================== //
    
    class Atom
    {
    public:
        enum Type
        {
            FLOAT,
            SYMBOL
        };
        
        Type        type = FLOAT;
        float       value = 0;
        std::string symbol;
        
        Atom() : type(FLOAT), value(0), symbol() {}
        Atom(const float val) : type(FLOAT), value(val), symbol() {}
        Atom(const std::string& sym) : type(SYMBOL), value(0), symbol(sym) {}
    };
    
    class instance
    {
    public:
        
        instance();
        virtual ~instance();
        
        void prepareDSP(const int nins, const int nouts, const int blksize, const double samplerate);
        void releaseDSP();
        void performDSP(const int blksize, const int nins, float const** inputs, const int nouts, float** outputs);
        
        void sendNoteOn(const int channel, const int pitch, const int velocity);
        void sendControlChange(const int channel, const int controller, const int value);
        void sendProgramChange(const int channel, const int value);
        void sendPitchBend(const int channel, const int value);
        void sendAfterTouch(const int channel, const int value);
        void sendPolyAfterTouch(const int channel, const int pitch, const int value);
        void sendSysEx(const int port, const int byte);
        void sendSysRealTime(const int port, const int byte);
        void sendMidiByte(const int port, const int byte);
        
        virtual void receiveNoteOn(const int channel, const int pitch, const int velocity) {}
        virtual void receiveControlChange(const int channel, const int controller, const int value) {}
        virtual void receiveProgramChange(const int channel, const int value) {}
        virtual void receivePitchBend(const int channel, const int value) {}
        virtual void receiveAftertouch(const int channel, const int value) {}
        virtual void receivePolyAftertouch(const int channel, const int pitch, const int value) {}
        virtual void receiveMidiByte(const int port, const int byte) {}
        
        void sendBang(std::string const& receiver);
        void sendFloat(std::string const& receiver, float const value);
        void sendSymbol(std::string const& receiver, std::string const& symbol);
        void sendList(std::string const& receiver, const std::vector<Atom>& list);
        void sendMessage(std::string const& receiver, const std::string& msg, const std::vector<Atom>& list);
        
        virtual void print(const std::string& message) {};
        
        virtual void receiveBang(const std::string& dest) {}
        virtual void receiveFloat(const std::string& dest, float num) {}
        virtual void receiveSymbol(const std::string& dest, const std::string& symbol) {}
        virtual void receiveList(const std::string& dest, const std::vector<Atom>& list) {}
        virtual void receiveMessage(const std::string& dest, const std::string& msg, const std::vector<Atom>& list) {}
        
        void processReceive();
        
        void bind(std::string const& symbol);
        void unbind(std::string const& symbol);
        
        void open(std::string const& path, std::string const& name);
        void close();
    private:
        
        void* m_instance    = nullptr;
        void* m_patch       = nullptr;
        
        std::vector<float> m_inputs;
        std::vector<float> m_outputs;
        
        struct _libpd_multirec;
        std::mutex                               m_messages_mutex;
        std::vector<void*>                       m_receivers;
        struct message
        {
            std::string destination;
            std::string selector;
            std::vector<Atom> list;
        };
        std::queue<message> m_messages;
    };
}
