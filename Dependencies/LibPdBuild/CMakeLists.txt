cmake_minimum_required(VERSION 3.1)

#------------------------------------------------------------------------------#
# LIBPD PROJECT IN C
#------------------------------------------------------------------------------#
project(libpd C)

#------------------------------------------------------------------------------#
# CMAKE MAC OS SPECIFIC
#------------------------------------------------------------------------------#

set(CMAKE_OSX_DEPLOYMENT_TARGET 10.7)
set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

set(LIBPD_PATH "${PROJECT_SOURCE_DIR}/../LibPd")
set(LIBPD_OUTPUT_DIRECTORY "./..")
#------------------------------------------------------------------------------#
# OPTIONS
#------------------------------------------------------------------------------#
option(PD_UTILS "Compile libpd utilities" OFF)
option(PD_EXTRA "Compile extras" ON)
option(PD_MULTI "Compile with multiple instance support" ON)
option(PD_LOCALE "Set the LC_NUMERIC number format to the default C locale" ON)
option(LIBPD_INCLUDE_STATIC_LIBRARY  "Compile the libpd static library" ON)
option(LIBPD_INCLUDE_DYNAMIC_LIBRARY  "Compile the libpd dynamic library" OFF)

if(NOT DEFINED LIBPD_PATH)
	set(LIBPD_PATH "${PROJECT_SOURCE_DIR}/../libpd")
endif()

if(MSVC)
    option(MSVC_STATIC_RUNTIME "Set the runtime library of MSVC" ON)
    option(MSVC_PTHREAD_LIB "Set the Pthread library to link" "pthread.lib")
endif()

#------------------------------------------------------------------------------#
# OUTPUT DIRECTORY
#------------------------------------------------------------------------------#
if(DEFINED LIBPD_OUTPUT_DIRECTORY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${LIBPD_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBPD_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIBPD_OUTPUT_DIRECTORY})
foreach(OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBPD_OUTPUT_DIRECTORY})
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBPD_OUTPUT_DIRECTORY})
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${LIBPD_OUTPUT_DIRECTORY})
endforeach(OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES)
endif()

#------------------------------------------------------------------------------#
# SOURCES
#------------------------------------------------------------------------------#
set(SOURCE_FILES)

