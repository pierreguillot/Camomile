cmake_minimum_required(VERSION 3.12)

set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum OS X deployment version")
project(Camomile VERSION 1.0.8 LANGUAGES C CXX)

if("${CMAKE_SYSTEM}" MATCHES "Linux")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-Bsymbolic")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} -Wl,-Bsymbolic")
endif()

add_subdirectory(libpd)
add_subdirectory(Juce)

set(CAMOMILE_VERSION                    "1.0.8")
set(CAMOMILE_COMPANY_NAME               "Camomile")
set(CAMOMILE_COMPANY_COPYRIGHT          "Camomile by Pierre Guillot")
set(CAMOMILE_COMPANY_WEBSITE            "github.com/pierreguillot/camomile")
set(CAMOMILE_ICON_BIG                   "${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/icon.png")
set(CAMOMILE_PLUGINS_LOCATION           "${CMAKE_CURRENT_SOURCE_DIR}/Plugins")

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

file(GLOB_RECURSE CamomileLV2Sources
    ${CMAKE_CURRENT_SOURCE_DIR}/LV2/juce_LV2_Wrapper.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/LV2/juce_LV2_FileCreator.cpp)

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
    COPY_PLUGIN_AFTER_BUILD     TRUE
    PLUGIN_MANUFACTURER_CODE    PIGU
    PLUGIN_CODE                 Kpq8
    FORMATS                     AU VST3 # AAX Unity AUv3
    PRODUCT_NAME                "Camomile"
    AU_MAIN_TYPE                kAudioUnitType_MusicDevice
    VST3_CATEGORIES             Instrument
    VST2_CATEGORY               kPlugCategSynth
    VST_COPY_DIR                ${CAMOMILE_PLUGINS_LOCATION}
    VST3_COPY_DIR               ${CAMOMILE_PLUGINS_LOCATION}
    AU_COPY_DIR                 ${CAMOMILE_PLUGINS_LOCATION})

juce_add_plugin(CamomileFx
    VERSION                     ${CAMOMILE_VERSION}
    COMPANY_NAME                ${CAMOMILE_COMPANY_NAME}
    COMPANY_COPYRIGHT           ${CAMOMILE_COMPANY_COPYRIGHT}
    COMPANY_WEBSITE             ${CAMOMILE_COMPANY_WEBSITE}
    ICON_BIG                    ${CAMOMILE_ICON_BIG}
    PLUGIN_DESCRIPTION          "A plugin that loads Pure Data patches"
    IS_SYNTH                    FALSE
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           TRUE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD     TRUE
    PLUGIN_MANUFACTURER_CODE    PIGU
    PLUGIN_CODE                 Kpq9
    FORMATS                     AU VST3 # AAX Unity AUv3
    PRODUCT_NAME                "CamomileFx"
    AU_MAIN_TYPE                kAudioUnitType_MusicEffect
    VST3_CATEGORIES             Fx
    VST2_CATEGORY               kPlugCategEffect
    VST_COPY_DIR                ${CAMOMILE_PLUGINS_LOCATION}
    VST3_COPY_DIR               ${CAMOMILE_PLUGINS_LOCATION}
    AU_COPY_DIR                 ${CAMOMILE_PLUGINS_LOCATION})

juce_generate_juce_header(Camomile)
set_target_properties(Camomile PROPERTIES CXX_STANDARD 20)
target_sources(Camomile PRIVATE ${CamomileSources} ${CamomilePdSources})

juce_generate_juce_header(CamomileFx)
set_target_properties(CamomileFx PROPERTIES CXX_STANDARD 20)
target_sources(CamomileFx PRIVATE ${CamomileSources} ${CamomilePdSources})

add_library(Camomile_LV2 SHARED ${CamomileLV2Sources})
target_link_libraries(Camomile_LV2 PRIVATE CamomileFx)
set_target_properties(Camomile_LV2 PROPERTIES PREFIX "")

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
create_module_group(CamomileFx "Modules\\juce_audio_utils" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_utils")

set(CAMOMILE_COMPILE_DEFINITIONS
    JUCE_APP_CONFIG_HEADER="${SOURCES_DIRECTORY}/PluginConfig.h"
    JUCE_DONT_DECLARE_PROJECTINFO=1
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_LOG_ASSERTIONS=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    JUCE_WEB_BROWSER=0
    JUCE_USE_CURL=0)

target_compile_definitions(Camomile PUBLIC ${CAMOMILE_COMPILE_DEFINITIONS})
target_compile_definitions(CamomileFx PUBLIC ${CAMOMILE_COMPILE_DEFINITIONS})
target_compile_definitions(Camomile_LV2 PRIVATE "JucePlugin_Build_LV2=1")

list(APPEND LIBPD_INCLUDE_DIRECTORY
    "${CMAKE_CURRENT_SOURCE_DIR}/libpd/libpd/pure-data/src"
    "${CMAKE_CURRENT_SOURCE_DIR}/libpd/libpd/libpd_wrapper"
    "${CMAKE_CURRENT_SOURCE_DIR}/libpd/libpd/libpd_wrapper/util"
    "${CMAKE_CURRENT_SOURCE_DIR}/libpd/libpd/cpp")

target_include_directories(Camomile PUBLIC "$<BUILD_INTERFACE:${LIBPD_INCLUDE_DIRECTORY}>")
target_include_directories(CamomileFx PUBLIC "$<BUILD_INTERFACE:${LIBPD_INCLUDE_DIRECTORY}>")

file(GLOB CamomileBinaryDataSources
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Credits/CreditsAU
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Credits/CreditsLV2
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Credits/CreditsVST
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Credits/CreditsAU
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Fonts/DejaVuSansMono.ttf
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/settings.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/garbage.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/copy.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/reload.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/flower_petals.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/icon.png
    ${CMAKE_CURRENT_SOURCE_DIR}/Resources/Images/flower_center.png)

juce_add_binary_data(CamomileBinaryData SOURCES ${CamomileBinaryDataSources})
set_target_properties(CamomileBinaryData PROPERTIES POSITION_INDEPENDENT_CODE ON)

target_link_libraries(Camomile PRIVATE libpdstatic CamomileBinaryData juce::juce_audio_utils juce::juce_audio_plugin_client)
target_link_libraries(CamomileFx PRIVATE libpdstatic CamomileBinaryData juce::juce_audio_utils juce::juce_audio_plugin_client)
target_link_libraries(Camomile_LV2 PRIVATE libpdstatic CamomileBinaryData juce::juce_audio_utils juce::juce_audio_plugin_client)

add_executable(lv2_file_generator ${CMAKE_CURRENT_SOURCE_DIR}/LV2/main.c)
target_link_libraries(lv2_file_generator ${CMAKE_DL_LIBS})

set_target_properties(lv2_file_generator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CAMOMILE_PLUGINS_LOCATION})
set_target_properties(Camomile_LV2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CAMOMILE_PLUGINS_LOCATION})
set_target_properties(Camomile_LV2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CAMOMILE_PLUGINS_LOCATION})
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
		  string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
			set_target_properties(lv2_file_generator PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CAMOMILE_PLUGINS_LOCATION})
      set_target_properties(Camomile_LV2 PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CAMOMILE_PLUGINS_LOCATION})
      set_target_properties(Camomile_LV2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CAMOMILE_PLUGINS_LOCATION})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
