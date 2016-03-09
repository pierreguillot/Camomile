# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

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
    TARGET_ARCH := 
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "PD=1" -D "HAVE_UNISTD_H=1" -D "USEAPI_DUMMY=1" -D "HAVE_ALLOCA_H=1" -D "HAVE_LIBDL=1" -D "PD_INTERNAL=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=0.0.3" -D "JUCE_APP_VERSION_HEX=0x3" -I /usr/include -I /usr/include/freetype2 -I ../../ThirdParty/Vst -I ../../ThirdParty/Vst/vstsdk2.4 -I ../../JuceLibraryCode -I ../../ThirdParty/Juce/modules -I ../../ThirdParty/PureData/src
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
    TARGET_ARCH := 
  endif

  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "PD=1" -D "HAVE_UNISTD_H=1" -D "USEAPI_DUMMY=1" -D "HAVE_ALLOCA_H=1" -D "HAVE_LIBDL=1" -D "PD_INTERNAL=1" -D "JUCER_LINUX_MAKE_6D53C8B4=1" -D "JUCE_APP_VERSION=0.0.3" -D "JUCE_APP_VERSION_HEX=0x3" -I /usr/include -I /usr/include/freetype2 -I ../../ThirdParty/Vst -I ../../ThirdParty/Vst/vstsdk2.4 -I ../../JuceLibraryCode -I ../../ThirdParty/Juce/modules -I ../../ThirdParty/PureData/src
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -fPIC -O3
  CXXFLAGS += $(CFLAGS) -std=c++11
  LDFLAGS += $(TARGET_ARCH) -L$(BINDIR) -L$(LIBDIR) -Wl,--no-undefined -shared -fvisibility=hidden -L/usr/X11R6/lib/ -lX11 -lXext -lXinerama -ldl -lfreetype -lpthread -lrt 

  TARGET := Camomile.so
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
  CLEANCMD = rm -rf $(OUTDIR)/$(TARGET) $(OBJDIR)
endif

