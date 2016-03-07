/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#ifndef __CAMOMILE_PATCH_EDITOR__
#define __CAMOMILE_PATCH_EDITOR__

#include "../JuceLibraryCode/JuceHeader.h"
#include "InstanceProcessor.h"
#include "LookAndFeel.h"
#include "GuiPatcher.hpp"

// ==================================================================================== //
//                                  CAMOMILE INTERFACE                                  //
// ==================================================================================== //

class PatchEditor : public AudioProcessorEditor, public InstanceProcessor::Listener, public Button::Listener
{
public:
    PatchEditor(InstanceProcessor&);
    ~PatchEditor();
    void paint(Graphics&) override;
    void buttonClicked(Button* button) override;
    void patchChanged() override;
    
    static Font getFont(){return Font(String("Monaco"), 13.f, juce::Font::plain);}
    static int getBordersize() noexcept {return 1;}
    static Colour const& getColorBg() noexcept {return Colours::lightgrey;}
    static Colour const& getColorBd() noexcept {return Colours::darkgrey;}
    static Colour const& getColorTxt() noexcept {return Colours::darkgrey;}
    static Colour const& getColorInv() noexcept {
        static Colour c(Colour::fromFloatRGBA(0.f, 0.f, 0.f, 0.f));
        return c;}
    
private:
    class ImgButton;
    class PatchWin;
    class About;
    class Console;
    
    InstanceProcessor&                      m_processor;
    bool                                    m_dropping;
    Toolbar                                 m_menu;
    ScopedPointer<ImgButton>                m_button;
    ScopedPointer<DocumentWindow>           m_window;
    ScopedPointer<GuiPatcher>               m_patcher;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PatchEditor)
};



#endif  // PLUGINEDITOR_H_INCLUDED
