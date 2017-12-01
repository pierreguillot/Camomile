#!/bin/bash
echo Camomile Generates the new plugins

CamomileInst=Camomile
CamomileFx=CamomileFx

VstExtension=so

ThisPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
VstPath="/usr/lib/vst"

install_plugin() {
    if [ -f $VstPath/$DisPatchName.$VstExtension ]; then
        rm -f $VstPath/$DisPatchName.$VstExtension
    fi
    if [ -d $VstPath/$DisPatchName ]; then
        rm -rf $VstPath/$DisPatchName
    fi
    cp $ThisPath/Builds/$DisPatchName.$VstExtension $VstPath/$DisPatchName.$VstExtension
    cp -rf $ThisPath/Builds/$DisPatchName/ $VstPath/$DisPatchName
    rm -f $ThisPath/Builds/$DisPatchName.$VstExtension
    rm -rf $ThisPath/Builds/$DisPatchName
    echo -n $DisPatchName " "
}

install_all_plugins() {
    echo -n "install "
    for Patch in $ThisPath/Builds/*
    do
      PatchExtension="${Patch##*.}"
      PatchName="${Patch%.*}"
      DisPatch=${Patch##*/}
      DisPatchName="${DisPatch%.*}"
      if [ "$PatchExtension" == "$VstExtension" ]; then
          if [ -d $PatchName ]; then
              install_plugin
          else
              echo -n "(~"$DisPatch "- no folder) "
          fi
      fi
    done
    echo " "
}

generate_plugin() {
    if [ -d $ThisPath/Camomile/$CamomileName.$1 ]; then
        if [ -d $ThisPath/Builds/$PatchName.$1 ]; then
            rm -rf $ThisPath/Builds/$PatchName.$1
        fi
        cp -rf $ThisPath/Camomile/$CamomileName.$1/ $ThisPath/Builds/$PatchName.$1
        cp -rf $PatchesPath/$PatchName/ $ThisPath/Builds/$PatchName
        echo -n $1 " "
    fi
}

generate_plugins_in_folder() {
    if [ "$1" == "Effect" ]; then
        CamomileName=$CamomileFx
    else
        CamomileName=$CamomileInst
    fi
    for Patch in $PatchesPath/*
    do
      PatchName=${Patch##*/}
      if [ -d $PatchesPath/$PatchName ]; then
          echo -n $PatchName
          echo -n " ($1):"
          generate_plugin $VstExtension
          echo ""
      fi
    done
}

if [ ! -d $ThisPath/Builds ]; then
    mkdir $ThisPath/Builds
fi

PatchesPath=$ThisPath/Effects
generate_plugins_in_folder Effect
PatchesPath=$ThisPath/Instruments
generate_plugins_in_folder Instrument

if [ "$1" == "install" ]; then
    install_all_plugins
fi
