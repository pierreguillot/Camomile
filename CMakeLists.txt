cmake_minimum_required(VERSION 3.12)

project(Camomile VERSION 1.0.8 LANGUAGES C CXX)

add_subdirectory(Juce)
add_subdirectory(Dependencies/LibPdBuild)

juce_set_vst2_sdk_path(/Users/guillot/Downloads/vstsdk2.4)

set(CAMOMILE_VERSION                    "1.0.8")
set(CAMOMILE_COMPANY_NAME               "Camomile")
set(CAMOMILE_COMPANY_COPYRIGHT          "Camomile by Pierre Guillot")
set(CAMOMILE_COMPANY_WEBSITE            "github.com/pierreguillot/camomile")
set(CAMOMILE_ICON_BIG                   "${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/icon.png")

juce_add_plugin(Camomile
    VERSION                     ${CAMOMILE_VERSION}
    COMPANY_NAME                ${CAMOMILE_COMPANY_NAME}
    COMPANY_COPYRIGHT           ${CAMOMILE_COMPANY_COPYRIGHT}
    COMPANY_WEBSITE             ${CAMOMILE_COMPANY_WEBSITE}
    PLUGIN_DESCRIPTION          "A plugin that loads Pure Data patches"
    ICON_BIG                    ${CAMOMILE_ICON_BIG}
    IS_SYNTH                    TRUE
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           TRUE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD     FALSE
    PLUGIN_MANUFACTURER_CODE    PIGU
    PLUGIN_CODE                 Kpq8
    FORMATS                     AU VST VST3 # AAX Unity VST AU AUv3
    PRODUCT_NAME                "Camomile"
    AU_MAIN_TYPE                kAudioUnitType_MusicDevice
    VST3_CATEGORIES             Instrument)
    # VST2_CATEGORY kPlugCategSynth

juce_add_plugin(CamomileFx
    VERSION                     ${CAMOMILE_VERSION}
    COMPANY_NAME                ${CAMOMILE_COMPANY_NAME}
    COMPANY_COPYRIGHT           ${CAMOMILE_COMPANY_COPYRIGHT}
    COMPANY_WEBSITE             ${CAMOMILE_COMPANY_WEBSITE}
    ICON_BIG                    ${CAMOMILE_ICON_BIG}
    IS_SYNTH                    FALSE
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           TRUE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD     FALSE
    PLUGIN_MANUFACTURER_CODE    PIGU
    PLUGIN_CODE                 Kpq9
    FORMATS                     AU VST VST3 # AAX Unity VST AU AUv3
    PRODUCT_NAME                "CamomileFx"
    AU_MAIN_TYPE                kAudioUnitType_MusicEffect
    VST3_CATEGORIES             Fx)
    # VST2_CATEGORY kPlugCategEffect

juce_generate_juce_header(Camomile)
set_target_properties(Camomile PROPERTIES CXX_STANDARD 20)

juce_generate_juce_header(CamomileFx)
set_target_properties(CamomileFx PROPERTIES CXX_STANDARD 20)

set(SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Source)

file(GLOB CamomileGlobalSources
    ${CMAKE_CACHEFILE_DIR}/Camomile_artefacts/JuceLibraryCode/JuceHeader.h)
source_group("Source" FILES ${CamomileGlobalSources})

file(GLOB CamomileFxGlobalSources
    ${CMAKE_CACHEFILE_DIR}/CamomileFx_artefacts/JuceLibraryCode/JuceHeader.h)
source_group("Source" FILES ${CamomileFxGlobalSources})

file(GLOB CamomileSources
    ${SOURCES_DIRECTORY}/PluginConsole.h
    ${SOURCES_DIRECTORY}/PluginConfig.h
    ${SOURCES_DIRECTORY}/PluginEditor.cpp
    ${SOURCES_DIRECTORY}/PluginEditor.h
    ${SOURCES_DIRECTORY}/PluginEditorComponents.cpp
    ${SOURCES_DIRECTORY}/PluginEditorComponents.h
    ${SOURCES_DIRECTORY}/PluginEditorConsole.cpp
    ${SOURCES_DIRECTORY}/PluginEditorConsole.hpp
    ${SOURCES_DIRECTORY}/PluginEditorInteraction.cpp
    ${SOURCES_DIRECTORY}/PluginEditorInteraction.h
    ${SOURCES_DIRECTORY}/PluginEditorObject.cpp
    ${SOURCES_DIRECTORY}/PluginEditorObject.hpp
    ${SOURCES_DIRECTORY}/PluginEnvironment.cpp
    ${SOURCES_DIRECTORY}/PluginEnvironment.h
    ${SOURCES_DIRECTORY}/PluginFileWatcher.cpp
    ${SOURCES_DIRECTORY}/PluginFileWatcher.h
    ${SOURCES_DIRECTORY}/PluginLookAndFeel.cpp
    ${SOURCES_DIRECTORY}/PluginLookAndFeel.hpp
    ${SOURCES_DIRECTORY}/PluginParameter.cpp
    ${SOURCES_DIRECTORY}/PluginParameter.h
    ${SOURCES_DIRECTORY}/PluginParser.cpp
    ${SOURCES_DIRECTORY}/PluginParser.h
    ${SOURCES_DIRECTORY}/PluginProcessor.cpp
    ${SOURCES_DIRECTORY}/PluginProcessor.h
    ${SOURCES_DIRECTORY}/PluginProcessorBuses.cpp
    ${SOURCES_DIRECTORY}/PluginProcessorReceive.cpp)
