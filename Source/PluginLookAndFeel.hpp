/*
 // Copyright (c) 2015-2018 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
 */

#pragma once

#include <JuceHeader.h>

class JUCE_API  CamoLookAndFeel  : public LookAndFeel_V4
{
public:
    CamoLookAndFeel();
    ~CamoLookAndFeel();

    void drawPopupMenuBackground (Graphics&, int width, int height) override;
    Font getPopupMenuFont() override;
    Font getTabButtonFont(TabBarButton&, float height) override;
    void drawLabel (Graphics& g, Label& label) override;
    
    static Font getDefaultFont();
    static Font getFont(const std::string& name);
    static Image const& getImage();
    static String const& getDescription();
    
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CamoLookAndFeel)
};


