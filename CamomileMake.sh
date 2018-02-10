#!/bin/bash

clear
echo "Generate libpd"
make -C libpd MULTI=true
echo "Generate Camomile Instrument"
make -C Instrument/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
echo "Generate Camomile Effect"
make -C Effect/Builds/LinuxMakefile TARGET_ARCH=-m64 CONFIG=Release
