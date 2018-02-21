/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include <vector>
#include <map>
#include <utility>
#include <string>
#include "../../Dependencies/ReaderwriterQueue/readerwriterqueue.h"
#include "../../Dependencies/ConcurrentQueue/concurrentqueue.h"

namespace pd
{
    class Patch;
    class Atom;
    // ==================================================================================== //
    //                                      INSTANCE                                        //
    // ==================================================================================== //
    
    class Instance
    {
    public:
        
        Instance();
        virtual ~Instance();
        
        void prepareDSP(const int nins, const int nouts, const int blksize, const double samplerate);
        void startDSP();
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
        
        void enqueueMessages(const std::string& dest, const std::string& msg, std::vector<Atom>&& list);
        void enqueueDirectMessages(void* object, const std::string& msg);
        void enqueueDirectMessages(void* object, const float msg);
        
        virtual void messageEnqueued() {};
        
        void dequeueMessages();
        void processMessages();
        void processPrints();
        void processMidi();
        
        void bind(std::string const& symbol);
        void unbind(std::string const& symbol);
        
        void openPatch(std::string const& path, std::string const& name);
        void closePatch();
        Patch getPatch();
        
        void readArray(std::string const& name, std::vector<float>& output) const;
        void writeArray(std::string const& name, std::vector<float> const& input);

        void setThis();
    private:
        
        void* m_instance    = nullptr;
        void* m_patch       = nullptr;
        void* m_atoms       = nullptr;
        std::vector<float> m_inputs  = std::vector<float>(64);
        std::vector<float> m_outputs = std::vector<float>(64);
        int                m_advance = 0;
        
        struct message
        {
            std::string destination;
            std::string selector;
            std::vector<Atom> list;
        };
        
        struct dmessage
        {
            void*       object;
            std::string destination;
            std::string selector;
            std::vector<Atom> list;
        };
        
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
        
        typedef moodycamel::ConcurrentQueue<dmessage> message_queue;
        message_queue m_send_queue = message_queue(4096);
        moodycamel::ReaderWriterQueue<message> m_message_queue = moodycamel::ReaderWriterQueue<message>(4096);
        moodycamel::ReaderWriterQueue<midievent> m_midi_queue = moodycamel::ReaderWriterQueue<midievent>(4096);
        moodycamel::ReaderWriterQueue<std::string> m_print_queue = moodycamel::ReaderWriterQueue<std::string>(4096);
        
        std::map<std::string, void*> m_message_receivers;
        void*   m_midi_receiver;
        void*   m_print_receiver;
        
        struct internal;
    };
    
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
}
