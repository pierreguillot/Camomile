/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE__INTERFACE__
#define __CAMOMILE__INTERFACE__

#include "CamoPatcher.h"

namespace camo
{
    //! @brief The camomille component for an Object.
    //! @details This class is the juce component of an Object.
    class Interface : public juce::Component
    {
    private:
         //! @brief The object.
        Object m_object;
        
    public:
        
        //! @brief The attribute constructor.
        Interface(Object const& object);
        
        //! @brief The paint method.
        void paint(Graphics& g) override;
    };
}

#endif
