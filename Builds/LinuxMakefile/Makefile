# Automatically generated makefile, created by the Projucer
# Don't edit this file! Your changes will be overwritten when you re-save the Projucer project!

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DDEBUG=1 -D_DEBUG=1 -DPD=1 -DUSEAPI_DUMMY=1 -DPD_INTERNAL=1 -DHAVE_UNISTD_H=1 -DHAVE_LIBDL=1 -DHAVE_ALLOCA_H=1 -DJUCER_LINUX_MAKE_6D53C8B4=1 -DJUCE_APP_VERSION=0.0.8 -DJUCE_APP_VERSION_HEX=0x8 -I /usr/include -I /usr/include/freetype2 -I ../../ThirdParty/Vst/vstsdk2.4 -I ../../JuceLibraryCode -I ../../ThirdParty/Juce/modules -I ../../ThirdParty/zpd/pd/src
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -fPIC -O0
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -Wl,--no-undefined -shared -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 

  TARGET := Camomile.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := -march=native
  endif

  CPPFLAGS := $(DEPFLAGS) -DLINUX=1 -DNDEBUG=1 -DPD=1 -DUSEAPI_DUMMY=1 -DPD_INTERNAL=1 -DHAVE_UNISTD_H=1 -DHAVE_LIBDL=1 -DHAVE_ALLOCA_H=1 -DJUCER_LINUX_MAKE_6D53C8B4=1 -DJUCE_APP_VERSION=0.0.8 -DJUCE_APP_VERSION_HEX=0x8 -I /usr/include -I /usr/include/freetype2 -I ../../ThirdParty/Vst/vstsdk2.4 -I ../../JuceLibraryCode -I ../../ThirdParty/Juce/modules -I ../../ThirdParty/zpd/pd/src
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -O3
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -Wl,--no-undefined -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 

  TARGET := Camomile.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/InstanceProcessor_bc7e525e.o \
  $(OBJDIR)/LookAndFeel_40552bdf.o \
  $(OBJDIR)/CamomileEditor_6e8172eb.o \
  $(OBJDIR)/camo_instance_fae2212e.o \
  $(OBJDIR)/camo_parameter_9fd439fa.o \
  $(OBJDIR)/Gui_edc4c728.o \
  $(OBJDIR)/GuiAbout_58af930f.o \
  $(OBJDIR)/GuiComment_699305a1.o \
  $(OBJDIR)/GuiConsole_79dfc099.o \
  $(OBJDIR)/GuiFlowerButton_5b7395b5.o \
  $(OBJDIR)/GuiLabel_844fe2f6.o \
  $(OBJDIR)/GuiNumbox_64ab530d.o \
  $(OBJDIR)/GuiParameter_d0a746ab.o \
  $(OBJDIR)/GuiPatcher_2b7a1737.o \
  $(OBJDIR)/GuiRadio_6eb49c7d.o \
  $(OBJDIR)/GuiSlider_ac956169.o \
  $(OBJDIR)/GuiToggle_37d7325c.o \
  $(OBJDIR)/GuiWindow_d9aaa4f8.o \
  $(OBJDIR)/xpd_atom_52d1534d.o \
  $(OBJDIR)/xpd_console_51e2c365.o \
  $(OBJDIR)/xpd_environment_14673da1.o \
  $(OBJDIR)/xpd_gui_7b2431c9.o \
  $(OBJDIR)/xpd_instance_986f9111.o \
  $(OBJDIR)/xpd_midi_d87d351d.o \
  $(OBJDIR)/xpd_mutex_61425dcd.o \
  $(OBJDIR)/xpd_object_7fa8a07b.o \
  $(OBJDIR)/xpd_patch_fc2d0016.o \
  $(OBJDIR)/xpd_symbol_4fee9e54.o \
  $(OBJDIR)/xpd_tie_1622ae9e.o \
  $(OBJDIR)/cpd_dsp_ddb4c965.o \
  $(OBJDIR)/cpd_environment_eb854a37.o \
  $(OBJDIR)/cpd_gui_dddfde5f.o \
  $(OBJDIR)/cpd_instance_cebdfcbb.o \
  $(OBJDIR)/cpd_message_96543aab.o \
  $(OBJDIR)/cpd_midi_e7ae78c7.o \
  $(OBJDIR)/cpd_mutex_237b7de3.o \
  $(OBJDIR)/cpd_object_1d873125.o \
  $(OBJDIR)/cpd_patch_a00c1e6c.o \
  $(OBJDIR)/cpd_post_ed288a86.o \
  $(OBJDIR)/cpd_types_9c620e5d.o \
  $(OBJDIR)/bob~_6f7631bb.o \
  $(OBJDIR)/bonk~_b8f0a745.o \
  $(OBJDIR)/choice_7edb8dbb.o \
  $(OBJDIR)/fiddle~_dc214121.o \
  $(OBJDIR)/loop~_75717e91.o \
  $(OBJDIR)/lrshift~_7ae1a3db.o \
  $(OBJDIR)/pique_3f576cad.o \
  $(OBJDIR)/sigmund~_e4c2067b.o \
  $(OBJDIR)/stdout_5057aa7b.o \
  $(OBJDIR)/d_arithmetic_2b9b5daf.o \
  $(OBJDIR)/d_array_84daea7e.o \
  $(OBJDIR)/d_ctl_5e496dc0.o \
  $(OBJDIR)/d_dac_5e4ec06b.o \
  $(OBJDIR)/d_delay_d0a0f28.o \
  $(OBJDIR)/d_fft_fftsg_b1b08be2.o \
  $(OBJDIR)/d_fft_5e6d7519.o \
  $(OBJDIR)/d_filter_3896bcfd.o \
  $(OBJDIR)/d_global_43499668.o \
  $(OBJDIR)/d_math_7aed788d.o \
  $(OBJDIR)/d_misc_7b5dad71.o \
  $(OBJDIR)/d_osc_5ef1f1a4.o \
  $(OBJDIR)/d_resample_87f3a9e2.o \
  $(OBJDIR)/d_soundfile_17edfab0.o \
  $(OBJDIR)/d_ugen_88e20f80.o \
  $(OBJDIR)/g_all_guis_291aa898.o \
  $(OBJDIR)/g_array_41a83781.o \
  $(OBJDIR)/g_bang_9fc8f25a.o \
  $(OBJDIR)/g_canvas_3a21c23a.o \
  $(OBJDIR)/g_clone_a112f185.o \
  $(OBJDIR)/g_editor_9ff8bd0f.o \
  $(OBJDIR)/g_graph_7e249d36.o \
  $(OBJDIR)/g_guiconnect_158bf1.o \
  $(OBJDIR)/g_hdial_9b90f940.o \
  $(OBJDIR)/g_hslider_bd6b43b1.o \
  $(OBJDIR)/g_io_31761d08.o \
  $(OBJDIR)/g_mycanvas_f2e3dca6.o \
  $(OBJDIR)/g_numbox_d0031227.o \
  $(OBJDIR)/g_readwrite_2123b3b1.o \
  $(OBJDIR)/g_rtext_c7af0847.o \
  $(OBJDIR)/g_scalar_b4517ce.o \
  $(OBJDIR)/g_template_2f4d519c.o \
  $(OBJDIR)/g_text_bebd480f.o \
  $(OBJDIR)/g_toggle_f7ec7936.o \
  $(OBJDIR)/g_traversal_48d13726.o \
  $(OBJDIR)/g_vdial_802836ce.o \
  $(OBJDIR)/g_vslider_d92955bf.o \
  $(OBJDIR)/g_vumeter_d7e00052.o \
  $(OBJDIR)/m_atom_e67706d.o \
  $(OBJDIR)/m_binbuf_321a26a8.o \
  $(OBJDIR)/m_class_19eabce6.o \
  $(OBJDIR)/m_conf_118a1d80.o \
  $(OBJDIR)/m_glob_18339ed4.o \
  $(OBJDIR)/m_memory_d42f6a5d.o \
  $(OBJDIR)/m_obj_3b0266e5.o \
  $(OBJDIR)/m_pd_3bb63610.o \
  $(OBJDIR)/m_sched_594ee265.o \
  $(OBJDIR)/s_audio_dummy_67bc5773.o \
  $(OBJDIR)/s_audio_393a29ca.o \
  $(OBJDIR)/s_file_859a3b12.o \
  $(OBJDIR)/s_inter_d559c950.o \
  $(OBJDIR)/s_loader_21ea07a9.o \
  $(OBJDIR)/s_main_911a300f.o \
  $(OBJDIR)/s_path_963da37b.o \
  $(OBJDIR)/s_print_4de1e6e1.o \
  $(OBJDIR)/s_utf8_9fca8bc7.o \
  $(OBJDIR)/x_acoustics_5d8fac89.o \
  $(OBJDIR)/x_arithmetic_d0ef1e1b.o \
  $(OBJDIR)/x_array_1a339692.o \
  $(OBJDIR)/x_connective_3ddab41f.o \
  $(OBJDIR)/x_gui_807ed5f4.o \
  $(OBJDIR)/x_interface_9de57772.o \
  $(OBJDIR)/x_list_9740960f.o \
  $(OBJDIR)/x_midi_98ee73d2.o \
  $(OBJDIR)/x_misc_98f52edd.o \
  $(OBJDIR)/x_net_80da5dd6.o \
  $(OBJDIR)/x_scalar_44259add.o \
  $(OBJDIR)/x_text_a4b142de.o \
  $(OBJDIR)/x_time_a4e4687e.o \
  $(OBJDIR)/x_vexp_fun_fb712858.o \
  $(OBJDIR)/x_vexp_if_9480a2ae.o \
  $(OBJDIR)/x_vexp_a81ae518.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_6b797ca1.o \
  $(OBJDIR)/juce_audio_plugin_client_utils_35fbf7.o \
  $(OBJDIR)/juce_audio_plugin_client_VST2_fd137df.o \
  $(OBJDIR)/juce_audio_processors_dea3173d.o \
  $(OBJDIR)/juce_core_75b14332.o \
  $(OBJDIR)/juce_data_structures_72d3da2c.o \
  $(OBJDIR)/juce_events_d2be882c.o \
  $(OBJDIR)/juce_graphics_9c18891e.o \
  $(OBJDIR)/juce_gui_basics_8a6da59c.o \
  $(OBJDIR)/juce_gui_extra_4a026f23.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(RESOURCES)
	@echo Linking Camomile
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning Camomile
	@$(CLEANCMD)

