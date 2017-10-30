# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# build with "V=1" for verbose builds
ifeq ($(V), 1)
V_AT =
else
V_AT = @
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef STRIP
  STRIP=strip
endif

ifndef AR
  AR=ar
endif

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DPD=1 -DUSEAPI_DUMMY=1 -DPD_INTERNAL=1 -DTHREAD_LOCKING=0 -DHAVE_UNISTD_H=1 -DHAVE_LIBDL=1 -DHAVE_ALLOCA_H=1 -DJUCER_LINUX_MAKE_6D53C8B4=1 -DJUCE_APP_VERSION=0.1.0 -DJUCE_APP_VERSION_HEX=0x100 $(shell pkg-config --cflags webkit2gtk-4.0 gtk+-x11-3.0) -pthread -I../../JuceLibraryCode -I../../ThirdParty/Juce/modules -I../../ThirdParty/zpd/pd/src $(CPPFLAGS)

  JUCE_CPPFLAGS_VST := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := Camomile.so

  JUCE_CPPFLAGS_SHARED_CODE := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJUCE_SHARED_CODE=1
  JUCE_TARGET_SHARED_CODE := Camomile.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L/usr/X11R6/lib/ $(shell pkg-config --libs webkit2gtk-4.0 gtk+-x11-3.0) -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DPD=1 -DUSEAPI_DUMMY=1 -DPD_INTERNAL=1 -DTHREAD_LOCKING=0 -DHAVE_UNISTD_H=1 -DHAVE_LIBDL=1 -DHAVE_ALLOCA_H=1 -DJUCER_LINUX_MAKE_6D53C8B4=1 -DJUCE_APP_VERSION=0.1.0 -DJUCE_APP_VERSION_HEX=0x100 $(shell pkg-config --cflags webkit2gtk-4.0 gtk+-x11-3.0) -pthread -I../../JuceLibraryCode -I../../ThirdParty/Juce/modules -I../../ThirdParty/zpd/pd/src $(CPPFLAGS)

  JUCE_CPPFLAGS_VST := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0
  JUCE_CFLAGS_VST := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST := -shared -Wl,--no-undefined
  JUCE_TARGET_VST := Camomile.so

  JUCE_CPPFLAGS_SHARED_CODE := -DJucePlugin_Build_VST=1 -DJucePlugin_Build_VST3=0 -DJucePlugin_Build_AU=0 -DJucePlugin_Build_AUv3=0 -DJucePlugin_Build_RTAS=0 -DJucePlugin_Build_AAX=0 -DJucePlugin_Build_Standalone=0 -DJUCE_SHARED_CODE=1
  JUCE_TARGET_SHARED_CODE := Camomile.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L/usr/X11R6/lib/ $(shell pkg-config --libs webkit2gtk-4.0 gtk+-x11-3.0) -fvisibility=hidden -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_ALL := \

OBJECTS_VST := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_dd551e08.o \

