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

JUCE_ARCH_LABEL := $(shell uname -m)

ifeq ($(CONFIG),Debug)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Debug
  JUCE_OUTDIR := ../../../Plugins

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DPD_INTERNAL=1" "-DJUCE_VST3_CAN_REPLACE_VST2=0" "-DPD=1" "-DPDINSTANCE=1" "-DCAMOMILE=1" "-DHAVE_UNISTD_H=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.7" "-DJUCE_APP_VERSION_HEX=0x10007" $(shell pkg-config --cflags freetype2) -pthread -I../../../Juce/modules/juce_audio_processors/format_types/VST3_SDK -I../../../Dependencies/Vst2 -I../../JuceLibraryCode -I../../../Juce/modules -I../../../Dependencies/LibPd/pure-data/src -I../../../Dependencies/LibPd/libpd_wrapper -I../../../Dependencies/LibPd/libpd_wrapper/util -I../../../Dependencies/LibPd/cpp -I../../../Source/Pd/ELSE -I../../../Source/Pd/ELSE/shared $(CPPFLAGS)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := CamomileFx.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/CamomileFx.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := CamomileFx.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L../../../Dependencies/LibPdBuild $(shell pkg-config --libs freetype2) -fvisibility=hidden -lrt -ldl -lpthread -lpd-multi $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

ifeq ($(CONFIG),Release)
  JUCE_BINDIR := build
  JUCE_LIBDIR := build
  JUCE_OBJDIR := build/intermediate/Release
  JUCE_OUTDIR := ../../../Plugins

  ifeq ($(TARGET_ARCH),)
    TARGET_ARCH := 
  endif

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DPD_INTERNAL=1" "-DJUCE_VST3_CAN_REPLACE_VST2=0" "-DPD=1" "-DPDINSTANCE=1" "-DCAMOMILE=1" "-DHAVE_UNISTD_H=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.7" "-DJUCE_APP_VERSION_HEX=0x10007" $(shell pkg-config --cflags freetype2) -pthread -I../../../Juce/modules/juce_audio_processors/format_types/VST3_SDK -I../../../Dependencies/Vst2 -I../../JuceLibraryCode -I../../../Juce/modules -I../../../Dependencies/LibPd/pure-data/src -I../../../Dependencies/LibPd/libpd_wrapper -I../../../Dependencies/LibPd/libpd_wrapper/util -I../../../Dependencies/LibPd/cpp -I../../../Source/Pd/ELSE -I../../../Source/Pd/ELSE/shared $(CPPFLAGS)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := CamomileFx.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/CamomileFx.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := CamomileFx.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 $(CFLAGS)
  JUCE_CXXFLAGS += $(JUCE_CFLAGS) -std=c++11 $(CXXFLAGS)
  JUCE_LDFLAGS += $(TARGET_ARCH) -L$(JUCE_BINDIR) -L$(JUCE_LIBDIR) -L../../../Dependencies/LibPdBuild $(shell pkg-config --libs freetype2) -fvisibility=hidden -lrt -ldl -lpthread -lpd-multi $(LDFLAGS)

  CLEANCMD = rm -rf $(JUCE_OUTDIR)/$(TARGET) $(JUCE_OBJDIR)
endif

OBJECTS_ALL := \

