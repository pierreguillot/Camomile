#!/bin/bash

CamomileInst=Camomile
CamomileFx=CamomileFx
VstExtension=vst
Vst3Extension=vst3
AuExtension=component
ThisPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

################################################################################
#           Install all the plugins from ./Builds to a destination             #
################################################################################
install_plugin() {
    local InstallationPath
    if [ "$2" == "$VstExtension" ]; then
        InstallationPath=$3/VST
    elif [ "$2" == "$Vst3Extension" ]; then
        InstallationPath=$3/VST3
    elif [ "$2" == "$AuExtension" ]; then
        InstallationPath=$3/Components
    else
        echo -e "\033[31m"$PluginName.$PluginExtension" extension not recognized\033[0m"
        return
    fi

    if [ -d $InstallationPath/$1.$2 ]; then
        rm -rf $InstallationPath/$1.$2
    fi

    cp -rf $ThisPath/Builds/$1.$2 $InstallationPath/$1.$2
    echo $PluginName.$PluginExtension" in "$InstallationPath
}

install_all_plugins() {
    if [ -d $1 ]; then
        echo  -e "\033[1;30mInstallation plugins to "$1"\033[0m"
        for Plugin in $ThisPath/Builds/*
        do
            local PluginName=$(basename "$Plugin")
            local PluginExtension="${PluginName##*.}"
            local PluginName="${PluginName%.*}"
            install_plugin $PluginName $PluginExtension $1
        done
        echo -e "\033[1;30mFinished\033[0m"
    else
        echo -e "\033[31m"$1" invalid path\033[0m"
    fi
}

################################################################################
#                       Clean all the plugins from ./Builds                    #
################################################################################

clean_plugin() {
    if [ "$2" == "$VstExtension" ] || [ "$2" == "$Vst3Extension" ] || [ "$2" == "$AuExtension" ]; then
        rm -rf $ThisPath/Builds/$1.$2
        echo $PluginName.$PluginExtension
    else
        echo -e "\033[31m"$PluginName.$PluginExtension" extension not recognized\033[0m"
        return
    fi
}

clean_all_plugins() {
    echo  -e "\033[1;30mClean plugins\033[0m"
    for Plugin in $ThisPath/Builds/*
    do
        local PluginName=$(basename "$Plugin")
        local PluginExtension="${PluginName##*.}"
        local PluginName="${PluginName%.*}"
        clean_plugin $PluginName $PluginExtension

    done
    echo -e "\033[1;30mFinished\033[0m"
}

################################################################################
#                       Generate all the plugins from ./Builds                    #
################################################################################

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

if [ "$1" == "install" ]; then
    if [ -z "$2" ]; then
        install_all_plugins $HOME/Library/Audio/Plug-Ins
    else
        install_all_plugins $2
    fi
elif [ "$1" == "clean" ]; then
    clean_all_plugins
else
    echo Camomile Generates the new plugins from $ThisPath
    PatchesPath=$ThisPath/Effects
    generate_plugins_in_folder Effect
    PatchesPath=$ThisPath/Instruments
    generate_plugins_in_folder Instrument
fi