# PURE DATA SOURCES
#------------------------------------------------------------------------------#
file(GLOB PD_SOURCES
    ${LIBPD_PATH}/pure-data/src/d_arithmetic.c
    ${LIBPD_PATH}/pure-data/src/d_array.c
    ${LIBPD_PATH}/pure-data/src/d_ctl.c
    ${LIBPD_PATH}/pure-data/src/d_dac.c
    ${LIBPD_PATH}/pure-data/src/d_delay.c
    ${LIBPD_PATH}/pure-data/src/d_fft.c
    ${LIBPD_PATH}/pure-data/src/d_fft_fftsg.c
    ${LIBPD_PATH}/pure-data/src/d_filter.c
    ${LIBPD_PATH}/pure-data/src/d_global.c
    ${LIBPD_PATH}/pure-data/src/d_math.c
    ${LIBPD_PATH}/pure-data/src/d_misc.c
    ${LIBPD_PATH}/pure-data/src/d_osc.c
    ${LIBPD_PATH}/pure-data/src/d_resample.c
    ${LIBPD_PATH}/pure-data/src/d_soundfile.c
    ${LIBPD_PATH}/pure-data/src/d_ugen.c
    ${LIBPD_PATH}/pure-data/src/g_all_guis.c
    ${LIBPD_PATH}/pure-data/src/g_all_guis.h
    ${LIBPD_PATH}/pure-data/src/g_array.c
    ${LIBPD_PATH}/pure-data/src/g_bang.c
    ${LIBPD_PATH}/pure-data/src/g_canvas.c
    ${LIBPD_PATH}/pure-data/src/g_canvas.h
    ${LIBPD_PATH}/pure-data/src/g_clone.c
		${LIBPD_PATH}/pure-data/src/g_editor_extras.c
    ${LIBPD_PATH}/pure-data/src/g_editor.c
    ${LIBPD_PATH}/pure-data/src/g_graph.c
    ${LIBPD_PATH}/pure-data/src/g_guiconnect.c
    ${LIBPD_PATH}/pure-data/src/g_hdial.c
    ${LIBPD_PATH}/pure-data/src/g_hslider.c
    ${LIBPD_PATH}/pure-data/src/g_io.c
    ${LIBPD_PATH}/pure-data/src/g_mycanvas.c
    ${LIBPD_PATH}/pure-data/src/g_numbox.c
    ${LIBPD_PATH}/pure-data/src/g_readwrite.c
    ${LIBPD_PATH}/pure-data/src/g_rtext.c
    ${LIBPD_PATH}/pure-data/src/g_scalar.c
    ${LIBPD_PATH}/pure-data/src/g_template.c
    ${LIBPD_PATH}/pure-data/src/g_text.c
    ${LIBPD_PATH}/pure-data/src/g_toggle.c
    ${LIBPD_PATH}/pure-data/src/g_traversal.c
		${LIBPD_PATH}/pure-data/src/g_undo.c
		${LIBPD_PATH}/pure-data/src/g_undo.h
    ${LIBPD_PATH}/pure-data/src/g_vdial.c
    ${LIBPD_PATH}/pure-data/src/g_vslider.c
    ${LIBPD_PATH}/pure-data/src/g_vumeter.c
    ${LIBPD_PATH}/pure-data/src/m_atom.c
    ${LIBPD_PATH}/pure-data/src/m_binbuf.c
    ${LIBPD_PATH}/pure-data/src/m_class.c
    ${LIBPD_PATH}/pure-data/src/m_conf.c
    ${LIBPD_PATH}/pure-data/src/m_glob.c
    ${LIBPD_PATH}/pure-data/src/m_imp.h
    ${LIBPD_PATH}/pure-data/src/m_memory.c
    ${LIBPD_PATH}/pure-data/src/m_obj.c
    ${LIBPD_PATH}/pure-data/src/m_pd.c
    ${LIBPD_PATH}/pure-data/src/m_pd.h
    ${LIBPD_PATH}/pure-data/src/m_sched.c
    ${LIBPD_PATH}/pure-data/src/s_audio.c
    ${LIBPD_PATH}/pure-data/src/s_audio_dummy.c
    ${LIBPD_PATH}/pure-data/src/s_inter.c
    ${LIBPD_PATH}/pure-data/src/s_loader.c
    ${LIBPD_PATH}/pure-data/src/s_main.c
		${LIBPD_PATH}/pure-data/src/s_net.c
		${LIBPD_PATH}/pure-data/src/s_net.h
    ${LIBPD_PATH}/pure-data/src/s_path.c
    ${LIBPD_PATH}/pure-data/src/s_print.c
    ${LIBPD_PATH}/pure-data/src/s_stuff.h
    ${LIBPD_PATH}/pure-data/src/s_utf8.c
    ${LIBPD_PATH}/pure-data/src/s_utf8.h
    ${LIBPD_PATH}/pure-data/src/x_acoustics.c
    ${LIBPD_PATH}/pure-data/src/x_arithmetic.c
    ${LIBPD_PATH}/pure-data/src/x_array.c
    ${LIBPD_PATH}/pure-data/src/x_connective.c
    ${LIBPD_PATH}/pure-data/src/x_gui.c
    ${LIBPD_PATH}/pure-data/src/x_interface.c
    ${LIBPD_PATH}/pure-data/src/x_list.c
    ${LIBPD_PATH}/pure-data/src/x_midi.c
    ${LIBPD_PATH}/pure-data/src/x_misc.c
    ${LIBPD_PATH}/pure-data/src/x_net.c
    ${LIBPD_PATH}/pure-data/src/x_scalar.c
    ${LIBPD_PATH}/pure-data/src/x_text.c
    ${LIBPD_PATH}/pure-data/src/x_time.c
    ${LIBPD_PATH}/pure-data/src/x_vexp.c
    ${LIBPD_PATH}/pure-data/src/x_vexp_fun.c
    ${LIBPD_PATH}/pure-data/src/x_vexp_if.c
)
include_directories(${LIBPD_PATH}/pure-data/src)
source_group(pd FILES ${PD_SOURCES})
list(APPEND SOURCE_FILES ${PD_SOURCES})