OBJECTS_VST3 := \
  $(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST3_dd633589.o \

OBJECTS_SHARED_CODE := \
  $(JUCE_OBJDIR)/PluginProcessor_319d19ef.o \
  $(JUCE_OBJDIR)/PluginProcessorBuses_ff06f3c9.o \
  $(JUCE_OBJDIR)/PluginProcessorReceive_8862f77e.o \
  $(JUCE_OBJDIR)/PluginEditor_ef07f2fa.o \
  $(JUCE_OBJDIR)/PluginEditorComponents_6d39f4f0.o \
  $(JUCE_OBJDIR)/PluginEditorConsole_207d0487.o \
  $(JUCE_OBJDIR)/PluginEditorInteraction_f8a5a242.o \
  $(JUCE_OBJDIR)/PluginEditorObject_7e10b319.o \
  $(JUCE_OBJDIR)/PluginEnvironment_564e0cf0.o \
  $(JUCE_OBJDIR)/PluginParameter_9c951d86.o \
  $(JUCE_OBJDIR)/PluginParser_125664ac.o \
  $(JUCE_OBJDIR)/PluginLookAndFeel_1523addb.o \
  $(JUCE_OBJDIR)/buffer_f4d93f9f.o \
  $(JUCE_OBJDIR)/file_507c945b.o \
  $(JUCE_OBJDIR)/grow_52b1e132.o \
  $(JUCE_OBJDIR)/magic_2376edb8.o \
  $(JUCE_OBJDIR)/mifi_5c6bd57e.o \
  $(JUCE_OBJDIR)/random_5e7e7b62.o \
  $(JUCE_OBJDIR)/s_utf8_6961b7dc.o \
  $(JUCE_OBJDIR)/above~_73cf3b36.o \
  $(JUCE_OBJDIR)/add~_f904d7b2.o \
  $(JUCE_OBJDIR)/adsr~_286530f1.o \
  $(JUCE_OBJDIR)/allpass.2nd~_48f4a1c7.o \
  $(JUCE_OBJDIR)/allpass.rev~_b5b424ac.o \
  $(JUCE_OBJDIR)/args_f9cb5492.o \
  $(JUCE_OBJDIR)/asr~_f9de9573.o \
  $(JUCE_OBJDIR)/autofade~_16c23568.o \
  $(JUCE_OBJDIR)/autofade2~_c16311ac.o \
  $(JUCE_OBJDIR)/balance~_9c647397.o \
  $(JUCE_OBJDIR)/bandpass~_b77a986d.o \
  $(JUCE_OBJDIR)/bandstop~_765fa2dc.o \
  $(JUCE_OBJDIR)/bend.in_7b52fc6f.o \
  $(JUCE_OBJDIR)/bend.out_ef654dce.o \
  $(JUCE_OBJDIR)/bicoeff_eabe0487.o \
  $(JUCE_OBJDIR)/biquads~_51cfe1ae.o \
  $(JUCE_OBJDIR)/blocksize~_9dc36725.o \
  $(JUCE_OBJDIR)/break_7461fa34.o \
  $(JUCE_OBJDIR)/brown~_2a264afd.o \
  $(JUCE_OBJDIR)/button_d13729a7.o \
  $(JUCE_OBJDIR)/canvas.active_c5faba51.o \
  $(JUCE_OBJDIR)/canvas.bounds_aa9a0240.o \
  $(JUCE_OBJDIR)/canvas.edit_2170b5d5.o \
  $(JUCE_OBJDIR)/canvas.gop_d7eb1567.o \
  $(JUCE_OBJDIR)/canvas.mouse_c7469bc4.o \
  $(JUCE_OBJDIR)/canvas.name_30a3a616.o \
  $(JUCE_OBJDIR)/canvas.pos_d869f433.o \
  $(JUCE_OBJDIR)/canvas.setname_3d53708c.o \
  $(JUCE_OBJDIR)/canvas.vis_d8bbc6ff.o \
  $(JUCE_OBJDIR)/canvas.wname_d5738361.o \
  $(JUCE_OBJDIR)/canvas.zoom_45e41d5e.o \
  $(JUCE_OBJDIR)/ceil_fc7ea2ba.o \
  $(JUCE_OBJDIR)/ceil~_9356dace.o \
  $(JUCE_OBJDIR)/cents2ratio_6b7d9299.o \
  $(JUCE_OBJDIR)/cents2ratio~_435e6cf.o \
  $(JUCE_OBJDIR)/chance_68a11d29.o \
  $(JUCE_OBJDIR)/chance~_ab83ae3f.o \
  $(JUCE_OBJDIR)/changed_abbbaaa9.o \
  $(JUCE_OBJDIR)/changed~_cbbad0bf.o \
  $(JUCE_OBJDIR)/changed2~_ab7de135.o \
  $(JUCE_OBJDIR)/click_9f44687d.o \
  $(JUCE_OBJDIR)/clipnoise~_d6ddfde9.o \
  $(JUCE_OBJDIR)/cmul~_a1a6b9d2.o \
  $(JUCE_OBJDIR)/coin_fd0b9546.o \
  $(JUCE_OBJDIR)/coin~_a46839c2.o \
  $(JUCE_OBJDIR)/colors_edc72865.o \
  $(JUCE_OBJDIR)/comb.filt~_7634a89b.o \
  $(JUCE_OBJDIR)/comb.rev~_bd3fe1fd.o \
  $(JUCE_OBJDIR)/common.div_775fe583.o \
  $(JUCE_OBJDIR)/cosine~_32eeda5a.o \
  $(JUCE_OBJDIR)/crackle~_57b91660.o \
  $(JUCE_OBJDIR)/crossover~_e795a25f.o \
  $(JUCE_OBJDIR)/ctl.in_f2ae2ecd.o \
  $(JUCE_OBJDIR)/ctl.out_63706730.o \
  $(JUCE_OBJDIR)/cusp~_af332144.o \
  $(JUCE_OBJDIR)/decay~_348c75f9.o \
  $(JUCE_OBJDIR)/decay2~_5ce0e33b.o \
  $(JUCE_OBJDIR)/detect~_e5e63070.o \
  $(JUCE_OBJDIR)/dir_94983a42.o \
  $(JUCE_OBJDIR)/dollsym_5a558191.o \
  $(JUCE_OBJDIR)/downsample~_4c4121a7.o \
  $(JUCE_OBJDIR)/drive~_ef996229.o \
  $(JUCE_OBJDIR)/dust~_e41b2e01.o \
  $(JUCE_OBJDIR)/dust2~_9f292c33.o \
  $(JUCE_OBJDIR)/else_4f69ee.o \
  $(JUCE_OBJDIR)/envgen~_8e64cfd0.o \
  $(JUCE_OBJDIR)/eq~_94aa21c7.o \
  $(JUCE_OBJDIR)/f2s~_fed34d2c.o \
  $(JUCE_OBJDIR)/factor_31bce884.o \
  $(JUCE_OBJDIR)/fader~_329feabd.o \
  $(JUCE_OBJDIR)/fbdelay~_92e1644c.o \
  $(JUCE_OBJDIR)/fbsine~_a94ce00a.o \
  $(JUCE_OBJDIR)/fbsine2~_802dbb4a.o \
  $(JUCE_OBJDIR)/fdn.rev~_77335cae.o \
  $(JUCE_OBJDIR)/ffdelay~_e3f32050.o \
  $(JUCE_OBJDIR)/float2bits_bf9bd351.o \
  $(JUCE_OBJDIR)/float2sig~_dc987658.o \
  $(JUCE_OBJDIR)/floor_3e513601.o \
  $(JUCE_OBJDIR)/floor~_8bd6b067.o \
  $(JUCE_OBJDIR)/fold_22b56b6.o \
  $(JUCE_OBJDIR)/fold~_4340a652.o \
  $(JUCE_OBJDIR)/fontsize_4f06ffc5.o \
  $(JUCE_OBJDIR)/format_2f83dd2c.o \
  $(JUCE_OBJDIR)/freq.shift~_e7c84ce7.o \
  $(JUCE_OBJDIR)/function_4707a4cd.o \
  $(JUCE_OBJDIR)/function~_99ee1b1b.o \
  $(JUCE_OBJDIR)/gate2imp~_befc5e2e.o \
  $(JUCE_OBJDIR)/gbman~_de88c0f4.o \
  $(JUCE_OBJDIR)/giga.rev~_759e3f62.o \
  $(JUCE_OBJDIR)/glide~_e8d9de2e.o \
  $(JUCE_OBJDIR)/glide2~_324081a6.o \
  $(JUCE_OBJDIR)/gray~_7cb3f4b0.o \
  $(JUCE_OBJDIR)/gui_94c7d370.o \
  $(JUCE_OBJDIR)/henon~_e796c143.o \
  $(JUCE_OBJDIR)/highpass~_68c7fc60.o \
  $(JUCE_OBJDIR)/highshelf~_41d6752b.o \
  $(JUCE_OBJDIR)/hot_94d35a02.o \
  $(JUCE_OBJDIR)/hz2rad_d83ad46a.o \
  $(JUCE_OBJDIR)/hz2rad~_2f20df1e.o \
  $(JUCE_OBJDIR)/ikeda~_7ce0c8b3.o \
  $(JUCE_OBJDIR)/imp~_72fe4a7.o \
  $(JUCE_OBJDIR)/imp2~_deab4a4d.o \
  $(JUCE_OBJDIR)/impseq~_4eab8000.o \
  $(JUCE_OBJDIR)/impulse~_fc94dade.o \
  $(JUCE_OBJDIR)/impulse2~_95e51af6.o \
  $(JUCE_OBJDIR)/initmess_85c097fd.o \
  $(JUCE_OBJDIR)/int~_73fcda4.o \
  $(JUCE_OBJDIR)/keyboard_fedd1c.o \
  $(JUCE_OBJDIR)/lag~_ba13d21.o \
  $(JUCE_OBJDIR)/lag2~_68650113.o \
  $(JUCE_OBJDIR)/lastvalue~_f1e62978.o \
  $(JUCE_OBJDIR)/latoocarfian~_2ae2466e.o \
  $(JUCE_OBJDIR)/lb_3e9d0eeb.o \
  $(JUCE_OBJDIR)/lfnoise~_b94bde13.o \
  $(JUCE_OBJDIR)/limit_76792df0.o \
  $(JUCE_OBJDIR)/lincong~_545eafd.o \
  $(JUCE_OBJDIR)/loadbanger_8a03c580.o \
  $(JUCE_OBJDIR)/logistic~_9c7f2f93.o \
  $(JUCE_OBJDIR)/loop_c69f499.o \
  $(JUCE_OBJDIR)/lorenz~_2da6af71.o \
  $(JUCE_OBJDIR)/lowpass~_bde42c6e.o \
  $(JUCE_OBJDIR)/lowshelf~_904046dd.o \
  $(JUCE_OBJDIR)/match~_24f4f40e.o \
  $(JUCE_OBJDIR)/median~_d49edca9.o \
  $(JUCE_OBJDIR)/merge_a4d15b2d.o \
  $(JUCE_OBJDIR)/message_ff293f3c.o \
  $(JUCE_OBJDIR)/messbox_ff3b4108.o \
  $(JUCE_OBJDIR)/midi_dc525d6.o \
  $(JUCE_OBJDIR)/mouse_b6118c5a.o \
  $(JUCE_OBJDIR)/mov.avg~_a715fbfb.o \
  $(JUCE_OBJDIR)/mov.rms~_c39eff75.o \
  $(JUCE_OBJDIR)/mtx~_e698ea2.o \
  $(JUCE_OBJDIR)/nbang_d3acb31b.o \
  $(JUCE_OBJDIR)/note_fd5c267.o \
  $(JUCE_OBJDIR)/note.in_bc6e2d56.o \
  $(JUCE_OBJDIR)/note.out_d1b039c7.o \
  $(JUCE_OBJDIR)/nyquist~_1802b918.o \
  $(JUCE_OBJDIR)/op~_95369872.o \
  $(JUCE_OBJDIR)/openfile_7f5b143b.o \
  $(JUCE_OBJDIR)/pack2_3bde5bee.o \
  $(JUCE_OBJDIR)/pad_953d7cc8.o \
  $(JUCE_OBJDIR)/pan2~_3c60929e.o \
  $(JUCE_OBJDIR)/pan4~_3c617b5c.o \
  $(JUCE_OBJDIR)/panic_3c792dac.o \
  $(JUCE_OBJDIR)/parabolic~_e1a4ca1a.o \
  $(JUCE_OBJDIR)/peak~_4296acb4.o \
  $(JUCE_OBJDIR)/pgm.in_8b214c72.o \
  $(JUCE_OBJDIR)/pgm.out_d960fe2b.o \
  $(JUCE_OBJDIR)/pic_95411bff.o \
  $(JUCE_OBJDIR)/pimp~_4a156f17.o \
  $(JUCE_OBJDIR)/pinknoise~_5c4e560f.o \
  $(JUCE_OBJDIR)/pluck~_a4333c32.o \
  $(JUCE_OBJDIR)/pmosc~_cfba38d1.o \
  $(JUCE_OBJDIR)/properties_7bf89368.o \
  $(JUCE_OBJDIR)/pulse~_71ce71ba.o \
  $(JUCE_OBJDIR)/pulsecount~_2ea6d11d.o \
  $(JUCE_OBJDIR)/pulsediv~_9e10689b.o \
  $(JUCE_OBJDIR)/quad~_92c7434c.o \
  $(JUCE_OBJDIR)/quantizer_ef8bd216.o \
  $(JUCE_OBJDIR)/quantizer~_1ef96f2.o \
  $(JUCE_OBJDIR)/rad2hz_e5abbc4.o \
  $(JUCE_OBJDIR)/rad2hz~_bcfde304.o \
  $(JUCE_OBJDIR)/ramp~_a63b20a1.o \
  $(JUCE_OBJDIR)/rampnoise~_b598c4ab.o \
  $(JUCE_OBJDIR)/rand.f_22112092.o \
  $(JUCE_OBJDIR)/rand.f~_201417f6.o \
  $(JUCE_OBJDIR)/rand.i_22112bd5.o \
  $(JUCE_OBJDIR)/rand.i~_20157513.o \
  $(JUCE_OBJDIR)/rand.seq_e31bb08b.o \
  $(JUCE_OBJDIR)/randpulse~_c8f348df.o \
  $(JUCE_OBJDIR)/randpulse2~_55546d15.o \
  $(JUCE_OBJDIR)/range~_2254c196.o \
  $(JUCE_OBJDIR)/ratio2cents_e08d6299.o \
  $(JUCE_OBJDIR)/ratio2cents~_312016cf.o \
  $(JUCE_OBJDIR)/receiver_573ef124.o \
  $(JUCE_OBJDIR)/rescale_c934262c.o \
  $(JUCE_OBJDIR)/rescale~_5d51c59c.o \
  $(JUCE_OBJDIR)/resonant~_c8dc29eb.o \
  $(JUCE_OBJDIR)/resonant2~_5287ad89.o \
  $(JUCE_OBJDIR)/rint_165215f2.o \
  $(JUCE_OBJDIR)/rint~_b3f1ce96.o \
  $(JUCE_OBJDIR)/rms~_168cdf5b.o \
  $(JUCE_OBJDIR)/rotate~_a855eb8.o \
  $(JUCE_OBJDIR)/routeall_8145afad.o \
  $(JUCE_OBJDIR)/router_1394effe.o \
  $(JUCE_OBJDIR)/routetype_c8962538.o \
  $(JUCE_OBJDIR)/s2f~_14fc646c.o \
  $(JUCE_OBJDIR)/saw~_179a6f6a.o \
  $(JUCE_OBJDIR)/saw2~_db9217ea.o \
  $(JUCE_OBJDIR)/schmitt~_d1820e3f.o \
  $(JUCE_OBJDIR)/selector_e81e3f14.o \
  $(JUCE_OBJDIR)/separate_cc990d58.o \
  $(JUCE_OBJDIR)/sequencer~_e08be182.o \
  $(JUCE_OBJDIR)/sh~_956b537e.o \
  $(JUCE_OBJDIR)/shaper~_f3566762.o \
  $(JUCE_OBJDIR)/sig2float~_edae9c98.o \
  $(JUCE_OBJDIR)/sin~_1807141b.o \
  $(JUCE_OBJDIR)/sine~_e8d13846.o \
  $(JUCE_OBJDIR)/slice_eda80607.o \
  $(JUCE_OBJDIR)/sort_185d4d13.o \
  $(JUCE_OBJDIR)/spread_aa6867a8.o \
  $(JUCE_OBJDIR)/spread~_a2a5b3a0.o \
  $(JUCE_OBJDIR)/square~_a35633b6.o \
  $(JUCE_OBJDIR)/sr~_956fdf34.o \
  $(JUCE_OBJDIR)/standard~_c8904a16.o \
  $(JUCE_OBJDIR)/status~_d999d0c1.o \
  $(JUCE_OBJDIR)/stepnoise~_27f82565.o \
  $(JUCE_OBJDIR)/susloop~_8a0d5b5e.o \
  $(JUCE_OBJDIR)/suspedal_4bf3ba7e.o \
  $(JUCE_OBJDIR)/svfilter~_56009078.o \
  $(JUCE_OBJDIR)/symbol2any_1576887.o \
  $(JUCE_OBJDIR)/t2_3e9ffdb3.o \
  $(JUCE_OBJDIR)/table~_dde36965.o \
  $(JUCE_OBJDIR)/tabplayer~_ac08c57d.o \
  $(JUCE_OBJDIR)/tabwriter~_c7d87aab.o \
  $(JUCE_OBJDIR)/tempo~_c47e8ef8.o \
  $(JUCE_OBJDIR)/timed.gate~_e657e991.o \
  $(JUCE_OBJDIR)/toggleff~_e7d5325f.o \
  $(JUCE_OBJDIR)/touch.in_e8dd2829.o \
  $(JUCE_OBJDIR)/touch.out_33209954.o \
  $(JUCE_OBJDIR)/tri~_1a387a68.o \
  $(JUCE_OBJDIR)/trig.delay~_b9d0f22.o \
  $(JUCE_OBJDIR)/trig.delay2~_67e36f32.o \
  $(JUCE_OBJDIR)/trigger2_9c0ab1ef.o \
  $(JUCE_OBJDIR)/trighold~_2b059138.o \
  $(JUCE_OBJDIR)/unmerge_f3dd9e74.o \
  $(JUCE_OBJDIR)/voices_9daff036.o \
  $(JUCE_OBJDIR)/vsaw~_97e55d60.o \
  $(JUCE_OBJDIR)/vu~_959b82d4.o \
  $(JUCE_OBJDIR)/wavetable~_9210735e.o \
  $(JUCE_OBJDIR)/wrap2_cb12741d.o \
  $(JUCE_OBJDIR)/wrap2~_973d35cb.o \
  $(JUCE_OBJDIR)/wt~_95a925f6.o \
  $(JUCE_OBJDIR)/xfade~_83c1b07f.o \
  $(JUCE_OBJDIR)/xgate~_b98963d0.o \
  $(JUCE_OBJDIR)/xgate2~_7781b044.o \
  $(JUCE_OBJDIR)/xmod~_f8316629.o \
  $(JUCE_OBJDIR)/xmod2~_dd9f90b.o \
  $(JUCE_OBJDIR)/xselect~_66eb7fff.o \
  $(JUCE_OBJDIR)/xselect2~_766319f5.o \
  $(JUCE_OBJDIR)/zerocross~_aa2cb65b.o \
  $(JUCE_OBJDIR)/PdInstance_c9d7d554.o \
  $(JUCE_OBJDIR)/PdPatch_2b25dab3.o \
  $(JUCE_OBJDIR)/PdGui_34dd0fa6.o \
  $(JUCE_OBJDIR)/PdArray_f4d0bc44.o \
  $(JUCE_OBJDIR)/PdObject_2fcb197e.o \
  $(JUCE_OBJDIR)/x_libpd_multi_a98b54cb.o \
  $(JUCE_OBJDIR)/x_libpd_extra_utils_b8efa354.o \
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

.PHONY: clean all strip VST3

all : VST3

VST3 : $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3)


