/*
 // Copyright (c) 2015-2017 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include <vector>
#include <string>

namespace xpd
{
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
        
        void sendBang(std::string const& receiver);
        void sendFloat(std::string const& receiver, float const value);
        void sendSymbol(std::string const& receiver, std::string const& symbol);
        
        void open(std::string const& path, std::string const& name);
        void close();
    private:
        void* m_ptr         = nullptr;
        void* m_patch       = nullptr;
        std::vector<float> m_inputs;
        std::vector<float> m_outputs;
    };
}
