#!/bin/bash
# Change the file type of include_juce_audio_plugin_client_AU.r in Xcode
# to sourcecode.cpp.objcpp.preprocessed (otherwise Au doesn't compile)

#while read a ; do echo ${a//abc/XYZ} ; done < /tmp/file.txt > /tmp/file.txt.t ; mv /tmp/file.txt{.t,}

ProjectFile=$PWD/Builds/MacOSX/Camomile.xcodeproj/project.pbxproj
echo $ProjectFile
while read Line; do
	if [ "$Line" == "/* Begin PBXFileReference section */" ]; then
    	echo "Match:" $Line
	fi
done < $ProjectFile
