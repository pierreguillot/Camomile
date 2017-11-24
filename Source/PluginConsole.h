/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#pragma once

#include <string>
#include <utility>
#include <vector>
#include <mutex>

//! @brief A class that manages the console
class CamomileConsole
{
public:
    //! @brief A small class that describes a message in the console
    class Message
    {
    public:
        enum class Level
        {
            Unknown = 0,
            Fatal = 1,
            Error = 2,
            Normal = 3,
            Log = 4
        };
        Level       level;
        std::string text;
    };
    
    //! @brief A small class that manages the history of message in the console
    class History
    {
    public:
        typedef Message::Level Level;
        //! @brief the constructor.
        History();
        
        //! @brief Gets the number of all messages.
        inline size_t getNumberOfMessages() const noexcept {return m_messages.size();}
        
        //! @brief Gets the number of fatal messages.
        inline size_t getNumberOfFatalMessages() const noexcept {return m_fatal_count;}
        
        //! @brief Gets the number of error messages.
        inline size_t getNumberOfErrorMessages() const noexcept {return m_error_count;}
        
        //! @brief Gets the number of post messages.
        inline size_t getNumberOfNormalMessages() const noexcept {return m_post_count;}
        
        //! @brief Gets the number of log messages.
        inline size_t getNumberOfLogMessages() const noexcept {return m_log_count;}
        
        //! @brief Gets the number of messages until a level.
        size_t getNumberOfMessageUntilLevel(Level level) const noexcept;
        
        //! @brief Gets a message at an index.
        Message getMessage(size_t index) const noexcept;
        
        //! @brief Gets a fatal message at an index.
        std::string getFatal(size_t index) const noexcept;
        
        //! @brief Gets an error message at an index.
        std::string getError(size_t index) const noexcept;
        
        //! @brief Gets a post message at an index.
        std::string getNormal(size_t index) const noexcept;
        
        //! @brief Gets a log message at an index.
        std::string getLog(size_t index) const noexcept;
        
        //! @brief Gets a message at an index until a level.
        Message getMessageUntilLevel(Level level, size_t index) const noexcept;
        
        //! @brief Clears the history.
        void clear() noexcept;
        
        //! @brief Retrieves a copy of the history.
        inline std::vector<Message> getMessages() const {return m_messages;}
        
        //! @brief Adds a message in the history.
        void add(Message message) noexcept;
        
        //! @brief Adds a fatal message in the history.
        void addFatal(std::string message) noexcept;
        
        //! @brief Adds an error message in the history.
        void addError(std::string message) noexcept;
        
        //! @brief Adds a normal message in the history.
        void addNormal(std::string message) noexcept;
        
        //! @brief Adds a log message in the history.
        void addLog(std::string message) noexcept;
        
    private:
        mutable std::mutex   m_mutex;
        size_t               m_fatal_count;
        size_t               m_error_count;
        size_t               m_post_count;
        size_t               m_log_count;
        std::vector<Message> m_messages;
    };
};
