/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_INTANCE_LOADER__
#define __CAMOMILE_INTANCE_LOADER__

#include "Pd/Pd.hpp"
#include "../JuceLibraryCode/JuceHeader.h"

class InstanceLoader
{
public:
    InstanceLoader();
    ~InstanceLoader();
    
    inline String getName() const {return m_name;}
    inline int getNumberOfInputs() const noexcept {return m_ninputs;}
    inline int getNumberOfOutputs() const noexcept {return m_noutputs;}
private:
    String                      m_name;
    int                         m_ninputs;
    int                         m_noutputs;
    std::vector<pd::Parameter>  m_parameters;
};



#endif
