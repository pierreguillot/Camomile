/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "PdObject.h"

namespace pd
{
    // ==================================================================================== //
    //                                          OBJECT                                      //
    // ==================================================================================== //
    
    Object::Object(void* handle) : m_handle(handle)
    {
        if(!handle)
        {
            class Error : public std::exception {
            public:
                const char* what() const noexcept override {
                    return "The object isn't valid !";}
            };
        }
    }
}