OBJECTS := \
  $(OBJDIR)/LookAndFeel_40552bdf.o \
  $(OBJDIR)/InstanceProcessor_bc7e525e.o \
  $(OBJDIR)/InstanceEditor_fa2c28eb.o \
  $(OBJDIR)/Gui_2b5c821c.o \
  $(OBJDIR)/GuiWindow_fc7f58ec.o \
  $(OBJDIR)/GuiAbout_73a909b.o \
  $(OBJDIR)/GuiConsole_b1a18b25.o \
  $(OBJDIR)/GuiFlowerButton_762682a9.o \
  $(OBJDIR)/GuiPatcher_633be1c3.o \
  $(OBJDIR)/GuiComment_a154d02d.o \
  $(OBJDIR)/GuiLabel_32dae082.o \
  $(OBJDIR)/GuiNumbox_87800701.o \
  $(OBJDIR)/GuiSlider_cf6a155d.o \
  $(OBJDIR)/GuiToggle_5aabe650.o \
  $(OBJDIR)/GuiRadio_1d3f9a09.o \
  $(OBJDIR)/GuiParameter_1f209e37.o \
  $(OBJDIR)/Pd_51c89d7d.o \
  $(OBJDIR)/PdGui_8982f688.o \
  $(OBJDIR)/PdPatch_eded9115.o \
  $(OBJDIR)/PdInstance_9098ebb2.o \
  $(OBJDIR)/bob~_dea63fa8.o \
  $(OBJDIR)/bonk~_1c54edf2.o \
  $(OBJDIR)/choice_9a48dd28.o \
  $(OBJDIR)/vexp_42c95f1e.o \
  $(OBJDIR)/vexp_fun_46a72f5e.o \
  $(OBJDIR)/vexp_if_a8aa2e8.o \
  $(OBJDIR)/fiddle~_d178694e.o \
  $(OBJDIR)/loop~_d8d5c53e.o \
  $(OBJDIR)/lrshift~_770f74c8.o \
  $(OBJDIR)/pique_a2bbb35a.o \
  $(OBJDIR)/sigmund~_e0efd768.o \
  $(OBJDIR)/stdout_6bc4f9e8.o \
  $(OBJDIR)/d_arithmetic_a26d0d62.o \
  $(OBJDIR)/d_array_bff0f6eb.o \
  $(OBJDIR)/d_ctl_3e61b16d.o \
  $(OBJDIR)/d_dac_3e670418.o \
  $(OBJDIR)/d_delay_48201b95.o \
  $(OBJDIR)/d_fft_3e85b8c6.o \
  $(OBJDIR)/d_fft_fftsg_20e099cf.o \
  $(OBJDIR)/d_filter_60423e30.o \
  $(OBJDIR)/d_global_6af5179b.o \
  $(OBJDIR)/d_math_9dddaa80.o \
  $(OBJDIR)/d_misc_9e4ddf64.o \
  $(OBJDIR)/d_osc_3f0a3551.o \
  $(OBJDIR)/d_resample_72c3aa55.o \
  $(OBJDIR)/d_soundfile_871e089d.o \
  $(OBJDIR)/d_ugen_abd24173.o \
  $(OBJDIR)/g_all_guis_13eaa90b.o \
  $(OBJDIR)/g_array_7cbe43ee.o \
  $(OBJDIR)/g_bang_c2b9244d.o \
  $(OBJDIR)/g_canvas_61cd436d.o \
  $(OBJDIR)/g_editor_c7a43e42.o \
  $(OBJDIR)/g_graph_b93aa9a3.o \
  $(OBJDIR)/g_guiconnect_76e73ba4.o \
  $(OBJDIR)/g_hdial_d6a705ad.o \
  $(OBJDIR)/g_hslider_8b2fe8de.o \
  $(OBJDIR)/g_io_f6a02fbb.o \
  $(OBJDIR)/g_mycanvas_ddb3dd19.o \
  $(OBJDIR)/g_numbox_f7ae935a.o \
  $(OBJDIR)/g_readwrite_9053c19e.o \
  $(OBJDIR)/g_rtext_2c514b4.o \
  $(OBJDIR)/g_scalar_32f09901.o \
  $(OBJDIR)/g_template_1a1d520f.o \
  $(OBJDIR)/g_text_e1ad7a02.o \
  $(OBJDIR)/g_toggle_1f97fa69.o \
  $(OBJDIR)/g_traversal_b8014513.o \
  $(OBJDIR)/g_vdial_bb3e433b.o \
  $(OBJDIR)/g_vslider_a6edfaec.o \
  $(OBJDIR)/g_vumeter_a5a4a57f.o \
  $(OBJDIR)/m_atom_3157a260.o \
  $(OBJDIR)/m_binbuf_59c5a7db.o \
  $(OBJDIR)/m_class_5500c953.o \
  $(OBJDIR)/m_conf_347a4f73.o \
  $(OBJDIR)/m_glob_3b23d0c7.o \
  $(OBJDIR)/m_memory_fbdaeb90.o \
  $(OBJDIR)/m_obj_1b1aaa92.o \
  $(OBJDIR)/m_pd_e048c3.o \
  $(OBJDIR)/m_sched_9464eed2.o \
  $(OBJDIR)/s_audio_74503637.o \
  $(OBJDIR)/s_audio_dummy_cb209e20.o \
  $(OBJDIR)/s_file_a88a6d05.o \
  $(OBJDIR)/s_inter_106fd5bd.o \
  $(OBJDIR)/s_loader_499588dc.o \
  $(OBJDIR)/s_main_b40a6202.o \
  $(OBJDIR)/s_midi_b478c56a.o \
  $(OBJDIR)/s_midi_dummy_723fbb13.o \
  $(OBJDIR)/s_path_b92dd56e.o \
  $(OBJDIR)/s_print_88f7f34e.o \
  $(OBJDIR)/s_utf8_c2babdba.o \
  $(OBJDIR)/x_acoustics_ccbfba76.o \
  $(OBJDIR)/x_arithmetic_47c0cdce.o \
  $(OBJDIR)/x_array_5549a2ff.o \
  $(OBJDIR)/x_connective_b4ac63d2.o \
  $(OBJDIR)/x_gui_609719a1.o \
  $(OBJDIR)/x_interface_d15855f.o \
  $(OBJDIR)/x_list_ba30c802.o \
  $(OBJDIR)/x_midi_bbdea5c5.o \
  $(OBJDIR)/x_misc_bbe560d0.o \
  $(OBJDIR)/x_net_60f2a183.o \
  $(OBJDIR)/x_scalar_6bd11c10.o \
  $(OBJDIR)/x_text_c7a174d1.o \
  $(OBJDIR)/x_time_c7d49a71.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_audio_basics_4f86222c.o \
  $(OBJDIR)/juce_audio_processors_4fc0fe4.o \
  $(OBJDIR)/juce_core_d990830e.o \
  $(OBJDIR)/juce_data_structures_aa53984a.o \
  $(OBJDIR)/juce_events_e5eeb882.o \
  $(OBJDIR)/juce_graphics_369f86e6.o \
  $(OBJDIR)/juce_gui_basics_39990b62.o \
  $(OBJDIR)/juce_gui_extra_302aad6a.o \
  $(OBJDIR)/juce_PluginUtilities_829ccaf6.o \
  $(OBJDIR)/juce_VST_Wrapper_d073fbff.o \
  $(OBJDIR)/juce_VST3_Wrapper_8cff317d.o \

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

