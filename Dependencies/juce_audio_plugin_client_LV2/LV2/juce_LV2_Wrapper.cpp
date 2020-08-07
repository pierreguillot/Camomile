/*
  ==============================================================================

   Juce LV2 Wrapper

  ==============================================================================
*/


#define JUCE_GUI_BASICS_INCLUDE_XHEADERS 1
#include <juce_gui_basics/juce_gui_basics.h>

#include <juce_audio_plugin_client/utility/juce_CheckSettingMacros.h>
#include <juce_audio_plugin_client/utility/juce_IncludeModuleHeaders.h>
#include <juce_core/system/juce_TargetPlatform.h>

#if JucePlugin_Build_LV2

/** Plugin requires processing with a fixed/constant block size */
#ifndef JucePlugin_WantsLV2FixedBlockSize
#define JucePlugin_WantsLV2FixedBlockSize 0
#endif

/** Enable latency port */
#ifndef JucePlugin_WantsLV2Latency
#define JucePlugin_WantsLV2Latency 1
#endif

/** Use non-parameter states */
#ifndef JucePlugin_WantsLV2State
#define JucePlugin_WantsLV2State 1
#endif

/** States are strings, needs custom get/setStateInformationString */
#ifndef JucePlugin_WantsLV2StateString
#define JucePlugin_WantsLV2StateString 0
#endif

/** Export presets */
#ifndef JucePlugin_WantsLV2Presets
#define JucePlugin_WantsLV2Presets 1
#endif

/** Request time position */
#ifndef JucePlugin_WantsLV2TimePos
#define JucePlugin_WantsLV2TimePos 1
#endif

/** Using string states require enabling states first */
#if JucePlugin_WantsLV2StateString && ! JucePlugin_WantsLV2State
#undef JucePlugin_WantsLV2State
#define JucePlugin_WantsLV2State 1
#endif

#if JUCE_LINUX && ! JUCE_AUDIOPROCESSOR_NO_GUI
#include <X11/Xlib.h>
#define JUCE_GUI_BASICS_INCLUDE_XHEADERS 1

#include <juce_audio_plugin_client/utility/juce_FakeMouseMoveGenerator.h>
#include <juce_audio_plugin_client/utility/juce_WindowsHooks.h>
#undef KeyPress
#endif

#include <fstream>
#include <iostream>

// LV2 includes..
#include "lv2/core/lv2.h"
#include "lv2/atom/atom.h"
#include "lv2/atom/util.h"
#include "lv2/buf-size/buf-size.h"
#include "lv2/instance-access/instance-access.h"
#include "lv2/midi/midi.h"
#include "lv2/options/options.h"
#include "lv2/port-props/port-props.h"
#include "lv2/presets/presets.h"
#include "lv2/state/state.h"
#include "lv2/time/time.h"
#include "lv2/ui/ui.h"
#include "lv2/urid/urid.h"
#include "includes/lv2_external_ui.h"
#include "includes/lv2_programs.h"

#define JUCE_LV2_STATE_STRING_URI "urn:juce:stateString"
#define JUCE_LV2_STATE_BINARY_URI "urn:juce:stateBinary"

//==============================================================================
// Various helper functions for creating the ttl files

#if JUCE_MAC
#define PLUGIN_EXT ".dylib"
#elif JUCE_LINUX
#define PLUGIN_EXT ".so"
#elif JUCE_WINDOWS
#define PLUGIN_EXT ".dll"
#endif

using namespace juce;

const float getParameter2(AudioProcessor* const filter, int index)
{
    if(auto* param = filter->getParameters()[index])
        return param->getValue();
    else
        return 0.0;
}

const void setParameter2(AudioProcessor* const filter, int index, float value)
{
    if (auto* param = filter->getParameters()[index])
        param->setValue(value);
}

bool isParameterAutomatable2(AudioProcessor* const filter, int index)
{
    if (auto* param = filter->getParameters()[index])
        return param->isAutomatable();
    
    return true;
}

const String getParameterName2(AudioProcessor* const filter, int index)
{
    if(auto* param = filter->getParameters()[index])
        return param->getName(1024);
    else
        return {};
}

/** Returns plugin type, defined in AppConfig.h or JucePluginCharacteristics.h */
const String getPluginType()
{
    String pluginType;
#ifdef JucePlugin_LV2Category
    pluginType  = "lv2:" JucePlugin_LV2Category;
    pluginType += ", ";
#elif JucePlugin_IsSynth
    pluginType  = "lv2:InstrumentPlugin, ";
#endif
    pluginType += "lv2:Plugin";
    return pluginType;
}

/** Returns plugin URI */
static const String& getPluginURI()
{
    // JucePlugin_LV2URI might be defined as a function (eg. allowing dynamic URIs based on filename)
    static const String pluginURI(JucePlugin_LV2URI);
    return pluginURI;
}

static Array<String> usedSymbols;

/** Converts a parameter name to an LV2 compatible symbol. */
const String nameToSymbol (const String& name, const uint32 portIndex)
{
    String symbol, trimmedName = name.trimStart().trimEnd().toLowerCase();
    
    if (trimmedName.isEmpty())
    {
        symbol += "lv2_port_";
        symbol += String(portIndex+1);
    }
    else
    {
        for (int i=0; i < trimmedName.length(); ++i)
        {
            const juce_wchar c = trimmedName[i];
            if (i == 0 && CharacterFunctions::isDigit(c))
                symbol += "_";
            else if (CharacterFunctions::isLetter(c) || CharacterFunctions::isDigit(c))
                symbol += c;
            else
                symbol += "_";
        }
    }
    
    // Do not allow identical symbols
    if (usedSymbols.contains(symbol))
    {
        int offset = 2;
        String offsetStr = "_2";
        symbol += offsetStr;
        
        while (usedSymbols.contains(symbol))
        {
            offset += 1;
            String newOffsetStr = "_" + String(offset);
            symbol = symbol.replace(offsetStr, newOffsetStr);
            offsetStr = newOffsetStr;
        }
    }
    usedSymbols.add(symbol);
    
    return symbol;
}

/** Prevents NaN or out of 0.0<->1.0 bounds parameter values. */
float safeParamValue (float value)
{
    if (std::isnan(value))
        value = 0.0f;
    else if (value < 0.0f)
        value = 0.0f;
    else if (value > 1.0f)
        value = 1.0f;
    return value;
}

/** Create the manifest.ttl file contents */
const String makeManifestFile (AudioProcessor* const filter, const String& binary)
{
    const String& pluginURI(getPluginURI());
    String text;
    
    // Header
    text += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
    text += "@prefix pset: <" LV2_PRESETS_PREFIX "> .\n";
    text += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    text += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
    text += "\n";
    
    // Plugin
    text += "<" + pluginURI + ">\n";
    text += "    a lv2:Plugin ;\n";
    text += "    lv2:binary <" + binary + PLUGIN_EXT "> ;\n";
    text += "    rdfs:seeAlso <" + binary + ".ttl> .\n";
    text += "\n";
    
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
    // UIs
    if (filter->hasEditor())
    {
        text += "<" + pluginURI + "#ExternalUI>\n";
        text += "    a <" LV2_EXTERNAL_UI__Widget "> ;\n";
        text += "    ui:binary <" + binary + PLUGIN_EXT "> ;\n";
        text += "    lv2:requiredFeature <" LV2_INSTANCE_ACCESS_URI "> ;\n";
        text += "    lv2:extensionData <" LV2_PROGRAMS__UIInterface "> .\n";
        text += "\n";
        
        text += "<" + pluginURI + "#ParentUI>\n";
#if JUCE_MAC
        text += "    a ui:CocoaUI ;\n";
#elif JUCE_LINUX
        text += "    a ui:X11UI ;\n";
#elif JUCE_WINDOWS
        text += "    a ui:WindowsUI ;\n";
#endif
        text += "    ui:binary <" + binary + PLUGIN_EXT "> ;\n";
        text += "    lv2:requiredFeature <" LV2_INSTANCE_ACCESS_URI "> ;\n";
        text += "    lv2:optionalFeature ui:noUserResize ;\n";
        text += "    lv2:extensionData <" LV2_PROGRAMS__UIInterface "> .\n";
        text += "\n";
    }
#endif
    
#if JucePlugin_WantsLV2Presets
    const String presetSeparator(pluginURI.contains("#") ? ":" : "#");
    
    // Presets
    for (int i = 0; i < filter->getNumPrograms(); ++i)
    {
        text += "<" + pluginURI + presetSeparator + "preset" + String::formatted("%03i", i+1) + ">\n";
        text += "    a pset:Preset ;\n";
        text += "    lv2:appliesTo <" + pluginURI + "> ;\n";
        text += "    rdfs:label \"" + filter->getProgramName(i) + "\" ;\n";
        text += "    rdfs:seeAlso <presets.ttl> .\n";
        text += "\n";
    }
#endif
    
    return text;
}

