/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_INSTANCE__
#define __CAMOMILE_PD_INSTANCE__

#include "PdPatch.hpp"

namespace pd
{
    // ==================================================================================== //
    //                                          INSTANCE                                    //
    // ==================================================================================== //
    
    //! @brief The Pure Data instance.
    //! @details The Instance is a wrapper for the pd's native t_pdinstance.
    //! With the default constructor, the Instance won't be initialized. A valid
    //! Instance should be created with a name. The Instance has some kind of smart
    //! pointer behavior so when no Instance uses a t_pdinstance anymore the
    //! t_pdinstance is deleted. For the moment, several Instance can share the same
    //! name, but to ensure future compatibilty you should give a different name to
    //! all specifics Instances.
    class Instance
    {
    public:
        
        //! @brief The constructor for an empty Instance.
        //! @details Creates an Instance that can be used as an empty reference inside
        //! another class.
        Instance() noexcept;
        
        //! @brief The constructor for a new Instance.
        //! Creates a new valid Instance.
        Instance(std::string const& name) noexcept;
        
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
        
        //! @brief Retrieves if the name of the Instance.
        std::string getName() const noexcept;
        
    protected:
        
        //! @brief Prepares the digital signal processing chain of the Instance.
        void prepareDsp(const int nins, const int nouts, const int samplerate, const int nsamples) noexcept;
        
        //! @brief Performs the digital signal processing chain of the Instance.
        void performDsp(int nsamples, const int nins, const float** inputs, const int nouts, float** outputs) noexcept;
        
        //! @brief Releases the digital signal processing chain of the Instance.
        void releaseDsp() noexcept;
        
    private:
        
        void* createCanvas(std::string const& name, std::string const& path);
        
        void freeCanvas(void* cnv);
        
        class Internal;
        Internal*   m_internal;
        friend class Patch;
    };

}

#endif
