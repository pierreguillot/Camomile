/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "Pd.hpp"
#include "PdInstance.hpp"
#include <signal.h>

static std::vector<pd::MidiEvent> midiout;

extern "C"
{
#include "../ThirdParty/PureData/src/m_pd.h"
#include "../ThirdParty/PureData/src/g_canvas.h"
#include "../ThirdParty/PureData/src/s_stuff.h"
#include "../ThirdParty/PureData/src/m_imp.h"
EXTERN void pd_init(void);
    
void bob_tilde_setup();
void bonk_tilde_setup();
void choice_setup();
void expr_setup();
void fiddle_tilde_setup();
void loop_tilde_setup();
void lrshift_tilde_setup();
void pique_setup();
void sigmund_tilde_setup();
void stdout_setup();
    
void sys_get_midi_apis(char *buf) {}
void sys_listmididevs(void) {}
void sys_get_midi_params(int *pnmidiindev, int *pmidiindev,int *pnmidioutdev, int *pmidioutdev) {}
void sys_open_midi(int nmidiindev, int *midiindev, int nmidioutdev, int *midioutdev, int enable) {}
void sys_close_midi() {}
void sys_reopen_midi(void) {}
void sys_initmidiqueue(void) {}
void sys_pollmidiqueue(void) {}
void sys_setmiditimediff(double inbuftime, double outbuftime) {}
void glob_midi_setapi(void *dummy, t_floatarg f) {}
void glob_midi_properties(t_pd *dummy, t_floatarg flongform) {}
void glob_midi_dialog(t_pd *dummy, t_symbol *s, int argc, t_atom *argv) {}
int sys_mididevnametonumber(int output, const char *name) { return 0; }
void sys_mididevnumbertoname(int output, int devno, char *name, int namesize) {}
}

namespace pd
{
    // ==================================================================================== //
    //                                      PD                                              //
    // ==================================================================================== //
    