/** Create the -plugin-.ttl file contents */
const String makePluginFile (AudioProcessor* const filter, const int maxNumInputChannels, const int maxNumOutputChannels)
{
    const String& pluginURI(getPluginURI());
    String text;
    
    // Header
    text += "@prefix atom: <" LV2_ATOM_PREFIX "> .\n";
    text += "@prefix doap: <http://usefulinc.com/ns/doap#> .\n";
    text += "@prefix foaf: <http://xmlns.com/foaf/0.1/> .\n";
    text += "@prefix lv2:  <" LV2_CORE_PREFIX "> .\n";
    text += "@prefix rdfs: <http://www.w3.org/2000/01/rdf-schema#> .\n";
    text += "@prefix ui:   <" LV2_UI_PREFIX "> .\n";
    text += "\n";
    
    // Plugin
    text += "<" + pluginURI + ">\n";
    text += "    a " + getPluginType() + " ;\n";
    text += "    lv2:requiredFeature <" LV2_BUF_SIZE__boundedBlockLength "> ,\n";
#if JucePlugin_WantsLV2FixedBlockSize
    text += "                        <" LV2_BUF_SIZE__fixedBlockLength "> ,\n";
#endif
    text += "                        <" LV2_URID__map "> ;\n";
    text += "    lv2:extensionData <" LV2_OPTIONS__interface "> ,\n";
#if JucePlugin_WantsLV2State
    text += "                      <" LV2_STATE__interface "> ,\n";
#endif
    text += "                      <" LV2_PROGRAMS__Interface "> ;\n";
    text += "\n";
    
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
    // UIs
    if (filter->hasEditor())
    {
        text += "    ui:ui <" + pluginURI + "#ExternalUI> ,\n";
        text += "          <" + pluginURI + "#ParentUI> ;\n";
        text += "\n";
    }
#endif
    
    uint32 portIndex = 0;
    
#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
    // MIDI input
    text += "    lv2:port [\n";
    text += "        a lv2:InputPort, atom:AtomPort ;\n";
    text += "        atom:bufferType atom:Sequence ;\n";
#if JucePlugin_WantsMidiInput
    text += "        atom:supports <" LV2_MIDI__MidiEvent "> ;\n";
#endif
#if JucePlugin_WantsLV2TimePos
    text += "        atom:supports <" LV2_TIME__Position "> ;\n";
#endif
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_events_in\" ;\n";
    text += "        lv2:name \"Events Input\" ;\n";
    text += "        lv2:designation lv2:control ;\n";
#if ! JucePlugin_IsSynth
    text += "        lv2:portProperty lv2:connectionOptional ;\n";
#endif
    text += "    ] ;\n";
    text += "\n";
#endif
    
#if JucePlugin_ProducesMidiOutput
    // MIDI output
    text += "    lv2:port [\n";
    text += "        a lv2:OutputPort, atom:AtomPort ;\n";
    text += "        atom:bufferType atom:Sequence ;\n";
    text += "        atom:supports <" LV2_MIDI__MidiEvent "> ;\n";
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_midi_out\" ;\n";
    text += "        lv2:name \"MIDI Output\" ;\n";
    text += "    ] ;\n";
    text += "\n";
#endif
    
    // Freewheel port
    text += "    lv2:port [\n";
    text += "        a lv2:InputPort, lv2:ControlPort ;\n";
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_freewheel\" ;\n";
    text += "        lv2:name \"Freewheel\" ;\n";
    text += "        lv2:default 0.0 ;\n";
    text += "        lv2:minimum 0.0 ;\n";
    text += "        lv2:maximum 1.0 ;\n";
    text += "        lv2:designation <" LV2_CORE__freeWheeling "> ;\n";
    text += "        lv2:portProperty lv2:toggled, <" LV2_PORT_PROPS__notOnGUI "> ;\n";
    text += "    ] ;\n";
    text += "\n";
    
#if JucePlugin_WantsLV2Latency
    // Latency port
    text += "    lv2:port [\n";
    text += "        a lv2:OutputPort, lv2:ControlPort ;\n";
    text += "        lv2:index " + String(portIndex++) + " ;\n";
    text += "        lv2:symbol \"lv2_latency\" ;\n";
    text += "        lv2:name \"Latency\" ;\n";
    text += "        lv2:designation <" LV2_CORE__latency "> ;\n";
    text += "        lv2:portProperty lv2:reportsLatency, lv2:integer ;\n";
    text += "    ] ;\n";
    text += "\n";
#endif
    
    // Audio inputs
    for (int i=0; i < maxNumInputChannels; ++i)
    {
        if (i == 0)
            text += "    lv2:port [\n";
        else
            text += "    [\n";
        
        text += "        a lv2:InputPort, lv2:AudioPort ;\n";
        text += "        lv2:index " + String(portIndex++) + " ;\n";
        text += "        lv2:symbol \"lv2_audio_in_" + String(i+1) + "\" ;\n";
        text += "        lv2:name \"Audio Input " + String(i+1) + "\" ;\n";
        
        if (i+1 == maxNumInputChannels)
            text += "    ] ;\n\n";
        else
            text += "    ] ,\n";
    }
    
    // Audio outputs
    for (int i=0; i < maxNumOutputChannels; ++i)
    {
        if (i == 0)
            text += "    lv2:port [\n";
        else
            text += "    [\n";
        
        text += "        a lv2:OutputPort, lv2:AudioPort ;\n";
        text += "        lv2:index " + String(portIndex++) + " ;\n";
        text += "        lv2:symbol \"lv2_audio_out_" + String(i+1) + "\" ;\n";
        text += "        lv2:name \"Audio Output " + String(i+1) + "\" ;\n";
        
        if (i+1 == maxNumOutputChannels)
            text += "    ] ;\n\n";
        else
            text += "    ] ,\n";
    }
    
    // Parameters
    for (int i=0; i < filter->getParameters().size(); ++i)
    {
        if (i == 0)
            text += "    lv2:port [\n";
        else
            text += "    [\n";
        
        text += "        a lv2:InputPort, lv2:ControlPort ;\n";
        text += "        lv2:index " + String(portIndex++) + " ;\n";
        text += "        lv2:symbol \"" + nameToSymbol(getParameterName2(filter, i), i) + "\" ;\n";
        
        if (getParameterName2(filter, i).isNotEmpty())
            text += "        lv2:name \"" + getParameterName2(filter, i) + "\" ;\n";
        else
            text += "        lv2:name \"Port " + String(i+1) + "\" ;\n";
        
        text += "        lv2:default " + String::formatted("%f", safeParamValue(getParameter2(filter, i))) + " ;\n";
        text += "        lv2:minimum 0.0 ;\n";
        text += "        lv2:maximum 1.0 ;\n";
        
        if (! isParameterAutomatable2(filter, i))
            text += "        lv2:portProperty <" LV2_PORT_PROPS__expensive "> ;\n";
        
        if (i+1 == filter->getParameters().size())
            text += "    ] ;\n\n";
        else
            text += "    ] ,\n";
    }
    
    text += "    doap:name \"" + filter->getName() + "\" ;\n";
    text += "    doap:maintainer [ foaf:name \"" + juce::String(JucePlugin_Manufacturer) + "\" ] .\n";
    
    return text;
}

/** Create the presets.ttl file contents */
const String makePresetsFile (AudioProcessor* const filter)
{
    const String& pluginURI(getPluginURI());
    String text;
    
    // Header
    text += "@prefix atom:  <" LV2_ATOM_PREFIX "> .\n";
    text += "@prefix lv2:   <" LV2_CORE_PREFIX "> .\n";
    text += "@prefix pset:  <" LV2_PRESETS_PREFIX "> .\n";
    text += "@prefix rdf:   <http://www.w3.org/1999/02/22-rdf-syntax-ns#> .\n";
    text += "@prefix rdfs:  <http://www.w3.org/2000/01/rdf-schema#> .\n";
    text += "@prefix state: <" LV2_STATE_PREFIX "> .\n";
    text += "@prefix xsd:   <http://www.w3.org/2001/XMLSchema#> .\n";
    text += "\n";
    
    // Presets
    const int numPrograms = filter->getNumPrograms();
    const String presetSeparator(pluginURI.contains("#") ? ":" : "#");
    
    for (int i = 0; i < numPrograms; ++i)
    {
        std::cout << "\nSaving preset " << i+1 << "/" << numPrograms+1 << "...";
        std::cout.flush();
        
        String preset;
        
        // Label
        filter->setCurrentProgram(i);
        preset += "<" + pluginURI + presetSeparator + "preset" + String::formatted("%03i", i+1) + "> a pset:Preset ;\n";
        
        // State
#if JucePlugin_WantsLV2State
        preset += "    state:state [\n";
#if JucePlugin_WantsLV2StateString
        preset += "        <" JUCE_LV2_STATE_STRING_URI ">\n";
        preset += "\"\"\"\n";
        preset += filter->getStateInformationString().replace("\r\n","\n");
        preset += "\"\"\"\n";
#else
        MemoryBlock chunkMemory;
        filter->getCurrentProgramStateInformation(chunkMemory);
        const String chunkString(Base64::toBase64(chunkMemory.getData(), chunkMemory.getSize()));
        
        preset += "        <" JUCE_LV2_STATE_BINARY_URI "> [\n";
        preset += "            a atom:Chunk ;\n";
        preset += "            rdf:value \"" + chunkString + "\"^^xsd:base64Binary ;\n";
        preset += "        ] ;\n";
#endif
        if (filter->getParameters().size() == 0)
        {
            preset += "    ] .\n\n";
            continue;
        }
        
        preset += "    ] ;\n\n";
#endif
        
        // Port values
        usedSymbols.clear();
        
        for (int j=0; j < filter->getParameters().size(); ++j)
        {
            if (j == 0)
                preset += "    lv2:port [\n";
            else
                preset += "    [\n";
            
            preset += "        lv2:symbol \"" + nameToSymbol(getParameterName2(filter, j), j) + "\" ;\n";
            preset += "        pset:value " + String::formatted("%f", safeParamValue(getParameter2(filter, j))) + " ;\n";
            
            if (j+1 == filter->getParameters().size())
                preset += "    ] ";
            else
                preset += "    ] ,\n";
        }
        preset += ".\n\n";
        
        text += preset;
    }
    
    return text;
}

