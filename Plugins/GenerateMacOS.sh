#!/bin/bash
echo Camomile Generates the new plugins

CamomileInst=Camomile
CamomileFx=CamomileFx

VstExtension=vst
Vst3Extension=vst3
AuExtension=component

VstPath=$HOME/Library/Audio/Plug-Ins/VST
Vst3Path=$HOME/Library/Audio/Plug-Ins/VST3
AuPath=$HOME/Library/Audio/Plug-Ins/Components

ThisPath=$(PWD)

if [ ! -d $VstPath/$VstCamomile ]; then
    echo "Can't find" $VstCamomile "in" $VstPath
fi
if [ ! -d $Vst3Path/$Vst3Camomile ]; then
    echo "Can't find" $Vst3Camomile "in" $Vst3Path
fi
if [ ! -d $AuPath/$AuCamomile ]; then
    echo "Can't find" $AuCamomile "in" $AuPath
fi

PatchesPath=$ThisPath/Effects
for Patch in $PatchesPath/*
do
  PatchName=${Patch##*/}
  if [ -d $PatchesPath/$PatchName ]; then
      echo -n $PatchName
      echo -n " (Effect):"
      CamomileName=CamomileFx
      if [ -d $ThisPath/Camomile/$CamomileName.$VstExtension ]; then
          if [ -d $ThisPath/$PatchName.$VstExtension ]; then
              rm -rf $ThisPath/$PatchName.$VstExtension
          fi
          cp -rf $ThisPath/Camomile/$CamomileName.$VstExtension/ $ThisPath/$PatchName.$VstExtension
          cp -rf $PatchesPath/$PatchName/ $ThisPath/$PatchName.$VstExtension/Contents/Resources
          if [ "$1" == "install" ]; then
              if [ -d $VstPath/$PatchName.$VstExtension ]; then
                  rm -rf $VstPath/$PatchName.$VstExtension
              fi
              cp -rf $ThisPath/$PatchName.$VstExtension/ $VstPath/$PatchName.$VstExtension
              rm -rf $ThisPath/$PatchName.$VstExtension
          fi
          echo -n VST " "
      fi

      if [ -d $ThisPath/Camomile/$CamomileName.$Vst3Extension ]; then
          if [ -d $ThisPath/$PatchName.$Vst3Extension ]; then
              rm -rf $ThisPath/$PatchName.$Vst3Extension
          fi
          cp -rf $ThisPath/Camomile/$CamomileName.$Vst3Extension/ $ThisPath/$PatchName.$Vst3Extension
          cp -rf $PatchesPath/$PatchName/ $ThisPath/$PatchName.$Vst3Extension/Contents/Resources
          if [ "$1" == "install" ]; then
              if [ -d $Vst3Path/$PatchName.$Vst3Extension ]; then
                  rm -rf $Vst3Path/$PatchName.$Vst3Extension
              fi
              cp -rf $ThisPath/$PatchName.$Vst3Extension/ $Vst3Path/$PatchName.$Vst3Extension
              rm -rf $ThisPath/$PatchName.$Vst3Extension
          fi
          echo -n VST3 " "
      fi

      if [ -d $ThisPath/Camomile/$CamomileName.$AuExtension ]; then
          if [ -d $ThisPath/$PatchName.$AuExtension ]; then
              rm -rf $ThisPath/$PatchName.$AuExtension
          fi
          cp -rf $ThisPath/Camomile/$CamomileName.$AuExtension/ $ThisPath/$PatchName.$AuExtension
          cp -rf $PatchesPath/$PatchName/ $ThisPath/$PatchName.$AuExtension/Contents/Resources
          if [ "$1" == "install" ]; then
              if [ -d $AuPath/$PatchName.$AuExtension ]; then
                  rm -rf $AuPath/$PatchName.$AuExtension
              fi
              cp -rf $ThisPath/$PatchName.$AuExtension/ $AuPath/$PatchName.$AuExtension
              rm -rf $ThisPath/$PatchName.$AuExtension
          fi
          echo -n AudioUnit " "
      fi
      if [ "$1" == "install" ]; then
          echo -n "installed"
      fi
      echo ""
  fi
done

PatchesPath=$ThisPath/Instruments
for Patch in $PatchesPath/*
do
  PatchName=${Patch##*/}
  if [ -d $PatchesPath/$PatchName ]; then
      echo -n $PatchName
      echo -n " (Instrument):"
      CamomileName=Camomile
      if [ -d $ThisPath/Camomile/$CamomileName.$VstExtension ]; then
          if [ -d $ThisPath/$PatchName.$VstExtension ]; then
              rm -rf $ThisPath/$PatchName.$VstExtension
          fi
          cp -rf $ThisPath/Camomile/$CamomileName.$VstExtension/ $ThisPath/$PatchName.$VstExtension
          cp -rf $PatchesPath/$PatchName/ $ThisPath/$PatchName.$VstExtension/Contents/Resources
          if [ "$1" == "install" ]; then
              cp -rf $ThisPath/$PatchName.$VstExtension/ $VstPath/$PatchName.$VstExtension
              rm -rf $ThisPath/$PatchName.$VstExtension
          fi
          echo -n VST " "
      fi

      if [ -d $ThisPath/Camomile/$CamomileName.$Vst3Extension ]; then
          if [ -d $ThisPath/$PatchName.$Vst3Extension ]; then
              rm -rf $ThisPath/$PatchName.$Vst3Extension
          fi
          cp -rf $ThisPath/Camomile/$CamomileName.$Vst3Extension/ $ThisPath/$PatchName.$Vst3Extension
          cp -rf $PatchesPath/$PatchName/ $ThisPath/$PatchName.$Vst3Extension/Contents/Resources
          if [ "$1" == "install" ]; then
              if [ -d $Vst3Path/$PatchName.$Vst3Extension ]; then
                  rm -rf $Vst3Path/$PatchName.$Vst3Extension
              fi
              cp -rf $ThisPath/$PatchName.$Vst3Extension/ $Vst3Path/$PatchName.$Vst3Extension
              rm -rf $ThisPath/$PatchName.$Vst3Extension
          fi
          echo -n VST3 " "
      fi

      if [ -d $ThisPath/Camomile/$CamomileName.$AuExtension ]; then
          if [ -d $ThisPath/$PatchName.$AuExtension ]; then
              rm -rf $ThisPath/$PatchName.$AuExtension
          fi
          cp -rf $ThisPath/Camomile/$CamomileName.$AuExtension/ $ThisPath/$PatchName.$AuExtension
          cp -rf $PatchesPath/$PatchName/ $ThisPath/$PatchName.$AuExtension/Contents/Resources
          if [ "$1" == "install" ]; then
              if [ -d $AuPath/$PatchName.$AuExtension ]; then
                  rm -rf $AuPath/$PatchName.$AuExtension
              fi
              cp -rf $ThisPath/$PatchName.$AuExtension/ $AuPath/$PatchName.$AuExtension
              rm -rf $ThisPath/$PatchName.$AuExtension
          fi
          echo -n AudioUnit " "
      fi
      if [ "$1" == "install" ]; then
          echo -n "installed"
      fi
      echo ""
  fi
done
