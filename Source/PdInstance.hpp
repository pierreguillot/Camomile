/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_INSTANCE_HPP
#define Z_PD_INSTANCE_HPP

#include "PdEnvironment.hpp"

namespace pd
{
    class Patch;
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    //! @brief The Pure Data instance.
    //! @details The Instance is a wrapper for the Pure Data's native instance.
    //! With the default constructor, the Instance won't be initialized. The Instance has some
    //! kind of smart pointer behavior so when an Instance object is no more useful the object
    //! is deleted.
    class Instance
    {
    public:
        
        //! @brief The constructor for an empty Instance.
        //! @details Creates an Instance that can be used as an empty reference inside
        //! another class.
        Instance() noexcept;
        
        //! @brief The copy constructor.
        //! Creates a copy of an Instance and increments his counter.
        Instance(Instance const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Instance without incrementing his counter. The
        //! other Instance will be useless.
        Instance(Instance&& other) noexcept;
        
        //! @brief The copy operator.
        //! Copies the Instance and increments his counter.
        Instance& operator=(Instance const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Instance without incrementing his counter. The other
        //! Instance will be destroyed if needed.
        Instance& operator=(Instance&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Instance will be destroyed if no other copy exists.
        virtual ~Instance() noexcept;
        
        //! @brief Retrieves if the Instance is valid.
        bool isValid() const noexcept;
        
        //! @brief Retrieves the sample rate of the Instance.
        int getSampleRate() const noexcept;
        
    protected:
        
        //! @brief The real constructor.
        Instance(const std::string& name) noexcept;
        
        //! @brief Locks Instance.
        void lock() noexcept;
        
        //! @brief Unlocks Instance.
        void unlock() noexcept;
        
        //! @brief Prepares the digital signal processing chain of the Instance.
        void prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept;
        
        //! @brief Performs the digital signal processing chain of the Instance.
        //! @details You should locks the Instance to ensure thread safety.
        void performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept;
        
        //! @brief Releases the digital signal processing chain of the Instance.
        void releaseDsp() noexcept;
        
        
        
        //! @brief Sends a post.
        void sendPost(std::string const& message) const;
        
        //! @brief Receives a post.
        virtual void receivePost(std::string const& message) {};
        
        
        
        //! @brief Sends midi note on.
        void sendMidiNote(int channel, int pitch, int velocity) const;
        
        //! @brief Sends midi control change.
        void sendMidiControlChange(int channel, int controller, int value) const;
        
        //! @brief Sends midi program change.
        void sendMidiProgramChange(int channel, int value) const;
        
        //! @brief Sends midi pitch bend.
        void sendMidiPitchBend(int channel, int value) const;
        
        //! @brief Sends midi after touch.
        void sendMidiAfterTouch(int channel, int value) const;
        
        //! @brief Sends midi poly after touch.
        void sendMidiPolyAfterTouch(int channel, int pitch, int value) const;
        
        //! @brief Sends midi byte.
        void sendMidiByte(int port, int byte) const;
        
        //! @brief Sends midi sys ex.
        void sendMidiSysEx(int port, int byte) const;
        
        //! @brief Sends midi sys real time.
        void sendMidiSysRealtime(int port, int byte) const;
        
        //! @brief Receives midi note on.
        virtual void receiveMidiNoteOn(int port, int channel, int pitch, int velocity) {};
        
        //! @brief Receives midi control change.
        virtual void receiveMidiControlChange(int port, int channel, int control, int value) {}
        
        //! @brief Receives midi program change.
        virtual void receiveMidiProgramChange(int port, int channel, int value) {}
        
        //! @brief Receives midi pitch bend.
        virtual void receiveMidiPitchBend(int port, int channel, int value) {}
        
        //! @brief Receives midi after touch.
        virtual void receiveMidiAfterTouch(int port, int channel, int value) {}
        
        //! @brief Receives midi poly after touch.
        virtual void receiveMidiPolyAfterTouch(int port, int channel, int pitch, int value) {}
        
        //! @brief Receives midi byte.
        virtual void receiveMidiByte(int port, int value) {}
        
        
        
        
        //! @brief Sends bang.
        void sendMessageBang(Tie const& name) const;
        
        //! @brief Sends float.
        void sendMessageFloat(Tie const& name, float f) const;
        
        //! @brief Sends symbol.
        void sendMessageSymbol(Tie const& name, Symbol const& s) const;
        
        //! @brief Sends gpointer.
        void sendMessageGpointer(Tie const& name, Gpointer const& g) const;
        
        //! @brief Sends list.
        void sendMessageList(Tie const& name, List const& list) const;
        
        //! @brief Sends anything.
        void sendMessageAnything(Tie const& name, Symbol const& s, List const& list) const;
        
        //! @brief Receives bang.
        virtual void receiveMessageBang(Tie const& tie) {}
        
        //! @brief Receives float.
        virtual void receiveMessageFloat(Tie const& tie, float f) {}
        
        //! @brief Receives symbol.
        virtual void receiveMessageSymbol(Tie const& tie, Symbol const& s) {}
        
        //! @brief Receives gpointer.
        virtual void receiveMessageGpointer(Tie const& tie, Gpointer const& g) {}
        
        //! @brief Receives list.
        virtual void receiveMessageList(Tie const& tie, List const& list) {}
        
        //! @brief Receives anything.
        virtual void receiveMessageAnything(Tie const& tie, Symbol const& s, List const& list) {}
        
    private:
        struct Internal;
        void release() noexcept;
        
        void*               m_ptr;
        std::atomic<long>*  m_count;
        friend class Patch;
        
    };

}

#endif // Z_PD_INSTANCE_HPP