/** Creates manifest.ttl, plugin.ttl and presets.ttl files */
void createLv2Files(const char* basename)
{
    const ScopedJuceInitialiser_GUI juceInitialiser;
    std::unique_ptr<AudioProcessor> filter (createPluginFilterOfType (AudioProcessor::wrapperType_LV2));
    
    String binary(basename);
    String binaryTTL(binary + ".ttl");
    
    std::cout << "Writing manifest.ttl..."; std::cout.flush();
    std::fstream manifest("manifest.ttl", std::ios::out);
    manifest << makeManifestFile(filter.get(), binary) << std::endl;
    manifest.close();
    std::cout << " done!" << std::endl;
    
    std::cout << "Writing " << binary << ".ttl..."; std::cout.flush();
    std::fstream plugin(binaryTTL.toUTF8(), std::ios::out);
    plugin << makePluginFile(filter.get(), filter->getTotalNumInputChannels(), filter->getTotalNumOutputChannels()) << std::endl;
    plugin.close();
    std::cout << " done!" << std::endl;
    
#if JucePlugin_WantsLV2Presets
    std::cout << "Writing presets.ttl..."; std::cout.flush();
    std::fstream presets("presets.ttl", std::ios::out);
    presets << makePresetsFile(filter.get()) << std::endl;
    presets.close();
    std::cout << " done!" << std::endl;
#endif
}

//==============================================================================
#if JUCE_LINUX

struct SharedMessageThread  : public Thread
{
    SharedMessageThread()  : Thread ("Lv2MessageThread")
    {
        startThread (7);
        
        while (! initialised)
            sleep (1);
    }
    
    ~SharedMessageThread() override
    {
        signalThreadShouldExit();
        JUCEApplicationBase::quit();
        waitForThreadToExit (5000);
    }
    
    void run() override
    {
        ScopedJuceInitialiser_GUI juceInitialiser;
        initialised = true;
        
        MessageManager::getInstance()->setCurrentThreadAsMessageThread();
        
        XWindowSystem::getInstance();
        
        while ((! threadShouldExit()) && MessageManager::getInstance()->runDispatchLoopUntil (250))
        {}
    }
    
    bool initialised = false;
};

#endif

#if ! JUCE_AUDIOPROCESSOR_NO_GUI
//==============================================================================
/**
 Lightweight DocumentWindow subclass for external ui
 */
class JuceLv2ExternalUIWindow : public DocumentWindow
{
public:
    /** Creates a Document Window wrapper */
    JuceLv2ExternalUIWindow (AudioProcessorEditor* editor, const String& title) :
    DocumentWindow (title, Colours::white, DocumentWindow::minimiseButton | DocumentWindow::closeButton, false),
    closed (false),
    lastPos (0, 0)
    {
        setOpaque (true);
        setContentNonOwned (editor, true);
        setSize (editor->getWidth(), editor->getHeight());
        setUsingNativeTitleBar (true);
    }
    
    /** Close button handler */
    void closeButtonPressed()
    {
        saveLastPos();
        removeFromDesktop();
        closed = true;
    }
    
    void saveLastPos()
    {
        lastPos = getScreenPosition();
    }
    
    void restoreLastPos()
    {
        setTopLeftPosition (lastPos.getX(), lastPos.getY());
    }
    
    Point<int> getLastPos()
    {
        return lastPos;
    }
    
    bool isClosed()
    {
        return closed;
    }
    
    void reset()
    {
        closed = false;
    }
    
private:
    bool closed;
    Point<int> lastPos;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ExternalUIWindow);
};

//==============================================================================
/**
 Juce LV2 External UI handle
 */
class JuceLv2ExternalUIWrapper : public LV2_External_UI_Widget
{
public:
    JuceLv2ExternalUIWrapper (AudioProcessorEditor* editor, const String& title)
    : window (editor, title)
    {
        // external UI calls
        run  = doRun;
        show = doShow;
        hide = doHide;
    }
    
    ~JuceLv2ExternalUIWrapper()
    {
        if (window.isOnDesktop())
            window.removeFromDesktop();
    }
    
    void close()
    {
        window.closeButtonPressed();
    }
    
    bool isClosed()
    {
        return window.isClosed();
    }
    
    void reset(const String& title)
    {
        window.reset();
        window.setName(title);
    }
    
    void repaint()
    {
        window.repaint();
    }
    
    Point<int> getScreenPosition()
    {
        if (window.isClosed())
            return window.getLastPos();
        else
            return window.getScreenPosition();
    }
    
    void setScreenPos (int x, int y)
    {
        if (! window.isClosed())
            window.setTopLeftPosition(x, y);
    }
    
    //==============================================================================
    static void doRun (LV2_External_UI_Widget* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUIWrapper* self = (JuceLv2ExternalUIWrapper*) _this_;
        
        if (! self->isClosed())
            self->window.repaint();
    }
    
    static void doShow (LV2_External_UI_Widget* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUIWrapper* self = (JuceLv2ExternalUIWrapper*) _this_;
        
        if (! self->isClosed())
        {
            if (! self->window.isOnDesktop())
                self->window.addToDesktop();
            
            self->window.restoreLastPos();
            self->window.setVisible(true);
        }
    }
    
    static void doHide (LV2_External_UI_Widget* _this_)
    {
        const MessageManagerLock mmLock;
        JuceLv2ExternalUIWrapper* self = (JuceLv2ExternalUIWrapper*) _this_;
        
        if (! self->isClosed())
        {
            self->window.saveLastPos();
            self->window.setVisible(false);
        }
    }
    
private:
    JuceLv2ExternalUIWindow window;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ExternalUIWrapper);
};

//==============================================================================
/**
 Juce LV2 Parent UI container, listens for resize events and passes them to ui-resize
 */
class JuceLv2ParentContainer : public Component
{
public:
    JuceLv2ParentContainer (AudioProcessorEditor* editor, const LV2UI_Resize* uiResize_)
    : uiResize(uiResize_)
    {
        setOpaque (true);
        editor->setOpaque (true);
        setBounds (editor->getBounds());
        
        editor->setTopLeftPosition (0, 0);
        addAndMakeVisible (editor);
    }
    
    ~JuceLv2ParentContainer()
    {
    }
    
    void paint (Graphics&) {}
    void paintOverChildren (Graphics&) {}
    
    void childBoundsChanged (Component* child)
    {
        const int cw = child->getWidth();
        const int ch = child->getHeight();
        
#if JUCE_LINUX
        X11Symbols::getInstance()->xResizeWindow (display, (Window) getWindowHandle(), cw, ch);
#else
        setSize (cw, ch);
#endif
        
        if (uiResize != nullptr)
            uiResize->ui_resize (uiResize->handle, cw, ch);
    }
    
    void reset (const LV2UI_Resize* uiResize_)
    {
        uiResize = uiResize_;
        
        if (uiResize != nullptr)
            uiResize->ui_resize (uiResize->handle, getWidth(), getHeight());
    }
    
private:
    //==============================================================================
    const LV2UI_Resize* uiResize;
#if JUCE_LINUX
    ::Display* display = XWindowSystem::getInstance()->getDisplay();
#endif
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2ParentContainer);
};

//==============================================================================
/**
 Juce LV2 UI handle
 */