OBJECTS_SHARED_CODE := \
  $(JUCE_OBJDIR)/LookAndFeel_40552bdf.o \
  $(JUCE_OBJDIR)/CamomileEditor_6e8172eb.o \
  $(JUCE_OBJDIR)/camo_gui_67b103ac.o \
  $(JUCE_OBJDIR)/camo_processor_7b0f5e83.o \
  $(JUCE_OBJDIR)/Gui_edc4c728.o \
  $(JUCE_OBJDIR)/GuiAbout_58af930f.o \
  $(JUCE_OBJDIR)/GuiComment_699305a1.o \
  $(JUCE_OBJDIR)/GuiConsole_79dfc099.o \
  $(JUCE_OBJDIR)/GuiFlowerButton_5b7395b5.o \
  $(JUCE_OBJDIR)/GuiLabel_844fe2f6.o \
  $(JUCE_OBJDIR)/GuiNumbox_64ab530d.o \
  $(JUCE_OBJDIR)/GuiParameter_d0a746ab.o \
  $(JUCE_OBJDIR)/GuiPatcher_2b7a1737.o \
  $(JUCE_OBJDIR)/GuiRadio_6eb49c7d.o \
  $(JUCE_OBJDIR)/GuiSlider_ac956169.o \
  $(JUCE_OBJDIR)/GuiToggle_37d7325c.o \
  $(JUCE_OBJDIR)/GuiWindow_d9aaa4f8.o \
  $(JUCE_OBJDIR)/xpd_atom_52d1534d.o \
  $(JUCE_OBJDIR)/xpd_console_51e2c365.o \
  $(JUCE_OBJDIR)/xpd_environment_14673da1.o \
  $(JUCE_OBJDIR)/xpd_gui_7b2431c9.o \
  $(JUCE_OBJDIR)/xpd_instance_986f9111.o \
  $(JUCE_OBJDIR)/xpd_midi_d87d351d.o \
  $(JUCE_OBJDIR)/xpd_mutex_61425dcd.o \
  $(JUCE_OBJDIR)/xpd_object_7fa8a07b.o \
  $(JUCE_OBJDIR)/xpd_patch_fc2d0016.o \
  $(JUCE_OBJDIR)/xpd_symbol_4fee9e54.o \
  $(JUCE_OBJDIR)/xpd_tie_1622ae9e.o \
  $(JUCE_OBJDIR)/cpd_dsp_ddb4c965.o \
  $(JUCE_OBJDIR)/cpd_environment_eb854a37.o \
  $(JUCE_OBJDIR)/cpd_gui_dddfde5f.o \
  $(JUCE_OBJDIR)/cpd_instance_cebdfcbb.o \
  $(JUCE_OBJDIR)/cpd_message_96543aab.o \
  $(JUCE_OBJDIR)/cpd_midi_e7ae78c7.o \
  $(JUCE_OBJDIR)/cpd_mutex_237b7de3.o \
  $(JUCE_OBJDIR)/cpd_object_1d873125.o \
  $(JUCE_OBJDIR)/cpd_patch_a00c1e6c.o \
  $(JUCE_OBJDIR)/cpd_post_ed288a86.o \
  $(JUCE_OBJDIR)/cpd_types_9c620e5d.o \
  $(JUCE_OBJDIR)/thd_f3d9d546.o \
  $(JUCE_OBJDIR)/bob~_6f7631bb.o \
  $(JUCE_OBJDIR)/bonk~_b8f0a745.o \
  $(JUCE_OBJDIR)/choice_7edb8dbb.o \
  $(JUCE_OBJDIR)/fiddle~_dc214121.o \
  $(JUCE_OBJDIR)/loop~_75717e91.o \
  $(JUCE_OBJDIR)/lrshift~_7ae1a3db.o \
  $(JUCE_OBJDIR)/pique_3f576cad.o \
  $(JUCE_OBJDIR)/sigmund~_e4c2067b.o \
  $(JUCE_OBJDIR)/stdout_5057aa7b.o \
  $(JUCE_OBJDIR)/d_arithmetic_2b9b5daf.o \
  $(JUCE_OBJDIR)/d_array_84daea7e.o \
  $(JUCE_OBJDIR)/d_ctl_5e496dc0.o \
  $(JUCE_OBJDIR)/d_dac_5e4ec06b.o \
  $(JUCE_OBJDIR)/d_delay_d0a0f28.o \
  $(JUCE_OBJDIR)/d_fft_fftsg_b1b08be2.o \
  $(JUCE_OBJDIR)/d_fft_5e6d7519.o \
  $(JUCE_OBJDIR)/d_filter_3896bcfd.o \
  $(JUCE_OBJDIR)/d_global_43499668.o \
  $(JUCE_OBJDIR)/d_math_7aed788d.o \
  $(JUCE_OBJDIR)/d_misc_7b5dad71.o \
  $(JUCE_OBJDIR)/d_osc_5ef1f1a4.o \
  $(JUCE_OBJDIR)/d_resample_87f3a9e2.o \
  $(JUCE_OBJDIR)/d_soundfile_17edfab0.o \
  $(JUCE_OBJDIR)/d_ugen_88e20f80.o \
  $(JUCE_OBJDIR)/g_all_guis_291aa898.o \
  $(JUCE_OBJDIR)/g_array_41a83781.o \
  $(JUCE_OBJDIR)/g_bang_9fc8f25a.o \
  $(JUCE_OBJDIR)/g_canvas_3a21c23a.o \
  $(JUCE_OBJDIR)/g_clone_a112f185.o \
  $(JUCE_OBJDIR)/g_editor_9ff8bd0f.o \
  $(JUCE_OBJDIR)/g_graph_7e249d36.o \
  $(JUCE_OBJDIR)/g_guiconnect_158bf1.o \
  $(JUCE_OBJDIR)/g_hdial_9b90f940.o \
  $(JUCE_OBJDIR)/g_hslider_bd6b43b1.o \
  $(JUCE_OBJDIR)/g_io_31761d08.o \
  $(JUCE_OBJDIR)/g_mycanvas_f2e3dca6.o \
  $(JUCE_OBJDIR)/g_numbox_d0031227.o \
  $(JUCE_OBJDIR)/g_readwrite_2123b3b1.o \
  $(JUCE_OBJDIR)/g_rtext_c7af0847.o \
  $(JUCE_OBJDIR)/g_scalar_b4517ce.o \
  $(JUCE_OBJDIR)/g_template_2f4d519c.o \
  $(JUCE_OBJDIR)/g_text_bebd480f.o \
  $(JUCE_OBJDIR)/g_toggle_f7ec7936.o \
  $(JUCE_OBJDIR)/g_traversal_48d13726.o \
  $(JUCE_OBJDIR)/g_vdial_802836ce.o \
  $(JUCE_OBJDIR)/g_vslider_d92955bf.o \
  $(JUCE_OBJDIR)/g_vumeter_d7e00052.o \
  $(JUCE_OBJDIR)/m_atom_e67706d.o \
  $(JUCE_OBJDIR)/m_binbuf_321a26a8.o \
  $(JUCE_OBJDIR)/m_class_19eabce6.o \
  $(JUCE_OBJDIR)/m_conf_118a1d80.o \
  $(JUCE_OBJDIR)/m_glob_18339ed4.o \
  $(JUCE_OBJDIR)/m_memory_d42f6a5d.o \
  $(JUCE_OBJDIR)/m_obj_3b0266e5.o \
  $(JUCE_OBJDIR)/m_pd_3bb63610.o \
  $(JUCE_OBJDIR)/m_sched_594ee265.o \
  $(JUCE_OBJDIR)/s_audio_dummy_67bc5773.o \
  $(JUCE_OBJDIR)/s_audio_393a29ca.o \
  $(JUCE_OBJDIR)/s_file_859a3b12.o \
  $(JUCE_OBJDIR)/s_inter_d559c950.o \
  $(JUCE_OBJDIR)/s_loader_21ea07a9.o \
  $(JUCE_OBJDIR)/s_main_911a300f.o \
  $(JUCE_OBJDIR)/s_path_963da37b.o \
  $(JUCE_OBJDIR)/s_print_4de1e6e1.o \
  $(JUCE_OBJDIR)/s_utf8_9fca8bc7.o \
  $(JUCE_OBJDIR)/x_acoustics_5d8fac89.o \
  $(JUCE_OBJDIR)/x_arithmetic_d0ef1e1b.o \
  $(JUCE_OBJDIR)/x_array_1a339692.o \
  $(JUCE_OBJDIR)/x_connective_3ddab41f.o \
  $(JUCE_OBJDIR)/x_gui_807ed5f4.o \
  $(JUCE_OBJDIR)/x_interface_9de57772.o \
  $(JUCE_OBJDIR)/x_list_9740960f.o \
  $(JUCE_OBJDIR)/x_midi_98ee73d2.o \
  $(JUCE_OBJDIR)/x_misc_98f52edd.o \
  $(JUCE_OBJDIR)/x_net_80da5dd6.o \
  $(JUCE_OBJDIR)/x_scalar_44259add.o \
  $(JUCE_OBJDIR)/x_text_a4b142de.o \
  $(JUCE_OBJDIR)/x_time_a4e4687e.o \
  $(JUCE_OBJDIR)/x_vexp_fun_fb712858.o \
  $(JUCE_OBJDIR)/x_vexp_if_9480a2ae.o \
  $(JUCE_OBJDIR)/x_vexp_a81ae518.o \
  $(JUCE_OBJDIR)/BinaryData_ce4232d4.o \
  $(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_e32edaee.o \
  $(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o \
  $(JUCE_OBJDIR)/include_juce_core_f26d17db.o \
  $(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o \
  $(JUCE_OBJDIR)/include_juce_events_fd7d695.o \
  $(JUCE_OBJDIR)/include_juce_graphics_f817e147.o \
  $(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o \
  $(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o \

.PHONY: clean all VST

all : VST

VST : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST)


$(JUCE_OUTDIR)/$(JUCE_TARGET_VST) : check-pkg-config $(OBJECTS_VST) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@echo Linking "Camomile - VST"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST) $(OBJECTS_VST) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_VST) $(RESOURCES) $(TARGET_ARCH)

$(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) : check-pkg-config $(OBJECTS_SHARED_CODE) $(RESOURCES)
	@echo Linking "Camomile - Shared Code"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(AR) -rcs $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(OBJECTS_SHARED_CODE)

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST2_dd551e08.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_VST2.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_VST2.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST) $(JUCE_CFLAGS_VST) -o "$@" -c "$<"

$(JUCE_OBJDIR)/LookAndFeel_40552bdf.o: ../../Source/LookAndFeel.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling LookAndFeel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/CamomileEditor_6e8172eb.o: ../../Source/CamomileEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling CamomileEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/camo_gui_67b103ac.o: ../../Source/camo/camo_gui.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling camo_gui.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/camo_processor_7b0f5e83.o: ../../Source/camo/camo_processor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling camo_processor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/Gui_edc4c728.o: ../../Source/Gui/Gui.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling Gui.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiAbout_58af930f.o: ../../Source/Gui/GuiAbout.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiAbout.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiComment_699305a1.o: ../../Source/Gui/GuiComment.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiComment.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiConsole_79dfc099.o: ../../Source/Gui/GuiConsole.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiConsole.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiFlowerButton_5b7395b5.o: ../../Source/Gui/GuiFlowerButton.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiFlowerButton.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiLabel_844fe2f6.o: ../../Source/Gui/GuiLabel.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiLabel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiNumbox_64ab530d.o: ../../Source/Gui/GuiNumbox.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiNumbox.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiParameter_d0a746ab.o: ../../Source/Gui/GuiParameter.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiParameter.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiPatcher_2b7a1737.o: ../../Source/Gui/GuiPatcher.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiPatcher.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiRadio_6eb49c7d.o: ../../Source/Gui/GuiRadio.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiRadio.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiSlider_ac956169.o: ../../Source/Gui/GuiSlider.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiSlider.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiToggle_37d7325c.o: ../../Source/Gui/GuiToggle.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiToggle.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/GuiWindow_d9aaa4f8.o: ../../Source/Gui/GuiWindow.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling GuiWindow.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_atom_52d1534d.o: ../../ThirdParty/zpd/xpd/xpd_atom.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_atom.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_console_51e2c365.o: ../../ThirdParty/zpd/xpd/xpd_console.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_console.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_environment_14673da1.o: ../../ThirdParty/zpd/xpd/xpd_environment.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_environment.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_gui_7b2431c9.o: ../../ThirdParty/zpd/xpd/xpd_gui.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_gui.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_instance_986f9111.o: ../../ThirdParty/zpd/xpd/xpd_instance.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_instance.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_midi_d87d351d.o: ../../ThirdParty/zpd/xpd/xpd_midi.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_midi.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_mutex_61425dcd.o: ../../ThirdParty/zpd/xpd/xpd_mutex.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_mutex.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_object_7fa8a07b.o: ../../ThirdParty/zpd/xpd/xpd_object.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_object.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_patch_fc2d0016.o: ../../ThirdParty/zpd/xpd/xpd_patch.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_patch.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_symbol_4fee9e54.o: ../../ThirdParty/zpd/xpd/xpd_symbol.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_symbol.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xpd_tie_1622ae9e.o: ../../ThirdParty/zpd/xpd/xpd_tie.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xpd_tie.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_dsp_ddb4c965.o: ../../ThirdParty/zpd/cpd/cpd_dsp.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_dsp.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_environment_eb854a37.o: ../../ThirdParty/zpd/cpd/cpd_environment.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_environment.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_gui_dddfde5f.o: ../../ThirdParty/zpd/cpd/cpd_gui.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_gui.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_instance_cebdfcbb.o: ../../ThirdParty/zpd/cpd/cpd_instance.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_instance.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_message_96543aab.o: ../../ThirdParty/zpd/cpd/cpd_message.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_message.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_midi_e7ae78c7.o: ../../ThirdParty/zpd/cpd/cpd_midi.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_midi.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_mutex_237b7de3.o: ../../ThirdParty/zpd/cpd/cpd_mutex.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_mutex.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_object_1d873125.o: ../../ThirdParty/zpd/cpd/cpd_object.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_object.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_patch_a00c1e6c.o: ../../ThirdParty/zpd/cpd/cpd_patch.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_patch.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_post_ed288a86.o: ../../ThirdParty/zpd/cpd/cpd_post.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_post.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cpd_types_9c620e5d.o: ../../ThirdParty/zpd/cpd/cpd_types.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cpd_types.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/thd_f3d9d546.o: ../../ThirdParty/zpd/thread/src/thd.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling thd.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bob~_6f7631bb.o: ../../ThirdParty/zpd/pd/extra/bob~/bob~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bob~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bonk~_b8f0a745.o: ../../ThirdParty/zpd/pd/extra/bonk~/bonk~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bonk~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/choice_7edb8dbb.o: ../../ThirdParty/zpd/pd/extra/choice/choice.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling choice.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fiddle~_dc214121.o: ../../ThirdParty/zpd/pd/extra/fiddle~/fiddle~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fiddle~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/loop~_75717e91.o: ../../ThirdParty/zpd/pd/extra/loop~/loop~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling loop~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lrshift~_7ae1a3db.o: ../../ThirdParty/zpd/pd/extra/lrshift~/lrshift~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lrshift~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pique_3f576cad.o: ../../ThirdParty/zpd/pd/extra/pique/pique.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pique.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sigmund~_e4c2067b.o: ../../ThirdParty/zpd/pd/extra/sigmund~/sigmund~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sigmund~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/stdout_5057aa7b.o: ../../ThirdParty/zpd/pd/extra/stdout/stdout.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling stdout.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_arithmetic_2b9b5daf.o: ../../ThirdParty/zpd/pd/src/d_arithmetic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_arithmetic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_array_84daea7e.o: ../../ThirdParty/zpd/pd/src/d_array.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_array.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_ctl_5e496dc0.o: ../../ThirdParty/zpd/pd/src/d_ctl.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_ctl.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_dac_5e4ec06b.o: ../../ThirdParty/zpd/pd/src/d_dac.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_dac.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_delay_d0a0f28.o: ../../ThirdParty/zpd/pd/src/d_delay.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_delay.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_fft_fftsg_b1b08be2.o: ../../ThirdParty/zpd/pd/src/d_fft_fftsg.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_fft_fftsg.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_fft_5e6d7519.o: ../../ThirdParty/zpd/pd/src/d_fft.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_fft.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_filter_3896bcfd.o: ../../ThirdParty/zpd/pd/src/d_filter.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_filter.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_global_43499668.o: ../../ThirdParty/zpd/pd/src/d_global.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_global.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_math_7aed788d.o: ../../ThirdParty/zpd/pd/src/d_math.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_math.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_misc_7b5dad71.o: ../../ThirdParty/zpd/pd/src/d_misc.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_misc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_osc_5ef1f1a4.o: ../../ThirdParty/zpd/pd/src/d_osc.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_osc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_resample_87f3a9e2.o: ../../ThirdParty/zpd/pd/src/d_resample.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_resample.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_soundfile_17edfab0.o: ../../ThirdParty/zpd/pd/src/d_soundfile.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_soundfile.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/d_ugen_88e20f80.o: ../../ThirdParty/zpd/pd/src/d_ugen.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling d_ugen.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_all_guis_291aa898.o: ../../ThirdParty/zpd/pd/src/g_all_guis.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_all_guis.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_array_41a83781.o: ../../ThirdParty/zpd/pd/src/g_array.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_array.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_bang_9fc8f25a.o: ../../ThirdParty/zpd/pd/src/g_bang.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_bang.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_canvas_3a21c23a.o: ../../ThirdParty/zpd/pd/src/g_canvas.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_canvas.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_clone_a112f185.o: ../../ThirdParty/zpd/pd/src/g_clone.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_clone.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_editor_9ff8bd0f.o: ../../ThirdParty/zpd/pd/src/g_editor.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_editor.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_graph_7e249d36.o: ../../ThirdParty/zpd/pd/src/g_graph.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_graph.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_guiconnect_158bf1.o: ../../ThirdParty/zpd/pd/src/g_guiconnect.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_guiconnect.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_hdial_9b90f940.o: ../../ThirdParty/zpd/pd/src/g_hdial.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_hdial.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_hslider_bd6b43b1.o: ../../ThirdParty/zpd/pd/src/g_hslider.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_hslider.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_io_31761d08.o: ../../ThirdParty/zpd/pd/src/g_io.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_io.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_mycanvas_f2e3dca6.o: ../../ThirdParty/zpd/pd/src/g_mycanvas.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_mycanvas.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_numbox_d0031227.o: ../../ThirdParty/zpd/pd/src/g_numbox.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_numbox.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_readwrite_2123b3b1.o: ../../ThirdParty/zpd/pd/src/g_readwrite.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_readwrite.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_rtext_c7af0847.o: ../../ThirdParty/zpd/pd/src/g_rtext.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_rtext.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_scalar_b4517ce.o: ../../ThirdParty/zpd/pd/src/g_scalar.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_scalar.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_template_2f4d519c.o: ../../ThirdParty/zpd/pd/src/g_template.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_template.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_text_bebd480f.o: ../../ThirdParty/zpd/pd/src/g_text.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_text.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_toggle_f7ec7936.o: ../../ThirdParty/zpd/pd/src/g_toggle.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_toggle.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_traversal_48d13726.o: ../../ThirdParty/zpd/pd/src/g_traversal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_traversal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_vdial_802836ce.o: ../../ThirdParty/zpd/pd/src/g_vdial.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_vdial.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_vslider_d92955bf.o: ../../ThirdParty/zpd/pd/src/g_vslider.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_vslider.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/g_vumeter_d7e00052.o: ../../ThirdParty/zpd/pd/src/g_vumeter.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling g_vumeter.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_atom_e67706d.o: ../../ThirdParty/zpd/pd/src/m_atom.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_atom.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_binbuf_321a26a8.o: ../../ThirdParty/zpd/pd/src/m_binbuf.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_binbuf.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_class_19eabce6.o: ../../ThirdParty/zpd/pd/src/m_class.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_class.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_conf_118a1d80.o: ../../ThirdParty/zpd/pd/src/m_conf.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_conf.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_glob_18339ed4.o: ../../ThirdParty/zpd/pd/src/m_glob.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_glob.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_memory_d42f6a5d.o: ../../ThirdParty/zpd/pd/src/m_memory.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_memory.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_obj_3b0266e5.o: ../../ThirdParty/zpd/pd/src/m_obj.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_obj.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_pd_3bb63610.o: ../../ThirdParty/zpd/pd/src/m_pd.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_pd.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/m_sched_594ee265.o: ../../ThirdParty/zpd/pd/src/m_sched.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling m_sched.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_audio_dummy_67bc5773.o: ../../ThirdParty/zpd/pd/src/s_audio_dummy.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_audio_dummy.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_audio_393a29ca.o: ../../ThirdParty/zpd/pd/src/s_audio.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_audio.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_file_859a3b12.o: ../../ThirdParty/zpd/pd/src/s_file.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_file.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_inter_d559c950.o: ../../ThirdParty/zpd/pd/src/s_inter.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_inter.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_loader_21ea07a9.o: ../../ThirdParty/zpd/pd/src/s_loader.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_loader.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_main_911a300f.o: ../../ThirdParty/zpd/pd/src/s_main.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_main.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_path_963da37b.o: ../../ThirdParty/zpd/pd/src/s_path.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_path.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_print_4de1e6e1.o: ../../ThirdParty/zpd/pd/src/s_print.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_print.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_utf8_9fca8bc7.o: ../../ThirdParty/zpd/pd/src/s_utf8.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_utf8.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_acoustics_5d8fac89.o: ../../ThirdParty/zpd/pd/src/x_acoustics.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_acoustics.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_arithmetic_d0ef1e1b.o: ../../ThirdParty/zpd/pd/src/x_arithmetic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_arithmetic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_array_1a339692.o: ../../ThirdParty/zpd/pd/src/x_array.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_array.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_connective_3ddab41f.o: ../../ThirdParty/zpd/pd/src/x_connective.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_connective.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_gui_807ed5f4.o: ../../ThirdParty/zpd/pd/src/x_gui.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_gui.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_interface_9de57772.o: ../../ThirdParty/zpd/pd/src/x_interface.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_interface.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_list_9740960f.o: ../../ThirdParty/zpd/pd/src/x_list.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_list.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_midi_98ee73d2.o: ../../ThirdParty/zpd/pd/src/x_midi.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_midi.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_misc_98f52edd.o: ../../ThirdParty/zpd/pd/src/x_misc.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_misc.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_net_80da5dd6.o: ../../ThirdParty/zpd/pd/src/x_net.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_net.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_scalar_44259add.o: ../../ThirdParty/zpd/pd/src/x_scalar.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_scalar.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_text_a4b142de.o: ../../ThirdParty/zpd/pd/src/x_text.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_text.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_time_a4e4687e.o: ../../ThirdParty/zpd/pd/src/x_time.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_time.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_vexp_fun_fb712858.o: ../../ThirdParty/zpd/pd/src/x_vexp_fun.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_vexp_fun.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_vexp_if_9480a2ae.o: ../../ThirdParty/zpd/pd/src/x_vexp_if.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_vexp_if.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_vexp_a81ae518.o: ../../ThirdParty/zpd/pd/src/x_vexp.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_vexp.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling BinaryData.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_basics_8a4e984a.o: ../../JuceLibraryCode/include_juce_audio_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_utils_e32edaee.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_utils.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_utils.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_audio_processors_10c03666.o: ../../JuceLibraryCode/include_juce_audio_processors.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_processors.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_core_f26d17db.o: ../../JuceLibraryCode/include_juce_core.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_core.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_data_structures_7471b1e3.o: ../../JuceLibraryCode/include_juce_data_structures.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_data_structures.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_events_fd7d695.o: ../../JuceLibraryCode/include_juce_events.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_events.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_graphics_f817e147.o: ../../JuceLibraryCode/include_juce_graphics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_graphics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_basics_e3f79785.o: ../../JuceLibraryCode/include_juce_gui_basics.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_basics.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/include_juce_gui_extra_6dee1c1a.o: ../../JuceLibraryCode/include_juce_gui_extra.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_gui_extra.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

check-pkg-config:
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors webkit2gtk-4.0 gtk+-x11-3.0

clean:
	@echo Cleaning Camomile
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping Camomile
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_VST:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