# PURE DATA EXTRA SOURCES
#------------------------------------------------------------------------------#
if(PD_EXTRA)
    file(GLOB PD_EXTRA_SOURCES
    ${LIBPD_PATH}/pure-data/extra/bob~/bob~.c
    ${LIBPD_PATH}/pure-data/extra/bonk~/bonk~.c
    ${LIBPD_PATH}/pure-data/extra/choice/choice.c
    ${LIBPD_PATH}/pure-data/extra/fiddle~/fiddle~.c
    ${LIBPD_PATH}/pure-data/extra/loop~/loop~.c
    ${LIBPD_PATH}/pure-data/extra/lrshift~/lrshift~.c
    ${LIBPD_PATH}/pure-data/extra/pd~/pd~.c
    ${LIBPD_PATH}/pure-data/extra/pd~/pdsched.c
    ${LIBPD_PATH}/pure-data/extra/pique/pique.c
    ${LIBPD_PATH}/pure-data/extra/sigmund~/sigmund~.c
    ${LIBPD_PATH}/pure-data/extra/stdout/stdout.c
    )
    include_directories(${LIBPD_PATH}/pure-data/extra)
    source_group(pd\\extra FILES ${PD_EXTRA_SOURCES})
    list(APPEND SOURCE_FILES ${PD_EXTRA_SOURCES})
endif()

# LIBPD SOURCES
#------------------------------------------------------------------------------#
file(GLOB LIBPD_SOURCES
    ${LIBPD_PATH}/libpd_wrapper/s_libpdmidi.c
    ${LIBPD_PATH}/libpd_wrapper/x_libpdreceive.c
    ${LIBPD_PATH}/libpd_wrapper/x_libpdreceive.h
    ${LIBPD_PATH}/libpd_wrapper/z_hooks.c
    ${LIBPD_PATH}/libpd_wrapper/z_hooks.h
    ${LIBPD_PATH}/libpd_wrapper/z_libpd.c
)
include_directories(libpd_wrapper)
source_group(libpd FILES ${LIBPD_SOURCES})
list(APPEND SOURCE_FILES ${LIBPD_SOURCES})

# LIBPD UTIL SOURCES
#------------------------------------------------------------------------------#
if(PD_UTILS)
    file(GLOB LIBPD_UTIL_SOURCES
        ${LIBPD_PATH}/libpd_wrapper/util/ringbuffer.c
        ${LIBPD_PATH}/libpd_wrapper/util/ringbuffer.h
        ${LIBPD_PATH}/libpd_wrapper/util/z_print_util.c
        ${LIBPD_PATH}/libpd_wrapper/util/z_print_util.h
        ${LIBPD_PATH}/libpd_wrapper/util/z_queued.c
        ${LIBPD_PATH}/libpd_wrapper/util/z_queued.h
    )
    include_directories(${LIBPD_PATH}/libpd_wrapper/util)
    source_group(libpd\\util FILES ${LIBPD_UTIL_SOURCES})
    list(APPEND SOURCE_FILES ${LIBPD_UTIL_SOURCES})
endif()

#------------------------------------------------------------------------------#
# COMPILE DEFINITIONS
#------------------------------------------------------------------------------#
set(LIBPD_COMPILE_DEFINITIONS PD=1 USEAPI_DUMMY=1 PD_INTERNAL=1)

