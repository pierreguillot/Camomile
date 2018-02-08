/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class JUCE_API  CamoLookAndFeel  : public LookAndFeel_V4
{
public:
    CamoLookAndFeel();
    ~CamoLookAndFeel();

    void drawPopupMenuBackground (Graphics&, int width, int height) override;
    Font getPopupMenuFont() override;
    Font getTabButtonFont(TabBarButton&, float height) override;
    static Font getDefaultFont();
    static Image const& getImage();
    static String const& getDescription();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamoLookAndFeel)
};


