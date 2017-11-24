/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PluginConsole.h"

CamomileConsole::History::History() :
m_fatal_count(0),
m_error_count(0),
m_post_count(0),
m_log_count(0)
{
    m_messages.reserve(512);
}

size_t CamomileConsole::History::getNumberOfMessageUntilLevel(CamomileConsole::Message::Level level) const noexcept
{
    if(level == Message::Level::Fatal)
        return m_fatal_count;
    if(level == Message::Level::Error)
        return m_fatal_count + m_error_count;
    if(level == Message::Level::Normal)
        return m_fatal_count + m_error_count + m_post_count;
    return m_fatal_count + m_error_count + m_post_count + m_log_count;
}

CamomileConsole::Message CamomileConsole::History::getMessage(size_t index) const  noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(m_messages.size() > index)
        return m_messages[index];
    return Message{Message::Level::Normal, std::string()};
}

std::string CamomileConsole::History::getFatal(size_t index) const noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(m_fatal_count > index)
    {
        for(size_t i = 0, c = 0; i < m_messages.size(); ++i)
        {
            if(m_messages[i].level == Level::Fatal)
            {
                ++c;
                if(c == index+1)
                {
                    return m_messages[i].text;
                }
            }
            
        }
    }
    return std::string();
}

std::string CamomileConsole::History::getError(size_t index) const noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(m_fatal_count > index)
    {
        for(size_t i = 0, c = 0; i < m_messages.size(); ++i)
        {
            if(m_messages[i].level == Level::Error)
            {
                ++c;
                if(c == index+1)
                {
                    return m_messages[i].text;
                }
            }
            
        }
    }
    return std::string();
}

std::string CamomileConsole::History::getNormal(size_t index) const noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(m_fatal_count > index)
    {
        for(size_t i = 0, c = 0; i < m_messages.size(); ++i)
        {
            if(m_messages[i].level == Level::Normal)
            {
                ++c;
                if(c == index+1)
                {
                    return m_messages[i].text;
                }
            }
            
        }
    }
    return std::string();
}

std::string CamomileConsole::History::getLog(size_t index) const noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(m_fatal_count > index)
    {
        for(size_t i = 0, c = 0; i < m_messages.size(); ++i)
        {
            if(m_messages[i].level == Level::Log)
            {
                ++c;
                if(c == index+1)
                {
                    return m_messages[i].text;
                }
            }
            
        }
    }
    return std::string();
}

CamomileConsole::Message CamomileConsole::History::getMessageUntilLevel(CamomileConsole::Message::Level level, size_t index) const noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(getNumberOfMessageUntilLevel(level) > index)
    {
        for(size_t i = 0, c = 0; i < m_messages.size(); ++i)
        {
            if(m_messages[i].level <= level)
            {
                ++c;
                if(c == index+1)
                {
                    return m_messages[i];
                }
            }
            
        }
    }
    return Message();
}

void CamomileConsole::History::clear() noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_fatal_count = m_error_count = m_post_count = m_log_count = 0;
    return m_messages.clear();
}

void CamomileConsole::History::add(Message message) noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if(message.level == Level::Fatal)
    {
        m_fatal_count++;
    }
    if(message.level == Level::Error)
    {
        m_error_count++;
    }
    if(message.level == Level::Normal)
    {
        m_post_count++;
    }
    else
    {
        m_log_count++;
    }
    m_messages.push_back(std::move(message));
}

void CamomileConsole::History::addFatal(std::string message) noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_fatal_count++;
    m_messages.push_back({Level::Fatal, std::move(message)});
}

void CamomileConsole::History::addError(std::string message) noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_error_count++;
    m_messages.push_back({Level::Error, std::move(message)});
}

void CamomileConsole::History::addNormal(std::string message) noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_post_count++;
    m_messages.push_back({Level::Normal, std::move(message)});
}

void CamomileConsole::History::addLog(std::string message) noexcept
{
    std::lock_guard<std::mutex> guard(m_mutex);
    m_log_count++;
    m_messages.push_back({Level::Log, std::move(message)});
}
