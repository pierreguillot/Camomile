//
//  CicmObject.h
//  Camomile
//
//  Created by Guillot Pierre on 27/07/2015.
//
//

#ifndef __Camomile__CicmObject__
#define __Camomile__CicmObject__

#include "CamoWrapper.h"

class CicmPatch;

class CicmObject
{
private:
    t_ebox*         m_box;
    Rectangle<int>  m_bounds;
public:
    CicmObject();
    CicmObject(CicmPatch const& patch, t_ebox* box);
    CicmObject(CicmObject const& other);
    ~CicmObject();
    void operator=(CicmObject const& from);
    
    Point<int> getPosition() const noexcept;
    int getX() const noexcept;
    int getY() const noexcept;
    Point<int> getSize() const noexcept;
    int getWidth() const noexcept;
    int getHeight() const noexcept;
    Rectangle<int> getBounds() const noexcept;
    
    Colour getBackgroundColor() const noexcept;
    Colour getBorderColor() const noexcept;
    int getBorderSize() const noexcept;
};

#endif /* defined(__Camomile__CicmObject__) */
