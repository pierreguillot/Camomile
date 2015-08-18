/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE__WRAPPER__
#define __CAMOMILE__WRAPPER__

#include "../JuceLibraryCode/JuceHeader.h"
//#include "../ThirdParty/Pd/cpp/PdBase.hpp"
//#include "../ThirdParty/Cream/c.library.hpp"

namespace camo
{
    
    //! @brief Converts a set of point to a juce::Path.
    /*
    inline static juce::Path toJuce(int size, t_pt* points)
    {
        juce::Path path;
        for(int i = 0; i < size; i++)
        {
            if(points[i].x == E_PATH_MOVE && i < size - 1)
            {
                path.startNewSubPath(points[i+1].x, points[i+1].y);
                ++i;
            }
            else if(points[i].x == E_PATH_LINE && i < size - 1)
            {
                path.lineTo(points[i+1].x, points[i+1].y);
                ++i;
            }
            else if(points[i].x == E_PATH_CURVE && i < size - 3)
            {
                path.cubicTo(points[i+1].x, points[i+1].y,
                             points[i+2].x, points[i+2].y,
                             points[i+3].x, points[i+3].y);
                i += 3;
            }
            else if(points[i].x == E_PATH_CLOSE)
            {
                path.closeSubPath();
            }
        }
       
        return path;
    }*/
}

#endif
