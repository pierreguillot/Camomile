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
    private:
        void* m_ptr         = nullptr;
        std::vector<float> m_inputs;
        std::vector<float> m_outputs;
    };
}
