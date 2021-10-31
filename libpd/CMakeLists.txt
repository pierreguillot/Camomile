cmake_minimum_required(VERSION 3.1)

#------------------------------------------------------------------------------#
# LIBPD PROJECT IN C
#------------------------------------------------------------------------------#
project(libpd VERSION 1.0.0 LANGUAGES C)

if (MSVC)
    add_subdirectory(pthreads-win32)
endif()

#------------------------------------------------------------------------------#

set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(LIBPD_PATH "pure-data")
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
    ${LIBPD_PATH}/src/d_arithmetic.c
    ${LIBPD_PATH}/src/d_array.c
    ${LIBPD_PATH}/src/d_ctl.c
    ${LIBPD_PATH}/src/d_dac.c
    ${LIBPD_PATH}/src/d_delay.c
    ${LIBPD_PATH}/src/d_fft.c
    ${LIBPD_PATH}/src/d_fft_fftsg.c
    ${LIBPD_PATH}/src/d_filter.c
    ${LIBPD_PATH}/src/d_global.c
    ${LIBPD_PATH}/src/d_math.c
    ${LIBPD_PATH}/src/d_misc.c
    ${LIBPD_PATH}/src/d_osc.c
    ${LIBPD_PATH}/src/d_resample.c
    ${LIBPD_PATH}/src/d_soundfile_aiff.c
    ${LIBPD_PATH}/src/d_soundfile_caf.c
    ${LIBPD_PATH}/src/d_soundfile_next.c
    ${LIBPD_PATH}/src/d_soundfile_wave.c
    ${LIBPD_PATH}/src/d_soundfile.c
    ${LIBPD_PATH}/src/d_ugen.c
    ${LIBPD_PATH}/src/g_all_guis.c
    ${LIBPD_PATH}/src/g_all_guis.h
    ${LIBPD_PATH}/src/g_array.c
    ${LIBPD_PATH}/src/g_bang.c
    ${LIBPD_PATH}/src/g_canvas.c
    ${LIBPD_PATH}/src/g_canvas.h
    ${LIBPD_PATH}/src/g_clone.c
		${LIBPD_PATH}/src/g_editor_extras.c
    ${LIBPD_PATH}/src/g_editor.c
    ${LIBPD_PATH}/src/g_graph.c
    ${LIBPD_PATH}/src/g_guiconnect.c
    ${LIBPD_PATH}/src/g_hdial.c
    ${LIBPD_PATH}/src/g_hslider.c
    ${LIBPD_PATH}/src/g_io.c
    ${LIBPD_PATH}/src/g_mycanvas.c
    ${LIBPD_PATH}/src/g_numbox.c
    ${LIBPD_PATH}/src/g_readwrite.c
    ${LIBPD_PATH}/src/g_rtext.c
    ${LIBPD_PATH}/src/g_scalar.c
    ${LIBPD_PATH}/src/g_template.c
    ${LIBPD_PATH}/src/g_text.c
    ${LIBPD_PATH}/src/g_toggle.c
    ${LIBPD_PATH}/src/g_traversal.c
		${LIBPD_PATH}/src/g_undo.c
		${LIBPD_PATH}/src/g_undo.h
    ${LIBPD_PATH}/src/g_vdial.c
    ${LIBPD_PATH}/src/g_vslider.c
    ${LIBPD_PATH}/src/g_vumeter.c
    ${LIBPD_PATH}/src/m_atom.c
    ${LIBPD_PATH}/src/m_binbuf.c
    ${LIBPD_PATH}/src/m_class.c
    ${LIBPD_PATH}/src/m_conf.c
    ${LIBPD_PATH}/src/m_glob.c
    ${LIBPD_PATH}/src/m_imp.h
    ${LIBPD_PATH}/src/m_memory.c
    ${LIBPD_PATH}/src/m_obj.c
    ${LIBPD_PATH}/src/m_pd.c
    ${LIBPD_PATH}/src/m_pd.h
    ${LIBPD_PATH}/src/m_sched.c
    ${LIBPD_PATH}/src/s_audio.c
    ${LIBPD_PATH}/src/s_audio_dummy.c
    ${LIBPD_PATH}/src/s_inter.c
    ${LIBPD_PATH}/src/s_libpdmidi.c
    ${LIBPD_PATH}/src/s_loader.c
    ${LIBPD_PATH}/src/s_main.c
		${LIBPD_PATH}/src/s_net.c
		${LIBPD_PATH}/src/s_net.h
    ${LIBPD_PATH}/src/s_path.c
    ${LIBPD_PATH}/src/s_print.c
    ${LIBPD_PATH}/src/s_stuff.h
    ${LIBPD_PATH}/src/s_utf8.c
    ${LIBPD_PATH}/src/s_utf8.h
    ${LIBPD_PATH}/src/x_acoustics.c
    ${LIBPD_PATH}/src/x_arithmetic.c
    ${LIBPD_PATH}/src/x_array.c
    ${LIBPD_PATH}/src/x_connective.c
    ${LIBPD_PATH}/src/x_file.c
    ${LIBPD_PATH}/src/x_gui.c
    ${LIBPD_PATH}/src/x_interface.c
    ${LIBPD_PATH}/src/x_libpdreceive.c
    ${LIBPD_PATH}/src/x_libpdreceive.h
    ${LIBPD_PATH}/src/x_list.c
    ${LIBPD_PATH}/src/x_midi.c
    ${LIBPD_PATH}/src/x_misc.c
    ${LIBPD_PATH}/src/x_net.c
    ${LIBPD_PATH}/src/x_scalar.c
    ${LIBPD_PATH}/src/x_text.c
    ${LIBPD_PATH}/src/x_time.c
    ${LIBPD_PATH}/src/x_vexp.c
    ${LIBPD_PATH}/src/x_vexp_fun.c
    ${LIBPD_PATH}/src/x_vexp_if.c
    ${LIBPD_PATH}/src/z_hooks.c
    ${LIBPD_PATH}/src/z_hooks.h
    ${LIBPD_PATH}/src/z_libpd.c
    ${LIBPD_PATH}/src/z_libpd.h
    ${LIBPD_PATH}/src/z_print_util.c
    ${LIBPD_PATH}/src/z_print_util.h
    ${LIBPD_PATH}/src/z_queued.c
    ${LIBPD_PATH}/src/z_queued.h
    ${LIBPD_PATH}/src/z_ringbuffer.c
    ${LIBPD_PATH}/src/z_ringbuffer.h
)
include_directories(${LIBPD_PATH}/src)
source_group(pd FILES ${PD_SOURCES})
list(APPEND SOURCE_FILES ${PD_SOURCES})