class JuceLv2UIWrapper : public AudioProcessorListener,
public Timer
{
public:
    JuceLv2UIWrapper (AudioProcessor* filter_, LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_,
                      LV2UI_Widget* widget, const LV2_Feature* const* features, bool isExternal_)
    : filter (filter_),
    writeFunction (writeFunction_),
    controller (controller_),
    isExternal (isExternal_),
    controlPortOffset (0),
    lastProgramCount (0),
    uiTouch (nullptr),
    programsHost (nullptr),
    externalUIHost (nullptr),
    lastExternalUIPos (-1, -1),
    uiResize (nullptr)
    {
        jassert (filter != nullptr);
        
        filter->addListener(this);
        
        if (filter->hasEditor())
        {
            editor = std::unique_ptr<AudioProcessorEditor>(filter->createEditorIfNeeded());
            
            if (editor == nullptr)
            {
                *widget = nullptr;
                return;
            }
        }
        
        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_UI__touch) == 0)
                uiTouch = (const LV2UI_Touch*)features[i]->data;
            
            else if (strcmp(features[i]->URI, LV2_PROGRAMS__Host) == 0)
                programsHost = (const LV2_Programs_Host*)features[i]->data;
        }
        
        if (isExternal)
        {
            resetExternalUI (features);
            
            if (externalUIHost != nullptr)
            {
                String title (filter->getName());
                
                if (externalUIHost->plugin_human_id != nullptr)
                    title = externalUIHost->plugin_human_id;
                
                externalUI = std::make_unique<JuceLv2ExternalUIWrapper>(editor.get(), title);
                *widget = externalUI.get();
                startTimer (100);
            }
            else
            {
                *widget = nullptr;
            }
        }
        else
        {
            resetParentUI (features);
            
            if (parentContainer != nullptr)
                *widget = parentContainer->getWindowHandle();
            else
                *widget = nullptr;
        }
        
#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
        controlPortOffset += 1;
#endif
#if JucePlugin_ProducesMidiOutput
        controlPortOffset += 1;
#endif
        controlPortOffset += 1; // freewheel
#if JucePlugin_WantsLV2Latency
        controlPortOffset += 1;
#endif
        controlPortOffset += filter->getTotalNumInputChannels();
        controlPortOffset += filter->getTotalNumOutputChannels();
        
        lastProgramCount = filter->getNumPrograms();
    }
    
    ~JuceLv2UIWrapper()
    {
        PopupMenu::dismissAllActiveMenus();
        
        filter->removeListener(this);
        
        parentContainer = nullptr;
        externalUI = nullptr;
        externalUIHost = nullptr;
        
        if (editor != nullptr)
        {
            filter->editorBeingDeleted (editor.get());
            editor = nullptr;
        }
    }
    
    //==============================================================================
    // LV2 core calls
    
    void lv2Cleanup()
    {
        const MessageManagerLock mmLock;
        
        if (isExternal)
        {
            if (isTimerRunning())
                stopTimer();
            
            externalUIHost = nullptr;
            
            if (externalUI != nullptr)
            {
                lastExternalUIPos = externalUI->getScreenPosition();
                externalUI->close();
            }
        }
        else
        {
            if (parentContainer)
            {
                parentContainer->setVisible (false);
                if (parentContainer->isOnDesktop())
                    parentContainer->removeFromDesktop();
            }
        }
    }
    
    //==============================================================================
    // Juce calls
    
    void audioProcessorParameterChanged (AudioProcessor*, int index, float newValue)
    {
        if (writeFunction != nullptr && controller != nullptr)
            writeFunction (controller, index + controlPortOffset, sizeof (float), 0, &newValue);
    }
    
    void audioProcessorChanged (AudioProcessor*)
    {
        if (filter != nullptr && programsHost != nullptr)
        {
            if (filter->getNumPrograms() != lastProgramCount)
            {
                programsHost->program_changed (programsHost->handle, -1);
                lastProgramCount = filter->getNumPrograms();
            }
            else
                programsHost->program_changed (programsHost->handle, filter->getCurrentProgram());
        }
    }
    
    void audioProcessorParameterChangeGestureBegin (AudioProcessor*, int parameterIndex)
    {
        if (uiTouch != nullptr)
            uiTouch->touch (uiTouch->handle, parameterIndex + controlPortOffset, true);
    }
    
    void audioProcessorParameterChangeGestureEnd (AudioProcessor*, int parameterIndex)
    {
        if (uiTouch != nullptr)
            uiTouch->touch (uiTouch->handle, parameterIndex + controlPortOffset, false);
    }
    
    void timerCallback()
    {
        if (externalUI != nullptr && externalUI->isClosed())
        {
            if (externalUIHost != nullptr)
                externalUIHost->ui_closed (controller);
            
            if (isTimerRunning())
                stopTimer();
        }
    }
    
    //==============================================================================
    void resetIfNeeded (LV2UI_Write_Function writeFunction_, LV2UI_Controller controller_, LV2UI_Widget* widget,
                        const LV2_Feature* const* features)
    {
        writeFunction = writeFunction_;
        controller = controller_;
        uiTouch = nullptr;
        programsHost = nullptr;
        
        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_UI__touch) == 0)
                uiTouch = (const LV2UI_Touch*)features[i]->data;
            
            else if (strcmp(features[i]->URI, LV2_PROGRAMS__Host) == 0)
                programsHost = (const LV2_Programs_Host*)features[i]->data;
        }
        
        if (isExternal)
        {
            resetExternalUI (features);
            *widget = externalUI.get();
        }
        else
        {
            resetParentUI (features);
            *widget = parentContainer->getWindowHandle();
        }
    }
    
    void repaint()
    {
        const MessageManagerLock mmLock;
        
        if (editor != nullptr)
            editor->repaint();
        
        if (parentContainer != nullptr)
            parentContainer->repaint();
        
        if (externalUI != nullptr)
            externalUI->repaint();
    }
    
private:
    AudioProcessor* const filter;
    std::unique_ptr<AudioProcessorEditor> editor;
    
    LV2UI_Write_Function writeFunction;
    LV2UI_Controller controller;
    const bool isExternal;
    
    uint32 controlPortOffset;
    int lastProgramCount;
    
    const LV2UI_Touch* uiTouch;
    const LV2_Programs_Host* programsHost;
    
    std::unique_ptr<JuceLv2ExternalUIWrapper> externalUI;
    const LV2_External_UI_Host* externalUIHost;
    Point<int> lastExternalUIPos;
    
    std::unique_ptr<JuceLv2ParentContainer> parentContainer;
    const LV2UI_Resize* uiResize;
    
#if JUCE_LINUX
    ::Display* display = XWindowSystem::getInstance()->getDisplay();
#endif
    
    //==============================================================================
    void resetExternalUI (const LV2_Feature* const* features)
    {
        externalUIHost = nullptr;
        
        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_EXTERNAL_UI__Host) == 0)
            {
                externalUIHost = (const LV2_External_UI_Host*)features[i]->data;
                break;
            }
        }
        
        if (externalUI != nullptr)
        {
            String title(filter->getName());
            
            if (externalUIHost->plugin_human_id != nullptr)
                title = externalUIHost->plugin_human_id;
            
            if (lastExternalUIPos.getX() != -1 && lastExternalUIPos.getY() != -1)
                externalUI->setScreenPos(lastExternalUIPos.getX(), lastExternalUIPos.getY());
            
            externalUI->reset(title);
            startTimer (100);
        }
    }
    
    void resetParentUI (const LV2_Feature* const* features)
    {
        void* parent = nullptr;
        uiResize = nullptr;
        
        for (int i = 0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_UI__parent) == 0)
                parent = features[i]->data;
            
            else if (strcmp(features[i]->URI, LV2_UI__resize) == 0)
                uiResize = (const LV2UI_Resize*)features[i]->data;
        }
        
        if (parent != nullptr)
        {
            if (parentContainer == nullptr)
                parentContainer = std::make_unique<JuceLv2ParentContainer>(editor.get(), uiResize);
            
            parentContainer->setVisible (false);
            
            if (parentContainer->isOnDesktop())
                parentContainer->removeFromDesktop();
            
            parentContainer->addToDesktop (0, parent);
            
#if JUCE_LINUX
            Window hostWindow = (Window) parent;
            Window editorWnd  = (Window) parentContainer->getWindowHandle();
            X11Symbols::getInstance()->xReparentWindow (display, editorWnd, hostWindow, 0, 0);
#endif
            
            parentContainer->reset (uiResize);
            parentContainer->setVisible (true);
        }
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2UIWrapper)
};

#endif /* JUCE_AUDIOPROCESSOR_NO_GUI */

//==============================================================================
/**
 Juce LV2 handle
 */
