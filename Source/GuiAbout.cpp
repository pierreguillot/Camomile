/*
 // Copyright (c) 2015 Pierre Guillot.
 // For information on usage and redistribution, and for a DISCLAIMER OF ALL
 // WARRANTIES, see the file, "LICENSE.txt," in this distribution.
*/

#include "GuiAbout.hpp"
#include "Gui.hpp"

// ==================================================================================== //
//                                      GUI TOGGLE                                      //
// ==================================================================================== //

GuiAbout::GuiAbout()
{
    m_image1.setImage(ImageCache::getFromMemory(BinaryData::flowerG_png, BinaryData::flowerG_pngSize));
    m_image1.setBoundingBox(RelativeParallelogram(Rectangle<float>(300.f - 128.f, 370.f - 128.f, 128.f, 128.f)));
    m_image1.setOpacity(0.5f);
    addAndMakeVisible(&m_image1);
    
    m_text.setMultiLine(true);
    m_text.setReadOnly(true);
    m_text.setScrollbarsShown(false);
    m_text.setCaretVisible(false);
    m_text.setPopupMenuEnabled(true);
    m_text.setColour(juce::TextEditor::backgroundColourId, Gui::getColorInv());
    m_text.setColour(juce::TextEditor::outlineColourId, Gui::getColorInv());
    m_text.setColour(juce::TextEditor::shadowColourId,Gui::getColorInv());
    m_text.setColour(juce::TextEditor::textColourId, Gui::getColorTxt());
    m_text.setFont(Gui::getFont());
    m_text.setText("Camomile is a dynamic plugin made with Juce that allows to load and to control Pure Data patches inside a digital audio workstation.\n\n"
                   "Author :\n"+ String(JucePlugin_Manufacturer) + "\n\n"
                   "Organizations :\nCICM | Université Paris 8 | Labex Arts H2H\n\n"
                   "Web Site :\n" + String(JucePlugin_ManufacturerWebsite)+"\n\n"
                   "Credits :\nPure Data by Miller Puckette\nJuce by ROLI Ltd."
#ifdef JucePlugin_Build_VST
                   + "\nVST PlugIn Technology by Steinberg Media Technologies");
#elif JucePlugin_Build_VST3
                   +  "\nVST PlugIn Technology by Steinberg Media Technologies");
#else
                    );
#endif
    m_text.setBounds(0, 0, 300, 370);
    addAndMakeVisible(&m_text, -1);
}