    Pd::Pd() noexcept
    {
        signal(SIGFPE, SIG_IGN);
        sys_printhook = NULL;
        sys_soundin = NULL;
        sys_soundout = NULL;
        sys_schedblocksize = DEFDACBLKSIZE;
        sys_externalschedlib = 0;
        sys_printtostderr = 0;
        sys_usestdpath = 0;
        sys_debuglevel = 1;
        sys_verbose = DEBUG;
        sys_noloadbang = 0;
        sys_nogui = 1;
        sys_hipriority = 0;
        sys_nmidiin = 0;
        sys_nmidiout = 0;
        sys_init_fdpoll();
#ifdef HAVE_SCHED_TICK_ARG
        sys_time = 0;
#endif
        pd_init();
        sys_set_audio_api(API_DUMMY);
        sys_searchpath = NULL;
        
        int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
        outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];
        indev[0] = outdev[0] = DEFAULTAUDIODEV;
        inch[0] = m_max_channels;
        outch[0] = m_max_channels;
        sys_set_audio_settings(1, indev, 1, inch,
                               1, outdev, 1, outch, 44100, -1, 1, DEFDACBLKSIZE);
        sched_set_using_audio(SCHED_AUDIO_CALLBACK);
        sys_reopen_audio();
        m_sample_ins    = sys_soundin;
        m_sample_outs   = sys_soundout;
        midiout.reserve(1024);
        m_console.reserve(256);
        sys_soundin     = nullptr;
        sys_soundout    = nullptr;
    }
    
    Pd::~Pd() noexcept
    {
        if(m_sample_ins)
        {
            freebytes(m_sample_ins, (sys_inchannels ? sys_inchannels : 2) * (DEFDACBLKSIZE*sizeof(t_sample)));
        }
        if(m_sample_outs)
        {
            freebytes(m_sample_outs, (sys_outchannels ? sys_outchannels : 2) * (DEFDACBLKSIZE*sizeof(t_sample)));
        }
    }
    
    Pd& Pd::get() noexcept
    {
        static Pd pd;
        static bool initialized = false;
        if(!initialized)
        {
            bob_tilde_setup();
            bonk_tilde_setup();
            choice_setup();
            expr_setup();
            fiddle_tilde_setup();
            loop_tilde_setup();
            lrshift_tilde_setup();
            pique_setup();
            sigmund_tilde_setup();
            stdout_setup();
            pd.m_console.clear();
            sys_printhook = reinterpret_cast<t_printhook>(print);
            initialized = true;
        }
        return pd;
    }
    
    void Pd::print(const char* s)
    {
        Pd& pd = Pd::get();
        std::string message(s);
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        if(pd.m_console.size() >= 256)
        {
            pd.m_console.clear();
        }
        if(message.compare(0, 5, "error"))
        {
            pd.m_console.push_back({message, Post::Type::Error});
        }
        else if(message.compare(0, 7, "verbose"))
        {
            pd.m_console.push_back({message, Post::Type::Log});
        }
        else
        {
            pd.m_console.push_back({message, Post::Type::Post});
        }
        pd.m_console_changed = true;
#ifdef DEBUG
        std::cout << s;
#endif
    }
    
    std::string Pd::getPdVersion()
    {
        return std::to_string(PD_MAJOR_VERSION) + "." +
        std::to_string(PD_MINOR_VERSION) + "." +
        std::to_string(PD_BUGFIX_VERSION);
    }
    
    void Pd::addToSearchPath(std::string const& path) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        sys_searchpath = namelist_append(sys_searchpath, path.c_str(), 0);
    }
    
    void Pd::clearSearchPath() noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        namelist_free(sys_searchpath);
        sys_searchpath = NULL;
    }
    
    void Pd::clearConsole() noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        bool state = !pd.m_console.empty();
        pd.m_console.clear();
        pd.m_console_changed = state;
    }
    
    void Pd::postToConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console.push_back({text + "\n", Post::Type::Post});
        pd.m_console_changed = true;
    }
    
    void Pd::logToConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console.push_back({text + "\n", Post::Type::Log});
        pd.m_console_changed = true;
    }
    
    void Pd::errorToConsole(std::string const& text) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console.push_back({text + "\n", Post::Type::Error});
        pd.m_console_changed = true;
    }
    
    std::vector<Post> Pd::getConsole(bool state) noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        pd.m_console_changed = state;
        return pd.m_console;
    }
    
    bool Pd::hasConsoleChanged() noexcept
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_console_mutex);
        return pd.m_console_changed;
    }
    
    void Pd::lock() noexcept
    {
        Pd& pd = Pd::get();
        pd.m_mutex.lock();
    }
    
    void Pd::unlock() noexcept
    {
        Pd& pd = Pd::get();
        pd.m_mutex.unlock();
    }
    
    Instance Pd::createInstance() noexcept
    {
        Pd& pd = Pd::get();
        pd.m_mutex.lock();
        Instance instance(pdinstance_new());
        pd.m_mutex.unlock();
        return instance;
    }
    
    void Pd::free(Instance& instance)
    {
        Pd& pd = Pd::get();
        std::lock_guard<std::mutex> guard(pd.m_mutex);
        pdinstance_free(reinterpret_cast<t_pdinstance *>(instance.m_ptr));
    }
    
    // From libPD