class JuceLv2Wrapper : public AudioPlayHead
{
public:
    //==============================================================================
    JuceLv2Wrapper (double sampleRate_, const LV2_Feature* const* features)
    : bufferSize (2048),
    sampleRate (sampleRate_),
    uridMap (nullptr),
    uridAtomBlank (0),
    uridAtomObject (0),
    uridAtomDouble (0),
    uridAtomFloat (0),
    uridAtomInt (0),
    uridAtomLong (0),
    uridAtomSequence (0),
    uridMidiEvent (0),
    uridTimePos (0),
    uridTimeBar (0),
    uridTimeBarBeat (0),
    uridTimeBeatsPerBar (0),
    uridTimeBeatsPerMinute (0),
    uridTimeBeatUnit (0),
    uridTimeFrame (0),
    uridTimeSpeed (0),
    usingNominalBlockLength (false)
    {
        {
            const MessageManagerLock mmLock;
            filter = std::unique_ptr<AudioProcessor>(createPluginFilterOfType (AudioProcessor::wrapperType_LV2));
        }
        jassert (filter != nullptr);
        
        filter->setPlayConfigDetails (filter->getTotalNumInputChannels(), filter->getTotalNumOutputChannels(), 0, 0);
        filter->setPlayHead (this);
        
#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
        portEventsIn = nullptr;
#endif
#if JucePlugin_ProducesMidiOutput
        portMidiOut = nullptr;
#endif
        
        portFreewheel = nullptr;
        
#if JucePlugin_WantsLV2Latency
        portLatency = nullptr;
#endif
        portAudioIns.resize(filter->getTotalNumInputChannels(), nullptr);
        portAudioOuts.resize(filter->getTotalNumOutputChannels(), nullptr);

        portControls.insertMultiple (0, nullptr, filter->getParameters().size());
        
        for (int i=0; i < filter->getParameters().size(); ++i)
            lastControlValues.add (getParameter3(i));
        
        curPosInfo.resetToDefault();
        
        // we need URID_Map first
        for (int i=0; features[i] != nullptr; ++i)
        {
            if (strcmp(features[i]->URI, LV2_URID__map) == 0)
            {
                uridMap = (const LV2_URID_Map*)features[i]->data;
                break;
            }
        }
        
        // we require uridMap to work properly (it's set as required feature)
        jassert (uridMap != nullptr);
        
        if (uridMap != nullptr)
        {
            uridAtomBlank = uridMap->map(uridMap->handle, LV2_ATOM__Blank);
            uridAtomObject = uridMap->map(uridMap->handle, LV2_ATOM__Object);
            uridAtomDouble = uridMap->map(uridMap->handle, LV2_ATOM__Double);
            uridAtomFloat = uridMap->map(uridMap->handle, LV2_ATOM__Float);
            uridAtomInt = uridMap->map(uridMap->handle, LV2_ATOM__Int);
            uridAtomLong = uridMap->map(uridMap->handle, LV2_ATOM__Long);
            uridAtomSequence = uridMap->map(uridMap->handle, LV2_ATOM__Sequence);
            uridMidiEvent = uridMap->map(uridMap->handle, LV2_MIDI__MidiEvent);
            uridTimePos = uridMap->map(uridMap->handle, LV2_TIME__Position);
            uridTimeBar = uridMap->map(uridMap->handle, LV2_TIME__bar);
            uridTimeBarBeat = uridMap->map(uridMap->handle, LV2_TIME__barBeat);
            uridTimeBeatsPerBar = uridMap->map(uridMap->handle, LV2_TIME__beatsPerBar);
            uridTimeBeatsPerMinute = uridMap->map(uridMap->handle, LV2_TIME__beatsPerMinute);
            uridTimeBeatUnit = uridMap->map(uridMap->handle, LV2_TIME__beatUnit);
            uridTimeFrame = uridMap->map(uridMap->handle, LV2_TIME__frame);
            uridTimeSpeed = uridMap->map(uridMap->handle, LV2_TIME__speed);
            
            for (int i=0; features[i] != nullptr; ++i)
            {
                if (strcmp(features[i]->URI, LV2_OPTIONS__options) == 0)
                {
                    const LV2_Options_Option* options = (const LV2_Options_Option*)features[i]->data;
                    
                    for (int j=0; options[j].key != 0; ++j)
                    {
                        if (options[j].key == uridMap->map(uridMap->handle, LV2_BUF_SIZE__nominalBlockLength))
                        {
                            if (options[j].type == uridAtomInt)
                            {
                                bufferSize = *(int*)options[j].value;
                                usingNominalBlockLength = true;
                            }
                            else
                            {
                                std::cerr << "Host provides nominalBlockLength but has wrong value type" << std::endl;
                            }
                            break;
                        }
                        
                        if (options[j].key == uridMap->map(uridMap->handle, LV2_BUF_SIZE__maxBlockLength))
                        {
                            if (options[j].type == uridAtomInt)
                                bufferSize = *(int*)options[j].value;
                            else
                                std::cerr << "Host provides maxBlockLength but has wrong value type" << std::endl;
                            
                            // no break, continue in case host supports nominalBlockLength
                        }
                    }
                    break;
                }
            }
        }
        
        progDesc.bank = 0;
        progDesc.program = 0;
        progDesc.name = nullptr;
    }
    
    ~JuceLv2Wrapper ()
    {
        const MessageManagerLock mmLock;
        
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
        ui = nullptr;
#endif
        filter = nullptr;
        
        if (progDesc.name != nullptr)
            free((void*)progDesc.name);
        
        portControls.clear();
        lastControlValues.clear();
    }
    
    //==============================================================================
    // LV2 core calls
    
    const float getParameter3(int index)
    {
        if(auto* param = filter->getParameters()[index])
            return param->getValue();
        else
            return 0.0;
    }
    
    const void setParameter3(int index, float value)
    {
        if (auto* param = filter->getParameters()[index])
        {
            param->setValue(value);
            param->sendValueChangedMessageToListeners (value);
        }
    }
    
    bool isParameterAutomatable3(int index)
    {
        if (auto* param = filter->getParameters()[index])
            return param->isAutomatable();
        
        return true;
    }
    
    const String getParameterName3(int index)
    {
        if(auto* param = filter->getParameters()[index])
            return param->getName(1024);
        else
            return {};
    }
    
    void lv2ConnectPort (uint32 portId, void* dataLocation)
    {
        uint32 index = 0;
        
#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
        if (portId == index++)
        {
            portEventsIn = (LV2_Atom_Sequence*)dataLocation;
            return;
        }
#endif
        
#if JucePlugin_ProducesMidiOutput
        if (portId == index++)
        {
            portMidiOut = (LV2_Atom_Sequence*)dataLocation;
            return;
        }
#endif
        
        if (portId == index++)
        {
            portFreewheel = (float*)dataLocation;
            return;
        }
        
#if JucePlugin_WantsLV2Latency
        if (portId == index++)
        {
            portLatency = (float*)dataLocation;
            return;
        }
#endif
        
        for (int i=0; i < filter->getTotalNumInputChannels(); ++i)
        {
            if (portId == index++)
            {
                portAudioIns[i] = (float*)dataLocation;
                return;
            }
        }
        
        for (int i=0; i < filter->getTotalNumOutputChannels(); ++i)
        {
            if (portId == index++)
            {
                portAudioOuts[i] = (float*)dataLocation;
                return;
            }
        }
        
        for (int i=0; i < filter->getParameters().size(); ++i)
        {
            if (portId == index++)
            {
                portControls.set(i, (float*)dataLocation);
                return;
            }
        }
    }
    
    void lv2Activate()
    {
        jassert (filter != nullptr);
        
        filter->prepareToPlay (sampleRate, bufferSize);
        filter->setPlayConfigDetails (filter->getTotalNumInputChannels(), filter->getTotalNumOutputChannels(), sampleRate, bufferSize);
        
        channels.calloc (filter->getTotalNumInputChannels() + filter->getTotalNumOutputChannels());
        
#if (JucePlugin_WantsMidiInput || JucePlugin_ProducesMidiOutput)
        midiEvents.ensureSize (2048);
        midiEvents.clear();
#endif
    }
    
    void lv2Deactivate()
    {
        jassert (filter != nullptr);
        
        filter->releaseResources();
        
        channels.free();
    }
    
