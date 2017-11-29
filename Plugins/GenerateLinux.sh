#!/bin/bash
echo Camomile Generates the new plugins

CamomileInst=Camomile
CamomileFx=CamomileFx

VstExtension=so
ThisPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

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
