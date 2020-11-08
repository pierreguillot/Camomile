cmake_minimum_required(VERSION 3.12)

project(Camomile VERSION 1.0.8 LANGUAGES C CXX)

add_subdirectory(Juce)
add_subdirectory(Dependencies/LibPdBuild)

# juce_set_vst2_sdk_path(...)
# juce_set_aax_sdk_path(...)

set(CAMOMILE_VERSION                    "1.0.8")
set(CAMOMILE_COMPANY_NAME               "Pierre Guillot")
set(CAMOMILE_COMPANY_COPYRIGHT          "Camomile by Pierre Guillot")
set(CAMOMILE_COMPANY_WEBSITE            "github.com/pierreguillot/camomile")
set(CAMOMILE_ICON_BIG                   "${CMAKE_CURRENT_SOURCE_DIR}/Ressources/Images/icon.png")

juce_add_plugin(Camomile
    VERSION                     ${CAMOMILE_VERSION}
    COMPANY_NAME                ${CAMOMILE_COMPANY_NAME}
    COMPANY_COPYRIGHT           ${CAMOMILE_COMPANY_COPYRIGHT}
    COMPANY_WEBSITE             ${CAMOMILE_COMPANY_WEBSITE}
    ICON_BIG                    ${CAMOMILE_ICON_BIG}
    IS_SYNTH                    TRUE
    NEEDS_MIDI_INPUT            TRUE
    NEEDS_MIDI_OUTPUT           TRUE
    IS_MIDI_EFFECT              FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
    COPY_PLUGIN_AFTER_BUILD     FALSE
    PLUGIN_MANUFACTURER_CODE    PIGU
    PLUGIN_CODE                 Kpq8
    FORMATS                     AU VST3 # AAX Unity VST AU AUv3
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
    FORMATS                     AU VST3 # AAX Unity VST AU AUv3
    PRODUCT_NAME                "CamomileFx"
    AU_MAIN_TYPE                kAudioUnitType_MusicEffect
    VST3_CATEGORIES             Fx)
    # VST2_CATEGORY kPlugCategEffect

juce_generate_juce_header(Camomile)
set_target_properties(Camomile PROPERTIES CXX_STANDARD 20)

juce_generate_juce_header(CamomileFx)
set_target_properties(CamomileFx PROPERTIES CXX_STANDARD 20)

set(SOURCES_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Source)

#file(GLOB_RECURSE GlobalSources
#    ${SOURCES_DIRECTORY}/main.cpp
#    ${CMAKE_CACHEFILE_DIR}/Camomile_artefacts/JuceLibraryCode/JuceHeader.h)

file(GLOB_RECURSE CamomileSources
    ${SOURCES_DIRECTORY}/*.c
    ${SOURCES_DIRECTORY}/*.h
    ${SOURCES_DIRECTORY}/*.cpp
    ${SOURCES_DIRECTORY}/*.hpp)

function(create_module_group TARGET GROUP_PATH MODULE_PATH)
if(APPLE)
    file(GLOB MAIN_CPP_SOURCES ${MODULE_PATH}/*.cpp)
    set_source_files_properties(${MAIN_CPP_SOURCES} PROPERTIES HEADER_FILE_ONLY TRUE)
    source_group(${GROUP_PATH} FILES ${MAIN_CPP_SOURCES})
    target_sources(${TARGET} PRIVATE ${MAIN_CPP_SOURCES})

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

create_module_group(CamomileFx "Modules\\juce_core" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_core")
create_module_group(CamomileFx "Modules\\juce_graphics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_graphics")
create_module_group(CamomileFx "Modules\\juce_events" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_events")
create_module_group(CamomileFx "Modules\\juce_gui_basics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_gui_basics")
create_module_group(CamomileFx "Modules\\juce_gui_extra" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_gui_extra")
create_module_group(CamomileFx "Modules\\juce_data_structures" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_data_structures")
create_module_group(CamomileFx "Modules\\juce_audio_basics" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_basics")
create_module_group(CamomileFx "Modules\\juce_audio_devices" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_devices")
create_module_group(CamomileFx "Modules\\juce_audio_processors" "${CMAKE_CURRENT_SOURCE_DIR}/Juce/modules/juce_audio_processors")

target_sources(Camomile PRIVATE ${CamomileSources} )
target_sources(CamomileFx PRIVATE ${CamomileSources} )

set(CAMOMILE_COMPILE_DEFINITIONS
    JUCE_ALLOW_STATIC_NULL_VARIABLES=0
    JUCE_DISPLAY_SPLASH_SCREEN=0
    JUCE_VST3_CAN_REPLACE_VST2=0
    JUCE_REPORT_APP_USAGE=0
    JUCE_LOG_ASSERTIONS=1
    JUCE_STRICT_REFCOUNTEDPOINTER=1
    PD_INTERNAL=1)

target_compile_definitions(Camomile INTERFACE ${CAMOMILE_COMPILE_DEFINITIONS})
target_compile_definitions(CamomileFx INTERFACE ${CAMOMILE_COMPILE_DEFINITIONS})

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
    juce::juce_audio_utils)

target_link_libraries(CamomileFx PRIVATE
    libpdstatic
    CamomileBinaryData
    juce::juce_audio_utils)