    void lv2Run (uint32 sampleCount)
    {
        jassert (filter != nullptr);
        
#if JucePlugin_WantsLV2Latency
        if (portLatency != nullptr)
            *portLatency = filter->getLatencySamples();
#endif
        
        if (portFreewheel != nullptr)
            filter->setNonRealtime (*portFreewheel >= 0.5f);
        
        if (sampleCount == 0)
        {
            /**
             LV2 pre-roll
             Hosts might use this to force plugins to update its output control ports.
             (plugins can only access port locations during run) */
            return;
        }
        
        // Check for updated parameters
        {
            float curValue;
            
            for (int i = 0; i < portControls.size(); ++i)
            {
                if (portControls[i] != nullptr)
                {
                    curValue = *portControls[i];
                    
                    if (lastControlValues[i] != curValue)
                    {
                        setParameter3(i, curValue);
                        lastControlValues.setUnchecked (i, curValue);
                    }
                }
            }
        }
        
        {
            const ScopedLock sl (filter->getCallbackLock());
            
            if (filter->isSuspended() && false)
            {
                for (int i = 0; i < filter->getTotalNumOutputChannels(); ++i)
                    zeromem (portAudioOuts[i], sizeof (float) * sampleCount);
            }
            else
            {
                int i;
                for (i = 0; i < filter->getTotalNumOutputChannels(); ++i)
                {
                    channels[i] = portAudioOuts[i];
                    
                    if (i < filter->getTotalNumInputChannels() && portAudioIns[i] != portAudioOuts[i])
                        FloatVectorOperations::copy (portAudioOuts [i], portAudioIns[i], sampleCount);
                }
                
                for (; i < filter->getTotalNumInputChannels(); ++i)
                    channels [i] = portAudioIns[i];
                
#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
                if (portEventsIn != nullptr)
                {
                    midiEvents.clear();
                    
                    LV2_ATOM_SEQUENCE_FOREACH(portEventsIn, iter)
                    {
                        const LV2_Atom_Event* event = (const LV2_Atom_Event*)iter;
                        
                        if (event == nullptr)
                            continue;
                        if (event->time.frames >= sampleCount)
                            break;
                        
#if JucePlugin_WantsMidiInput
                        if (event->body.type == uridMidiEvent)
                        {
                            const uint8* data = (const uint8*)(event + 1);
                            midiEvents.addEvent(data, event->body.size, static_cast<int>(event->time.frames));
                            continue;
                        }
#endif
#if JucePlugin_WantsLV2TimePos
                        if (event->body.type == uridAtomBlank || event->body.type == uridAtomObject)
                        {
                            const LV2_Atom_Object* obj = (LV2_Atom_Object*)&event->body;
                            
                            if (obj->body.otype != uridTimePos)
                                continue;
                            
                            LV2_Atom* bar = nullptr;
                            LV2_Atom* barBeat = nullptr;
                            LV2_Atom* beatUnit = nullptr;
                            LV2_Atom* beatsPerBar = nullptr;
                            LV2_Atom* beatsPerMinute = nullptr;
                            LV2_Atom* frame = nullptr;
                            LV2_Atom* speed = nullptr;
                            
                            lv2_atom_object_get (obj,
                                                 uridTimeBar, &bar,
                                                 uridTimeBarBeat, &barBeat,
                                                 uridTimeBeatUnit, &beatUnit,
                                                 uridTimeBeatsPerBar, &beatsPerBar,
                                                 uridTimeBeatsPerMinute, &beatsPerMinute,
                                                 uridTimeFrame, &frame,
                                                 uridTimeSpeed, &speed,
                                                 nullptr);
                            
                            // need to handle this first as other values depend on it
                            if (speed != nullptr)
                            {
                                /**/ if (speed->type == uridAtomDouble)
                                    lastPositionData.speed = ((LV2_Atom_Double*)speed)->body;
                                else if (speed->type == uridAtomFloat)
                                    lastPositionData.speed = ((LV2_Atom_Float*)speed)->body;
                                else if (speed->type == uridAtomInt)
                                    lastPositionData.speed = ((LV2_Atom_Int*)speed)->body;
                                else if (speed->type == uridAtomLong)
                                    lastPositionData.speed = ((LV2_Atom_Long*)speed)->body;
                                
                                curPosInfo.isPlaying = lastPositionData.speed != 0.0;
                            }
                            
                            if (bar != nullptr)
                            {
                                /**/ if (bar->type == uridAtomDouble)
                                    lastPositionData.bar = ((LV2_Atom_Double*)bar)->body;
                                else if (bar->type == uridAtomFloat)
                                    lastPositionData.bar = ((LV2_Atom_Float*)bar)->body;
                                else if (bar->type == uridAtomInt)
                                    lastPositionData.bar = ((LV2_Atom_Int*)bar)->body;
                                else if (bar->type == uridAtomLong)
                                    lastPositionData.bar = ((LV2_Atom_Long*)bar)->body;
                            }
                            
                            if (barBeat != nullptr)
                            {
                                /**/ if (barBeat->type == uridAtomDouble)
                                    lastPositionData.barBeat = ((LV2_Atom_Double*)barBeat)->body;
                                else if (barBeat->type == uridAtomFloat)
                                    lastPositionData.barBeat = ((LV2_Atom_Float*)barBeat)->body;
                                else if (barBeat->type == uridAtomInt)
                                    lastPositionData.barBeat = ((LV2_Atom_Int*)barBeat)->body;
                                else if (barBeat->type == uridAtomLong)
                                    lastPositionData.barBeat = ((LV2_Atom_Long*)barBeat)->body;
                            }
                            
                            if (beatUnit != nullptr)
                            {
                                /**/ if (beatUnit->type == uridAtomDouble)
                                    lastPositionData.beatUnit = ((LV2_Atom_Double*)beatUnit)->body;
                                else if (beatUnit->type == uridAtomFloat)
                                    lastPositionData.beatUnit = ((LV2_Atom_Float*)beatUnit)->body;
                                else if (beatUnit->type == uridAtomInt)
                                    lastPositionData.beatUnit = ((LV2_Atom_Int*)beatUnit)->body;
                                else if (beatUnit->type == uridAtomLong)
                                    lastPositionData.beatUnit = static_cast<uint32_t>(((LV2_Atom_Long*)beatUnit)->body);
                                
                                if (lastPositionData.beatUnit > 0)
                                    curPosInfo.timeSigDenominator = lastPositionData.beatUnit;
                            }
                            
                            if (beatsPerBar != nullptr)
                            {
                                /**/ if (beatsPerBar->type == uridAtomDouble)
                                    lastPositionData.beatsPerBar = ((LV2_Atom_Double*)beatsPerBar)->body;
                                else if (beatsPerBar->type == uridAtomFloat)
                                    lastPositionData.beatsPerBar = ((LV2_Atom_Float*)beatsPerBar)->body;
                                else if (beatsPerBar->type == uridAtomInt)
                                    lastPositionData.beatsPerBar = ((LV2_Atom_Int*)beatsPerBar)->body;
                                else if (beatsPerBar->type == uridAtomLong)
                                    lastPositionData.beatsPerBar = ((LV2_Atom_Long*)beatsPerBar)->body;
                                
                                if (lastPositionData.beatsPerBar > 0.0f)
                                    curPosInfo.timeSigNumerator = lastPositionData.beatsPerBar;
                            }
                            
                            if (beatsPerMinute != nullptr)
                            {
                                /**/ if (beatsPerMinute->type == uridAtomDouble)
                                    lastPositionData.beatsPerMinute = ((LV2_Atom_Double*)beatsPerMinute)->body;
                                else if (beatsPerMinute->type == uridAtomFloat)
                                    lastPositionData.beatsPerMinute = ((LV2_Atom_Float*)beatsPerMinute)->body;
                                else if (beatsPerMinute->type == uridAtomInt)
                                    lastPositionData.beatsPerMinute = ((LV2_Atom_Int*)beatsPerMinute)->body;
                                else if (beatsPerMinute->type == uridAtomLong)
                                    lastPositionData.beatsPerMinute = ((LV2_Atom_Long*)beatsPerMinute)->body;
                                
                                if (lastPositionData.beatsPerMinute > 0.0f)
                                {
                                    curPosInfo.bpm = lastPositionData.beatsPerMinute;
                                    
                                    if (lastPositionData.speed != 0)
                                        curPosInfo.bpm *= std::abs(lastPositionData.speed);
                                }
                            }
                            
                            if (frame != nullptr)
                            {
                                /**/ if (frame->type == uridAtomDouble)
                                    lastPositionData.frame = ((LV2_Atom_Double*)frame)->body;
                                else if (frame->type == uridAtomFloat)
                                    lastPositionData.frame = ((LV2_Atom_Float*)frame)->body;
                                else if (frame->type == uridAtomInt)
                                    lastPositionData.frame = ((LV2_Atom_Int*)frame)->body;
                                else if (frame->type == uridAtomLong)
                                    lastPositionData.frame = ((LV2_Atom_Long*)frame)->body;
                                
                                if (lastPositionData.frame >= 0)
                                {
                                    curPosInfo.timeInSamples = lastPositionData.frame;
                                    curPosInfo.timeInSeconds = double(curPosInfo.timeInSamples)/sampleRate;
                                }
                            }
                            
                            if (lastPositionData.bar >= 0 && lastPositionData.beatsPerBar > 0.0f)
                            {
                                curPosInfo.ppqPositionOfLastBarStart = lastPositionData.bar * lastPositionData.beatsPerBar;
                                
                                if (lastPositionData.barBeat >= 0.0f)
                                    curPosInfo.ppqPosition = curPosInfo.ppqPositionOfLastBarStart + lastPositionData.barBeat;
                            }
                            
                            lastPositionData.extraValid = (lastPositionData.beatsPerMinute > 0.0 &&
                                                           lastPositionData.beatUnit > 0 &&
                                                           lastPositionData.beatsPerBar > 0.0f);
                        }
#endif
                    }
                }
#endif
                {
                    AudioSampleBuffer chans (channels, jmax (filter->getTotalNumInputChannels(), filter->getTotalNumOutputChannels()), sampleCount);
                    filter->processBlock (chans, midiEvents);
                }
            }
        }
        
#if JucePlugin_WantsLV2TimePos
        // update timePos for next callback
        if (lastPositionData.speed != 0.0)
        {
            if (lastPositionData.speed > 0.0)
            {
                // playing forwards
                lastPositionData.frame += sampleCount;
            }
            else
            {
                // playing backwards
                lastPositionData.frame -= sampleCount;
                
                if (lastPositionData.frame < 0)
                    lastPositionData.frame = 0;
            }
            
            curPosInfo.timeInSamples = lastPositionData.frame;
            curPosInfo.timeInSeconds = double(curPosInfo.timeInSamples)/sampleRate;
            
            if (lastPositionData.extraValid)
            {
                const double beatsPerMinute = lastPositionData.beatsPerMinute * lastPositionData.speed;
                const double framesPerBeat  = 60.0 * sampleRate / beatsPerMinute;
                const double addedBarBeats  = double(sampleCount) / framesPerBeat;
                
                if (lastPositionData.bar >= 0 && lastPositionData.barBeat >= 0.0f)
                {
                    lastPositionData.bar    += std::floor((lastPositionData.barBeat+addedBarBeats)/
                                                          lastPositionData.beatsPerBar);
                    lastPositionData.barBeat = std::fmod(lastPositionData.barBeat+addedBarBeats,
                                                         lastPositionData.beatsPerBar);
                    
                    if (lastPositionData.bar < 0)
                        lastPositionData.bar = 0;
                    
                    curPosInfo.ppqPositionOfLastBarStart = lastPositionData.bar * lastPositionData.beatsPerBar;
                    curPosInfo.ppqPosition = curPosInfo.ppqPositionOfLastBarStart + lastPositionData.barBeat;
                }
                
                curPosInfo.bpm = std::abs(beatsPerMinute);
            }
        }
#endif
        
#if JucePlugin_ProducesMidiOutput
        if (portMidiOut != nullptr)
        {
            const uint32_t capacity = portMidiOut->atom.size;
            
            portMidiOut->atom.size = sizeof(LV2_Atom_Sequence_Body);
            portMidiOut->atom.type = uridAtomSequence;
            portMidiOut->body.unit = 0;
            portMidiOut->body.pad  = 0;
            
            uint32_t offset = 0;
            for(auto it = midiEvents.cbegin(); it != midiEvents.cend(); ++it)
            {
                if (sizeof(LV2_Atom_Event) + (*it).numBytes > capacity - offset)
                    break;
                
                auto* aev = (LV2_Atom_Event*)((char*)LV2_ATOM_CONTENTS(LV2_Atom_Sequence, portMidiOut) + offset);
                aev->time.frames = (*it).samplePosition;
                aev->body.type   = uridMidiEvent;
                aev->body.size   = (*it).numBytes;
                memcpy(LV2_ATOM_BODY(&aev->body), (*it).data, (*it).numBytes);
                
                auto const size = lv2_atom_pad_size(sizeof(LV2_Atom_Event) + (*it).numBytes);
                offset += size;
                portMidiOut->atom.size += size;
            }
            midiEvents.clear();
            
        } else
#endif
            if (! midiEvents.isEmpty())
            {
                midiEvents.clear();
            }
    }
    
