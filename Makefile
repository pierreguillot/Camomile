all:
	$(MAKE) -C Dependencies/libpd.builds/LinuxMakefile libpdstatic
	$(MAKE) -C Instrument/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	$(MAKE) -C Effect/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	$(MAKE) -C LV2/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	mv ./Plugins/libCamomileLV2.so ./Plugins/CamomileLV2.so
