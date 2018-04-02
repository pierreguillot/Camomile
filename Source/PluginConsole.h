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
#include <array>
#include <cassert>
#include <limits>

//! @brief A class that manages the console
template<size_t SIZE> class CamomileConsole
{
public:
    public:
    
    //! @brief the constructor.
    CamomileConsole(size_t const preallocate = 512) : m_messages() {
        m_messages.reserve(preallocate), m_counters.fill(0); }
    
    //! @brief Gets the number of all messages.
    size_t size(size_t level) const noexcept {
        assert(level <= SIZE && "wrong level of message");
        std::lock_guard<std::mutex> guard(m_mutex);
        size_t size = m_counters[level];
        while (level--) { size += m_counters[level]; }
        return size;
    }
    
    //! @brief Gets a message at an index until a level.
    std::pair<size_t, std::string> get(size_t level, size_t index) const noexcept
    {
        assert(level <= SIZE && "wrong level of message");
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
    void clear(size_t level = SIZE, size_t index = std::numeric_limits<size_t>::max()) noexcept
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
    void add(size_t level, std::string message) noexcept
    {
        assert(level < SIZE && "wrong level of message");
        std::lock_guard<std::mutex> guard(m_mutex);
        if(m_messages.size() < m_messages.capacity())
        {
            ++m_counters[level];
            m_messages.push_back(std::pair<size_t, std::string>({level, std::move(message)}));
        }
    }
    
private:
    mutable std::mutex       m_mutex;
    std::array<size_t, SIZE> m_counters;
    std::vector<std::pair<size_t, std::string>> m_messages;
};
