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
      if [ -d $VstPath/$CamomileName.$VstExtension ]; then
          if [ -d $VstPath/$PatchName.$VstExtension ]; then
              rm -rf $VstPath/$PatchName.$VstExtension
          fi
          cp -rf $VstPath/$CamomileName.$VstExtension $VstPath/$PatchName.$VstExtension
          cp -rf $PatchesPath/$PatchName/ $VstPath/$PatchName.$VstExtension/Contents/Resources
          echo -n VST " "
      fi

      if [ -d $Vst3Path/$CamomileName.$Vst3Extension ]; then
          if [ -d $Vst3Path/$PatchName.$Vst3Extension ]; then
              rm -rf $Vst3Path/$PatchName.$Vst3Extension
          fi
          cp -rf $Vst3Path/$CamomileName.$Vst3Extension $Vst3Path/$PatchName.$Vst3Extension
          cp -rf $PatchesPath/$PatchName/ $Vst3Path/$PatchName.$Vst3Extension/Contents/Resources
          echo -n VST3 " "
      fi

      if [ -d $AuPath/$CamomileName.$AuExtension ]; then
          if [ -d $AuPath/$PatchName.$AuExtension ]; then
              rm -r $AuPath/$PatchName.$AuExtension
          fi
          cp -r $AuPath/$CamomileName.$AuExtension $AuPath/$PatchName.$AuExtension
          cp -r $PatchesPath/$PatchName/ $AuPath/$PatchName.$AuExtension/Contents/Resources
          echo -n AudioUnit " "
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
      if [ -d $VstPath/$CamomileName.$VstExtension ]; then
          if [ -d $VstPath/$PatchName.$VstExtension ]; then
              rm -rf $VstPath/$PatchName.$VstExtension
          fi
          cp -rf $VstPath/$CamomileName.$VstExtension $VstPath/$PatchName.$VstExtension
          cp -rf $PatchesPath/$PatchName/ $VstPath/$PatchName.$VstExtension/Contents/Resources
          echo -n VST " "
      fi

      if [ -d $Vst3Path/$CamomileName.$Vst3Extension ]; then
          if [ -d $Vst3Path/$PatchName.$Vst3Extension ]; then
              rm -rf $Vst3Path/$PatchName.$Vst3Extension
          fi
          cp -rf $Vst3Path/$CamomileName.$Vst3Extension $Vst3Path/$PatchName.$Vst3Extension
          cp -rf $PatchesPath/$PatchName/ $Vst3Path/$PatchName.$Vst3Extension/Contents/Resources
          echo -n VST3 " "
      fi

      if [ -d $AuPath/$CamomileName.$AuExtension ]; then
          if [ -d $AuPath/$PatchName.$AuExtension ]; then
              rm -r $AuPath/$PatchName.$AuExtension
          fi
          cp -r $AuPath/$CamomileName.$AuExtension $AuPath/$PatchName.$AuExtension
          cp -r $PatchesPath/$PatchName/ $AuPath/$PatchName.$AuExtension/Contents/Resources
          echo -n AudioUnit " "
      fi
      echo ""
  fi
done
