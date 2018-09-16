/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PluginProcessor.h"
#include "PluginParameter.h"

//////////////////////////////////////////////////////////////////////////////////////////////
//                                          MIDI METHODS                                    //
//////////////////////////////////////////////////////////////////////////////////////////////

void CamomileAudioProcessor::receiveNoteOn(const int channel, const int pitch, const int velocity)
{
    if(velocity == 0)
    {
        m_midi_buffer_out.addEvent(MidiMessage::noteOff(channel, pitch, uint8(0)), m_audio_advancement);
    }
    else
    {
        m_midi_buffer_out.addEvent(MidiMessage::noteOn(channel, pitch, static_cast<uint8>(velocity)), m_audio_advancement);
    }
}

void CamomileAudioProcessor::receiveControlChange(const int channel, const int controller, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::controllerEvent(channel, controller, value), m_audio_advancement);
}

void CamomileAudioProcessor::receiveProgramChange(const int channel, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::programChange(channel, value), m_audio_advancement);
}

void CamomileAudioProcessor::receivePitchBend(const int channel, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::pitchWheel(channel, value + 8192), m_audio_advancement);
}

void CamomileAudioProcessor::receiveAftertouch(const int channel, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::channelPressureChange(channel, value), m_audio_advancement);
}

void CamomileAudioProcessor::receivePolyAftertouch(const int channel, const int pitch, const int value)
{
    m_midi_buffer_out.addEvent(MidiMessage::aftertouchChange(channel, pitch, value), m_audio_advancement);
}

