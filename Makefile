all:
	$(MAKE) -C Dependencies/LibPdBuild/LinuxMakefile libpdstatic
	$(MAKE) -C Instrument/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	$(MAKE) -C Effect/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	$(MAKE) -C LV2/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	$(MAKE) -C LV2/lv2_file_generator
	mv ./Plugins/libCamomileLV2.so ./Plugins/CamomileLV2.so
