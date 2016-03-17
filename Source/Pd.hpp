/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD__
#define __CAMOMILE_PD__

#include "PdGui.hpp"

extern "C"
{
#include "../ThirdParty/PureData/src/m_pd.h"
}

namespace pd
{
    class Instance;
    
    // ==================================================================================== //
    //                                      MIDI EVENT                                      //
    // ==================================================================================== //
    class MidiEvent
    {
    public:
        typedef unsigned char data_t;
        enum class Type : data_t
        {
            NoteOn          = 0,
            NoteOff         = 1,
            ControlChange   = 2,
            ProgramChange   = 3,
            PitchBend       = 4,
            AfterTouch      = 5,
            PolyafterTouch  = 6,
            Byte            = 7
        };
        
        inline static constexpr MidiEvent Note(const data_t channel, const data_t pitch, const data_t velocity) {return MidiEvent(velocity ? 0 : 1, channel, pitch, velocity);}
        inline static constexpr MidiEvent NoteOn(const data_t channel, const data_t pitch, const data_t velocity) {return MidiEvent(0, channel, pitch, velocity);}
        inline static constexpr MidiEvent NoteOff(const data_t channel, const data_t pitch, const data_t velocity) {return MidiEvent(1, channel, pitch, velocity);}
        inline static constexpr MidiEvent ControlChange(const data_t channel, const data_t controller, const data_t control) {return MidiEvent(2, channel, controller, control);}
        inline static constexpr MidiEvent ProgramChange(const data_t channel, const data_t program) {return MidiEvent(3, channel, program, 0);}
        inline static MidiEvent PitchBend(const data_t channel, const int pitchbend) {return MidiEvent(4, channel, pitchbend);}
        inline static constexpr MidiEvent AfterTouch(const data_t channel, const data_t aftertouch) {return MidiEvent(5, channel, 0, aftertouch);}
        inline static constexpr MidiEvent PolyafterTouch(const data_t channel, const data_t pitch, const data_t aftertouch) {return MidiEvent(6, channel, pitch, aftertouch);}
        inline static constexpr MidiEvent Byte(const data_t port, const data_t byte) {return MidiEvent(7, port, byte, 0);}
        
        inline Type getType() const noexcept {return *(reinterpret_cast<const Type*>(m_datas));}
        inline bool isNote() const noexcept {return getType() == Type::NoteOn || getType() == Type::NoteOff;}
        inline bool isNoteOn() const noexcept {return getType() == Type::NoteOn;}
        inline bool isNoteOff() const noexcept {return getType() == Type::NoteOff;}
        inline bool isControlChange() const noexcept {return getType() == Type::ControlChange;}
        inline bool isProgramChange() const noexcept {return getType() == Type::ProgramChange;}
        inline bool isPitchBend() const noexcept {return getType() == Type::PitchBend;}
        inline bool isAfterTouch() const noexcept {return getType() == Type::AfterTouch;}
        inline bool isPolyafterTouch() const noexcept {return getType() == Type::PolyafterTouch;}
        inline bool isMidiByte() const noexcept {return getType() == Type::Byte;}
                                     
        inline data_t getChannel() const noexcept {return m_datas[1];}
        inline data_t getPitch() const noexcept {return m_datas[2];}
        inline data_t getVelocity() const noexcept {return m_datas[3];}
        inline data_t getController() const noexcept {return m_datas[2];}
        inline data_t getControl() const noexcept {return m_datas[3];}
        inline data_t getProgram() const noexcept {return m_datas[2];}
        inline int getPitchBend() const noexcept {return *(reinterpret_cast<const int*>(m_datas+2));}
        inline data_t getAfterTouch() const noexcept {return m_datas[3];}
        inline data_t getPort() const noexcept {return m_datas[1];}
        inline data_t getByte() const noexcept {return m_datas[2];}
    private:
        inline constexpr MidiEvent(const data_t type, const data_t val1, const data_t val2, const data_t val3) : m_datas{type, val1, val2, val3} {}
        inline MidiEvent(const data_t type, const data_t val1, const int val2) :
        m_datas{type, val1, *(reinterpret_cast<const data_t*>(&val2)), *(reinterpret_cast<const data_t*>(&val2)+1)} {}
        
        const data_t m_datas[4];
    };
    
    typedef std::vector<MidiEvent> MidiList;
    
    // ==================================================================================== //
    //                                      POST                                            //
    // ==================================================================================== //
    //! @brief The post.
    //! @details The wrapper for post, error and log messages.
    class Post
    {
    public:
        enum class Type : unsigned char
        {
            Post    = 0,
            Error   = 1,
            Log     = 2
        };
        std::string message;
        Type        type;
    };
    
    // ==================================================================================== //
    //                                      PD                                              //
    // ==================================================================================== //
    
    //! @brief Pure Data.
    //! @details The wrapper for Pure Data environment.
    class Pd
    {
    public:        
        //! @brief Adds a path the global search path.
        static std::string getPdVersion();
        
        //! @brief Adds a path the global search path.
        static void addToSearchPath(std::string const& path) noexcept;
        
        //! @brief Clears all the paths of the global search path.
        static void clearSearchPath() noexcept;
        
        //! @brief Sets the text of the console.
        static void clearConsole() noexcept;
        
        //! @brief Sets the text of the console.
        static void postToConsole(std::string const& text) noexcept;
        
        //! @brief Sets the text of the console.
        static void logToConsole(std::string const& text) noexcept;
        
        //! @brief Sets the text of the console.
        static void errorToConsole(std::string const& text) noexcept;
        
        //! @brief Retrieves the text of the console.
        static std::vector<Post> getConsole(bool state = false) noexcept;
        
        //! @brief Retrieves the text of the console.
        static bool hasConsoleChanged() noexcept;
        
        //! @brief Creates a new Instance object.
        static Instance createInstance() noexcept;
        
        
        
        
        static void sendNote(int channel, int pitch, int velocity);
        
        static void sendControlChange(int channel, int controller, int value);
        
        static void sendProgramChange(int channel, int value);
        
        static void sendPitchBend(int channel, int value);
        
        static void sendAfterTouch(int channel, int value);
        
        static void sendPolyAfterTouch(int channel, int pitch, int value);
        
        static void sendMidiByte(int port, int byte);
        
        static void sendSysEx(int port, int byte);
        
        static void sendSysRealtime(int port, int byte);
        
        //! Dirty
        static void clearMidi();
        
        //! Dirty
        static std::vector<MidiEvent>::const_iterator getMidiBegin();
        
        //! Dirty
        static std::vector<MidiEvent>::const_iterator getMidiEnd();
    
    private:
        
        //! @brief The Pure Data contructor.
        Pd() noexcept;
        
        //! @brief The Pure Data destructor.
        ~Pd() noexcept;
        
        //! @brief Gets the singleton of Pure Data.
        static Pd& get() noexcept;
        
        //! @brief Locks Pure Data.
        static void lock() noexcept;
        
        //! @brief Unlocks Pure Data.
        static void unlock() noexcept;
        
        // For Instance
        
        //! @brief Releases an Instance.
        static void free(Instance& instance);
        
        
        const int                   m_max_channels = 16;
        std::mutex                  m_mutex;
        void*                       m_sample_ins;
        void*                       m_sample_outs;
        
        std::mutex                  m_console_mutex;
        bool                        m_console_changed;
        std::vector<Post>           m_console;
        
        static void print(const char* s);
        
        friend class Instance;
    };
}

#endif
