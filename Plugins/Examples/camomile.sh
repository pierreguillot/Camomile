#!/bin/bash

CamomileInst=Camomile
CamomileFx=CamomileFx
VstExtension=vst
Vst3Extension=vst3
AuExtension=component
LibExtension=so
ThisPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

################################################################################
#           Install all the plugins from ./Builds to a destination             #
################################################################################
install_plugin_mac() {
    local InstallationPath
    if [ "$2" == "$VstExtension" ]; then
        InstallationPath=$3/VST
    elif [ "$2" == "$Vst3Extension" ]; then
        InstallationPath=$3/VST3
    elif [ "$2" == "$AuExtension" ]; then
        InstallationPath=$3/Components
    else
        echo -e "\033[31m"$1.$2" extension not recognized\033[0m"
        return
    fi

    if [ ! -d $InstallationPath ]; then
        mkdir $InstallationPath
    fi

    if [ -d $InstallationPath/$1.$2 ]; then
        rm -rf $InstallationPath/$1.$2
    fi

    cp -rf $ThisPath/Builds/$1.$2 $InstallationPath/$1.$2
    echo $1.$2" in "$InstallationPath
}

install_all_plugins_mac() {
    if [ -d $1 ]; then
        echo  -e "\033[1;30mInstalling Plugins to "$1"\033[0m"
        for Plugin in $ThisPath/Builds/*
        do
            local PluginName=$(basename "$Plugin")
            local PluginExtension="${PluginName##*.}"
            local PluginName="${PluginName%.*}"
            install_plugin_mac $PluginName $PluginExtension $1
        done
        echo -e "\033[1;30mFinished\033[0m"
    else
        echo -e "\033[31m"$1" invalid path\033[0m"
    fi
}

install_plugin_linux() {
    local InstallationPath
    if [ "$2" == "$LibExtension" ]; then
        InstallationPath=$3/vst
    else
        echo -e "\033[31m"$1.$2" extension not recognized\033[0m"
        return
    fi

    if [ ! -d $ThisPath/Builds/$1 ]; then
        echo -e "\033[31m"$2" has no folder\033[0m"
        return
    fi

    if [ ! -d $InstallationPath ]; then
        mkdir $InstallationPath
    fi

    if [ -f $InstallationPath/$1.$2 ]; then
        rm -f $InstallationPath/$1.$2
    fi
    if [ -d $InstallationPath/$1 ]; then
        rm -rf $InstallationPath/$1
    fi
    cp $ThisPath/Builds/$1.$2 $InstallationPath/$1.$2
    cp -rf $ThisPath/Builds/$1/ $InstallationPath/$1

    echo $1.$2" in "$InstallationPath
}

install_all_plugins_linux() {
    if [ -d $1 ]; then
        echo  -e "\033[1;30mInstalling Plugins to "$1"\033[0m"
        for Plugin in $ThisPath/Builds/*
        do
            if [ ! -d $Plugin ]; then
                local PluginName=$(basename "$Plugin")
                local PluginExtension="${PluginName##*.}"
                local PluginName="${PluginName%.*}"
                install_plugin_linux $PluginName $PluginExtension $1
            fi
        done
    else
        echo -e "\033[31m"$1" invalid path\033[0m"
    fi
}

################################################################################
#                       clean all the plugins from ./Builds                    #
################################################################################

clean_plugin_mac() {
    if [ "$2" == "$VstExtension" ] || [ "$2" == "$Vst3Extension" ] || [ "$2" == "$AuExtension" ]; then
        rm -rf $ThisPath/Builds/$1.$2
        echo $1.$2
    else
        echo -e "\033[31m"$1.$2" extension not recognized\033[0m"
        return
    fi
}

clean_plugin_linux() {
    if [ "$2" == "$LibExtension" ]; then
        rm -f $ThisPath/Builds/$1.$2
        if [ -d $ThisPath/Builds/$1 ]; then
            rm -rf $ThisPath/Builds/$1
        fi
        echo $1.$2
    else
        echo -e "\033[31m"$1.$2" extension not recognized\033[0m"
        return
    fi
}

clean_all_plugins_mac() {
    echo  -e "\033[1;30mcleaning Plugins\033[0m"
    for Plugin in $ThisPath/Builds/*
    do
        local PluginName=$(basename "$Plugin")
        local PluginExtension="${PluginName##*.}"
        local PluginName="${PluginName%.*}"
        clean_plugin $PluginName $PluginExtension

    done
    echo -e "\033[1;30mFinished\033[0m"
}

clean_all_plugins_linux() {
    echo  -e "\033[1;30mcleaning Plugins\033[0m"
    for Plugin in $ThisPath/Builds/*
    do
        if [ ! -d $Plugin ]; then
            local PluginName=$(basename "$Plugin")
            local PluginExtension="${PluginName##*.}"
            local PluginName="${PluginName%.*}"
            clean_plugin $PluginName $PluginExtension
        fi
    done
    echo -e "\033[1;30mFinished\033[0m"
}

################################################################################
#                       Generate all the plugins from ./Builds                    #
################################################################################

generate_plugin_vst() {
    if [ -d $ThisPath/../$1.$VstExtension ]; then
        if [ -d $ThisPath/Builds/$3.$VstExtension ]; then
            rm -rf $ThisPath/Builds/$3.$VstExtension
        fi

        cp -rf $ThisPath/../$1.$VstExtension/ $ThisPath/Builds/$3.$VstExtension
        cp -rf $2/$3/ $ThisPath/Builds/$3.$VstExtension/Contents/Resources
        plutil -replace CFBundleName -string $3 $ThisPath/Builds/$3.$VstExtension/Contents/Info.plist
        plutil -replace CFBundleDisplayName -string $3 $ThisPath/Builds/$3.$VstExtension/Contents/Info.plist
        echo -n $VstExtension " "
    else
        echo -n -e "\033[2;30m"$VstExtension" \033[0m"
    fi
}

generate_plugin_vst3() {
    if [ -d $ThisPath/../$1.$Vst3Extension ]; then
        if [ -d $ThisPath/Builds/$3.$Vst3Extension ]; then
            rm -rf $ThisPath/Builds/$3.$Vst3Extension
        fi

        cp -rf $ThisPath/../$1.$Vst3Extension/ $ThisPath/Builds/$3.$Vst3Extension
        cp -rf $2/$3/ $ThisPath/Builds/$3.$Vst3Extension/Contents/Resources
        plutil -replace CFBundleName -string $3 $ThisPath/Builds/$3.$Vst3Extension/Contents/Info.plist
        plutil -replace CFBundleDisplayName -string $3 $ThisPath/Builds/$3.$Vst3Extension/Contents/Info.plist
        echo -n $Vst3Extension " "
    else
        echo -n -e "\033[2;30m"$Vst3Extension" \033[0m"
    fi
}

au_get_plugin_code() {
    while IFS='' read -r line || [[ -n "$line" ]]; do
        local wline=($line)
        if [ "${wline[0]}" == "code" ]; then
            echo ${wline[1]}
            return
        fi
    done < "$1"
    echo "0"
}

generate_plugin_au() {
    if [ ! -f $2/$3/$3.txt ]; then
        echo -n -e "\033[31m(No config file) \033[0m"
        return
    fi

    local code=$(au_get_plugin_code $2/$3/$3.txt)
    if [ "$code" == "0" ]; then
        echo -n -e "\033[31mNo plugin code defined\033[0m"
        return
    fi
    code=${code::4}
    if [ -d $ThisPath/../$1.$AuExtension ]; then
        if [ -d $ThisPath/Builds/$3.$AuExtension ]; then
            rm -rf $ThisPath/Builds/$3.$AuExtension
        fi

        cp -rf $ThisPath/../$1.$AuExtension/ $ThisPath/Builds/$3.$AuExtension
        cp -rf $2/$3/ $ThisPath/Builds/$3.$AuExtension/Contents/Resources
        plutil -replace CFBundleName -string $3 $ThisPath/Builds/$3.$AuExtension/Contents/Info.plist
        plutil -replace CFBundleDisplayName -string $3 $ThisPath/Builds/$3.$AuExtension/Contents/Info.plist
        plutil -replace AudioComponents.name -string $3 $ThisPath/Builds/$3.$AuExtension/Contents/Info.plist
        plutil -replace AudioComponents.subtype -string $code $ThisPath/Builds/$3.$AuExtension/Contents/Info.plist
        echo -n $AuExtension
    else
        echo -n -e "\033[2;30m"$AuExtension"\033[0m"
    fi
}

generate_plugin_lib() {
    if [ -d $ThisPath/$1.$LibExtension ]; then
        if [ -f $ThisPath/Builds/$3.$LibExtension ]; then
            rm -f $ThisPath/Builds/$3.$LibExtension
        fi
        if [ -d $ThisPath/Builds/$3 ]; then
            rm -rf $ThisPath/Builds/$3
        fi

        cp -f $ThisPath/$1.$LibExtension/ $ThisPath/Builds/$3.$LibExtension
        cp -rf $2/$3/ $ThisPath/Builds/$3
        echo -n $LibExtension " "
    else
        echo -n -e "\033[2;30m"$LibExtension" \033[0m"
    fi
}

plugin_get_type() {
    while IFS='' read -r line || [[ -n "$line" ]]; do
        local wline=($line)
        if [ "${wline[0]}" == "type" ]; then
            echo ${wline[1]}
            return
        fi
    done < "$1"
    echo "0"
}

generate_plugins_mac() {
    CamomileName=$CamomileFx
    local type="effect"
    if [ -f $1/$2/$2.txt ]; then
        type=$(plugin_get_type $1/$2/$2.txt)
        type="${type%?}"
        if [ "$type" == "0" ]; then
            CamomileName=$CamomileFx
        elif [ "$type" == "instrument" ] || [ "$type" == "synthesizer" ] || [ "$type" == "inst" ] || [ "$type" == "syn" ]; then
            CamomileName=$CamomileInst
            CamomileName=$CamomileInst
        elif [ "$type" == "effect" ] || [ "$type" == "fx" ]; then
            CamomileName=$CamomileFx
        else
            echo -n -e "\033[31mNo plugin type defined\033[0m"
            return
        fi
    else
        echo -e $2 " \033[31mNo config file defined\033[0m"
        return
    fi
    echo -n $2 "-" $type "- ("
    generate_plugin_vst $CamomileName $1 $2
    generate_plugin_vst3 $CamomileName $1 $2
    generate_plugin_au $CamomileName $1 $2
    echo ")"
}

generate_all_plugins_mac() {
    echo  -e "\033[1;30mGenerating Effects Plugins\033[0m"
    for Patch in $ThisPath/*
    do
      if [ -d $Patch ]; then
          local PluginName=$(basename "$Patch")
          local PluginExtension="${PluginName##*.}"
          local PluginName="${PluginName%.*}"
          generate_plugins_mac $ThisPath $PluginName
      fi
    done
    echo -e "\033[1;30mFinished\033[0m"
}

generate_plugins_linux() {
    if [ "$1" == "Effects" ]; then
        CamomileName=$CamomileFx
    elif [ "$1" == "Instruments" ]; then
        CamomileName=$CamomileInst
    else
        echo -e "\033[31mWrong type of plugins\033[0m"
    fi
    echo -n $PluginName "("
    generate_plugin_lib $1 $2 $3
    echo ")"
}

generate_all_plugins_linux() {
    local CamomileName

    if [ ! -d $PatchesPath ]; then
        echo -e "\033[31m"$2" wrong arguments\033[0m"
        return
    fi

    echo  -e "\033[1;30mGenerating Effects Plugins\033[0m"
    for Patch in $ThisPath/*
    do
      if [ -d $Patch ]; then
          local PluginName=$(basename "$Patch")
          local PluginExtension="${PluginName##*.}"
          local PluginName="${PluginName%.*}"
          generate_plugins_linux $CamomileName $ThisPath $PluginName
      fi
    done
    echo -e "\033[1;30mFinished\033[0m"
}

################################################################################
#                                   Main method                                #
################################################################################


unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac

if [ ! -d $ThisPath/Builds ]; then
    mkdir $ThisPath/Builds
fi

if [ "$1" == "install" ]; then
    if [ -z "$2" ]; then
        if [ $machine == "Mac" ]; then
            install_all_plugins_mac $HOME/Library/Audio/Plug-Ins
        else
            install_all_plugins_linux "/usr/lib/"
        fi
    else
        if [ $machine == "Mac" ]; then
            install_all_plugins_mac $2
        else
            install_all_plugins_linux $2
        fi
    fi
elif [ "$1" == "generate" ]; then
    if [ $machine == "Mac" ]; then
        if [ -z "$2" ]; then
            generate_all_plugins_mac
        else
            echo -e "\033[31m"$2" wrong arguments\033[0m"
        fi
    else
        if [ -z "$2" ]; then
            generate_all_plugins_linux
        else
            echo -e "\033[31m"$2" wrong arguments\033[0m"
        fi
    fi
elif [ "$1" == "clean" ]; then
    if [ $machine == "Mac" ]; then
        clean_all_plugins_mac
    else
        clean_all_plugins_linux "/usr/lib/"
    fi
elif [ -z "$1" ]; then
    echo -e "\033[31mArguments required\033[0m"
else
    echo -e "\033[31m"$1" wrong arguments\033[0m"
fi