strip:
	@echo Stripping Camomile
	-@strip --strip-unneeded $(OUTDIR)/$(TARGET)

$(OBJDIR)/InstanceProcessor_bc7e525e.o: ../../Source/InstanceProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InstanceProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LookAndFeel_40552bdf.o: ../../Source/LookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/CamomileEditor_6e8172eb.o: ../../Source/CamomileEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling CamomileEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/camo_instance_fae2212e.o: ../../Source/Camo/camo_instance.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling camo_instance.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/camo_parameter_9fd439fa.o: ../../Source/Camo/camo_parameter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling camo_parameter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Gui_edc4c728.o: ../../Source/Gui/Gui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Gui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiAbout_58af930f.o: ../../Source/Gui/GuiAbout.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiAbout.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiComment_699305a1.o: ../../Source/Gui/GuiComment.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiComment.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiConsole_79dfc099.o: ../../Source/Gui/GuiConsole.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiConsole.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiFlowerButton_5b7395b5.o: ../../Source/Gui/GuiFlowerButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiFlowerButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiLabel_844fe2f6.o: ../../Source/Gui/GuiLabel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiLabel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiNumbox_64ab530d.o: ../../Source/Gui/GuiNumbox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiNumbox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiParameter_d0a746ab.o: ../../Source/Gui/GuiParameter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiParameter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiPatcher_2b7a1737.o: ../../Source/Gui/GuiPatcher.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiPatcher.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiRadio_6eb49c7d.o: ../../Source/Gui/GuiRadio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiRadio.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiSlider_ac956169.o: ../../Source/Gui/GuiSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiToggle_37d7325c.o: ../../Source/Gui/GuiToggle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiToggle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiWindow_d9aaa4f8.o: ../../Source/Gui/GuiWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_atom_52d1534d.o: ../../ThirdParty/zpd/xpd/xpd_atom.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_atom.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_console_51e2c365.o: ../../ThirdParty/zpd/xpd/xpd_console.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_console.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_environment_14673da1.o: ../../ThirdParty/zpd/xpd/xpd_environment.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_environment.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_gui_7b2431c9.o: ../../ThirdParty/zpd/xpd/xpd_gui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_gui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_instance_986f9111.o: ../../ThirdParty/zpd/xpd/xpd_instance.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_instance.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_midi_d87d351d.o: ../../ThirdParty/zpd/xpd/xpd_midi.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_midi.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_mutex_61425dcd.o: ../../ThirdParty/zpd/xpd/xpd_mutex.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_mutex.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_object_7fa8a07b.o: ../../ThirdParty/zpd/xpd/xpd_object.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_object.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_patch_fc2d0016.o: ../../ThirdParty/zpd/xpd/xpd_patch.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_patch.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_symbol_4fee9e54.o: ../../ThirdParty/zpd/xpd/xpd_symbol.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_symbol.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/xpd_tie_1622ae9e.o: ../../ThirdParty/zpd/xpd/xpd_tie.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling xpd_tie.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_dsp_ddb4c965.o: ../../ThirdParty/zpd/cpd/cpd_dsp.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_dsp.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_environment_eb854a37.o: ../../ThirdParty/zpd/cpd/cpd_environment.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_environment.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_gui_dddfde5f.o: ../../ThirdParty/zpd/cpd/cpd_gui.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_gui.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_instance_cebdfcbb.o: ../../ThirdParty/zpd/cpd/cpd_instance.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_instance.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_message_96543aab.o: ../../ThirdParty/zpd/cpd/cpd_message.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_message.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_midi_e7ae78c7.o: ../../ThirdParty/zpd/cpd/cpd_midi.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_midi.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_mutex_237b7de3.o: ../../ThirdParty/zpd/cpd/cpd_mutex.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_mutex.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_object_1d873125.o: ../../ThirdParty/zpd/cpd/cpd_object.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_object.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_patch_a00c1e6c.o: ../../ThirdParty/zpd/cpd/cpd_patch.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_patch.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_post_ed288a86.o: ../../ThirdParty/zpd/cpd/cpd_post.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_post.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/cpd_types_9c620e5d.o: ../../ThirdParty/zpd/cpd/cpd_types.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling cpd_types.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/bob~_6f7631bb.o: ../../ThirdParty/zpd/pd/extra/bob~/bob~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling bob~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/bonk~_b8f0a745.o: ../../ThirdParty/zpd/pd/extra/bonk~/bonk~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling bonk~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/choice_7edb8dbb.o: ../../ThirdParty/zpd/pd/extra/choice/choice.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling choice.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/fiddle~_dc214121.o: ../../ThirdParty/zpd/pd/extra/fiddle~/fiddle~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling fiddle~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/loop~_75717e91.o: ../../ThirdParty/zpd/pd/extra/loop~/loop~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling loop~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lrshift~_7ae1a3db.o: ../../ThirdParty/zpd/pd/extra/lrshift~/lrshift~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lrshift~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pique_3f576cad.o: ../../ThirdParty/zpd/pd/extra/pique/pique.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pique.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sigmund~_e4c2067b.o: ../../ThirdParty/zpd/pd/extra/sigmund~/sigmund~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sigmund~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/stdout_5057aa7b.o: ../../ThirdParty/zpd/pd/extra/stdout/stdout.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling stdout.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_arithmetic_2b9b5daf.o: ../../ThirdParty/zpd/pd/src/d_arithmetic.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_arithmetic.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_array_84daea7e.o: ../../ThirdParty/zpd/pd/src/d_array.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_array.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_ctl_5e496dc0.o: ../../ThirdParty/zpd/pd/src/d_ctl.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_ctl.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_dac_5e4ec06b.o: ../../ThirdParty/zpd/pd/src/d_dac.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_dac.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_delay_d0a0f28.o: ../../ThirdParty/zpd/pd/src/d_delay.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_delay.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_fft_fftsg_b1b08be2.o: ../../ThirdParty/zpd/pd/src/d_fft_fftsg.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_fft_fftsg.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_fft_5e6d7519.o: ../../ThirdParty/zpd/pd/src/d_fft.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_fft.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_filter_3896bcfd.o: ../../ThirdParty/zpd/pd/src/d_filter.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_filter.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_global_43499668.o: ../../ThirdParty/zpd/pd/src/d_global.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_global.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_math_7aed788d.o: ../../ThirdParty/zpd/pd/src/d_math.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_math.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_misc_7b5dad71.o: ../../ThirdParty/zpd/pd/src/d_misc.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_misc.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_osc_5ef1f1a4.o: ../../ThirdParty/zpd/pd/src/d_osc.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_osc.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_resample_87f3a9e2.o: ../../ThirdParty/zpd/pd/src/d_resample.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_resample.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_soundfile_17edfab0.o: ../../ThirdParty/zpd/pd/src/d_soundfile.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_soundfile.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_ugen_88e20f80.o: ../../ThirdParty/zpd/pd/src/d_ugen.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_ugen.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_all_guis_291aa898.o: ../../ThirdParty/zpd/pd/src/g_all_guis.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_all_guis.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_array_41a83781.o: ../../ThirdParty/zpd/pd/src/g_array.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_array.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_bang_9fc8f25a.o: ../../ThirdParty/zpd/pd/src/g_bang.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_bang.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_canvas_3a21c23a.o: ../../ThirdParty/zpd/pd/src/g_canvas.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_canvas.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_clone_a112f185.o: ../../ThirdParty/zpd/pd/src/g_clone.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_clone.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_editor_9ff8bd0f.o: ../../ThirdParty/zpd/pd/src/g_editor.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_editor.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_graph_7e249d36.o: ../../ThirdParty/zpd/pd/src/g_graph.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_graph.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_guiconnect_158bf1.o: ../../ThirdParty/zpd/pd/src/g_guiconnect.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_guiconnect.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_hdial_9b90f940.o: ../../ThirdParty/zpd/pd/src/g_hdial.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_hdial.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_hslider_bd6b43b1.o: ../../ThirdParty/zpd/pd/src/g_hslider.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_hslider.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_io_31761d08.o: ../../ThirdParty/zpd/pd/src/g_io.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_io.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_mycanvas_f2e3dca6.o: ../../ThirdParty/zpd/pd/src/g_mycanvas.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_mycanvas.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_numbox_d0031227.o: ../../ThirdParty/zpd/pd/src/g_numbox.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_numbox.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_readwrite_2123b3b1.o: ../../ThirdParty/zpd/pd/src/g_readwrite.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_readwrite.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_rtext_c7af0847.o: ../../ThirdParty/zpd/pd/src/g_rtext.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_rtext.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_scalar_b4517ce.o: ../../ThirdParty/zpd/pd/src/g_scalar.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_scalar.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_template_2f4d519c.o: ../../ThirdParty/zpd/pd/src/g_template.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_template.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_text_bebd480f.o: ../../ThirdParty/zpd/pd/src/g_text.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_text.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_toggle_f7ec7936.o: ../../ThirdParty/zpd/pd/src/g_toggle.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_toggle.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_traversal_48d13726.o: ../../ThirdParty/zpd/pd/src/g_traversal.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_traversal.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_vdial_802836ce.o: ../../ThirdParty/zpd/pd/src/g_vdial.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_vdial.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_vslider_d92955bf.o: ../../ThirdParty/zpd/pd/src/g_vslider.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_vslider.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_vumeter_d7e00052.o: ../../ThirdParty/zpd/pd/src/g_vumeter.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_vumeter.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_atom_e67706d.o: ../../ThirdParty/zpd/pd/src/m_atom.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_atom.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_binbuf_321a26a8.o: ../../ThirdParty/zpd/pd/src/m_binbuf.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_binbuf.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_class_19eabce6.o: ../../ThirdParty/zpd/pd/src/m_class.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_class.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_conf_118a1d80.o: ../../ThirdParty/zpd/pd/src/m_conf.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_conf.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_glob_18339ed4.o: ../../ThirdParty/zpd/pd/src/m_glob.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_glob.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_memory_d42f6a5d.o: ../../ThirdParty/zpd/pd/src/m_memory.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_memory.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_obj_3b0266e5.o: ../../ThirdParty/zpd/pd/src/m_obj.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_obj.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_pd_3bb63610.o: ../../ThirdParty/zpd/pd/src/m_pd.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_pd.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_sched_594ee265.o: ../../ThirdParty/zpd/pd/src/m_sched.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_sched.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_audio_dummy_67bc5773.o: ../../ThirdParty/zpd/pd/src/s_audio_dummy.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_audio_dummy.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_audio_393a29ca.o: ../../ThirdParty/zpd/pd/src/s_audio.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_audio.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_file_859a3b12.o: ../../ThirdParty/zpd/pd/src/s_file.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_file.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_inter_d559c950.o: ../../ThirdParty/zpd/pd/src/s_inter.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_inter.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_loader_21ea07a9.o: ../../ThirdParty/zpd/pd/src/s_loader.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_loader.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_main_911a300f.o: ../../ThirdParty/zpd/pd/src/s_main.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_main.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_path_963da37b.o: ../../ThirdParty/zpd/pd/src/s_path.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_path.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_print_4de1e6e1.o: ../../ThirdParty/zpd/pd/src/s_print.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_print.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_utf8_9fca8bc7.o: ../../ThirdParty/zpd/pd/src/s_utf8.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_utf8.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_acoustics_5d8fac89.o: ../../ThirdParty/zpd/pd/src/x_acoustics.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_acoustics.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_arithmetic_d0ef1e1b.o: ../../ThirdParty/zpd/pd/src/x_arithmetic.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_arithmetic.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_array_1a339692.o: ../../ThirdParty/zpd/pd/src/x_array.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_array.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_connective_3ddab41f.o: ../../ThirdParty/zpd/pd/src/x_connective.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_connective.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_gui_807ed5f4.o: ../../ThirdParty/zpd/pd/src/x_gui.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_gui.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_interface_9de57772.o: ../../ThirdParty/zpd/pd/src/x_interface.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_interface.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_list_9740960f.o: ../../ThirdParty/zpd/pd/src/x_list.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_list.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_midi_98ee73d2.o: ../../ThirdParty/zpd/pd/src/x_midi.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_midi.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_misc_98f52edd.o: ../../ThirdParty/zpd/pd/src/x_misc.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_misc.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_net_80da5dd6.o: ../../ThirdParty/zpd/pd/src/x_net.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_net.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_scalar_44259add.o: ../../ThirdParty/zpd/pd/src/x_scalar.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_scalar.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_text_a4b142de.o: ../../ThirdParty/zpd/pd/src/x_text.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_text.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_time_a4e4687e.o: ../../ThirdParty/zpd/pd/src/x_time.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_time.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_vexp_fun_fb712858.o: ../../ThirdParty/zpd/pd/src/x_vexp_fun.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_vexp_fun.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_vexp_if_9480a2ae.o: ../../ThirdParty/zpd/pd/src/x_vexp_if.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_vexp_if.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_vexp_a81ae518.o: ../../ThirdParty/zpd/pd/src/x_vexp.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_vexp.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_6b797ca1.o: ../../JuceLibraryCode/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_plugin_client_utils_35fbf7.o: ../../JuceLibraryCode/juce_audio_plugin_client_utils.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_plugin_client_utils.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_plugin_client_VST2_fd137df.o: ../../JuceLibraryCode/juce_audio_plugin_client_VST2.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_plugin_client_VST2.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_dea3173d.o: ../../JuceLibraryCode/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_75b14332.o: ../../JuceLibraryCode/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_72d3da2c.o: ../../JuceLibraryCode/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_d2be882c.o: ../../JuceLibraryCode/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_9c18891e.o: ../../JuceLibraryCode/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_8a6da59c.o: ../../JuceLibraryCode/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_4a026f23.o: ../../JuceLibraryCode/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
