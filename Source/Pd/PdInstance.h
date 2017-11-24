/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include <vector>
#include <queue>
#include <map>
#include <utility>
#include <string>
#include <mutex>

namespace pd
{
    class Patch;
    // ==================================================================================== //
    //                                      INSTANCE                                        //
    // ==================================================================================== //
    
    class Atom
    {
    public:
        
        inline Atom() : type(FLOAT), value(0), symbol() {}
        inline Atom(const float val) : type(FLOAT), value(val), symbol() {}
        inline Atom(const std::string& sym) : type(SYMBOL), value(0), symbol(sym) {}
        inline Atom(const char* sym) : type(SYMBOL), value(0), symbol(sym) {}
        
        inline bool isFloat() const noexcept { return type == FLOAT; }
        inline bool isSymbol() const noexcept { return type == SYMBOL; }
        inline float getFloat() const noexcept { return value; }
        inline std::string const& getSymbol() const noexcept { return symbol; }
        
        inline bool operator==(Atom const& other) const noexcept {
            if(type == SYMBOL) { return other.type == SYMBOL && symbol == other.symbol; }
            else { return other.type == FLOAT && value == other.value; } }
    private:
        
        enum Type
        {
            FLOAT,
            SYMBOL
        };
        
        Type        type = FLOAT;
        float       value = 0;
        std::string symbol;
    };
    
    class Instance
    {
    public:
        
        Instance();
        virtual ~Instance();
        
        void prepareDSP(const int nins, const int nouts, const int blksize, const double samplerate);
        void releaseDSP();
        void performDSP(const int blksize, const int nins, float const** inputs, const int nouts, float** outputs);
        
        void sendNoteOn(const int channel, const int pitch, const int velocity) const;
        void sendControlChange(const int channel, const int controller, const int value) const;
        void sendProgramChange(const int channel, const int value) const;
        void sendPitchBend(const int channel, const int value) const;
        void sendAfterTouch(const int channel, const int value) const;
        void sendPolyAfterTouch(const int channel, const int pitch, const int value) const;
        void sendSysEx(const int port, const int byte) const;
        void sendSysRealTime(const int port, const int byte) const;
        void sendMidiByte(const int port, const int byte) const;
        
        virtual void receiveNoteOn(const int channel, const int pitch, const int velocity) {}
        virtual void receiveControlChange(const int channel, const int controller, const int value) {}
        virtual void receiveProgramChange(const int channel, const int value) {}
        virtual void receivePitchBend(const int channel, const int value) {}
        virtual void receiveAftertouch(const int channel, const int value) {}
        virtual void receivePolyAftertouch(const int channel, const int pitch, const int value) {}
        virtual void receiveMidiByte(const int port, const int byte) {}
        
        void sendBang(std::string const& receiver) const;
        void sendFloat(std::string const& receiver, float const value) const;
        void sendSymbol(std::string const& receiver, std::string const& symbol) const;
        void sendList(std::string const& receiver, const std::vector<Atom>& list) const;
        void sendMessage(std::string const& receiver, const std::string& msg, const std::vector<Atom>& list) const;
        
        virtual void receivePrint(const std::string& message) {};
        
        virtual void receiveBang(const std::string& dest) {}
        virtual void receiveFloat(const std::string& dest, float num) {}
        virtual void receiveSymbol(const std::string& dest, const std::string& symbol) {}
        virtual void receiveList(const std::string& dest, const std::vector<Atom>& list) {}
        virtual void receiveMessage(const std::string& dest, const std::string& msg, const std::vector<Atom>& list) {}
        
        
        void processMessages();
        void processPrints();
        void processMidi();
        
        void bind(std::string const& symbol);
        void unbind(std::string const& symbol);
        
        void openPatch(std::string const& path, std::string const& name);
        void closePatch();
        Patch getPatch();

    private:
        
        void* m_instance    = nullptr;
        void* m_patch       = nullptr;
        
        std::vector<float> m_inputs;
        std::vector<float> m_outputs;
        
        struct message
        {
            std::string destination;
            std::string selector;
            std::vector<Atom> list;
        };
        std::queue<message>             m_messages;
        std::mutex                      m_messages_mutex;
        std::map<std::string, void*>    m_receivers;
        
        typedef struct midievent
        {
            enum
            {
                NOTEON,
                CONTROLCHANGE,
                PROGRAMCHANGE,
                PITCHBEND,
                AFTERTOUCH,
                POLYAFTERTOUCH,
                MIDIBYTE
            } type;
            int  midi1;
            int  midi2;
            int  midi3;
        } midievent;
        
        std::queue<midievent> m_midi;
        std::mutex            m_midi_mutex;
        void*                 m_midi_receiver;
        
        std::queue<std::string> m_prints;
        std::mutex              m_prints_mutex;
        void*                   m_prints_receiver;
        
        struct internal;
    };
}