#define CHECK_CHANNEL if (channel < 0 || channel > 16) return;
#define CHECK_PORT if (port < 0 || port > 0x0fff) return;
#define CHECK_RANGE_7BIT(v) if (v < 0 || v > 0x7f) return;
#define CHECK_RANGE_8BIT(v) if (v < 0 || v > 0xff) return;
#define MIDI_PORT (channel >> 4)
#define MIDI_CHANNEL (channel & 0x0f)
    
    void Pd::sendNote(int channel, int pitch, int velocity) {
        CHECK_CHANNEL
        CHECK_RANGE_7BIT(pitch)
        CHECK_RANGE_7BIT(velocity)
        inmidi_noteon(MIDI_PORT, MIDI_CHANNEL, pitch, velocity);
    }
    
    void Pd::sendControlChange(int channel, int controller, int value) {
        CHECK_CHANNEL
        CHECK_RANGE_7BIT(controller)
        CHECK_RANGE_7BIT(value)
        inmidi_controlchange(MIDI_PORT, MIDI_CHANNEL, controller, value);
    }
    
    void Pd::sendProgramChange(int channel, int value) {
        CHECK_CHANNEL
        CHECK_RANGE_7BIT(value)
        inmidi_programchange(MIDI_PORT, MIDI_CHANNEL, value);
    }
    
    void Pd::sendPitchBend(int channel, int value) {
        CHECK_CHANNEL
        if (value < -8192 || value > 8191) return;
        inmidi_pitchbend(MIDI_PORT, MIDI_CHANNEL, value + 8192);
    }
    
    void Pd::sendAfterTouch(int channel, int value) {
        CHECK_CHANNEL
        CHECK_RANGE_7BIT(value)
        inmidi_aftertouch(MIDI_PORT, MIDI_CHANNEL, value);
    }
    
    void Pd::sendPolyAfterTouch(int channel, int pitch, int value) {
        CHECK_CHANNEL
        CHECK_RANGE_7BIT(pitch)
        CHECK_RANGE_7BIT(value)
        inmidi_polyaftertouch(MIDI_PORT, MIDI_CHANNEL, pitch, value);
    }
    
    void Pd::sendMidiByte(int port, int byte) {
        CHECK_PORT
        CHECK_RANGE_8BIT(byte)
        inmidi_byte(port, byte);
    }
    
    void Pd::sendSysEx(int port, int byte) {
        CHECK_PORT
        CHECK_RANGE_7BIT(byte)
        inmidi_sysex(port, byte);
    }
    
    void Pd::sendSysRealtime(int port, int byte) {
        CHECK_PORT
        CHECK_RANGE_8BIT(byte)
        inmidi_realtimein(port, byte);
    }
    
    void Pd::clearMidi()
    {
        midiout.clear();
    }
    
    std::vector<MidiEvent>::const_iterator Pd::getMidiBegin()
    {
        return midiout.cbegin();
    }
    
    std::vector<MidiEvent>::const_iterator Pd::getMidiEnd()
    {
        return midiout.cend();
    }
}


extern "C"
{
#define MIDIMAP_CHANNEL ((channel > 15) ? 16 : ((channel < 0) ? 1 : channel+1))
    
    void outmidi_noteon(int port, int channel, int pitch, int velo)
    {
        midiout.push_back(pd::MidiEvent::Note(static_cast<unsigned char>(MIDIMAP_CHANNEL),static_cast<unsigned char>(pitch),static_cast<unsigned char>(velo)));
    }
    
    void outmidi_controlchange(int port, int channel, int ctl, int value)
    {
        midiout.push_back(pd::MidiEvent::ControlChange(static_cast<unsigned char>(MIDIMAP_CHANNEL),static_cast<unsigned char>(ctl),static_cast<unsigned char>(value)));
    }
    
    void outmidi_programchange(int port, int channel, int value)
    {
        midiout.push_back(pd::MidiEvent::ProgramChange(static_cast<unsigned char>(MIDIMAP_CHANNEL),static_cast<unsigned char>(value)));
    }
    
    void outmidi_pitchbend(int port, int channel, int value)
    {
        midiout.push_back(pd::MidiEvent::PitchBend(static_cast<unsigned char>(MIDIMAP_CHANNEL),value));
    }
    
    void outmidi_aftertouch(int port, int channel, int value)
    {
        midiout.push_back(pd::MidiEvent::AfterTouch(static_cast<unsigned char>(MIDIMAP_CHANNEL),static_cast<unsigned char>(value)));
    }
    
    void outmidi_polyaftertouch(int port, int channel, int pitch, int value)
    {
        midiout.push_back(pd::MidiEvent::PolyafterTouch(static_cast<unsigned char>(MIDIMAP_CHANNEL),static_cast<unsigned char>(pitch),static_cast<unsigned char>(value)));
    }
    
    void outmidi_byte(int port, int value)
    {
        midiout.push_back(pd::MidiEvent::Byte(static_cast<unsigned char>(port),static_cast<unsigned char>(value)));
    }
}

#undef CHECK_CHANNEL
#undef MIDI_PORT
#undef MIDI_CHANNEL
#undef CHECK_PORT
#undef CHECK_RANGE_7BIT
#undef CHECK_RANGE_8BIT



