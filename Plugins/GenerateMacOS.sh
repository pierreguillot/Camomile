#!/bin/bash
echo Generates the default plugins
VstCamomile=Camomile.vst
Vst3Camomile=Camomile.vst3
AuCamomile=Camomile.component

VstPath=$HOME/Library/Audio/Plug-Ins/VST
Vst3Path=$HOME/Library/Audio/Plug-Ins/VST3
AuPath=$HOME/Library/Audio/Plug-Ins/Components

PatchesPath=$(PWD)
echo "$PatchesPath"

if [ ! -d $VstPath/$VstCamomile ]; then
    echo "Can't find" $VstCamomile "in" $VstPath
fi
if [ ! -d $Vst3Path/$Vst3Camomile ]; then
    echo "Can't find" $Vst3Camomile "in" $Vst3Path
fi
if [ ! -d $AuPath/$AuCamomile ]; then
    echo "Can't find" $AuCamomile "in" $AuPath
fi

for Patch in $PatchesPath/*
do
  PatchName=${Patch##*/}
  if [ -d $PatchesPath/$PatchName ]; then
      echo -n $PatchName " "
      if [ -d $VstPath/$VstCamomile ]; then
          if [ -d $VstPath/$PatchName.vst ]; then
              rm -rf $VstPath/$PatchName.vst
          fi
          cp -rf $VstPath/$VstCamomile $VstPath/$PatchName.vst
          rm $VstPath/$PatchName.vst/Contents/Resources/Camomile.pd
          rm $VstPath/$PatchName.vst/Contents/Resources/Camomile.txt
          cp -rf $PatchesPath/$PatchName/ $VstPath/$PatchName.vst/Contents/Resources
          echo -n VST " "
      fi

      if [ -d $Vst3Path/$Vst3Camomile ]; then
          if [ -d $Vst3Path/$PatchName.vst3 ]; then
              rm -rf $Vst3Path/$PatchName.vst3
          fi
          cp -rf $Vst3Path/$Vst3Camomile $Vst3Path/$PatchName.vst3
          rm $Vst3Path/$PatchName.vst3/Contents/Resources/Camomile.pd
          rm $Vst3Path/$PatchName.vst3/Contents/Resources/Camomile.txt
          cp -rf $PatchesPath/$PatchName/ $Vst3Path/$PatchName.vst3/Contents/Resources
          echo -n VST3 " "
      fi

      if [ -d $AuPath/$AuCamomile ]; then
          if [ -d $AuPath/$PatchName.component ]; then
              rm -r $AuPath/$PatchName.component
          fi
          cp -r $AuPath/$AuCamomile $AuPath/$PatchName.component
          rm $AuPath/$PatchName.component/Contents/Resources/Camomile.pd
          rm $AuPath/$PatchName.component/Contents/Resources/Camomile.txt
          cp -r $PatchesPath/$PatchName/ $AuPath/$PatchName.component/Contents/Resources
          echo -n AudioUnit " "
      fi
      echo ""
  fi
done