    //==============================================================================
    // LV2 extended calls
    
    uint32_t lv2GetOptions (LV2_Options_Option* options)
    {
        // currently unused
        ignoreUnused(options);
        
        return LV2_OPTIONS_SUCCESS;
    }
    
    uint32_t lv2SetOptions (const LV2_Options_Option* options)
    {
        for (int j=0; options[j].key != 0; ++j)
        {
            if (options[j].key == uridMap->map(uridMap->handle, LV2_BUF_SIZE__nominalBlockLength))
            {
                if (options[j].type == uridAtomInt)
                    bufferSize = *(int*)options[j].value;
                else
                    std::cerr << "Host changed nominalBlockLength but with wrong value type" << std::endl;
            }
            else if (options[j].key == uridMap->map(uridMap->handle, LV2_BUF_SIZE__maxBlockLength) && ! usingNominalBlockLength)
            {
                if (options[j].type == uridAtomInt)
                    bufferSize = *(int*)options[j].value;
                else
                    std::cerr << "Host changed maxBlockLength but with wrong value type" << std::endl;
            }
            else if (options[j].key == uridMap->map(uridMap->handle, LV2_CORE__sampleRate))
            {
                if (options[j].type == uridAtomDouble)
                    sampleRate = *(double*)options[j].value;
                else
                    std::cerr << "Host changed sampleRate but with wrong value type" << std::endl;
            }
        }
        
        return LV2_OPTIONS_SUCCESS;
    }
    
    const LV2_Program_Descriptor* lv2GetProgram (uint32_t index)
    {
        jassert (filter != nullptr);
        
        if (progDesc.name != nullptr)
        {
            free((void*)progDesc.name);
            progDesc.name = nullptr;
        }
        
        if ((int)index < filter->getNumPrograms())
        {
            progDesc.bank    = index / 128;
            progDesc.program = index % 128;
            progDesc.name    = strdup(filter->getProgramName(index).toUTF8());
            return &progDesc;
        }
        
        return nullptr;
    }
    
    void lv2SelectProgram (uint32_t bank, uint32_t program)
    {
        jassert (filter != nullptr);
        
        int realProgram = bank * 128 + program;
        
        if (realProgram < filter->getNumPrograms())
        {
            filter->setCurrentProgram(realProgram);
            
            // update input control ports now
            for (int i = 0; i < portControls.size(); ++i)
            {
                float value = getParameter3(i);
                
                if (portControls[i] != nullptr)
                    *portControls[i] = value;
                
                lastControlValues.set(i, value);
            }
        }
    }
    
    LV2_State_Status lv2SaveState (LV2_State_Store_Function store, LV2_State_Handle stateHandle)
    {
        jassert (filter != nullptr);
        
#if JucePlugin_WantsLV2StateString
        String stateData(filter->getStateInformationString().replace("\r\n","\n"));
        CharPointer_UTF8 charData(stateData.toUTF8());
        
        store (stateHandle,
               uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
               charData.getAddress(),
               charData.sizeInBytes(),
               uridMap->map(uridMap->handle, LV2_ATOM__String),
               LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
#else
        MemoryBlock chunkMemory;
        filter->getCurrentProgramStateInformation (chunkMemory);
        
        store (stateHandle,
               uridMap->map(uridMap->handle, JUCE_LV2_STATE_BINARY_URI),
               chunkMemory.getData(),
               chunkMemory.getSize(),
               uridMap->map(uridMap->handle, LV2_ATOM__Chunk),
               LV2_STATE_IS_POD|LV2_STATE_IS_PORTABLE);
#endif
        
        return LV2_STATE_SUCCESS;
    }
    
    LV2_State_Status lv2RestoreState (LV2_State_Retrieve_Function retrieve, LV2_State_Handle stateHandle, uint32_t flags)
    {
        jassert (filter != nullptr);
        
        size_t size = 0;
        uint32 type = 0;
        const void* data = retrieve (stateHandle,
#if JucePlugin_WantsLV2StateString
                                     uridMap->map(uridMap->handle, JUCE_LV2_STATE_STRING_URI),
#else
                                     uridMap->map(uridMap->handle, JUCE_LV2_STATE_BINARY_URI),
#endif
                                     &size, &type, &flags);
        
        if (data == nullptr || size == 0 || type == 0)
            return LV2_STATE_ERR_UNKNOWN;
        
#if JucePlugin_WantsLV2StateString
        if (type == uridMap->map (uridMap->handle, LV2_ATOM__String))
        {
            String stateData (CharPointer_UTF8(static_cast<const char*>(data)));
            filter->setStateInformationString (stateData);
            
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
            if (ui != nullptr)
                ui->repaint();
#endif
            
            return LV2_STATE_SUCCESS;
        }
#else
        if (type == uridMap->map (uridMap->handle, LV2_ATOM__Chunk))
        {
            filter->setCurrentProgramStateInformation (data, static_cast<int>(size));
            
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
            if (ui != nullptr)
                ui->repaint();
#endif
            
            return LV2_STATE_SUCCESS;
        }
#endif
        
        return LV2_STATE_ERR_BAD_TYPE;
    }
    
    //==============================================================================
    // Juce calls
    
    bool getCurrentPosition (AudioPlayHead::CurrentPositionInfo& info)
    {
#if JucePlugin_WantsLV2TimePos
        info = curPosInfo;
        return true;
#else
        ignoreUnused(info);
        return false;
#endif
    }
    
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
    //==============================================================================
    JuceLv2UIWrapper* getUI (LV2UI_Write_Function writeFunction, LV2UI_Controller controller, LV2UI_Widget* widget,
                             const LV2_Feature* const* features, bool isExternal)
    {
        const MessageManagerLock mmLock;
        
        if (ui != nullptr)
            ui->resetIfNeeded (writeFunction, controller, widget, features);
        else
            ui = std::make_unique<JuceLv2UIWrapper>(filter.get(), writeFunction, controller, widget, features, isExternal);
        
        return ui.get();
    }
#endif
    
private:
#if JUCE_LINUX
    SharedResourcePointer<SharedMessageThread> msgThread;
#else
    SharedResourcePointer<ScopedJuceInitialiser_GUI> sharedJuceGUI;
#endif
    
    std::unique_ptr<AudioProcessor> filter;
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
    std::unique_ptr<JuceLv2UIWrapper> ui;
#endif
    HeapBlock<float*> channels;
    MidiBuffer midiEvents;
    
#if (JucePlugin_WantsMidiInput || JucePlugin_WantsLV2TimePos)
    LV2_Atom_Sequence* portEventsIn;
#endif
#if JucePlugin_ProducesMidiOutput
    LV2_Atom_Sequence* portMidiOut;
#endif
    float* portFreewheel;
#if JucePlugin_WantsLV2Latency
    float* portLatency;
#endif
    std::vector<float*> portAudioIns;
    std::vector<float*> portAudioOuts;
    Array<float*> portControls;
    
    uint32 bufferSize;
    double sampleRate;
    Array<float> lastControlValues;
    AudioPlayHead::CurrentPositionInfo curPosInfo;
    
    struct Lv2PositionData {
        int64_t  bar;
        float    barBeat;
        uint32_t beatUnit;
        float    beatsPerBar;
        float    beatsPerMinute;
        int64_t  frame;
        double   speed;
        bool     extraValid;
        
        Lv2PositionData()
        : bar(-1),
        barBeat(-1.0f),
        beatUnit(0),
        beatsPerBar(0.0f),
        beatsPerMinute(0.0f),
        frame(-1),
        speed(0.0),
        extraValid(false) {}
    };
    Lv2PositionData lastPositionData;
    
    const LV2_URID_Map* uridMap;
    LV2_URID uridAtomBlank;
    LV2_URID uridAtomObject;
    LV2_URID uridAtomDouble;
    LV2_URID uridAtomFloat;
    LV2_URID uridAtomInt;
    LV2_URID uridAtomLong;
    LV2_URID uridAtomSequence;
    LV2_URID uridMidiEvent;
    LV2_URID uridTimePos;
    LV2_URID uridTimeBar;
    LV2_URID uridTimeBarBeat;
    LV2_URID uridTimeBeatsPerBar;    // timeSigNumerator
    LV2_URID uridTimeBeatsPerMinute; // bpm
    LV2_URID uridTimeBeatUnit;       // timeSigDenominator
    LV2_URID uridTimeFrame;          // timeInSamples
    LV2_URID uridTimeSpeed;
    
    bool usingNominalBlockLength; // if false use maxBlockLength
    
    LV2_Program_Descriptor progDesc;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceLv2Wrapper)
};

