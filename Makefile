all:
	$(MAKE) -C Dependencies/LibPd/build/makefile libpdstatic
	$(MAKE) -C Instrument/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	$(MAKE) -C Effect/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
	$(MAKE) -C LV2/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
