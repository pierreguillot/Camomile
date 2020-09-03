all:
	$(MAKE) -C Dependencies/LibPdBuild/LinuxMakefile libpdstatic
	$(MAKE) -C Instrument/Builds/LinuxMakefile
	$(MAKE) -C Effect/Builds/LinuxMakefile
	$(MAKE) -C LV2/Builds/LinuxMakefile
	$(MAKE) -C LV2/lv2_file_generator
	mv ./Plugins/libCamomileLV2.so ./Plugins/CamomileLV2.so