$(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) : $(OBJECTS_VST3) $(RESOURCES) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors freetype2
	@echo Linking "CamomileFx - VST3"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)/$(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)
	$(V_AT)$(CXX) -o $(JUCE_OUTDIR)/$(JUCE_TARGET_VST3) $(OBJECTS_VST3) $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(JUCE_LDFLAGS) $(JUCE_LDFLAGS_VST3) $(RESOURCES) $(TARGET_ARCH)
	-$(V_AT)mkdir -p $(JUCE_VST3DESTDIR)
	-$(V_AT)cp -R $(JUCE_COPYCMD_VST3)

$(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) : $(OBJECTS_SHARED_CODE) $(RESOURCES)
	@command -v pkg-config >/dev/null 2>&1 || { echo >&2 "pkg-config not installed. Please, install it."; exit 1; }
	@pkg-config --print-errors freetype2
	@echo Linking "CamomileFx - Shared Code"
	-$(V_AT)mkdir -p $(JUCE_BINDIR)
	-$(V_AT)mkdir -p $(JUCE_LIBDIR)
	-$(V_AT)mkdir -p $(JUCE_OUTDIR)
	$(V_AT)$(AR) -rcs $(JUCE_OUTDIR)/$(JUCE_TARGET_SHARED_CODE) $(OBJECTS_SHARED_CODE)