# PURE DATA EXTRA SOURCES
#------------------------------------------------------------------------------#
if(PD_EXTRA)
    file(GLOB PD_EXTRA_SOURCES
    ${LIBPD_PATH}/extra/bob~/bob~.c
    ${LIBPD_PATH}/extra/bonk~/bonk~.c
    ${LIBPD_PATH}/extra/choice/choice.c
    ${LIBPD_PATH}/extra/fiddle~/fiddle~.c
    ${LIBPD_PATH}/extra/loop~/loop~.c
    ${LIBPD_PATH}/extra/lrshift~/lrshift~.c
    ${LIBPD_PATH}/extra/pd~/pd~.c
    ${LIBPD_PATH}/extra/pd~/pdsched.c
    ${LIBPD_PATH}/extra/pique/pique.c
    ${LIBPD_PATH}/extra/sigmund~/sigmund~.c
    ${LIBPD_PATH}/extra/stdout/stdout.c
    )
    include_directories(${LIBPD_PATH}/pure-data/extra)
    source_group(pd\\extra FILES ${PD_EXTRA_SOURCES})
    list(APPEND SOURCE_FILES ${PD_EXTRA_SOURCES})
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
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -ffast-math -funroll-loops -fomit-frame-pointer -O3")
    if(NOT APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-Bsymbolic")
    endif()
elseif(CMAKE_C_COMPILER_ID STREQUAL Clang)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-unused-variable -Wno-int-to-pointer-cast -Wno-pointer-to-int-cast")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS} -ffast-math -funroll-loops -fomit-frame-pointer -O3")
    if(NOT APPLE)
        set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,-Bsymbolic")
    endif()
endif()

#------------------------------------------------------------------------------#
# TARGETS
#------------------------------------------------------------------------------#
if(LIBPD_INCLUDE_DYNAMIC_LIBRARY)
  add_library(libpdshared SHARED ${SOURCE_FILES})
  target_compile_definitions(libpdshared PRIVATE ${LIBPD_COMPILE_DEFINITIONS})
  set_target_properties(libpdshared PROPERTIES POSITION_INDEPENDENT_CODE ON)
endif()

if(LIBPD_INCLUDE_STATIC_LIBRARY)
  add_library(libpdstatic STATIC ${SOURCE_FILES})
  target_compile_definitions(libpdstatic PRIVATE ${LIBPD_COMPILE_DEFINITIONS})
  if(MSVC)
    target_compile_definitions(libpdstatic PRIVATE PTW32_STATIC_LIB=1 "EXTERN= ")
  endif()
  set_target_properties(libpdstatic PROPERTIES POSITION_INDEPENDENT_CODE ON)
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
    target_link_libraries(libpdshared PRIVATE ws2_32)
  endif()
  if(LIBPD_INCLUDE_STATIC_LIBRARY)
    target_link_libraries(libpdstatic PRIVATE ws2_32)
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
      target_link_libraries(libpdshared PRIVATE pthreads)
    endif()
    if(LIBPD_INCLUDE_STATIC_LIBRARY)
      target_link_libraries(libpdstatic PRIVATE pthreads)
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
