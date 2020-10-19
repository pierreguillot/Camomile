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

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DDEBUG=1" "-D_DEBUG=1" "-DPD_INTERNAL=1" "-DJUCE_VST3_CAN_REPLACE_VST2=0" "-DPD=1" "-DPDINSTANCE=1" "-DCAMOMILE=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.7" "-DJUCE_APP_VERSION_HEX=0x10007" $(shell pkg-config --cflags freetype2) -pthread -I../../../Juce/modules/juce_audio_processors/format_types/VST3_SDK -I../../../Dependencies/Vst2 -I../../JuceLibraryCode -I../../../Juce/modules -I../../../Dependencies/LibPd/pure-data/src -I../../../Dependencies/LibPd/libpd_wrapper -I../../../Dependencies/LibPd/libpd_wrapper/util -I../../../Dependencies/LibPd/cpp -I../../../Source/Pd/Externals -I../../../Source/Pd/Externals/shared $(CPPFLAGS)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := Camomile.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/Camomile.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := Camomile.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -g -ggdb -O0 -fPIC $(CFLAGS)
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

  JUCE_CPPFLAGS := $(DEPFLAGS) "-DLINUX=1" "-DNDEBUG=1" "-DPD_INTERNAL=1" "-DJUCE_VST3_CAN_REPLACE_VST2=0" "-DPD=1" "-DPDINSTANCE=1" "-DCAMOMILE=1" "-DJUCER_LINUX_MAKE_6D53C8B4=1" "-DJUCE_APP_VERSION=1.0.7" "-DJUCE_APP_VERSION_HEX=0x10007" $(shell pkg-config --cflags freetype2) -pthread -I../../../Juce/modules/juce_audio_processors/format_types/VST3_SDK -I../../../Dependencies/Vst2 -I../../JuceLibraryCode -I../../../Juce/modules -I../../../Dependencies/LibPd/pure-data/src -I../../../Dependencies/LibPd/libpd_wrapper -I../../../Dependencies/LibPd/libpd_wrapper/util -I../../../Dependencies/LibPd/cpp -I../../../Source/Pd/Externals -I../../../Source/Pd/Externals/shared $(CPPFLAGS)

  JUCE_CPPFLAGS_VST3 :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0"
  JUCE_CFLAGS_VST3 := -fPIC -fvisibility=hidden
  JUCE_LDFLAGS_VST3 := -shared -Wl,--no-undefined
  JUCE_VST3DIR := Camomile.vst3
  VST3_PLATFORM_ARCH := $(shell $(CXX) make_helpers/arch_detection.cpp 2>&1 | tr '\n' ' ' | sed "s/.*JUCE_ARCH \([a-zA-Z0-9_-]*\).*/\1/")
  JUCE_VST3SUBDIR := Contents/$(VST3_PLATFORM_ARCH)-linux
  JUCE_TARGET_VST3 := $(JUCE_VST3DIR)/$(JUCE_VST3SUBDIR)/Camomile.so
  JUCE_VST3DESTDIR := $(HOME)/.vst3
  JUCE_COPYCMD_VST3 := $(JUCE_OUTDIR)/$(JUCE_VST3DIR) $(JUCE_VST3DESTDIR)

  JUCE_CPPFLAGS_SHARED_CODE :=  "-DJucePlugin_Build_VST=0" "-DJucePlugin_Build_VST3=1" "-DJucePlugin_Build_AU=0" "-DJucePlugin_Build_AUv3=0" "-DJucePlugin_Build_RTAS=0" "-DJucePlugin_Build_AAX=0" "-DJucePlugin_Build_Standalone=0" "-DJucePlugin_Build_Unity=0" "-DJUCE_SHARED_CODE=1"
  JUCE_TARGET_SHARED_CODE := Camomile.a

  JUCE_CFLAGS += $(JUCE_CPPFLAGS) $(TARGET_ARCH) -fPIC -O3 -fPIC $(CFLAGS)
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
  $(JUCE_OBJDIR)/buffer_be9ac862.o \
  $(JUCE_OBJDIR)/file_cf7f71de.o \
  $(JUCE_OBJDIR)/grow_d1b4beb5.o \
  $(JUCE_OBJDIR)/magic_84cfc095.o \
  $(JUCE_OBJDIR)/mifi_db6eb301.o \
  $(JUCE_OBJDIR)/random_28400425.o \
  $(JUCE_OBJDIR)/s_utf8_3323409f.o \
  $(JUCE_OBJDIR)/above~_3182b7d3.o \
  $(JUCE_OBJDIR)/add~_93b8d78f.o \
  $(JUCE_OBJDIR)/adsr~_e4312cb4.o \
  $(JUCE_OBJDIR)/allpass.2nd~_aa4d74a4.o \
  $(JUCE_OBJDIR)/allpass.rev~_170cf789.o \
  $(JUCE_OBJDIR)/args_947f546f.o \
  $(JUCE_OBJDIR)/asr~_94929550.o \
  $(JUCE_OBJDIR)/autofade~_d0d497ab.o \
  $(JUCE_OBJDIR)/autofade2~_499cf7c9.o \
  $(JUCE_OBJDIR)/balance~_bb2b3cf4.o \
  $(JUCE_OBJDIR)/bandpass~_718cfab0.o \
  $(JUCE_OBJDIR)/bandstop~_3072051f.o \
  $(JUCE_OBJDIR)/bend.in_740f1372.o \
  $(JUCE_OBJDIR)/bend.out_e2c172b.o \
  $(JUCE_OBJDIR)/bicoeff_e37a1b8a.o \
  $(JUCE_OBJDIR)/biquads~_7096ab0b.o \
  $(JUCE_OBJDIR)/blocksize~_25fd4d42.o \
  $(JUCE_OBJDIR)/break_302df5f7.o \
  $(JUCE_OBJDIR)/brown~_e7d9c79a.o \
  $(JUCE_OBJDIR)/button_8eeaa644.o \
  $(JUCE_OBJDIR)/canvas.active_8fbc4314.o \
  $(JUCE_OBJDIR)/canvas.bounds_745b8b03.o \
  $(JUCE_OBJDIR)/canvas.edit_a0739358.o \
  $(JUCE_OBJDIR)/canvas.gop_6024fb84.o \
  $(JUCE_OBJDIR)/canvas.mouse_289f6ea1.o \
  $(JUCE_OBJDIR)/canvas.name_afa68399.o \
  $(JUCE_OBJDIR)/canvas.pos_60a3da50.o \
  $(JUCE_OBJDIR)/canvas.setname_abc30029.o \
  $(JUCE_OBJDIR)/canvas.vis_60f5ad1c.o \
  $(JUCE_OBJDIR)/canvas.wname_36cc563e.o \
  $(JUCE_OBJDIR)/canvas.zoom_c4e6fae1.o \
  $(JUCE_OBJDIR)/ceil_9732a297.o \
  $(JUCE_OBJDIR)/ceil~_4f22d691.o \
  $(JUCE_OBJDIR)/cents2ratio_ea80701c.o \
  $(JUCE_OBJDIR)/cents2ratio~_658eb9ac.o \
  $(JUCE_OBJDIR)/changed_a477c1ac.o \
  $(JUCE_OBJDIR)/changed~_ea819a1c.o \
  $(JUCE_OBJDIR)/changed2~_65904378.o \
  $(JUCE_OBJDIR)/click_5b106440.o \
  $(JUCE_OBJDIR)/clipnoise~_5f17e406.o \
  $(JUCE_OBJDIR)/cmul~_5d72b595.o \
  $(JUCE_OBJDIR)/coin_97bf9523.o \
  $(JUCE_OBJDIR)/coin~_60343585.o \
  $(JUCE_OBJDIR)/colors_ab7aa502.o \
  $(JUCE_OBJDIR)/comb.filt~_fe6e8eb8.o \
  $(JUCE_OBJDIR)/comb.rev~_77524440.o \
  $(JUCE_OBJDIR)/common.div_ff99cba0.o \
  $(JUCE_OBJDIR)/cosine~_2baaf15d.o \
  $(JUCE_OBJDIR)/crackle~_767fdfbd.o \
  $(JUCE_OBJDIR)/crossover~_6fcf887c.o \
  $(JUCE_OBJDIR)/ctl.in_b061ab6a.o \
  $(JUCE_OBJDIR)/ctl.out_5c2c7e33.o \
  $(JUCE_OBJDIR)/cusp~_6aff1d07.o \
  $(JUCE_OBJDIR)/decay~_f23ff296.o \
  $(JUCE_OBJDIR)/decay2~_559cfa3e.o \
  $(JUCE_OBJDIR)/detect~_dea24773.o \
  $(JUCE_OBJDIR)/dir_dba64ac5.o \
  $(JUCE_OBJDIR)/dollsym_53119894.o \
  $(JUCE_OBJDIR)/downsample~_cb43ff2a.o \
  $(JUCE_OBJDIR)/drive~_ad4cdec6.o \
  $(JUCE_OBJDIR)/dust~_9fe729c4.o \
  $(JUCE_OBJDIR)/dust2~_5cdca8d0.o \
  $(JUCE_OBJDIR)/else_9b0369cb.o \
  $(JUCE_OBJDIR)/envgen~_8720e6d3.o \
  $(JUCE_OBJDIR)/eq~_dbb8324a.o \
  $(JUCE_OBJDIR)/f2s~_99874d09.o \
  $(JUCE_OBJDIR)/factor_ef706521.o \
  $(JUCE_OBJDIR)/fader~_f053675a.o \
  $(JUCE_OBJDIR)/fbdelay~_b1a82da9.o \
  $(JUCE_OBJDIR)/fbsine~_a208f70d.o \
  $(JUCE_OBJDIR)/fbsine2~_9ef484a7.o \
  $(JUCE_OBJDIR)/fdn.rev~_95fa260b.o \
  $(JUCE_OBJDIR)/ffdelay~_2b9e9ad.o \
  $(JUCE_OBJDIR)/float2bits_47d5b96e.o \
  $(JUCE_OBJDIR)/float2sig~_64d25c75.o \
  $(JUCE_OBJDIR)/floor_fa1d31c4.o \
  $(JUCE_OBJDIR)/floor~_498a2d04.o \
  $(JUCE_OBJDIR)/fold_9cdf5693.o \
  $(JUCE_OBJDIR)/fold~_ff0ca215.o \
  $(JUCE_OBJDIR)/fontsize_6dcdc922.o \
  $(JUCE_OBJDIR)/format_ed3759c9.o \
  $(JUCE_OBJDIR)/freq.shift~_66cb2a6a.o \
  $(JUCE_OBJDIR)/function_65ce6e2a.o \
  $(JUCE_OBJDIR)/function~_54007d5e.o \
  $(JUCE_OBJDIR)/gate2imp~_790ec071.o \
  $(JUCE_OBJDIR)/gbman~_9c3c3d91.o \
  $(JUCE_OBJDIR)/giga.rev~_2fb0a1a5.o \
  $(JUCE_OBJDIR)/glide~_a68d5acb.o \
  $(JUCE_OBJDIR)/glide2~_2afc98a9.o \
  $(JUCE_OBJDIR)/gray~_387ff073.o \
  $(JUCE_OBJDIR)/gui_dbd5e3f3.o \
  $(JUCE_OBJDIR)/henon~_a54a3de0.o \
  $(JUCE_OBJDIR)/highpass~_22da5ea3.o \
  $(JUCE_OBJDIR)/highshelf~_ca105b48.o \
  $(JUCE_OBJDIR)/hot_dbe16a85.o \
  $(JUCE_OBJDIR)/hz2rad_95ee5107.o \
  $(JUCE_OBJDIR)/hz2rad~_27dcf621.o \
  $(JUCE_OBJDIR)/ikeda~_3a944550.o \
  $(JUCE_OBJDIR)/imp~_a1e3e484.o \
  $(JUCE_OBJDIR)/imp2~_9a774610.o \
  $(JUCE_OBJDIR)/impseq~_47679703.o \
  $(JUCE_OBJDIR)/impulse~_1b5ba43b.o \
  $(JUCE_OBJDIR)/impulse2~_4ff77d39.o \
  $(JUCE_OBJDIR)/initmess_a487615a.o \
  $(JUCE_OBJDIR)/int~_a1f3cd81.o \
  $(JUCE_OBJDIR)/keyboard_1fc5a679.o \
  $(JUCE_OBJDIR)/lag~_a6553cfe.o \
  $(JUCE_OBJDIR)/lag2~_2430fcd6.o \
  $(JUCE_OBJDIR)/lastvalue~_7a200f95.o \
  $(JUCE_OBJDIR)/latoocarfian~_f4a3cf31.o \
  $(JUCE_OBJDIR)/lb_7196208.o \
  $(JUCE_OBJDIR)/lfnoise~_d812a770.o \
  $(JUCE_OBJDIR)/lincong~_240cb45a.o \
  $(JUCE_OBJDIR)/loadbanger_123dab9d.o \
  $(JUCE_OBJDIR)/logistic~_569191d6.o \
  $(JUCE_OBJDIR)/loop_a71df476.o \
  $(JUCE_OBJDIR)/lorenz~_2662c674.o \
  $(JUCE_OBJDIR)/lowpass~_dcaaf5cb.o \
  $(JUCE_OBJDIR)/lowshelf~_4a52a920.o \
  $(JUCE_OBJDIR)/match~_e2a870ab.o \
  $(JUCE_OBJDIR)/median~_cd5af3ac.o \
  $(JUCE_OBJDIR)/merge_609d56f0.o \
  $(JUCE_OBJDIR)/message_f7e5563f.o \
  $(JUCE_OBJDIR)/messbox_f7f7580b.o \
  $(JUCE_OBJDIR)/midi_a87925b3.o \
  $(JUCE_OBJDIR)/mouse_71dd881d.o \
  $(JUCE_OBJDIR)/mov.avg~_c5dcc558.o \
  $(JUCE_OBJDIR)/mov.rms~_e265c8d2.o \
  $(JUCE_OBJDIR)/mtx~_a91d8e7f.o \
  $(JUCE_OBJDIR)/nbang_8f78aede.o \
  $(JUCE_OBJDIR)/note_aa89c244.o \
  $(JUCE_OBJDIR)/note.in_b52a4459.o \
  $(JUCE_OBJDIR)/note.out_f0770324.o \
  $(JUCE_OBJDIR)/nyquist~_36c98275.o \
  $(JUCE_OBJDIR)/op~_dc44a8f5.o \
  $(JUCE_OBJDIR)/openfile_9e21dd98.o \
  $(JUCE_OBJDIR)/oscilloscope_9a06b221.o \
  $(JUCE_OBJDIR)/pack2_f7aa57b1.o \
  $(JUCE_OBJDIR)/pad_dc4b8d4b.o \
  $(JUCE_OBJDIR)/pan2~_f82c8e61.o \
  $(JUCE_OBJDIR)/pan4~_f82d771f.o \
  $(JUCE_OBJDIR)/panic_f845296f.o \
  $(JUCE_OBJDIR)/parabolic~_69deb037.o \
  $(JUCE_OBJDIR)/peak~_fe62a877.o \
  $(JUCE_OBJDIR)/pgm.in_48d4c90f.o \
  $(JUCE_OBJDIR)/pgm.out_d21d152e.o \
  $(JUCE_OBJDIR)/pic_dc4f2c82.o \
  $(JUCE_OBJDIR)/pimp~_5e16ada.o \
  $(JUCE_OBJDIR)/pinknoise~_e4883c2c.o \
  $(JUCE_OBJDIR)/pluck~_61e6b8cf.o \
  $(JUCE_OBJDIR)/pmosc~_8d6db56e.o \
  $(JUCE_OBJDIR)/properties_4327985.o \
  $(JUCE_OBJDIR)/pulse~_2f81ee57.o \
  $(JUCE_OBJDIR)/pulsecount~_ada9aea0.o \
  $(JUCE_OBJDIR)/pulsediv~_5822cade.o \
  $(JUCE_OBJDIR)/quad~_4e933f0f.o \
  $(JUCE_OBJDIR)/quantizer_a99e3459.o \
  $(JUCE_OBJDIR)/quantizer~_8a297d0f.o \
  $(JUCE_OBJDIR)/rad2hz_cc0e3861.o \
  $(JUCE_OBJDIR)/rad2hz~_b5b9fa07.o \
  $(JUCE_OBJDIR)/ramp~_62071c64.o \
  $(JUCE_OBJDIR)/rampnoise~_3dd2aac8.o \
  $(JUCE_OBJDIR)/rand.f_dfc49d2f.o \
  $(JUCE_OBJDIR)/rand.f~_18d02ef9.o \
  $(JUCE_OBJDIR)/rand.i_dfc4a872.o \
  $(JUCE_OBJDIR)/rand.i~_18d18c16.o \
  $(JUCE_OBJDIR)/rand.seq_1e279e8.o \
  $(JUCE_OBJDIR)/randpulse~_512d2efc.o \
  $(JUCE_OBJDIR)/randpulse2~_d4574a98.o \
  $(JUCE_OBJDIR)/range~_e0083e33.o \
  $(JUCE_OBJDIR)/ratio2cents_5f90401c.o \
  $(JUCE_OBJDIR)/ratio2cents~_9278e9ac.o \
  $(JUCE_OBJDIR)/receiver_7605ba81.o \
  $(JUCE_OBJDIR)/rescale_c1f03d2f.o \
  $(JUCE_OBJDIR)/rescale~_7c188ef9.o \
  $(JUCE_OBJDIR)/resonant~_82ee8c2e.o \
  $(JUCE_OBJDIR)/resonant2~_dac193a6.o \
  $(JUCE_OBJDIR)/rint_b10615cf.o \
  $(JUCE_OBJDIR)/rint~_6fbdca59.o \
  $(JUCE_OBJDIR)/rms~_b140df38.o \
  $(JUCE_OBJDIR)/rotate~_34175bb.o \
  $(JUCE_OBJDIR)/routeall_a00c790a.o \
  $(JUCE_OBJDIR)/router_d1486c9b.o \
  $(JUCE_OBJDIR)/routetype_82a8877b.o \
  $(JUCE_OBJDIR)/s2f~_afb06449.o \
  $(JUCE_OBJDIR)/saw~_b24e6f47.o \
  $(JUCE_OBJDIR)/saw2~_975e13ad.o \
  $(JUCE_OBJDIR)/schmitt~_f048d79c.o \
  $(JUCE_OBJDIR)/selector_6e50871.o \
  $(JUCE_OBJDIR)/separate_eb5fd6b5.o \
  $(JUCE_OBJDIR)/sequencer~_68c5c79f.o \
  $(JUCE_OBJDIR)/sh~_dc796401.o \
  $(JUCE_OBJDIR)/shaper~_ec127e65.o \
  $(JUCE_OBJDIR)/sig2float~_75e882b5.o \
  $(JUCE_OBJDIR)/sin~_b2bb13f8.o \
  $(JUCE_OBJDIR)/sine~_a49d3409.o \
  $(JUCE_OBJDIR)/slice_a97401ca.o \
  $(JUCE_OBJDIR)/sort_b3114cf0.o \
  $(JUCE_OBJDIR)/spread~_9b61caa3.o \
  $(JUCE_OBJDIR)/square~_9c124ab9.o \
  $(JUCE_OBJDIR)/sr~_dc7defb7.o \
  $(JUCE_OBJDIR)/standard~_82a2ac59.o \
  $(JUCE_OBJDIR)/status~_d255e7c4.o \
  $(JUCE_OBJDIR)/stepnoise~_b0320b82.o \
  $(JUCE_OBJDIR)/susloop~_a8d424bb.o \
  $(JUCE_OBJDIR)/suspedal_6aba83db.o \
  $(JUCE_OBJDIR)/svfilter~_1012f2bb.o \
  $(JUCE_OBJDIR)/symbol2any_89914ea4.o \
  $(JUCE_OBJDIR)/t2_71c50d0.o \
  $(JUCE_OBJDIR)/table~_9b96e602.o \
  $(JUCE_OBJDIR)/tabplayer~_3442ab9a.o \
  $(JUCE_OBJDIR)/tabwriter~_501260c8.o \
  $(JUCE_OBJDIR)/tempo~_82320b95.o \
  $(JUCE_OBJDIR)/timed.gate~_655ac714.o \
  $(JUCE_OBJDIR)/toggleff~_a1e794a2.o \
  $(JUCE_OBJDIR)/touch.in_7a3f186.o \
  $(JUCE_OBJDIR)/touch.out_ed32fb97.o \
  $(JUCE_OBJDIR)/tri~_b4ec7a45.o \
  $(JUCE_OBJDIR)/trig.delay~_8a9feca5.o \
  $(JUCE_OBJDIR)/trig.delay2~_c93c420f.o \
  $(JUCE_OBJDIR)/trigger2_bad17b4c.o \
  $(JUCE_OBJDIR)/trighold~_e517f37b.o \
  $(JUCE_OBJDIR)/unmerge_ec99b577.o \
  $(JUCE_OBJDIR)/voices_5b636cd3.o \
  $(JUCE_OBJDIR)/vsaw~_53b15923.o \
  $(JUCE_OBJDIR)/vu~_dca99357.o \
  $(JUCE_OBJDIR)/wavetable~_1a4a597b.o \
  $(JUCE_OBJDIR)/wrap2_86de6fe0.o \
  $(JUCE_OBJDIR)/wrap2~_54f0b268.o \
  $(JUCE_OBJDIR)/wt~_dcb73679.o \
  $(JUCE_OBJDIR)/xfade~_41752d1c.o \
  $(JUCE_OBJDIR)/xgate~_773ce06d.o \
  $(JUCE_OBJDIR)/xgate2~_703dc747.o \
  $(JUCE_OBJDIR)/xmod~_b3fd61ec.o \
  $(JUCE_OBJDIR)/xmod2~_cb8d75a8.o \
  $(JUCE_OBJDIR)/xselect~_85b2495c.o \
  $(JUCE_OBJDIR)/xselect2~_30757c38.o \
  $(JUCE_OBJDIR)/zerocross~_32669c78.o \
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
	@echo Linking "Camomile - VST3"
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
	@echo Linking "Camomile - Shared Code"
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