$(JUCE_OBJDIR)/include_juce_audio_plugin_client_VST3_dd633589.o: ../../JuceLibraryCode/include_juce_audio_plugin_client_VST3.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling include_juce_audio_plugin_client_VST3.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_VST3) $(JUCE_CFLAGS_VST3) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessor_319d19ef.o: ../../../Source/PluginProcessor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessorBuses_ff06f3c9.o: ../../../Source/PluginProcessorBuses.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessorBuses.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginProcessorReceive_8862f77e.o: ../../../Source/PluginProcessorReceive.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginProcessorReceive.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditor_ef07f2fa.o: ../../../Source/PluginEditor.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditor.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditorComponents_6d39f4f0.o: ../../../Source/PluginEditorComponents.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditorComponents.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditorConsole_207d0487.o: ../../../Source/PluginEditorConsole.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditorConsole.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditorInteraction_f8a5a242.o: ../../../Source/PluginEditorInteraction.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditorInteraction.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEditorObject_7e10b319.o: ../../../Source/PluginEditorObject.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEditorObject.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginEnvironment_564e0cf0.o: ../../../Source/PluginEnvironment.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginEnvironment.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginParameter_9c951d86.o: ../../../Source/PluginParameter.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginParameter.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginParser_125664ac.o: ../../../Source/PluginParser.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginParser.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PluginLookAndFeel_1523addb.o: ../../../Source/PluginLookAndFeel.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PluginLookAndFeel.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/buffer_f4d93f9f.o: ../../../Source/Pd/ELSE/shared/buffer.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling buffer.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/file_507c945b.o: ../../../Source/Pd/ELSE/shared/file.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling file.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/grow_52b1e132.o: ../../../Source/Pd/ELSE/shared/grow.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling grow.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/magic_2376edb8.o: ../../../Source/Pd/ELSE/shared/magic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling magic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mifi_5c6bd57e.o: ../../../Source/Pd/ELSE/shared/mifi.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mifi.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/random_5e7e7b62.o: ../../../Source/Pd/ELSE/shared/random.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling random.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_utf8_6961b7dc.o: ../../../Source/Pd/ELSE/shared/s_utf8.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_utf8.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/above~_73cf3b36.o: ../../../Source/Pd/ELSE/above~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling above~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/add~_f904d7b2.o: ../../../Source/Pd/ELSE/add~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling add~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/adsr~_286530f1.o: ../../../Source/Pd/ELSE/adsr~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling adsr~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/allpass.2nd~_48f4a1c7.o: ../../../Source/Pd/ELSE/allpass.2nd~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling allpass.2nd~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/allpass.rev~_b5b424ac.o: ../../../Source/Pd/ELSE/allpass.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling allpass.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/args_f9cb5492.o: ../../../Source/Pd/ELSE/args.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling args.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/asr~_f9de9573.o: ../../../Source/Pd/ELSE/asr~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling asr~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/autofade~_16c23568.o: ../../../Source/Pd/ELSE/autofade~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling autofade~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/autofade2~_c16311ac.o: ../../../Source/Pd/ELSE/autofade2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling autofade2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/balance~_9c647397.o: ../../../Source/Pd/ELSE/balance~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling balance~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bandpass~_b77a986d.o: ../../../Source/Pd/ELSE/bandpass~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bandpass~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bandstop~_765fa2dc.o: ../../../Source/Pd/ELSE/bandstop~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bandstop~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bend.in_7b52fc6f.o: ../../../Source/Pd/ELSE/bend.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bend.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bend.out_ef654dce.o: ../../../Source/Pd/ELSE/bend.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bend.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bicoeff_eabe0487.o: ../../../Source/Pd/ELSE/bicoeff.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bicoeff.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/biquads~_51cfe1ae.o: ../../../Source/Pd/ELSE/biquads~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling biquads~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/blocksize~_9dc36725.o: ../../../Source/Pd/ELSE/blocksize~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling blocksize~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/break_7461fa34.o: ../../../Source/Pd/ELSE/break.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling break.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/brown~_2a264afd.o: ../../../Source/Pd/ELSE/brown~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling brown~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/button_d13729a7.o: ../../../Source/Pd/ELSE/button.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling button.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.active_c5faba51.o: ../../../Source/Pd/ELSE/canvas.active.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.active.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.bounds_aa9a0240.o: ../../../Source/Pd/ELSE/canvas.bounds.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.bounds.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.edit_2170b5d5.o: ../../../Source/Pd/ELSE/canvas.edit.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.edit.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.gop_d7eb1567.o: ../../../Source/Pd/ELSE/canvas.gop.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.gop.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.mouse_c7469bc4.o: ../../../Source/Pd/ELSE/canvas.mouse.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.mouse.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.name_30a3a616.o: ../../../Source/Pd/ELSE/canvas.name.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.name.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.pos_d869f433.o: ../../../Source/Pd/ELSE/canvas.pos.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.pos.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.setname_3d53708c.o: ../../../Source/Pd/ELSE/canvas.setname.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.setname.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.vis_d8bbc6ff.o: ../../../Source/Pd/ELSE/canvas.vis.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.vis.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.wname_d5738361.o: ../../../Source/Pd/ELSE/canvas.wname.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.wname.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.zoom_45e41d5e.o: ../../../Source/Pd/ELSE/canvas.zoom.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.zoom.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ceil_fc7ea2ba.o: ../../../Source/Pd/ELSE/ceil.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ceil.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ceil~_9356dace.o: ../../../Source/Pd/ELSE/ceil~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ceil~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cents2ratio_6b7d9299.o: ../../../Source/Pd/ELSE/cents2ratio.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cents2ratio.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cents2ratio~_435e6cf.o: ../../../Source/Pd/ELSE/cents2ratio~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cents2ratio~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/chance_68a11d29.o: ../../../Source/Pd/ELSE/chance.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling chance.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/chance~_ab83ae3f.o: ../../../Source/Pd/ELSE/chance~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling chance~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/changed_abbbaaa9.o: ../../../Source/Pd/ELSE/changed.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling changed.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/changed~_cbbad0bf.o: ../../../Source/Pd/ELSE/changed~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling changed~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/changed2~_ab7de135.o: ../../../Source/Pd/ELSE/changed2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling changed2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/click_9f44687d.o: ../../../Source/Pd/ELSE/click.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling click.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/clipnoise~_d6ddfde9.o: ../../../Source/Pd/ELSE/clipnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling clipnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cmul~_a1a6b9d2.o: ../../../Source/Pd/ELSE/cmul~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cmul~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/coin_fd0b9546.o: ../../../Source/Pd/ELSE/coin.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling coin.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/coin~_a46839c2.o: ../../../Source/Pd/ELSE/coin~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling coin~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/colors_edc72865.o: ../../../Source/Pd/ELSE/colors.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling colors.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/comb.filt~_7634a89b.o: ../../../Source/Pd/ELSE/comb.filt~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling comb.filt~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/comb.rev~_bd3fe1fd.o: ../../../Source/Pd/ELSE/comb.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling comb.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/common.div_775fe583.o: ../../../Source/Pd/ELSE/common.div.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling common.div.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cosine~_32eeda5a.o: ../../../Source/Pd/ELSE/cosine~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cosine~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/crackle~_57b91660.o: ../../../Source/Pd/ELSE/crackle~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling crackle~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/crossover~_e795a25f.o: ../../../Source/Pd/ELSE/crossover~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling crossover~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ctl.in_f2ae2ecd.o: ../../../Source/Pd/ELSE/ctl.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ctl.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ctl.out_63706730.o: ../../../Source/Pd/ELSE/ctl.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ctl.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cusp~_af332144.o: ../../../Source/Pd/ELSE/cusp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cusp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/decay~_348c75f9.o: ../../../Source/Pd/ELSE/decay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling decay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/decay2~_5ce0e33b.o: ../../../Source/Pd/ELSE/decay2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling decay2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/detect~_e5e63070.o: ../../../Source/Pd/ELSE/detect~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling detect~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dir_94983a42.o: ../../../Source/Pd/ELSE/dir.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dir.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dollsym_5a558191.o: ../../../Source/Pd/ELSE/dollsym.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dollsym.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/downsample~_4c4121a7.o: ../../../Source/Pd/ELSE/downsample~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling downsample~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/drive~_ef996229.o: ../../../Source/Pd/ELSE/drive~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling drive~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dust~_e41b2e01.o: ../../../Source/Pd/ELSE/dust~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dust~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dust2~_9f292c33.o: ../../../Source/Pd/ELSE/dust2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dust2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/else_4f69ee.o: ../../../Source/Pd/ELSE/else.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling else.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/envgen~_8e64cfd0.o: ../../../Source/Pd/ELSE/envgen~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling envgen~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/eq~_94aa21c7.o: ../../../Source/Pd/ELSE/eq~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling eq~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/f2s~_fed34d2c.o: ../../../Source/Pd/ELSE/f2s~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling f2s~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/factor_31bce884.o: ../../../Source/Pd/ELSE/factor.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling factor.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fader~_329feabd.o: ../../../Source/Pd/ELSE/fader~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fader~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fbdelay~_92e1644c.o: ../../../Source/Pd/ELSE/fbdelay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fbdelay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fbsine~_a94ce00a.o: ../../../Source/Pd/ELSE/fbsine~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fbsine~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fbsine2~_802dbb4a.o: ../../../Source/Pd/ELSE/fbsine2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fbsine2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fdn.rev~_77335cae.o: ../../../Source/Pd/ELSE/fdn.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fdn.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ffdelay~_e3f32050.o: ../../../Source/Pd/ELSE/ffdelay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ffdelay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/float2bits_bf9bd351.o: ../../../Source/Pd/ELSE/float2bits.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling float2bits.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/float2sig~_dc987658.o: ../../../Source/Pd/ELSE/float2sig~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling float2sig~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/floor_3e513601.o: ../../../Source/Pd/ELSE/floor.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling floor.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/floor~_8bd6b067.o: ../../../Source/Pd/ELSE/floor~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling floor~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fold_22b56b6.o: ../../../Source/Pd/ELSE/fold.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fold.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fold~_4340a652.o: ../../../Source/Pd/ELSE/fold~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fold~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fontsize_4f06ffc5.o: ../../../Source/Pd/ELSE/fontsize.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fontsize.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/format_2f83dd2c.o: ../../../Source/Pd/ELSE/format.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling format.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/freq.shift~_e7c84ce7.o: ../../../Source/Pd/ELSE/freq.shift~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling freq.shift~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/function_4707a4cd.o: ../../../Source/Pd/ELSE/function.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling function.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/function~_99ee1b1b.o: ../../../Source/Pd/ELSE/function~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling function~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gate2imp~_befc5e2e.o: ../../../Source/Pd/ELSE/gate2imp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gate2imp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gbman~_de88c0f4.o: ../../../Source/Pd/ELSE/gbman~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gbman~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/giga.rev~_759e3f62.o: ../../../Source/Pd/ELSE/giga.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling giga.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/glide~_e8d9de2e.o: ../../../Source/Pd/ELSE/glide~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling glide~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/glide2~_324081a6.o: ../../../Source/Pd/ELSE/glide2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling glide2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gray~_7cb3f4b0.o: ../../../Source/Pd/ELSE/gray~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gray~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gui_94c7d370.o: ../../../Source/Pd/ELSE/gui.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gui.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/henon~_e796c143.o: ../../../Source/Pd/ELSE/henon~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling henon~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/highpass~_68c7fc60.o: ../../../Source/Pd/ELSE/highpass~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling highpass~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/highshelf~_41d6752b.o: ../../../Source/Pd/ELSE/highshelf~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling highshelf~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hot_94d35a02.o: ../../../Source/Pd/ELSE/hot.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling hot.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hz2rad_d83ad46a.o: ../../../Source/Pd/ELSE/hz2rad.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling hz2rad.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hz2rad~_2f20df1e.o: ../../../Source/Pd/ELSE/hz2rad~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling hz2rad~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ikeda~_7ce0c8b3.o: ../../../Source/Pd/ELSE/ikeda~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ikeda~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/imp~_72fe4a7.o: ../../../Source/Pd/ELSE/imp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling imp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/imp2~_deab4a4d.o: ../../../Source/Pd/ELSE/imp2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling imp2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/impseq~_4eab8000.o: ../../../Source/Pd/ELSE/impseq~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling impseq~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/impulse~_fc94dade.o: ../../../Source/Pd/ELSE/impulse~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling impulse~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/impulse2~_95e51af6.o: ../../../Source/Pd/ELSE/impulse2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling impulse2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/initmess_85c097fd.o: ../../../Source/Pd/ELSE/initmess.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling initmess.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/int~_73fcda4.o: ../../../Source/Pd/ELSE/int~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling int~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/keyboard_fedd1c.o: ../../../Source/Pd/ELSE/keyboard.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling keyboard.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lag~_ba13d21.o: ../../../Source/Pd/ELSE/lag~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lag~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lag2~_68650113.o: ../../../Source/Pd/ELSE/lag2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lag2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lastvalue~_f1e62978.o: ../../../Source/Pd/ELSE/lastvalue~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lastvalue~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/latoocarfian~_2ae2466e.o: ../../../Source/Pd/ELSE/latoocarfian~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling latoocarfian~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lb_3e9d0eeb.o: ../../../Source/Pd/ELSE/lb.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lb.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lfnoise~_b94bde13.o: ../../../Source/Pd/ELSE/lfnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lfnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/limit_76792df0.o: ../../../Source/Pd/ELSE/limit.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling limit.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lincong~_545eafd.o: ../../../Source/Pd/ELSE/lincong~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lincong~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/loadbanger_8a03c580.o: ../../../Source/Pd/ELSE/loadbanger.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling loadbanger.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/logistic~_9c7f2f93.o: ../../../Source/Pd/ELSE/logistic~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling logistic~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/loop_c69f499.o: ../../../Source/Pd/ELSE/loop.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling loop.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lorenz~_2da6af71.o: ../../../Source/Pd/ELSE/lorenz~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lorenz~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lowpass~_bde42c6e.o: ../../../Source/Pd/ELSE/lowpass~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lowpass~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lowshelf~_904046dd.o: ../../../Source/Pd/ELSE/lowshelf~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lowshelf~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/match~_24f4f40e.o: ../../../Source/Pd/ELSE/match~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling match~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/median~_d49edca9.o: ../../../Source/Pd/ELSE/median~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling median~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/merge_a4d15b2d.o: ../../../Source/Pd/ELSE/merge.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling merge.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/message_ff293f3c.o: ../../../Source/Pd/ELSE/message.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling message.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/messbox_ff3b4108.o: ../../../Source/Pd/ELSE/messbox.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling messbox.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/midi_dc525d6.o: ../../../Source/Pd/ELSE/midi.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling midi.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mouse_b6118c5a.o: ../../../Source/Pd/ELSE/mouse.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mouse.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mov.avg~_a715fbfb.o: ../../../Source/Pd/ELSE/mov.avg~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mov.avg~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mov.rms~_c39eff75.o: ../../../Source/Pd/ELSE/mov.rms~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mov.rms~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mtx~_e698ea2.o: ../../../Source/Pd/ELSE/mtx~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mtx~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/nbang_d3acb31b.o: ../../../Source/Pd/ELSE/nbang.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling nbang.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/note_fd5c267.o: ../../../Source/Pd/ELSE/note.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling note.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/note.in_bc6e2d56.o: ../../../Source/Pd/ELSE/note.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling note.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/note.out_d1b039c7.o: ../../../Source/Pd/ELSE/note.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling note.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/nyquist~_1802b918.o: ../../../Source/Pd/ELSE/nyquist~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling nyquist~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/op~_95369872.o: ../../../Source/Pd/ELSE/op~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling op~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/openfile_7f5b143b.o: ../../../Source/Pd/ELSE/openfile.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling openfile.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pack2_3bde5bee.o: ../../../Source/Pd/ELSE/pack2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pack2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pad_953d7cc8.o: ../../../Source/Pd/ELSE/pad.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pad.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pan2~_3c60929e.o: ../../../Source/Pd/ELSE/pan2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pan2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pan4~_3c617b5c.o: ../../../Source/Pd/ELSE/pan4~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pan4~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/panic_3c792dac.o: ../../../Source/Pd/ELSE/panic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling panic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/parabolic~_e1a4ca1a.o: ../../../Source/Pd/ELSE/parabolic~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling parabolic~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/peak~_4296acb4.o: ../../../Source/Pd/ELSE/peak~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling peak~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pgm.in_8b214c72.o: ../../../Source/Pd/ELSE/pgm.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pgm.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pgm.out_d960fe2b.o: ../../../Source/Pd/ELSE/pgm.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pgm.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pic_95411bff.o: ../../../Source/Pd/ELSE/pic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pimp~_4a156f17.o: ../../../Source/Pd/ELSE/pimp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pimp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pinknoise~_5c4e560f.o: ../../../Source/Pd/ELSE/pinknoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pinknoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pluck~_a4333c32.o: ../../../Source/Pd/ELSE/pluck~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pluck~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pmosc~_cfba38d1.o: ../../../Source/Pd/ELSE/pmosc~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pmosc~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/properties_7bf89368.o: ../../../Source/Pd/ELSE/properties.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling properties.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pulse~_71ce71ba.o: ../../../Source/Pd/ELSE/pulse~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pulse~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pulsecount~_2ea6d11d.o: ../../../Source/Pd/ELSE/pulsecount~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pulsecount~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pulsediv~_9e10689b.o: ../../../Source/Pd/ELSE/pulsediv~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pulsediv~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/quad~_92c7434c.o: ../../../Source/Pd/ELSE/quad~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling quad~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/quantizer_ef8bd216.o: ../../../Source/Pd/ELSE/quantizer.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling quantizer.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/quantizer~_1ef96f2.o: ../../../Source/Pd/ELSE/quantizer~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling quantizer~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rad2hz_e5abbc4.o: ../../../Source/Pd/ELSE/rad2hz.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rad2hz.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rad2hz~_bcfde304.o: ../../../Source/Pd/ELSE/rad2hz~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rad2hz~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ramp~_a63b20a1.o: ../../../Source/Pd/ELSE/ramp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ramp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rampnoise~_b598c4ab.o: ../../../Source/Pd/ELSE/rampnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rampnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.f_22112092.o: ../../../Source/Pd/ELSE/rand.f.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.f.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.f~_201417f6.o: ../../../Source/Pd/ELSE/rand.f~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.f~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.i_22112bd5.o: ../../../Source/Pd/ELSE/rand.i.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.i.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.i~_20157513.o: ../../../Source/Pd/ELSE/rand.i~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.i~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.seq_e31bb08b.o: ../../../Source/Pd/ELSE/rand.seq.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.seq.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/randpulse~_c8f348df.o: ../../../Source/Pd/ELSE/randpulse~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling randpulse~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/randpulse2~_55546d15.o: ../../../Source/Pd/ELSE/randpulse2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling randpulse2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/range~_2254c196.o: ../../../Source/Pd/ELSE/range~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling range~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ratio2cents_e08d6299.o: ../../../Source/Pd/ELSE/ratio2cents.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ratio2cents.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ratio2cents~_312016cf.o: ../../../Source/Pd/ELSE/ratio2cents~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ratio2cents~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/receiver_573ef124.o: ../../../Source/Pd/ELSE/receiver.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling receiver.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rescale_c934262c.o: ../../../Source/Pd/ELSE/rescale.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rescale.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rescale~_5d51c59c.o: ../../../Source/Pd/ELSE/rescale~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rescale~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/resonant~_c8dc29eb.o: ../../../Source/Pd/ELSE/resonant~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling resonant~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/resonant2~_5287ad89.o: ../../../Source/Pd/ELSE/resonant2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling resonant2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rint_165215f2.o: ../../../Source/Pd/ELSE/rint.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rint.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rint~_b3f1ce96.o: ../../../Source/Pd/ELSE/rint~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rint~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rms~_168cdf5b.o: ../../../Source/Pd/ELSE/rms~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rms~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rotate~_a855eb8.o: ../../../Source/Pd/ELSE/rotate~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rotate~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/routeall_8145afad.o: ../../../Source/Pd/ELSE/routeall.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling routeall.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/router_1394effe.o: ../../../Source/Pd/ELSE/router.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling router.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/routetype_c8962538.o: ../../../Source/Pd/ELSE/routetype.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling routetype.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s2f~_14fc646c.o: ../../../Source/Pd/ELSE/s2f~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s2f~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saw~_179a6f6a.o: ../../../Source/Pd/ELSE/saw~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saw~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saw2~_db9217ea.o: ../../../Source/Pd/ELSE/saw2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saw2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/schmitt~_d1820e3f.o: ../../../Source/Pd/ELSE/schmitt~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling schmitt~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/selector_e81e3f14.o: ../../../Source/Pd/ELSE/selector.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling selector.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/separate_cc990d58.o: ../../../Source/Pd/ELSE/separate.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling separate.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sequencer~_e08be182.o: ../../../Source/Pd/ELSE/sequencer~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sequencer~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sh~_956b537e.o: ../../../Source/Pd/ELSE/sh~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sh~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/shaper~_f3566762.o: ../../../Source/Pd/ELSE/shaper~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling shaper~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sig2float~_edae9c98.o: ../../../Source/Pd/ELSE/sig2float~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sig2float~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sin~_1807141b.o: ../../../Source/Pd/ELSE/sin~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sin~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sine~_e8d13846.o: ../../../Source/Pd/ELSE/sine~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sine~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/slice_eda80607.o: ../../../Source/Pd/ELSE/slice.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling slice.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sort_185d4d13.o: ../../../Source/Pd/ELSE/sort.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sort.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/spread_aa6867a8.o: ../../../Source/Pd/ELSE/spread.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling spread.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/spread~_a2a5b3a0.o: ../../../Source/Pd/ELSE/spread~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling spread~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/square~_a35633b6.o: ../../../Source/Pd/ELSE/square~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling square~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sr~_956fdf34.o: ../../../Source/Pd/ELSE/sr~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sr~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/standard~_c8904a16.o: ../../../Source/Pd/ELSE/standard~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling standard~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/status~_d999d0c1.o: ../../../Source/Pd/ELSE/status~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling status~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/stepnoise~_27f82565.o: ../../../Source/Pd/ELSE/stepnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling stepnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/susloop~_8a0d5b5e.o: ../../../Source/Pd/ELSE/susloop~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling susloop~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/suspedal_4bf3ba7e.o: ../../../Source/Pd/ELSE/suspedal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling suspedal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/svfilter~_56009078.o: ../../../Source/Pd/ELSE/svfilter~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling svfilter~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/symbol2any_1576887.o: ../../../Source/Pd/ELSE/symbol2any.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling symbol2any.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/t2_3e9ffdb3.o: ../../../Source/Pd/ELSE/t2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling t2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/table~_dde36965.o: ../../../Source/Pd/ELSE/table~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling table~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tabplayer~_ac08c57d.o: ../../../Source/Pd/ELSE/tabplayer~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tabplayer~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tabwriter~_c7d87aab.o: ../../../Source/Pd/ELSE/tabwriter~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tabwriter~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tempo~_c47e8ef8.o: ../../../Source/Pd/ELSE/tempo~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tempo~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/timed.gate~_e657e991.o: ../../../Source/Pd/ELSE/timed.gate~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling timed.gate~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/toggleff~_e7d5325f.o: ../../../Source/Pd/ELSE/toggleff~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling toggleff~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/touch.in_e8dd2829.o: ../../../Source/Pd/ELSE/touch.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling touch.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/touch.out_33209954.o: ../../../Source/Pd/ELSE/touch.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling touch.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tri~_1a387a68.o: ../../../Source/Pd/ELSE/tri~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tri~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trig.delay~_b9d0f22.o: ../../../Source/Pd/ELSE/trig.delay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trig.delay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trig.delay2~_67e36f32.o: ../../../Source/Pd/ELSE/trig.delay2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trig.delay2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trigger2_9c0ab1ef.o: ../../../Source/Pd/ELSE/trigger2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trigger2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trighold~_2b059138.o: ../../../Source/Pd/ELSE/trighold~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trighold~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/unmerge_f3dd9e74.o: ../../../Source/Pd/ELSE/unmerge.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling unmerge.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/voices_9daff036.o: ../../../Source/Pd/ELSE/voices.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling voices.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/vsaw~_97e55d60.o: ../../../Source/Pd/ELSE/vsaw~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling vsaw~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/vu~_959b82d4.o: ../../../Source/Pd/ELSE/vu~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling vu~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wavetable~_9210735e.o: ../../../Source/Pd/ELSE/wavetable~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wavetable~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wrap2_cb12741d.o: ../../../Source/Pd/ELSE/wrap2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wrap2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wrap2~_973d35cb.o: ../../../Source/Pd/ELSE/wrap2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wrap2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wt~_95a925f6.o: ../../../Source/Pd/ELSE/wt~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wt~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xfade~_83c1b07f.o: ../../../Source/Pd/ELSE/xfade~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xfade~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xgate~_b98963d0.o: ../../../Source/Pd/ELSE/xgate~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xgate~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xgate2~_7781b044.o: ../../../Source/Pd/ELSE/xgate2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xgate2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xmod~_f8316629.o: ../../../Source/Pd/ELSE/xmod~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xmod~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xmod2~_dd9f90b.o: ../../../Source/Pd/ELSE/xmod2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xmod2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xselect~_66eb7fff.o: ../../../Source/Pd/ELSE/xselect~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xselect~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xselect2~_766319f5.o: ../../../Source/Pd/ELSE/xselect2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xselect2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/zerocross~_aa2cb65b.o: ../../../Source/Pd/ELSE/zerocross~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling zerocross~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PdInstance_c9d7d554.o: ../../../Source/Pd/PdInstance.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PdInstance.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PdPatch_2b25dab3.o: ../../../Source/Pd/PdPatch.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PdPatch.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PdGui_34dd0fa6.o: ../../../Source/Pd/PdGui.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PdGui.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PdArray_f4d0bc44.o: ../../../Source/Pd/PdArray.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PdArray.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/PdObject_2fcb197e.o: ../../../Source/Pd/PdObject.cpp
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling PdObject.cpp"
	$(V_AT)$(CXX) $(JUCE_CXXFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_libpd_multi_a98b54cb.o: ../../../Source/Pd/x_libpd_multi.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_libpd_multi.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/x_libpd_extra_utils_b8efa354.o: ../../../Source/Pd/x_libpd_extra_utils.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling x_libpd_extra_utils.c"
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

clean:
	@echo Cleaning CamomileFx
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping CamomileFx
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_VST3:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
