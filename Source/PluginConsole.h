/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */
#pragma once

#include <string>
#include <utility>
#include <vector>
#include <mutex>
#include <cassert>
#include <limits>

//! @brief A class that manages the console
class CamomileConsole
{
public:
    public:
    using level_t = size_t;
    using message_t = std::pair<level_t, std::string>;
    
    //! @brief the constructor.
    CamomileConsole(const level_t maxlevel, size_t const preallocate = 512) :
    m_max_level(maxlevel),
    m_counters(maxlevel, 0),
    m_messages(preallocate)
    {
        m_messages.clear();
    }
    
    //! @brief Gets the number of all messages.
    size_t size(level_t level) const noexcept
    {
        assert(level <= m_max_level && "wrong level of message");
        std::lock_guard<std::mutex> guard(m_mutex);
        size_t size = m_counters[level];
        while (level--) { size += m_counters[level]; }
        return size;
    }
    
    //! @brief Gets a message at an index until a level.
    message_t get(level_t level, size_t index) const noexcept
    {
        assert(level <= m_max_level && "wrong level of message");
        std::lock_guard<std::mutex> guard(m_mutex);
        for(size_t i = 0, c = 0; i < m_messages.size(); ++i)
        {
            if(m_messages[i].first <= level)
            {
                if(c++ == index)
                {
                    return m_messages[i];
                }
            }
        }
        return std::pair<size_t, std::string>();
    }
    
    //! @brief Clears the history.
    void clear(level_t level, size_t index = std::numeric_limits<size_t>::max()) noexcept
    {
        std::lock_guard<std::mutex> guard(m_mutex);
        size_t c = 0;
        for(auto it = m_messages.begin(); it != m_messages.end(); ++it)
        {
            if(it->first <= level)
            {
                if(c++ == index)
                {
                    --m_counters[it->first];
                    m_messages.erase(it);
                    return;
                }
            }
        }
    }

    
    //! @brief Adds a message to the history.
    void add(level_t level, std::string message) noexcept
    {
        assert(level < m_max_level && "wrong level of message");
        std::lock_guard<std::mutex> guard(m_mutex);
        if(m_messages.size() < m_messages.capacity())
        {
            ++m_counters[level];
            m_messages.push_back(message_t{level, std::move(message)});
        }
    }
    
private:
    mutable std::mutex          m_mutex;
    const level_t               m_max_level;
    std::vector<level_t>        m_counters;
    std::vector<message_t>      m_messages;
};