void CamomileAudioProcessor::receiveMidiByte(const int port, const int byte)
{
#if 0
    if(m_midibyte_index == 0)
    {
        add(ConsoleLevel::Error, "Process Send Midi Bytes ----");
    }
    add(ConsoleLevel::Error,  std::to_string(byte));
#endif
    
    m_midibyte_buffer[m_midibyte_index++] = byte;
    if(m_midibyte_index >= 3)
    {
        m_midi_buffer_out.addEvent(MidiMessage(m_midibyte_buffer[0], m_midibyte_buffer[1], m_midibyte_buffer[2]), m_audio_advancement);
        m_midibyte_index = 0;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                       PRINT METHOD                                       //
//////////////////////////////////////////////////////////////////////////////////////////////

void CamomileAudioProcessor::receivePrint(const std::string& message)
{
    if(!message.empty())
    {
        if(!message.compare(0, 6, "error:"))
        {
            std::string const temp(message.begin()+7, message.end());
            add(ConsoleLevel::Error, temp);
        }
        else if(!message.compare(0, 11, "verbose(4):"))
        {
            std::string const temp(message.begin()+12, message.end());
            add(ConsoleLevel::Error, temp);
        }
        else if(!message.compare(0, 5, "tried"))
        {
            add(ConsoleLevel::Log, message);
        }
        else if(!message.compare(0, 16, "input channels ="))
        {
            add(ConsoleLevel::Log, message);
        }
        else
        {
            add(ConsoleLevel::Normal, message);
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////
//                                        MESSAGE METHOD                                    //
//////////////////////////////////////////////////////////////////////////////////////////////

void CamomileAudioProcessor::receiveMessage(const std::string& msg, const std::vector<pd::Atom>& list)
{
    if(msg == std::string("param"))
    {
        if(list.size() >= 2 && list[0].isSymbol() && list[1].isFloat())
        {
            std::string const method = list[0].getSymbol();
            int const index = static_cast<int>(list[1].getFloat()) - 1;
            if(method == "set")
            {
                if(list.size() >= 3 && list[2].isFloat())
                {
                    CamomileAudioParameter* param = static_cast<CamomileAudioParameter *>(getParameters()[index]);
                    if(param)
                    {
                        param->setOriginalScaledValueNotifyingHost(list[2].getFloat());
                        if(list.size() > 3) { add(ConsoleLevel::Error,
                                                  "camomile parameter set method extra arguments"); }
                    }
                    else { add(ConsoleLevel::Error,
                               "camomile parameter set method index: out of range"); }
                }
                else { add(ConsoleLevel::Error,
                           "camomile parameter set method: wrong argument"); }
            }
            else if(method == "change")
            {
                if(list.size() >= 3 && list[2].isFloat())
                {
                    AudioProcessorParameter* param = getParameters()[index];
                    if(param)
                    {
                        if(list[2].getFloat() > std::numeric_limits<float>::epsilon())
                        {
                            if(m_params_states[index])
                            {
                                add(ConsoleLevel::Error,
                                    "camomile parameter change " + std::to_string(index+1) + " already started");
                            }
                            else
                            {
                                param->beginChangeGesture();
                                m_params_states[index] = true;
                                if(list.size() > 3) { add(ConsoleLevel::Error,
                                                          "camomile parameter change method extra arguments"); }
                            }
                        }
                        else
                        {
                            if(!m_params_states[index])
                            {
                                add(ConsoleLevel::Error,
                                    "camomile parameter change " + std::to_string(index+1) + " not started");
                            }
                            else
                            {
                                param->endChangeGesture();
                                m_params_states[index] = false;
                                if(list.size() > 3) { add(ConsoleLevel::Error,
                                                          "camomile parameter change method extra arguments"); }
                            }
                        }
                    }
                    else { add(ConsoleLevel::Error,
                               "camomile parameter change method index: out of range"); }
                }
                else { add(ConsoleLevel::Error,
                           "camomile parameter change method: wrong argument"); }
            }
            else { add(ConsoleLevel::Error,
                       "camomile param no method: " + method); }
        }
        else { add(ConsoleLevel::Error,
                   "camomile param error syntax: method index..."); }
    }
    else if(msg == std::string("program"))
    {
        parseProgram(list);
    }
    else if(msg == std::string("openpanel"))
    {
        parseOpenPanel(list);
    }
    else if(msg == std::string("savepanel"))
    {
        parseSavePanel(list);
    }
    else if(msg == std::string("array"))
    {
        parseArray(list);
    }
    else if(msg == std::string("save"))
    {
        parseSaveInformation(list);
    }
    else if(msg == std::string("gui"))
    {
        parseGui(list);
    }
    else if(msg == std::string("audio"))
    {
        parseAudio(list);
    }
    else {  add(ConsoleLevel::Error, "camomile unknow message : " + msg); }
}

void CamomileAudioProcessor::parseProgram(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1 && list[0].isSymbol() && list[0].getSymbol() == "updated")
    {
        updateHostDisplay();
    }
    else
    {
        add(ConsoleLevel::Error, "camomile program method accepts updated method only");
    }
}

void CamomileAudioProcessor::parseOpenPanel(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            if(list.size() > 1)
            {
                if(list[1].isSymbol())
                {
                    if(list[1].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("openpanel"), list[0].getSymbol(), std::string("-s")});
                    }
                    else if(list[0].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("openpanel"), list[1].getSymbol(), std::string("-s")});
                    }
                    else
                    {
                        add(ConsoleLevel::Error, "camomile openpanel one argument must be a flag \"-s\"");
                    }
                    if(list.size() > 2)
                    {
                        add(ConsoleLevel::Error, "camomile openpanel method extra arguments");
                    }
                }
                else
                {
                    add(ConsoleLevel::Error, "camomile openpanel second argument must be a symbol");
                }
            }
            else
            {
                if(list[0].getSymbol() == "-s")
                {
                    m_queue_gui.try_enqueue({std::string("openpanel"), std::string(), std::string("-s")});
                }
                else
                {
                    m_queue_gui.try_enqueue({std::string("openpanel"), list[0].getSymbol(), std::string()});
                }
            }
        }
        else
        {
            add(ConsoleLevel::Error, "camomile openpanel method argument must be a symbol");
        }
    }
    else
    {
        m_queue_gui.try_enqueue({std::string("openpanel"), std::string(), std::string()});
    }
}

