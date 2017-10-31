/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include <vector>

namespace xpd
{
    // ==================================================================================== //
    //                                      ENVIRONMENT                                     //
    // ==================================================================================== //
    
    //! @brief The environment manages xpd global variables and methods.
    class environment
    {
    public:
        //! @brief Initializes the environment.
        static void initialize() noexcept;
        
        //! @brief Clears the environment.
        static void  clear() noexcept;
    };
    
    class midi
    {
        
    };
    
    // ==================================================================================== //
    //                                      INSTANCE                                        //
    // ==================================================================================== //
    
    class instance
    {
    public:
        instance();
        ~instance();
        
        void prepare(const int nins, const int nouts, const int blksize, const double samplerate);
        void release();
        void perform(const int blksize, const int nins, float const** inputs, const int nouts, float** outputs);
        
        void sendNoteOn(const int channel, const int pitch, const int velocity);
        void sendControlChange(const int channel, const int controller, const int value);
        void sendProgramChange(const int channel, const int value);
        void sendPitchBend(const int channel, const int value);
        void sendAfterTouch(const int channel, const int value);
        void sendPolyAfterTouch(const int channel, const int pitch, const int value);
        void sendSysEx(const int port, const int byte);
        void sendSysRealTime(const int port, const int byte);
        void sendMidiByte(const int port, const int byte);
    private:
        void* m_ptr         = nullptr;
        std::vector<float> m_inputs;
        std::vector<float> m_outputs;
    };
}