//==============================================================================
// LV2 descriptor functions

static LV2_Handle juceLV2_Instantiate (const LV2_Descriptor*, double sampleRate, const char*, const LV2_Feature* const* features)
{
    return new JuceLv2Wrapper (sampleRate, features);
}

#define handlePtr ((JuceLv2Wrapper*)handle)

static void juceLV2_ConnectPort (LV2_Handle handle, uint32 port, void* dataLocation)
{
    handlePtr->lv2ConnectPort (port, dataLocation);
}

static void juceLV2_Activate (LV2_Handle handle)
{
    handlePtr->lv2Activate();
}

static void juceLV2_Run( LV2_Handle handle, uint32 sampleCount)
{
    handlePtr->lv2Run (sampleCount);
}

static void juceLV2_Deactivate (LV2_Handle handle)
{
    handlePtr->lv2Deactivate();
}

static void juceLV2_Cleanup (LV2_Handle handle)
{
    delete handlePtr;
}

//==============================================================================
// LV2 extended functions

static uint32_t juceLV2_getOptions (LV2_Handle handle, LV2_Options_Option* options)
{
    return handlePtr->lv2GetOptions(options);
}

static uint32_t juceLV2_setOptions (LV2_Handle handle, const LV2_Options_Option* options)
{
    return handlePtr->lv2SetOptions(options);
}

static const LV2_Program_Descriptor* juceLV2_getProgram (LV2_Handle handle, uint32_t index)
{
    return handlePtr->lv2GetProgram(index);
}

static void juceLV2_selectProgram (LV2_Handle handle, uint32_t bank, uint32_t program)
{
    handlePtr->lv2SelectProgram(bank, program);
}

static LV2_State_Status juceLV2_SaveState (LV2_Handle handle, LV2_State_Store_Function store, LV2_State_Handle stateHandle,
                                           uint32_t, const LV2_Feature* const*)
{
    return handlePtr->lv2SaveState(store, stateHandle);
}

static LV2_State_Status juceLV2_RestoreState (LV2_Handle handle, LV2_State_Retrieve_Function retrieve, LV2_State_Handle stateHandle,
                                              uint32_t flags, const LV2_Feature* const*)
{
    return handlePtr->lv2RestoreState(retrieve, stateHandle, flags);
}

#undef handlePtr

static const void* juceLV2_ExtensionData (const char* uri)
{
    static const LV2_Options_Interface options = { juceLV2_getOptions, juceLV2_setOptions };
    static const LV2_Programs_Interface programs = { juceLV2_getProgram, juceLV2_selectProgram };
    static const LV2_State_Interface state = { juceLV2_SaveState, juceLV2_RestoreState };
    
    if (strcmp(uri, LV2_OPTIONS__interface) == 0)
        return &options;
    if (strcmp(uri, LV2_PROGRAMS__Interface) == 0)
        return &programs;
    if (strcmp(uri, LV2_STATE__interface) == 0)
        return &state;
    
    return nullptr;
}

#if ! JUCE_AUDIOPROCESSOR_NO_GUI
//==============================================================================
// LV2 UI descriptor functions

static LV2UI_Handle juceLV2UI_Instantiate (LV2UI_Write_Function writeFunction, LV2UI_Controller controller,
                                           LV2UI_Widget* widget, const LV2_Feature* const* features, bool isExternal)
{
    for (int i = 0; features[i] != nullptr; ++i)
    {
        if (strcmp(features[i]->URI, LV2_INSTANCE_ACCESS_URI) == 0 && features[i]->data != nullptr)
        {
            JuceLv2Wrapper* wrapper = (JuceLv2Wrapper*)features[i]->data;
            return wrapper->getUI(writeFunction, controller, widget, features, isExternal);
        }
    }
    
    std::cerr << "Host does not support instance-access, cannot use UI" << std::endl;
    return nullptr;
}

static LV2UI_Handle juceLV2UI_InstantiateExternal (const LV2UI_Descriptor*, const char*, const char*, LV2UI_Write_Function writeFunction,
                                                   LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, true);
}

static LV2UI_Handle juceLV2UI_InstantiateParent (const LV2UI_Descriptor*, const char*, const char*, LV2UI_Write_Function writeFunction,
                                                 LV2UI_Controller controller, LV2UI_Widget* widget, const LV2_Feature* const* features)
{
    return juceLV2UI_Instantiate(writeFunction, controller, widget, features, false);
}

static void juceLV2UI_Cleanup (LV2UI_Handle handle)
{
    ((JuceLv2UIWrapper*)handle)->lv2Cleanup();
}
#endif

//==============================================================================
// static LV2 Descriptor objects

static const LV2_Descriptor JuceLv2Plugin = {
    strdup(getPluginURI().toRawUTF8()),
    juceLV2_Instantiate,
    juceLV2_ConnectPort,
    juceLV2_Activate,
    juceLV2_Run,
    juceLV2_Deactivate,
    juceLV2_Cleanup,
    juceLV2_ExtensionData
};

#if ! JUCE_AUDIOPROCESSOR_NO_GUI
static const LV2UI_Descriptor JuceLv2UI_External = {
    strdup(String(getPluginURI() + "#ExternalUI").toRawUTF8()),
    juceLV2UI_InstantiateExternal,
    juceLV2UI_Cleanup,
    nullptr,
    nullptr
};

static const LV2UI_Descriptor JuceLv2UI_Parent = {
    strdup(String(getPluginURI() + "#ParentUI").toRawUTF8()),
    juceLV2UI_InstantiateParent,
    juceLV2UI_Cleanup,
    nullptr,
    nullptr
};
#endif

static const struct DescriptorCleanup {
    DescriptorCleanup() {}
    ~DescriptorCleanup()
    {
        free((void*)JuceLv2Plugin.URI);
#if ! JUCE_AUDIOPROCESSOR_NO_GUI
        free((void*)JuceLv2UI_External.URI);
        free((void*)JuceLv2UI_Parent.URI);
#endif
    }
} _descCleanup;

#if JUCE_WINDOWS
#define JUCE_EXPORTED_FUNCTION extern "C" __declspec (dllexport)
#else
#define JUCE_EXPORTED_FUNCTION extern "C" __attribute__ ((visibility("default")))
#endif

//==============================================================================
// startup code..

JUCE_EXPORTED_FUNCTION const LV2_Descriptor* lv2_descriptor (uint32 index);
JUCE_EXPORTED_FUNCTION const LV2_Descriptor* lv2_descriptor (uint32 index)
{
    return (index == 0) ? &JuceLv2Plugin : nullptr;
}

#if ! JUCE_AUDIOPROCESSOR_NO_GUI
JUCE_EXPORTED_FUNCTION const LV2UI_Descriptor* lv2ui_descriptor (uint32 index);
JUCE_EXPORTED_FUNCTION const LV2UI_Descriptor* lv2ui_descriptor (uint32 index)
{
    switch (index)
    {
        case 0:
            return &JuceLv2UI_External;
        case 1:
            return &JuceLv2UI_Parent;
        default:
            return nullptr;
    }
}
#endif

#endif