# COMPILE DEFINITIONS OPTIONS
#------------------------------------------------------------------------------#
if(PD_EXTRA)
    list(APPEND LIBPD_COMPILE_DEFINITIONS LIBPD_EXTRA=1)
endif()
if(PD_MULTI)
    list(APPEND LIBPD_COMPILE_DEFINITIONS PDINSTANCE=1 PDTHREADS=1)
endif()
if(NOT PD_LOCALE)
    list(APPEND LIBPD_COMPILE_DEFINITIONS LIBPD_NO_NUMERIC=1)
endif()

# COMPILE DEFINITIONS OS
#------------------------------------------------------------------------------#
if(WIN32)
    list(APPEND LIBPD_COMPILE_DEFINITIONS WINVER=0x502 WIN32=1 _WIN32=1)
    if(${CMAKE_SIZEOF_VOID_P} EQUAL 8)
        list(APPEND LIBPD_COMPILE_DEFINITIONS "PD_LONGINTTYPE=long long")
	endif()
    if(MSVC)
        list(APPEND LIBPD_COMPILE_DEFINITIONS HAVE_STRUCT_TIMESPEC=1 _CRT_SECURE_NO_WARNINGS=1)
    endif()
elseif(UNIX)
    list(APPEND LIBPD_COMPILE_DEFINITIONS HAVE_LIBDL=1 HAVE_UNISTD_H=1)
endif()


#------------------------------------------------------------------------------#
# C FLAGS
#------------------------------------------------------------------------------#

# C FLAGS COMPILER OR GENERATOR
#------------------------------------------------------------------------------#
if(CMAKE_GENERATOR STREQUAL Xcode)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable -Wno-unused-function")
    set(CMAKE_C_FLAGS_RELEASE "-fomit-frame-pointer")
