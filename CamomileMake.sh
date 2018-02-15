#!/bin/bash

clear
echo "Generate libpd"
mkdir Dependencies/LibPd/builds/unixmakefile/
mkdir Dependencies/LibPd/builds/unixmakefile/Release
cd Dependencies/LibPd/builds/unixmakefile/Release
cmake -DCMAKE_BUILD_TYPE=Release ../../..
make libpdstatic
cd ../../../../..
echo "Generate Camomile Instrument"
make -C Instrument/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
echo "Generate Camomile Effect"
make -C Effect/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
