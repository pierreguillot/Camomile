/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE__PATCH__
#define __CAMOMILE__PATCH__

#include "CicmObject.h"

class CicmPatch : public pd::Patch
{
private:
    typedef struct _camomile
    {
        t_ebox      j_box;
        t_rgba		f_color_background;
        t_rgba		f_color_border;
        t_ebox**    f_boxes;
        int         f_nboxes;
    } t_camomile;
    
    t_camomile* m_controller;
    Rectangle<int>  m_bounds;
public:
    
    CicmPatch();
    CicmPatch(const std::string& filename, const std::string& path);
    CicmPatch(void* handle, int dollarZero, const std::string& filename, const std::string& path);
    CicmPatch(pd::Patch const& other);
    CicmPatch(CicmPatch const& other);
    void operator=(Patch const& from);
    void operator=(CicmPatch const& from);
    ~CicmPatch();
    
    bool isPlugin() const noexcept;
    
    Point<int> getPosition() const noexcept;
    int getX() const noexcept;
    int getY() const noexcept;
    Point<int> getSize() const noexcept;
    int getWidth() const noexcept;
    int getHeight() const noexcept;
    Rectangle<int> getBounds() const noexcept;
    //DrawParameters getDrawParameters() const noexcept;
    
    int getNumberOfObjects() const noexcept;
    std::vector<CicmObject> getObjects() const noexcept;
    
private:
    void loadController();
};

#endif /* defined(__Camomile__CicmPatch__) */