void CamomileAudioProcessor::parseSavePanel(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            if(list.size() > 1)
            {
                if(list[1].isSymbol())
                {
                    if(list[1].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("savepanel"), list[0].getSymbol(), std::string("-s")});
                    }
                    else if(list[0].getSymbol() == "-s")
                    {
                        m_queue_gui.try_enqueue({std::string("savepanel"), list[1].getSymbol(), std::string("-s")});
                    }
                    else
                    {
                        add(ConsoleLevel::Error, "camomile savepanel one argument must be a flag \"-s\"");
                    }
                    if(list.size() > 2)
                    {
                        add(ConsoleLevel::Error, "camomile savepanel method extra arguments");
                    }
                }
                else
                {
                    add(ConsoleLevel::Error, "camomile savepanel second argument must be a symbol");
                }
            }
            else
            {
                if(list[0].getSymbol() == "-s")
                {
                    m_queue_gui.try_enqueue({std::string("savepanel"), std::string(), std::string("-s")});
                }
                else
                {
                    m_queue_gui.try_enqueue({std::string("savepanel"), list[0].getSymbol(), std::string()});
                }
            }
        }
        else
        {
            add(ConsoleLevel::Error, "camomile savepanel method argument must be a symbol");
        }
    }
    else
    {
        m_queue_gui.try_enqueue({std::string("savepanel"), std::string(), std::string()});
    }
}

void CamomileAudioProcessor::parseArray(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            m_queue_gui.try_enqueue({std::string("array"), list[0].getSymbol(), ""});
            if(list.size() > 1)
            {
                add(ConsoleLevel::Error, "camomile array method extra arguments");
            }
        }
        else { add(ConsoleLevel::Error, "camomile array method argument must be a symbol"); }
    }
    else
    {
        add(ConsoleLevel::Error, "camomile array needs a name");
    }
}

void CamomileAudioProcessor::parseGui(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            m_queue_gui.try_enqueue({std::string("gui"), list[0].getSymbol(), ""});
            if(list.size() > 1)
            {
                add(ConsoleLevel::Error, "camomile gui method extra arguments");
            }
        }
        else { add(ConsoleLevel::Error, "camomile gui method argument must be a symbol"); }
    }
    else
    {
        add(ConsoleLevel::Error, "camomile gui needs a command");
    }
}

void CamomileAudioProcessor::parseAudio(const std::vector<pd::Atom>& list)
{
    if(list.size() >= 1)
    {
        if(list[0].isSymbol())
        {
            if(list[0].getSymbol() == std::string("latency"))
            {
                if(list.size() >= 2 && list[1].isFloat())
                {
                    const int latency = static_cast<int>(list[1].getFloat());
                    if(latency >= 0)
                    {
                        setLatencySamples(latency + Instance::getBlockSize());
                        if(list.size() > 2)
                        {
                            add(ConsoleLevel::Error, "camomile audio method: latency option extra arguments");
                        }
                        if(CamomileEnvironment::isLatencyInitialized())
                        {
                            add(ConsoleLevel::Error, "camomile audio method: latency overwrites the preferences");
                        }
                    }
                    else
                    {
                        add(ConsoleLevel::Error, "camomile audio method: latency must be positive or null");
                    }
                }
                else
                {
                    add(ConsoleLevel::Error, "camomile audio method: latency option expects a number");
                }
            }
            else
            {
                add(ConsoleLevel::Error, "camomile audio method: unknown option \"" + list[0].getSymbol() + "\"");
            }
        }
        else
        {
            add(ConsoleLevel::Error, "camomile audio method: first argument must be an option");
        }
    }
    else
    {
        add(ConsoleLevel::Error, "camomile audio method: expects arguments");
    }
}