elseif(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W3 /wd4005 /wd4091 /wd4100 /wd4133 /wd4102 /wd4267 /wd4311 /wd4477 /wd4996")
    if(MSVC_STATIC_RUNTIME)
        foreach(RFLAG CMAKE_C_FLAGS CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_MINSIZEREL CMAKE_C_FLAGS_RELWITHDEBINFO)
            if(${RFLAG} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${RFLAG} "${${RFLAG}}")
            endif()
        endforeach()
    endif()

elseif(CMAKE_C_COMPILER_ID STREQUAL GNU)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable -fPIC")
    set(CMAKE_C_FLAGS_RELEASE "-ffast-math -funroll-loops -fomit-frame-pointer -O3")
elseif(CMAKE_C_COMPILER_ID STREQUAL Clang)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable")
    set(CMAKE_C_FLAGS_RELEASE "-ffast-math -funroll-loops -fomit-frame-pointer -O3")
endif()

#------------------------------------------------------------------------------#
# TARGETS
#------------------------------------------------------------------------------#
if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
  add_library(libpdshared SHARED ${SOURCE_FILES})
  target_compile_definitions(libpdshared PUBLIC ${LIBPD_COMPILE_DEFINITIONS})
endif()

if(LIBPD_INCLUDE_STATIC_LIBRARY)
  add_library(libpdstatic STATIC ${SOURCE_FILES})
  target_compile_definitions(libpdstatic PUBLIC ${LIBPD_COMPILE_DEFINITIONS})
  target_compile_definitions(libpdstatic PUBLIC PTW32_STATIC_LIB=1)
endif()

#------------------------------------------------------------------------------#
# GENERATOR OPTIONS
#------------------------------------------------------------------------------#
if(CMAKE_GENERATOR STREQUAL Xcode)
    if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
      set_target_properties(libpdshared PROPERTIES GCC_WARN_UNUSED_VARIABLE False)
      set_target_properties(libpdshared PROPERTIES XCODE_ATTRIBUTE_LLVM_LTO[variant=Release] True)
      set_target_properties(libpdshared PROPERTIES GCC_OPTIMIZATION_LEVEL[variant=Release] 3)
      set_target_properties(libpdshared PROPERTIES GCC_UNROLL_LOOPS[variant=Release] True)
      set_target_properties(libpdshared PROPERTIES GCC_FAST_MATH[variant=Release] True)
    endif()

    if(LIBPD_INCLUDE_STATIC_LIBRARY)
      set_target_properties(libpdstatic PROPERTIES GCC_WARN_UNUSED_VARIABLE False)
      set_target_properties(libpdstatic PROPERTIES XCODE_ATTRIBUTE_LLVM_LTO[variant=Release] True)
      set_target_properties(libpdstatic PROPERTIES GCC_OPTIMIZATION_LEVEL[variant=Release] 3)
      set_target_properties(libpdstatic PROPERTIES GCC_UNROLL_LOOPS[variant=Release] True)
      set_target_properties(libpdstatic PROPERTIES GCC_FAST_MATH[variant=Release] True)
    endif()
endif()

#------------------------------------------------------------------------------#
# LINK
#------------------------------------------------------------------------------#

# LINK OS
#------------------------------------------------------------------------------#
if(WIN32)

  if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
    target_link_libraries(libpdshared ws2_32)
  endif()
  if(LIBPD_INCLUDE_STATIC_LIBRARY)
    target_link_libraries(libpdstatic ws2_32)
  endif()

else("${CMAKE_SYSTEM}" MATCHES "Linux")

  find_library(MATH_LIB m)
  if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
    target_link_libraries(libpdshared ${MATH_LIB})
  	target_link_libraries(libpdshared ${CMAKE_DL_LIBS})
  endif()
  if(LIBPD_INCLUDE_STATIC_LIBRARY)
    target_link_libraries(libpdstatic ${MATH_LIB})
  	target_link_libraries(libpdstatic ${CMAKE_DL_LIBS})
  endif()

endif()

# LINK PTHREAD
#------------------------------------------------------------------------------#
set(THREADS_PREFER_PTHREAD_FLAG On)
set(CMAKE_THREAD_PREFER_PTHREAD True)

if(MSVC)
    link_directories(${PROJECT_SOURCE_DIR}/pure-data)
    if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
      target_link_libraries(libpdshared ${MSVC_PTHREAD_LIB})
    endif()
    if(LIBPD_INCLUDE_STATIC_LIBRARY)
      target_link_libraries(libpdstatic ${MSVC_PTHREAD_LIB})
    endif()

endif()

#------------------------------------------------------------------------------#
# OUTPUT NAME
#------------------------------------------------------------------------------#
if(WIN32)
    if(PD_MULTI)

      if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
        set_target_properties(libpdshared PROPERTIES OUTPUT_NAME libpd-multi)
      endif()
      if(LIBPD_INCLUDE_STATIC_LIBRARY)
        set_target_properties(libpdstatic PROPERTIES OUTPUT_NAME libpd-multi-static)
      endif()

    else()

      if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
        set_target_properties(libpdshared PROPERTIES OUTPUT_NAME libpd)
      endif()
      if(LIBPD_INCLUDE_STATIC_LIBRARY)
    	   set_target_properties(libpdstatic PROPERTIES OUTPUT_NAME libpd-static)
      endif()

    endif()
else()
    if(PD_MULTI)

      if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
        set_target_properties(libpdshared PROPERTIES OUTPUT_NAME pd-multi)
      endif()
      if(LIBPD_INCLUDE_STATIC_LIBRARY)
    	   set_target_properties(libpdstatic PROPERTIES OUTPUT_NAME pd-multi)
      endif()

    else()

      if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
        set_target_properties(libpdshared PROPERTIES OUTPUT_NAME pd)
      endif()
      if(LIBPD_INCLUDE_STATIC_LIBRARY)
    	   set_target_properties(libpdstatic PROPERTIES OUTPUT_NAME pd)
      endif()

    endif()
endif()
