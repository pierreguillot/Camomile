/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#include "PdConsole.hpp"

namespace pd
{
    
    Console::History::History() :
    m_fatal_count(0),
    m_error_count(0),
    m_post_count(0),
    m_log_count(0)
    {
        m_messages.reserve(512);
    }
    
    size_t Console::History::getNumberOfMessageUntilLevel(Console::Message::Level level) const noexcept
    {
        if(level == Message::Level::Fatal)
            return m_fatal_count;
        if(level == Message::Level::Error)
            return m_fatal_count + m_error_count;
        if(level == Message::Level::Post)
            return m_fatal_count + m_error_count + m_post_count;
        return m_fatal_count + m_error_count + m_post_count + m_log_count;
    }
    
    Console::Message Console::History::getMessage(size_t index) const  noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if(m_messages.size() > index)
            return m_messages[index];
        return Message{Message::Level::Post, std::string()};
    }
    
    std::string Console::History::getFatal(size_t index) const noexcept
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
    
    std::string Console::History::getError(size_t index) const noexcept
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
    
    std::string Console::History::getPost(size_t index) const noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        if(m_fatal_count > index)
        {
            for(size_t i = 0, c = 0; i < m_messages.size(); ++i)
            {
                if(m_messages[i].level == Level::Post)
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
    
    std::string Console::History::getLog(size_t index) const noexcept
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
    
    Console::Message Console::History::getMessageUntilLevel(Console::Message::Level level, size_t index) const noexcept
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
    
    void Console::History::clear() noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_fatal_count = m_error_count = m_post_count = m_log_count = 0;
        return m_messages.clear();
    }
    
    void Console::History::add(Message message) noexcept
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
        if(message.level == Level::Post)
        {
            m_post_count++;
        }
        else
        {
            m_log_count++;
        }
        m_messages.push_back(std::move(message));
    }
    
    void Console::History::addFatal(std::string message) noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_fatal_count++;
        m_messages.push_back({Level::Fatal, std::move(message)});
    }
    
    void Console::History::addError(std::string message) noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_error_count++;
        m_messages.push_back({Level::Error, std::move(message)});
    }
    
    void Console::History::addPost(std::string message) noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_post_count++;
        m_messages.push_back({Level::Post, std::move(message)});
    }
    
    void Console::History::addLog(std::string message) noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        m_log_count++;
        m_messages.push_back({Level::Log, std::move(message)});
    }
}