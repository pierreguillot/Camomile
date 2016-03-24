/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_CONSOLE_HPP
#define Z_PD_CONSOLE_HPP

#include "PdTypes.hpp"

namespace pd
{
    class Console
    {
    public:
        class Message
        {
        public:
            enum class Level
            {
                Fatal = 0, Error = 1, Post = 2, Log = 3
            };
            Level       level;
            std::string text;
        };
        
        class History
        {
        public:
            //! @brief the constructor.
            History();
            
            //! @brief Gets the number of messages.
            inline size_t getNumberOfMessages() const noexcept {return m_messages.size();}
            
            //! @brief Gets the number of messages.
            inline size_t getNumberOfFatalMessages() const noexcept {return m_fatal_count;}
            
            //! @brief Gets the number of messages.
            inline size_t getNumberOfErrorMessages() const noexcept {return m_error_count;}
            
            //! @brief Gets the number of messages.
            inline size_t getNumberOfPostMessages() const noexcept {return m_post_count;}
            
            //! @brief Gets the number of messages.
            inline size_t getNumberOfLogMessages() const noexcept {return m_log_count;}
            
            //! @brief Gets the number of messages.
            inline size_t getNumberOfMessageUntilLevel(Message::Level level) const noexcept
            {
                if(level == Message::Level::Fatal)
                    return m_fatal_count;
                if(level == Message::Level::Error)
                    return m_fatal_count + m_error_count;
                if(level == Message::Level::Post)
                    return m_fatal_count + m_error_count + m_post_count;
                return m_fatal_count + m_error_count + m_post_count + m_log_count;
            }
            
            //! @brief Gets the a message.
            Message getMessage(size_t index) const noexcept;
            
            //! @brief Gets the a fatal.
            std::string getFatal(size_t index) const noexcept;
            
            //! @brief Gets the a fatal.
            std::string getError(size_t index) const noexcept;
            
            //! @brief Gets the a fatal.
            std::string getPost(size_t index) const noexcept;
            
            //! @brief Gets the a fatal.
            std::string getLog(size_t index) const noexcept;
            
            //! @brief Gets a message that the level i.
            Message getMessageUntilLevel(Message::Level level, size_t index) const noexcept;
            
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
            
            //! @brief Adds a post message in the history.
            void addPost(std::string message) noexcept;
            
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
}

#endif
