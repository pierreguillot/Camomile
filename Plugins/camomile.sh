#!/bin/bash
unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
    CYGWIN*)    machine=Cygwin;;
    MINGW*)     machine=MinGw;;
    *)          machine="UNKNOWN:${unameOut}"
esac


if [ $machine == "Mac" ]; then
    ThisPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
    $ThisPath/CamomileMacOS.sh $1
fi

if [ $machine == "Linux" ]; then
    echo $machine
    ThisPath="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
    $ThisPath/GenerateLinux.sh
fi