$(JUCE_OBJDIR)/buffer_be9ac862.o: ../../../Source/Pd/Externals/shared/buffer.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling buffer.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/file_cf7f71de.o: ../../../Source/Pd/Externals/shared/file.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling file.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/grow_d1b4beb5.o: ../../../Source/Pd/Externals/shared/grow.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling grow.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/magic_84cfc095.o: ../../../Source/Pd/Externals/shared/magic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling magic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mifi_db6eb301.o: ../../../Source/Pd/Externals/shared/mifi.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mifi.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/random_28400425.o: ../../../Source/Pd/Externals/shared/random.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling random.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s_utf8_3323409f.o: ../../../Source/Pd/Externals/shared/s_utf8.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s_utf8.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/above~_3182b7d3.o: ../../../Source/Pd/Externals/above~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling above~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/add~_93b8d78f.o: ../../../Source/Pd/Externals/add~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling add~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/adsr~_e4312cb4.o: ../../../Source/Pd/Externals/adsr~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling adsr~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/allpass.2nd~_aa4d74a4.o: ../../../Source/Pd/Externals/allpass.2nd~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling allpass.2nd~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/allpass.rev~_170cf789.o: ../../../Source/Pd/Externals/allpass.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling allpass.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/args_947f546f.o: ../../../Source/Pd/Externals/args.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling args.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/asr~_94929550.o: ../../../Source/Pd/Externals/asr~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling asr~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/autofade~_d0d497ab.o: ../../../Source/Pd/Externals/autofade~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling autofade~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/autofade2~_499cf7c9.o: ../../../Source/Pd/Externals/autofade2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling autofade2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/balance~_bb2b3cf4.o: ../../../Source/Pd/Externals/balance~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling balance~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bandpass~_718cfab0.o: ../../../Source/Pd/Externals/bandpass~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bandpass~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bandstop~_3072051f.o: ../../../Source/Pd/Externals/bandstop~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bandstop~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bend.in_740f1372.o: ../../../Source/Pd/Externals/bend.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bend.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bend.out_e2c172b.o: ../../../Source/Pd/Externals/bend.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bend.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/bicoeff_e37a1b8a.o: ../../../Source/Pd/Externals/bicoeff.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling bicoeff.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/biquads~_7096ab0b.o: ../../../Source/Pd/Externals/biquads~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling biquads~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/blocksize~_25fd4d42.o: ../../../Source/Pd/Externals/blocksize~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling blocksize~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/break_302df5f7.o: ../../../Source/Pd/Externals/break.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling break.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/brown~_e7d9c79a.o: ../../../Source/Pd/Externals/brown~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling brown~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/button_8eeaa644.o: ../../../Source/Pd/Externals/button.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling button.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.active_8fbc4314.o: ../../../Source/Pd/Externals/canvas.active.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.active.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.bounds_745b8b03.o: ../../../Source/Pd/Externals/canvas.bounds.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.bounds.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.edit_a0739358.o: ../../../Source/Pd/Externals/canvas.edit.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.edit.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.gop_6024fb84.o: ../../../Source/Pd/Externals/canvas.gop.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.gop.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.mouse_289f6ea1.o: ../../../Source/Pd/Externals/canvas.mouse.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.mouse.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.name_afa68399.o: ../../../Source/Pd/Externals/canvas.name.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.name.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.pos_60a3da50.o: ../../../Source/Pd/Externals/canvas.pos.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.pos.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.setname_abc30029.o: ../../../Source/Pd/Externals/canvas.setname.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.setname.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.vis_60f5ad1c.o: ../../../Source/Pd/Externals/canvas.vis.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.vis.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.wname_36cc563e.o: ../../../Source/Pd/Externals/canvas.wname.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.wname.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/canvas.zoom_c4e6fae1.o: ../../../Source/Pd/Externals/canvas.zoom.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling canvas.zoom.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ceil_9732a297.o: ../../../Source/Pd/Externals/ceil.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ceil.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ceil~_4f22d691.o: ../../../Source/Pd/Externals/ceil~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ceil~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cents2ratio_ea80701c.o: ../../../Source/Pd/Externals/cents2ratio.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cents2ratio.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cents2ratio~_658eb9ac.o: ../../../Source/Pd/Externals/cents2ratio~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cents2ratio~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/changed_a477c1ac.o: ../../../Source/Pd/Externals/changed.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling changed.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/changed~_ea819a1c.o: ../../../Source/Pd/Externals/changed~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling changed~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/changed2~_65904378.o: ../../../Source/Pd/Externals/changed2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling changed2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/click_5b106440.o: ../../../Source/Pd/Externals/click.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling click.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/clipnoise~_5f17e406.o: ../../../Source/Pd/Externals/clipnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling clipnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cmul~_5d72b595.o: ../../../Source/Pd/Externals/cmul~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cmul~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/coin_97bf9523.o: ../../../Source/Pd/Externals/coin.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling coin.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/coin~_60343585.o: ../../../Source/Pd/Externals/coin~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling coin~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/colors_ab7aa502.o: ../../../Source/Pd/Externals/colors.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling colors.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/comb.filt~_fe6e8eb8.o: ../../../Source/Pd/Externals/comb.filt~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling comb.filt~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/comb.rev~_77524440.o: ../../../Source/Pd/Externals/comb.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling comb.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/common.div_ff99cba0.o: ../../../Source/Pd/Externals/common.div.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling common.div.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cosine~_2baaf15d.o: ../../../Source/Pd/Externals/cosine~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cosine~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/crackle~_767fdfbd.o: ../../../Source/Pd/Externals/crackle~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling crackle~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/crossover~_6fcf887c.o: ../../../Source/Pd/Externals/crossover~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling crossover~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ctl.in_b061ab6a.o: ../../../Source/Pd/Externals/ctl.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ctl.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ctl.out_5c2c7e33.o: ../../../Source/Pd/Externals/ctl.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ctl.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/cusp~_6aff1d07.o: ../../../Source/Pd/Externals/cusp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling cusp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/decay~_f23ff296.o: ../../../Source/Pd/Externals/decay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling decay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/decay2~_559cfa3e.o: ../../../Source/Pd/Externals/decay2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling decay2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/detect~_dea24773.o: ../../../Source/Pd/Externals/detect~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling detect~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dir_dba64ac5.o: ../../../Source/Pd/Externals/dir.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dir.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dollsym_53119894.o: ../../../Source/Pd/Externals/dollsym.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dollsym.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/downsample~_cb43ff2a.o: ../../../Source/Pd/Externals/downsample~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling downsample~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/drive~_ad4cdec6.o: ../../../Source/Pd/Externals/drive~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling drive~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dust~_9fe729c4.o: ../../../Source/Pd/Externals/dust~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dust~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/dust2~_5cdca8d0.o: ../../../Source/Pd/Externals/dust2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling dust2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/else_9b0369cb.o: ../../../Source/Pd/Externals/else.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling else.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/envgen~_8720e6d3.o: ../../../Source/Pd/Externals/envgen~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling envgen~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/eq~_dbb8324a.o: ../../../Source/Pd/Externals/eq~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling eq~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/f2s~_99874d09.o: ../../../Source/Pd/Externals/f2s~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling f2s~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/factor_ef706521.o: ../../../Source/Pd/Externals/factor.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling factor.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fader~_f053675a.o: ../../../Source/Pd/Externals/fader~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fader~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fbdelay~_b1a82da9.o: ../../../Source/Pd/Externals/fbdelay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fbdelay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fbsine~_a208f70d.o: ../../../Source/Pd/Externals/fbsine~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fbsine~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fbsine2~_9ef484a7.o: ../../../Source/Pd/Externals/fbsine2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fbsine2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fdn.rev~_95fa260b.o: ../../../Source/Pd/Externals/fdn.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fdn.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ffdelay~_2b9e9ad.o: ../../../Source/Pd/Externals/ffdelay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ffdelay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/float2bits_47d5b96e.o: ../../../Source/Pd/Externals/float2bits.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling float2bits.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/float2sig~_64d25c75.o: ../../../Source/Pd/Externals/float2sig~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling float2sig~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/floor_fa1d31c4.o: ../../../Source/Pd/Externals/floor.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling floor.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/floor~_498a2d04.o: ../../../Source/Pd/Externals/floor~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling floor~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fold_9cdf5693.o: ../../../Source/Pd/Externals/fold.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fold.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fold~_ff0ca215.o: ../../../Source/Pd/Externals/fold~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fold~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/fontsize_6dcdc922.o: ../../../Source/Pd/Externals/fontsize.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling fontsize.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/format_ed3759c9.o: ../../../Source/Pd/Externals/format.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling format.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/freq.shift~_66cb2a6a.o: ../../../Source/Pd/Externals/freq.shift~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling freq.shift~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/function_65ce6e2a.o: ../../../Source/Pd/Externals/function.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling function.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/function~_54007d5e.o: ../../../Source/Pd/Externals/function~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling function~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gate2imp~_790ec071.o: ../../../Source/Pd/Externals/gate2imp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gate2imp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gbman~_9c3c3d91.o: ../../../Source/Pd/Externals/gbman~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gbman~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/giga.rev~_2fb0a1a5.o: ../../../Source/Pd/Externals/giga.rev~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling giga.rev~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/glide~_a68d5acb.o: ../../../Source/Pd/Externals/glide~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling glide~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/glide2~_2afc98a9.o: ../../../Source/Pd/Externals/glide2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling glide2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gray~_387ff073.o: ../../../Source/Pd/Externals/gray~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gray~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/gui_dbd5e3f3.o: ../../../Source/Pd/Externals/gui.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling gui.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/henon~_a54a3de0.o: ../../../Source/Pd/Externals/henon~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling henon~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/highpass~_22da5ea3.o: ../../../Source/Pd/Externals/highpass~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling highpass~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/highshelf~_ca105b48.o: ../../../Source/Pd/Externals/highshelf~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling highshelf~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hot_dbe16a85.o: ../../../Source/Pd/Externals/hot.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling hot.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hz2rad_95ee5107.o: ../../../Source/Pd/Externals/hz2rad.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling hz2rad.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/hz2rad~_27dcf621.o: ../../../Source/Pd/Externals/hz2rad~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling hz2rad~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ikeda~_3a944550.o: ../../../Source/Pd/Externals/ikeda~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ikeda~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/imp~_a1e3e484.o: ../../../Source/Pd/Externals/imp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling imp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/imp2~_9a774610.o: ../../../Source/Pd/Externals/imp2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling imp2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/impseq~_47679703.o: ../../../Source/Pd/Externals/impseq~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling impseq~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/impulse~_1b5ba43b.o: ../../../Source/Pd/Externals/impulse~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling impulse~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/impulse2~_4ff77d39.o: ../../../Source/Pd/Externals/impulse2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling impulse2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/initmess_a487615a.o: ../../../Source/Pd/Externals/initmess.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling initmess.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/int~_a1f3cd81.o: ../../../Source/Pd/Externals/int~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling int~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/keyboard_1fc5a679.o: ../../../Source/Pd/Externals/keyboard.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling keyboard.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lag~_a6553cfe.o: ../../../Source/Pd/Externals/lag~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lag~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lag2~_2430fcd6.o: ../../../Source/Pd/Externals/lag2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lag2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lastvalue~_7a200f95.o: ../../../Source/Pd/Externals/lastvalue~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lastvalue~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/latoocarfian~_f4a3cf31.o: ../../../Source/Pd/Externals/latoocarfian~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling latoocarfian~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lb_7196208.o: ../../../Source/Pd/Externals/lb.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lb.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lfnoise~_d812a770.o: ../../../Source/Pd/Externals/lfnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lfnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lincong~_240cb45a.o: ../../../Source/Pd/Externals/lincong~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lincong~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/loadbanger_123dab9d.o: ../../../Source/Pd/Externals/loadbanger.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling loadbanger.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/logistic~_569191d6.o: ../../../Source/Pd/Externals/logistic~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling logistic~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/loop_a71df476.o: ../../../Source/Pd/Externals/loop.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling loop.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lorenz~_2662c674.o: ../../../Source/Pd/Externals/lorenz~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lorenz~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lowpass~_dcaaf5cb.o: ../../../Source/Pd/Externals/lowpass~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lowpass~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/lowshelf~_4a52a920.o: ../../../Source/Pd/Externals/lowshelf~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling lowshelf~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/match~_e2a870ab.o: ../../../Source/Pd/Externals/match~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling match~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/median~_cd5af3ac.o: ../../../Source/Pd/Externals/median~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling median~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/merge_609d56f0.o: ../../../Source/Pd/Externals/merge.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling merge.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/message_f7e5563f.o: ../../../Source/Pd/Externals/message.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling message.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/messbox_f7f7580b.o: ../../../Source/Pd/Externals/messbox.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling messbox.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/midi_a87925b3.o: ../../../Source/Pd/Externals/midi.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling midi.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mouse_71dd881d.o: ../../../Source/Pd/Externals/mouse.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mouse.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mov.avg~_c5dcc558.o: ../../../Source/Pd/Externals/mov.avg~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mov.avg~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mov.rms~_e265c8d2.o: ../../../Source/Pd/Externals/mov.rms~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mov.rms~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/mtx~_a91d8e7f.o: ../../../Source/Pd/Externals/mtx~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling mtx~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/nbang_8f78aede.o: ../../../Source/Pd/Externals/nbang.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling nbang.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/note_aa89c244.o: ../../../Source/Pd/Externals/note.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling note.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/note.in_b52a4459.o: ../../../Source/Pd/Externals/note.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling note.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/note.out_f0770324.o: ../../../Source/Pd/Externals/note.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling note.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/nyquist~_36c98275.o: ../../../Source/Pd/Externals/nyquist~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling nyquist~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/op~_dc44a8f5.o: ../../../Source/Pd/Externals/op~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling op~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/openfile_9e21dd98.o: ../../../Source/Pd/Externals/openfile.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling openfile.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/oscilloscope_9a06b221.o: ../../../Source/Pd/Externals/oscilloscope.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling oscilloscope.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pack2_f7aa57b1.o: ../../../Source/Pd/Externals/pack2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pack2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pad_dc4b8d4b.o: ../../../Source/Pd/Externals/pad.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pad.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pan2~_f82c8e61.o: ../../../Source/Pd/Externals/pan2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pan2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pan4~_f82d771f.o: ../../../Source/Pd/Externals/pan4~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pan4~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/panic_f845296f.o: ../../../Source/Pd/Externals/panic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling panic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/parabolic~_69deb037.o: ../../../Source/Pd/Externals/parabolic~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling parabolic~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/peak~_fe62a877.o: ../../../Source/Pd/Externals/peak~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling peak~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pgm.in_48d4c90f.o: ../../../Source/Pd/Externals/pgm.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pgm.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pgm.out_d21d152e.o: ../../../Source/Pd/Externals/pgm.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pgm.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pic_dc4f2c82.o: ../../../Source/Pd/Externals/pic.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pic.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pimp~_5e16ada.o: ../../../Source/Pd/Externals/pimp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pimp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pinknoise~_e4883c2c.o: ../../../Source/Pd/Externals/pinknoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pinknoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pluck~_61e6b8cf.o: ../../../Source/Pd/Externals/pluck~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pluck~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pmosc~_8d6db56e.o: ../../../Source/Pd/Externals/pmosc~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pmosc~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/properties_4327985.o: ../../../Source/Pd/Externals/properties.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling properties.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pulse~_2f81ee57.o: ../../../Source/Pd/Externals/pulse~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pulse~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pulsecount~_ada9aea0.o: ../../../Source/Pd/Externals/pulsecount~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pulsecount~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/pulsediv~_5822cade.o: ../../../Source/Pd/Externals/pulsediv~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling pulsediv~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/quad~_4e933f0f.o: ../../../Source/Pd/Externals/quad~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling quad~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/quantizer_a99e3459.o: ../../../Source/Pd/Externals/quantizer.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling quantizer.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/quantizer~_8a297d0f.o: ../../../Source/Pd/Externals/quantizer~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling quantizer~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rad2hz_cc0e3861.o: ../../../Source/Pd/Externals/rad2hz.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rad2hz.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rad2hz~_b5b9fa07.o: ../../../Source/Pd/Externals/rad2hz~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rad2hz~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ramp~_62071c64.o: ../../../Source/Pd/Externals/ramp~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ramp~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rampnoise~_3dd2aac8.o: ../../../Source/Pd/Externals/rampnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rampnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.f_dfc49d2f.o: ../../../Source/Pd/Externals/rand.f.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.f.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.f~_18d02ef9.o: ../../../Source/Pd/Externals/rand.f~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.f~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.i_dfc4a872.o: ../../../Source/Pd/Externals/rand.i.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.i.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.i~_18d18c16.o: ../../../Source/Pd/Externals/rand.i~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.i~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rand.seq_1e279e8.o: ../../../Source/Pd/Externals/rand.seq.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rand.seq.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/randpulse~_512d2efc.o: ../../../Source/Pd/Externals/randpulse~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling randpulse~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/randpulse2~_d4574a98.o: ../../../Source/Pd/Externals/randpulse2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling randpulse2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/range~_e0083e33.o: ../../../Source/Pd/Externals/range~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling range~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ratio2cents_5f90401c.o: ../../../Source/Pd/Externals/ratio2cents.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ratio2cents.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/ratio2cents~_9278e9ac.o: ../../../Source/Pd/Externals/ratio2cents~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling ratio2cents~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/receiver_7605ba81.o: ../../../Source/Pd/Externals/receiver.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling receiver.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rescale_c1f03d2f.o: ../../../Source/Pd/Externals/rescale.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rescale.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rescale~_7c188ef9.o: ../../../Source/Pd/Externals/rescale~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rescale~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/resonant~_82ee8c2e.o: ../../../Source/Pd/Externals/resonant~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling resonant~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/resonant2~_dac193a6.o: ../../../Source/Pd/Externals/resonant2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling resonant2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rint_b10615cf.o: ../../../Source/Pd/Externals/rint.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rint.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rint~_6fbdca59.o: ../../../Source/Pd/Externals/rint~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rint~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rms~_b140df38.o: ../../../Source/Pd/Externals/rms~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rms~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/rotate~_34175bb.o: ../../../Source/Pd/Externals/rotate~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling rotate~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/routeall_a00c790a.o: ../../../Source/Pd/Externals/routeall.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling routeall.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/router_d1486c9b.o: ../../../Source/Pd/Externals/router.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling router.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/routetype_82a8877b.o: ../../../Source/Pd/Externals/routetype.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling routetype.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/s2f~_afb06449.o: ../../../Source/Pd/Externals/s2f~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling s2f~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saw~_b24e6f47.o: ../../../Source/Pd/Externals/saw~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saw~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/saw2~_975e13ad.o: ../../../Source/Pd/Externals/saw2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling saw2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/schmitt~_f048d79c.o: ../../../Source/Pd/Externals/schmitt~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling schmitt~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/selector_6e50871.o: ../../../Source/Pd/Externals/selector.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling selector.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/separate_eb5fd6b5.o: ../../../Source/Pd/Externals/separate.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling separate.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sequencer~_68c5c79f.o: ../../../Source/Pd/Externals/sequencer~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sequencer~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sh~_dc796401.o: ../../../Source/Pd/Externals/sh~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sh~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/shaper~_ec127e65.o: ../../../Source/Pd/Externals/shaper~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling shaper~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sig2float~_75e882b5.o: ../../../Source/Pd/Externals/sig2float~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sig2float~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sin~_b2bb13f8.o: ../../../Source/Pd/Externals/sin~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sin~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sine~_a49d3409.o: ../../../Source/Pd/Externals/sine~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sine~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/slice_a97401ca.o: ../../../Source/Pd/Externals/slice.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling slice.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sort_b3114cf0.o: ../../../Source/Pd/Externals/sort.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sort.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/spread~_9b61caa3.o: ../../../Source/Pd/Externals/spread~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling spread~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/square~_9c124ab9.o: ../../../Source/Pd/Externals/square~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling square~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/sr~_dc7defb7.o: ../../../Source/Pd/Externals/sr~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling sr~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/standard~_82a2ac59.o: ../../../Source/Pd/Externals/standard~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling standard~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/status~_d255e7c4.o: ../../../Source/Pd/Externals/status~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling status~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/stepnoise~_b0320b82.o: ../../../Source/Pd/Externals/stepnoise~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling stepnoise~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/susloop~_a8d424bb.o: ../../../Source/Pd/Externals/susloop~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling susloop~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/suspedal_6aba83db.o: ../../../Source/Pd/Externals/suspedal.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling suspedal.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/svfilter~_1012f2bb.o: ../../../Source/Pd/Externals/svfilter~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling svfilter~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/symbol2any_89914ea4.o: ../../../Source/Pd/Externals/symbol2any.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling symbol2any.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/t2_71c50d0.o: ../../../Source/Pd/Externals/t2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling t2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/table~_9b96e602.o: ../../../Source/Pd/Externals/table~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling table~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tabplayer~_3442ab9a.o: ../../../Source/Pd/Externals/tabplayer~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tabplayer~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tabwriter~_501260c8.o: ../../../Source/Pd/Externals/tabwriter~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tabwriter~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tempo~_82320b95.o: ../../../Source/Pd/Externals/tempo~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tempo~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/timed.gate~_655ac714.o: ../../../Source/Pd/Externals/timed.gate~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling timed.gate~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/toggleff~_a1e794a2.o: ../../../Source/Pd/Externals/toggleff~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling toggleff~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/touch.in_7a3f186.o: ../../../Source/Pd/Externals/touch.in.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling touch.in.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/touch.out_ed32fb97.o: ../../../Source/Pd/Externals/touch.out.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling touch.out.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/tri~_b4ec7a45.o: ../../../Source/Pd/Externals/tri~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling tri~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trig.delay~_8a9feca5.o: ../../../Source/Pd/Externals/trig.delay~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trig.delay~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trig.delay2~_c93c420f.o: ../../../Source/Pd/Externals/trig.delay2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trig.delay2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trigger2_bad17b4c.o: ../../../Source/Pd/Externals/trigger2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trigger2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/trighold~_e517f37b.o: ../../../Source/Pd/Externals/trighold~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling trighold~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/unmerge_ec99b577.o: ../../../Source/Pd/Externals/unmerge.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling unmerge.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/voices_5b636cd3.o: ../../../Source/Pd/Externals/voices.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling voices.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/vsaw~_53b15923.o: ../../../Source/Pd/Externals/vsaw~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling vsaw~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/vu~_dca99357.o: ../../../Source/Pd/Externals/vu~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling vu~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wavetable~_1a4a597b.o: ../../../Source/Pd/Externals/wavetable~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wavetable~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wrap2_86de6fe0.o: ../../../Source/Pd/Externals/wrap2.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wrap2.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wrap2~_54f0b268.o: ../../../Source/Pd/Externals/wrap2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wrap2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/wt~_dcb73679.o: ../../../Source/Pd/Externals/wt~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling wt~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xfade~_41752d1c.o: ../../../Source/Pd/Externals/xfade~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xfade~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xgate~_773ce06d.o: ../../../Source/Pd/Externals/xgate~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xgate~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xgate2~_703dc747.o: ../../../Source/Pd/Externals/xgate2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xgate2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xmod~_b3fd61ec.o: ../../../Source/Pd/Externals/xmod~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xmod~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xmod2~_cb8d75a8.o: ../../../Source/Pd/Externals/xmod2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xmod2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xselect~_85b2495c.o: ../../../Source/Pd/Externals/xselect~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xselect~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/xselect2~_30757c38.o: ../../../Source/Pd/Externals/xselect2~.c
	-$(V_AT)mkdir -p $(JUCE_OBJDIR)
	@echo "Compiling xselect2~.c"
	$(V_AT)$(CC) $(JUCE_CFLAGS) $(JUCE_CPPFLAGS_SHARED_CODE) $(JUCE_CFLAGS_SHARED_CODE) -o "$@" -c "$<"

$(JUCE_OBJDIR)/zerocross~_32669c78.o: ../../../Source/Pd/Externals/zerocross~.c
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
	@echo Cleaning Camomile
	$(V_AT)$(CLEANCMD)

strip:
	@echo Stripping Camomile
	-$(V_AT)$(STRIP) --strip-unneeded $(JUCE_OUTDIR)/$(TARGET)

-include $(OBJECTS_VST3:%.o=%.d)
-include $(OBJECTS_SHARED_CODE:%.o=%.d)