source_group("Source" FILES ${CamomileSources})

file(GLOB_RECURSE CamomilePdSources
    ${SOURCES_DIRECTORY}/Pd/*.c
    ${SOURCES_DIRECTORY}/Pd/*.h
    ${SOURCES_DIRECTORY}/Pd/*.cpp
    ${SOURCES_DIRECTORY}/Pd/*.hpp)
source_group("Source\\Pd" FILES ${CamomilePdSources})

function(create_module_group TARGET GROUP_PATH MODULE_PATH)
if(APPLE)
    file(GLOB MAIN_CPP_SOURCES ${MODULE_PATH}/*.cpp)
    source_group(${GROUP_PATH} FILES ${MAIN_CPP_SOURCES})

    file(GLOB MAIN_OTHER_SOURCES ${MODULE_PATH}/*.h ${MODULE_PATH}/*.mm)
    source_group(${GROUP_PATH} FILES ${MAIN_OTHER_SOURCES})
else()
    file(GLOB MAIN_OTHER_SOURCES ${MODULE_PATH}/*.h ${MODULE_PATH}/*.cpp)
    source_group(${GROUP_PATH} FILES ${MAIN_OTHER_SOURCES})
endif()

    file(GLOB_RECURSE SUB_SOURCES ${MODULE_PATH}/**/*.cpp ${MODULE_PATH}/**/*.h)
    set_source_files_properties(${SUB_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)

    foreach(SOURCE ${SUB_SOURCES})
        file(RELATIVE_PATH FILE_PATH_REL "${MODULE_PATH}" "${SOURCE}")
        get_filename_component(DIR_PATH_REL ${FILE_PATH_REL} DIRECTORY)

        string(REPLACE "/" "\\\\" SUBGROUP ${DIR_PATH_REL})
        source_group(${GROUP_PATH}\\${SUBGROUP} FILES ${SOURCE})
    endforeach()

    target_sources(${TARGET} PRIVATE ${SUB_SOURCES})
endfunction()

create_module_group(Camomile "Modules\\juce_core" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_core")
create_module_group(Camomile "Modules\\juce_graphics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_graphics")
create_module_group(Camomile "Modules\\juce_events" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_events")
create_module_group(Camomile "Modules\\juce_gui_basics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_gui_basics")
create_module_group(Camomile "Modules\\juce_gui_extra" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_gui_extra")
create_module_group(Camomile "Modules\\juce_data_structures" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_data_structures")
create_module_group(Camomile "Modules\\juce_audio_basics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_basics")
create_module_group(Camomile "Modules\\juce_audio_devices" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_devices")
create_module_group(Camomile "Modules\\juce_audio_processors" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_processors")
create_module_group(Camomile "Modules\\juce_audio_plugin_client" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_plugin_client")
create_module_group(Camomile "Modules\\juce_audio_formats" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_formats")
create_module_group(Camomile "Modules\\juce_audio_utils" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_utils")

create_module_group(CamomileFx "Modules\\juce_core" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_core")
create_module_group(CamomileFx "Modules\\juce_graphics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_graphics")
create_module_group(CamomileFx "Modules\\juce_events" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_events")
create_module_group(CamomileFx "Modules\\juce_gui_basics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_gui_basics")
create_module_group(CamomileFx "Modules\\juce_gui_extra" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_gui_extra")
create_module_group(CamomileFx "Modules\\juce_data_structures" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_data_structures")
create_module_group(CamomileFx "Modules\\juce_audio_basics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_basics")
create_module_group(CamomileFx "Modules\\juce_audio_devices" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_devices")
create_module_group(CamomileFx "Modules\\juce_audio_processors" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_processors")
create_module_group(CamomileFx "Modules\\juce_audio_plugin_client" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_plugin_client")
create_module_group(CamomileFx "Modules\\juce_audio_formats" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_formats")
create_module_group(Camomile "Modules\\juce_audio_utils" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_utils")

target_sources(Camomile PRIVATE ${CamomileSources} ${CamomilePdSources})
target_sources(CamomileFx PRIVATE ${CamomileSources} ${CamomilePdSources})

set(CAMOMILE_COMPILE_DEFINITIONS
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_LOG_ASSERTIONS=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    PD_INTERNAL=1
    JucePlugin_Build_LV2=0)

target_compile_definitions(Camomile PUBLIC ${CAMOMILE_COMPILE_DEFINITIONS})
target_compile_definitions(CamomileFx PUBLIC ${CAMOMILE_COMPILE_DEFINITIONS})

list(APPEND LIBPD_INCLUDE_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/LibPd/pure-data/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/LibPd/libpd_wrapper"
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/LibPd/libpd_wrapper/util"
    "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/LibPd/cpp")

target_include_directories(Camomile PRIVATE "$<BUILD_INTERFACE:${LIBPD_INCLUDE_DIRECTORY}>")
target_include_directories(CamomileFx PRIVATE "$<BUILD_INTERFACE:${LIBPD_INCLUDE_DIRECTORY}>")

file(GLOB CamomileBinaryDataSources
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Credits/CreditsAU
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Credits/CreditsLV2
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Credits/CreditsVST
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Credits/CreditsAU
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Fonts/DejaVuSansMono.ttf
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/settings.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/garbage.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/copy.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/reload.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/flower_petals.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/icon.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/flower_center.png)

juce_add_binary_data(CamomileBinaryData SOURCES ${CamomileBinaryDataSources})

target_link_libraries(Camomile PRIVATE
    libpdstatic
    CamomileBinaryData
    juce::juce_audio_utils
    juce::juce_audio_plugin_client)

target_link_libraries(CamomileFx PRIVATE
    libpdstatic
    CamomileBinaryData
    juce::juce_audio_utils
    juce::juce_audio_plugin_client)

function(clean_compile_definition TARGET PLUGIN_CODE)
    get_target_property(CompileDefinitions ${TARGET} COMPILE_DEFINITIONS)
    list(REMOVE_ITEM CompileDefinitions "JucePlugin_Name=\"$<TARGET_PROPERTY:${TARGET},JUCE_PLUGIN_NAME>\"")
    list(REMOVE_ITEM CompileDefinitions "JucePlugin_Desc=\"$<TARGET_PROPERTY:${TARGET},JUCE_DESCRIPTION>\"")
    list(REMOVE_ITEM CompileDefinitions "JucePlugin_Manufacturer=\"$<TARGET_PROPERTY:${TARGET},JUCE_COMPANY_NAME>\"")
    list(REMOVE_ITEM CompileDefinitions "JucePlugin_AUManufacturerCode=JucePlugin_ManufacturerCode")
    list(APPEND CompileDefinitions "JucePlugin_AUManufacturerCode=\"${PLUGIN_CODE}\"")
    #list(FILTER CompileDefinitions EXCLUDE REGEX [[^JucePlugin_PluginCode$]])
    set_property(TARGET ${TARGET} PROPERTY COMPILE_DEFINITIONS ${CompileDefinitions})

    target_compile_definitions("${TARGET}_AU" PUBLIC "JucePlugin_Name=\"${TARGET}\"")
    target_compile_definitions("${TARGET}_AU" PUBLIC "JucePlugin_Desc=\"${TARGET}\"")
endfunction()

clean_compile_definition(Camomile Kpq8)
clean_compile_definition(CamomileFx Kpq9)

function(clean_au_file TARGET AUMainType)
    set(SecretDirecory ${CMAKE_CACHEFILE_DIR}/${TARGET}_artefacts/JuceLibraryCode/${TARGET}_AU/secret)
    file(MAKE_DIRECTORY ${SecretDirecory})
    set(DEFINE_FILE_SRC ${CMAKE_CURRENT_SOURCE_DIR}/JucePluginDefines.h.in)
    set(DEFINE_FILE_DES ${SecretDirecory}/JucePluginDefines.h)
    file(TOUCH ${SecretDirecory}/JucePluginDefines.h)
    configure_file(${DEFINE_FILE_SRC} ${DEFINE_FILE_DES})
endfunction()

clean_au_file(Camomile aumu)
clean_au_file(CamomileFx aumf)
