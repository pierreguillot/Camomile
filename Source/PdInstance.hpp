/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef Z_PD_INSTANCE_HPP
#define Z_PD_INSTANCE_HPP

#include "PdEnvironment.hpp"

namespace pd
{
    class Patch;
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    //! @brief The Pure Data instance.
    //! @details The Instance is a wrapper for the Pure Data's native instance.
    //! With the default constructor, the Instance won't be initialized. A valid
    //! Instance should be created via Pd. The Instance has some kind of smart
    //! pointer behavior so when an Instance object is no more useful the object is deleted.
    class Instance
    {
    public:
        
        //! @brief The constructor for an empty Instance.
        //! @details Creates an Instance that can be used as an empty reference inside
        //! another class.
        Instance() noexcept;
        
        //! @brief The copy constructor.
        //! Creates a copy of an Instance and increments his counter.
        Instance(Instance const& other) noexcept;
        
        //! @brief The move constructor.
        //! @details Creates a copy of an Instance without incrementing his counter. The
        //! other Instance will be useless.
        Instance(Instance&& other) noexcept;
        
        //! @brief The copy operator.
        //! Copies the Instance and increments his counter.
        Instance& operator=(Instance const& other) noexcept;
        
        //! @brief The move operator.
        //! @details Copies the Instance without incrementing his counter. The other
        //! Instance will be destroyed if needed.
        Instance& operator=(Instance&& other) noexcept;
        
        //! @brief The destructor.
        //! @details The Instance will be destroyed if no other copy exists.
        ~Instance() noexcept;
        
        //! @brief Retrieves if the Instance is valid.
        bool isValid() const noexcept;
        
        //! @brief Retrieves the sample rate of the Instance.
        long getSampleRate() const noexcept;
        
    protected:
        
        //! @brief Locks Instance.
        void lock() noexcept;
        
        //! @brief Unlocks Instance.
        void unlock() noexcept;
        
        //! @brief Prepares the digital signal processing chain of the Instance.
        void prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept;
        
        //! @brief Performs the digital signal processing chain of the Instance.
        //! @details You should locks the Instance to ensure thread safety.
        void performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept;
        
        //! @brief Releases the digital signal processing chain of the Instance.
        void releaseDsp() noexcept;
        
        //! @brief Creates a Patch.
        Patch createPatch(std::string const& name, std::string const& path);
        
    private:
        
        //! @brief The constructor for a new Instance.
        //! Creates a new valid Instance.
        Instance(void* ptr) noexcept;
        
        //! @brief Release the Instance.
        void release() noexcept;
        
        //! @brief Free a Patch.
        void freePatch(Patch& patch);
        
        void*               m_ptr;
        std::atomic<long>*  m_count;
        
        friend class Environment;
        friend class Patch;
    };

}

#endif // Z_PD_INSTANCE_HPP
