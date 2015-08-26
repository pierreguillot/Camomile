/*
// Copyright (c) 2015 Pierre Guillot.
// For information on usage and redistribution, and for a DISCLAIMER OF ALL
// WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PD_WRAPPER__
#define __CAMOMILE_PD_WRAPPER__

#include "PdGui.h"
#include "PdMessenger.h"
#include "../JuceLibraryCode/JuceHeader.h"

namespace pd
{
    
    class CamoParameter : public Parameter, public AudioProcessorParameter
    {
    public:
        
        CamoParameter() : Parameter() {}
        
        CamoParameter(Parameter const& param) : Parameter(param) {}
        
        float getValue() const override {return Parameter::getNormalizedValue();}
        
        void setValue(float newValue) override {Parameter::setNormalizedValue(newValue);}
        
        float getDefaultValue() const override {return Parameter::getDefaultNormalizedValue();}
        
        String getName(int maximumStringLength) const override {
            return String(Parameter::getFullName().c_str(), maximumStringLength);}
        
        String getLabel() const override {return String(Parameter::getLabel());}
        
        String getText (float value, int maximumStringLength) const override {
            return String(Parameter::getTextForValue(value).c_str(), maximumStringLength);}
        
        float getValueForText(const String& text) const override {
            return Parameter::getValueForText(text.toStdString());}
        
        bool isAutomatable() const override {return Parameter::isAutomatable();}
        
        bool isMetaParameter() const override {return Parameter::isMetaParameter();}
    };
    
    static inline juce::Colour tojColor(std::array<float, 4> const& color)
    {
        return juce::Colour::fromFloatRGBA(color[0], color[1], color[2], color[3]);
    }
    
    static inline juce::Path fromPath(std::vector<t_pt> const& points)
    {
        juce::Path path;
        path.preallocateSpace(points.size());
        for(int i = 0; i < points.size(); i++)
        {
            if(points[i].x == E_PATH_MOVE)
            {
                path.startNewSubPath(points[i+1].x, points[i+1].y);
                ++i;
            }
            else if(points[i].x == E_PATH_LINE)
            {
                path.lineTo(points[i+1].x, points[i+1].y);
                ++i;
            }
            else if(points[i].x == E_PATH_CURVE)
            {
                path.cubicTo(points[i+1].x, points[i+1].y, points[i+2].x, points[i+2].y, points[i+3].x, points[i+3].y);
                i += 3;
            }
            else if(points[i].x == E_PATH_CLOSE)
            {
                path.closeSubPath();
            }
        }
        return path;
    }
    
    static inline juce::Path fromRect(std::vector<t_pt> const& points)
    {
        juce::Path path;
        if(points.size() == 5)
        {
            path.addRectangle(points[0].x, points[0].y, points[2].x - points[0].x, points[2].y - points[0].y);
        }
        else
        {
            path.addRoundedRectangle(points[6].x, points[0].y, points[2].x - points[6].x, points[5].y - points[0].y, points[2].y - points[0].y);
        }
        return path;
    }
    
    static inline juce::Path fromOval(std::vector<t_pt> const& points)
    {
        juce::Path path;
        path.addEllipse(points[0].x, points[0].y, points[1].x - points[0].x, points[1].y - points[0].y);
        return path;
    }
    
    static inline juce::Path tojPath(Gobj const& obj)
    {
        if(obj.type() == Gobj::Path)
        {
            return fromPath(obj.points());
        }
        else if(obj.type() == Gobj::Rect)
        {
            return fromRect(obj.points());
        }
        else if(obj.type() == Gobj::Oval)
        {
            return fromOval(obj.points());
        }
        else if(obj.type() == Gobj::Arc)
        {
            
        }
        return juce::Path();
    }
}

#endif
