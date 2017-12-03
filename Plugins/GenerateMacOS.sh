#!/bin/bash

CamomileInst=Camomile
CamomileFx=CamomileFx

VstExtension=vst
Vst3Extension=vst3
AuExtension=component

VstPath=$HOME/Library/Audio/Plug-Ins/VST
Vst3Path=$HOME/Library/Audio/Plug-Ins/VST3
AuPath=$HOME/Library/Audio/Plug-Ins/Components

ThisPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
BuildPath=$ThisPath/Builds

install_plugin() {
    local InstallationPath
    if [ "$2" == "$VstExtension" ]; then
        InstallationPath=$VstPath
    elif [ "$2" == "$Vst3Extension" ]; then
        InstallationPath=$Vst3Path
    elif [ "$2" == "$AuExtension" ]; then
        InstallationPath=$AuPath
    else
        echo -e "\033[31m"$PluginName.$PluginExtension" extension not recognized\033[0m"
        #
        return
    fi

    if [ -d $InstallationPath/$1.$2 ]; then
        rm -rf $InstallationPath/$1.$2
    fi

    cp -rf $BuildPath/$1.$2 $InstallationPath/$1.$2
    echo $PluginName.$PluginExtension" in "$InstallationPath
}

install_all_plugins() {
    echo  -e "\033[1;30mInstallation\033[0m"
    for Plugin in $BuildPath/*
    do
        local PluginName=$(basename "$Plugin")
        local PluginExtension="${PluginName##*.}"
        local PluginName="${PluginName%.*}"
        install_plugin $PluginName $PluginExtension
    done
    echo -e "\033[1;30mFinished\033[0m"
}




generate_plugin() {
    if [ -d $ThisPath/Camomile/$CamomileName.$1 ]; then
        if [ -d $ThisPath/Builds/$PatchName.$1 ]; then
            rm -rf $ThisPath/Builds/$PatchName.$1
        fi
        cp -rf $ThisPath/Camomile/$CamomileName.$1/ $ThisPath/Builds/$PatchName.$1
        cp -rf $PatchesPath/$PatchName/ $ThisPath/Builds/$PatchName.$1/Contents/Resources
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
          generate_plugin $Vst3Extension
          generate_plugin $AuExtension
          echo ""
      fi
    done
}

if [ ! -d $ThisPath/Builds ]; then
    mkdir $ThisPath/Builds
fi

echo Camomile Generates the new plugins from $ThisPath
PatchesPath=$ThisPath/Effects
generate_plugins_in_folder Effect
PatchesPath=$ThisPath/Instruments
generate_plugins_in_folder Instrument

if [ "$1" == "install" ]; then
    install_all_plugins
fi