$(OBJDIR)/LookAndFeel_40552bdf.o: ../../Source/LookAndFeel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LookAndFeel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InstanceProcessor_bc7e525e.o: ../../Source/InstanceProcessor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InstanceProcessor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/InstanceEditor_fa2c28eb.o: ../../Source/InstanceEditor.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling InstanceEditor.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Gui_2b5c821c.o: ../../Source/Gui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Gui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiWindow_fc7f58ec.o: ../../Source/GuiWindow.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiWindow.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiAbout_73a909b.o: ../../Source/GuiAbout.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiAbout.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiConsole_b1a18b25.o: ../../Source/GuiConsole.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiConsole.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiFlowerButton_762682a9.o: ../../Source/GuiFlowerButton.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiFlowerButton.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiPatcher_633be1c3.o: ../../Source/GuiPatcher.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiPatcher.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiComment_a154d02d.o: ../../Source/GuiComment.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiComment.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiLabel_32dae082.o: ../../Source/GuiLabel.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiLabel.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiNumbox_87800701.o: ../../Source/GuiNumbox.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiNumbox.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiSlider_cf6a155d.o: ../../Source/GuiSlider.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiSlider.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiToggle_5aabe650.o: ../../Source/GuiToggle.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiToggle.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiRadio_1d3f9a09.o: ../../Source/GuiRadio.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiRadio.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/GuiParameter_1f209e37.o: ../../Source/GuiParameter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling GuiParameter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Pd_51c89d7d.o: ../../Source/Pd.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Pd.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PdGui_8982f688.o: ../../Source/PdGui.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PdGui.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PdPatch_eded9115.o: ../../Source/PdPatch.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PdPatch.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/PdInstance_9098ebb2.o: ../../Source/PdInstance.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling PdInstance.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/bob~_dea63fa8.o: ../../ThirdParty/PureData/extra/bob~/bob~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling bob~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/bonk~_1c54edf2.o: ../../ThirdParty/PureData/extra/bonk~/bonk~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling bonk~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/choice_9a48dd28.o: ../../ThirdParty/PureData/extra/choice/choice.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling choice.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vexp_42c95f1e.o: ../../ThirdParty/PureData/extra/expr~/vexp.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vexp.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vexp_fun_46a72f5e.o: ../../ThirdParty/PureData/extra/expr~/vexp_fun.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vexp_fun.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/vexp_if_a8aa2e8.o: ../../ThirdParty/PureData/extra/expr~/vexp_if.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling vexp_if.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/fiddle~_d178694e.o: ../../ThirdParty/PureData/extra/fiddle~/fiddle~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling fiddle~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/loop~_d8d5c53e.o: ../../ThirdParty/PureData/extra/loop~/loop~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling loop~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/lrshift~_770f74c8.o: ../../ThirdParty/PureData/extra/lrshift~/lrshift~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling lrshift~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/pique_a2bbb35a.o: ../../ThirdParty/PureData/extra/pique/pique.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling pique.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sigmund~_e0efd768.o: ../../ThirdParty/PureData/extra/sigmund~/sigmund~.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sigmund~.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/stdout_6bc4f9e8.o: ../../ThirdParty/PureData/extra/stdout/stdout.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling stdout.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_arithmetic_a26d0d62.o: ../../ThirdParty/PureData/src/d_arithmetic.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_arithmetic.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_array_bff0f6eb.o: ../../ThirdParty/PureData/src/d_array.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_array.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_ctl_3e61b16d.o: ../../ThirdParty/PureData/src/d_ctl.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_ctl.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_dac_3e670418.o: ../../ThirdParty/PureData/src/d_dac.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_dac.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_delay_48201b95.o: ../../ThirdParty/PureData/src/d_delay.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_delay.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_fft_3e85b8c6.o: ../../ThirdParty/PureData/src/d_fft.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_fft.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_fft_fftsg_20e099cf.o: ../../ThirdParty/PureData/src/d_fft_fftsg.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_fft_fftsg.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_filter_60423e30.o: ../../ThirdParty/PureData/src/d_filter.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_filter.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_global_6af5179b.o: ../../ThirdParty/PureData/src/d_global.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_global.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_math_9dddaa80.o: ../../ThirdParty/PureData/src/d_math.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_math.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_misc_9e4ddf64.o: ../../ThirdParty/PureData/src/d_misc.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_misc.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_osc_3f0a3551.o: ../../ThirdParty/PureData/src/d_osc.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_osc.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_resample_72c3aa55.o: ../../ThirdParty/PureData/src/d_resample.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_resample.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_soundfile_871e089d.o: ../../ThirdParty/PureData/src/d_soundfile.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_soundfile.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/d_ugen_abd24173.o: ../../ThirdParty/PureData/src/d_ugen.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling d_ugen.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_all_guis_13eaa90b.o: ../../ThirdParty/PureData/src/g_all_guis.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_all_guis.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_array_7cbe43ee.o: ../../ThirdParty/PureData/src/g_array.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_array.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_bang_c2b9244d.o: ../../ThirdParty/PureData/src/g_bang.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_bang.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_canvas_61cd436d.o: ../../ThirdParty/PureData/src/g_canvas.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_canvas.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_editor_c7a43e42.o: ../../ThirdParty/PureData/src/g_editor.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_editor.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_graph_b93aa9a3.o: ../../ThirdParty/PureData/src/g_graph.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_graph.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_guiconnect_76e73ba4.o: ../../ThirdParty/PureData/src/g_guiconnect.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_guiconnect.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_hdial_d6a705ad.o: ../../ThirdParty/PureData/src/g_hdial.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_hdial.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_hslider_8b2fe8de.o: ../../ThirdParty/PureData/src/g_hslider.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_hslider.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_io_f6a02fbb.o: ../../ThirdParty/PureData/src/g_io.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_io.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_mycanvas_ddb3dd19.o: ../../ThirdParty/PureData/src/g_mycanvas.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_mycanvas.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_numbox_f7ae935a.o: ../../ThirdParty/PureData/src/g_numbox.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_numbox.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_readwrite_9053c19e.o: ../../ThirdParty/PureData/src/g_readwrite.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_readwrite.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_rtext_2c514b4.o: ../../ThirdParty/PureData/src/g_rtext.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_rtext.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_scalar_32f09901.o: ../../ThirdParty/PureData/src/g_scalar.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_scalar.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_template_1a1d520f.o: ../../ThirdParty/PureData/src/g_template.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_template.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_text_e1ad7a02.o: ../../ThirdParty/PureData/src/g_text.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_text.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_toggle_1f97fa69.o: ../../ThirdParty/PureData/src/g_toggle.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_toggle.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_traversal_b8014513.o: ../../ThirdParty/PureData/src/g_traversal.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_traversal.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_vdial_bb3e433b.o: ../../ThirdParty/PureData/src/g_vdial.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_vdial.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_vslider_a6edfaec.o: ../../ThirdParty/PureData/src/g_vslider.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_vslider.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/g_vumeter_a5a4a57f.o: ../../ThirdParty/PureData/src/g_vumeter.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling g_vumeter.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_atom_3157a260.o: ../../ThirdParty/PureData/src/m_atom.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_atom.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_binbuf_59c5a7db.o: ../../ThirdParty/PureData/src/m_binbuf.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_binbuf.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_class_5500c953.o: ../../ThirdParty/PureData/src/m_class.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_class.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_conf_347a4f73.o: ../../ThirdParty/PureData/src/m_conf.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_conf.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_glob_3b23d0c7.o: ../../ThirdParty/PureData/src/m_glob.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_glob.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_memory_fbdaeb90.o: ../../ThirdParty/PureData/src/m_memory.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_memory.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_obj_1b1aaa92.o: ../../ThirdParty/PureData/src/m_obj.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_obj.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_pd_e048c3.o: ../../ThirdParty/PureData/src/m_pd.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_pd.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/m_sched_9464eed2.o: ../../ThirdParty/PureData/src/m_sched.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling m_sched.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_audio_74503637.o: ../../ThirdParty/PureData/src/s_audio.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_audio.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_audio_dummy_cb209e20.o: ../../ThirdParty/PureData/src/s_audio_dummy.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_audio_dummy.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_file_a88a6d05.o: ../../ThirdParty/PureData/src/s_file.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_file.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_inter_106fd5bd.o: ../../ThirdParty/PureData/src/s_inter.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_inter.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_loader_499588dc.o: ../../ThirdParty/PureData/src/s_loader.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_loader.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_main_b40a6202.o: ../../ThirdParty/PureData/src/s_main.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_main.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_midi_b478c56a.o: ../../ThirdParty/PureData/src/s_midi.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_midi.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_midi_dummy_723fbb13.o: ../../ThirdParty/PureData/src/s_midi_dummy.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_midi_dummy.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_path_b92dd56e.o: ../../ThirdParty/PureData/src/s_path.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_path.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_print_88f7f34e.o: ../../ThirdParty/PureData/src/s_print.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_print.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/s_utf8_c2babdba.o: ../../ThirdParty/PureData/src/s_utf8.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling s_utf8.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_acoustics_ccbfba76.o: ../../ThirdParty/PureData/src/x_acoustics.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_acoustics.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_arithmetic_47c0cdce.o: ../../ThirdParty/PureData/src/x_arithmetic.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_arithmetic.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_array_5549a2ff.o: ../../ThirdParty/PureData/src/x_array.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_array.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_connective_b4ac63d2.o: ../../ThirdParty/PureData/src/x_connective.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_connective.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_gui_609719a1.o: ../../ThirdParty/PureData/src/x_gui.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_gui.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_interface_d15855f.o: ../../ThirdParty/PureData/src/x_interface.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_interface.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_list_ba30c802.o: ../../ThirdParty/PureData/src/x_list.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_list.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_midi_bbdea5c5.o: ../../ThirdParty/PureData/src/x_midi.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_midi.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_misc_bbe560d0.o: ../../ThirdParty/PureData/src/x_misc.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_misc.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_net_60f2a183.o: ../../ThirdParty/PureData/src/x_net.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_net.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_scalar_6bd11c10.o: ../../ThirdParty/PureData/src/x_scalar.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_scalar.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_text_c7a174d1.o: ../../ThirdParty/PureData/src/x_text.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_text.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/x_time_c7d49a71.o: ../../ThirdParty/PureData/src/x_time.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling x_time.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_basics_4f86222c.o: ../../ThirdParty/Juce/modules/juce_audio_basics/juce_audio_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_audio_processors_4fc0fe4.o: ../../ThirdParty/Juce/modules/juce_audio_processors/juce_audio_processors.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_audio_processors.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_d990830e.o: ../../ThirdParty/Juce/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_aa53984a.o: ../../ThirdParty/Juce/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_e5eeb882.o: ../../ThirdParty/Juce/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_369f86e6.o: ../../ThirdParty/Juce/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_39990b62.o: ../../ThirdParty/Juce/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_302aad6a.o: ../../ThirdParty/Juce/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_PluginUtilities_829ccaf6.o: ../../ThirdParty/Juce/modules/juce_audio_plugin_client/utility/juce_PluginUtilities.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_PluginUtilities.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST_Wrapper_d073fbff.o: ../../ThirdParty/Juce/modules/juce_audio_plugin_client/VST/juce_VST_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_VST3_Wrapper_8cff317d.o: ../../ThirdParty/Juce/modules/juce_audio_plugin_client/VST3/juce_VST3_Wrapper.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_VST3_Wrapper.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
