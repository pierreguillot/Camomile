# Camomile
![](https://cloud.githubusercontent.com/assets/1409918/13611206/9433a744-e561-11e5-8b30-7def4dd19cdd.png)

Camomile is a set of dynamic plugins with [Pure Data](http://msp.ucsd.edu/software.html) embedded. The plugins offer to load and to control patches inside a digital audio workstation. The plugins are available as VST, VST3 and Audio Unit for Windows, Linux and Mac.

![](https://cloud.githubusercontent.com/assets/1409918/13610631/ebdacae8-e55e-11e5-903c-fb3ad342adb8.png)


[![Travis](https://img.shields.io/travis/pierreguillot/Camomile.svg?label=travis)](https://travis-ci.org/pierreguillot/Camomile)  
[![Appveyor](https://img.shields.io/appveyor/ci/pierreguillot/Camomile.svg?label=appveyor)](https://ci.appveyor.com/project/pierreguillot/camomile/history)  
[![Release](https://img.shields.io/github/release/pierreguillot/Camomile.svg)](https://github.com/pierreguillot/Camomile/releases/latest)  
[![Documentation](https://img.shields.io/badge/wiki-documentation-blue.svg)](https://github.com/pierreguillot/Camomile/wiki)  
[![License](https://img.shields.io/badge/License-GPL--v3-blue.svg)](https://github.com/pierreguillot/Camomile/blob/master/LICENSE)

---
## Use
The Camomile plugins are a set of meta plugins. They are not directly usable in a DAW but can be used to generate new plugins. The distribution contains a *Camomile* folder with the effect version *CamomileFx* and the instrument version *Camomile* of the Camomile meta plugins and with the *extensions* VST (.vst), VST3 (.vst3) & AU (.component) on MacOS, VST (.dll) & VST3 (.vst3) on Windows and VST (.so) on Linux.

The folders *Effects* and *Instruments* contain each one a set of folders. And each of these folders can be use to generate a plugin. What is important is that the name of a folder corresponds to the name of the new plugin (the name that will appears in your DAW), that it contains one patch identically named (the main patch loaded by the plugin) and one text file identically named that defines the plugins options and functionalities and it can also contain abstraction, sound files, etc (or whatever you want).

To generate a new plugin with a folder, it's very straightforward and easy. You simply have to copy the Camomile plugin(s) of your choice (depending on if you want to create an instrument or an effect, an Audio Unit or a VST) and to rename it to the name of the folder. On MacOS, the plugins are bundles so you have to copy the content of the folder (with the patch and the information) inside  the *Resources* folder of the plugin (right click on the plugin, show package contents, open *Contents*, open *Resources*). To use it on MacOS, you only have to move the plugin to your favorite plugins location. And on Windows and Linux, you only have to move the plugin and the folder associated to your favorite plugins location.

If you want to generate all the examples, on MacOS, you can run
```
./GenerateMacOS.sh
```
or if you also want to install them in the standard plugin location, you can run
```
./GenerateMacOS.sh install
```
and on Linux, you can run
```
./GenerateLinux.sh
```

---
## Compilation
The cross-platform dependencies (libPd, Pure Data, JUCE and the VST SDK), are integrated as submodules to the repository. You need to pull the repository and its submodules:

```
git clone --recursive https://github.com/pierreguillot/Camomile.git  
cd Camomile
```

### MacOS
To compile the AU, VST & VST3 plugins on MacOS, you first need to compile the static version of libPd for multi instances and multi threads. The static library is expected to be in the folder *libpd/libs*.  Thereafter, you can compile the Camomile plugins. There two options:

- Manual  
For the first step, you can compile the *libpd-osx-multi* from the project *libpd.xcodeproj* located in the *libpd* folder (don't forget to change the destination folder). Then you can compile all the targets of the the project *Camomile.xcodeproj* located in *Builds/MacOSX*. If you want the Fx version of the plugin, you must change the configuration to **ReleaseFx** or *DebugFx*.

- Command Line  
 At the root of this directory, you can run the two following commands
```
xcodebuild -project libpd/libpd.xcodeproj -target libpd-osx-multi -configuration Release ONLY_ACTIVE_ARCH=NO CONFIGURATION_BUILD_DIR="./libs" | egrep -A 5 "(error|warning):"
xcodebuild -project Builds/MacOSX/Camomile.xcodeproj -configuration Release
```
And/or for the Fx version of the plugin:
```
xcodebuild -project Builds/MacOSX/Camomile.xcodeproj -configuration ReleaseFx
```

If you want to modify the Camomile project, you should use *Camomile.jucer* with the Juce's projucer application. If you want to compile the Audio Unit, after generating the XCode project, you must change the type of the *include_juce_audio_plugin_client_AU.r* located in the folder *JuceLibraryCode* to *Objective-C++ preprocessor*.

### Linux
To compile VST plugins on Linux, JUCE requires a large set of dependencies, to install everything you should run this command (for further information you should refer to the JUCE documentation):
```
sudo apt-get -qq update
sudo apt-get install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev python-dev libfreetype6-dev libgtk-3-dev libcurl4-gnutls-dev alsa libasound2-dev
sudo add-apt-repository -y ppa:webkit-team/ppa
sudo apt-get -qq update
sudo apt-get install -y libwebkit2gtk-4.0-37 libwebkit2gtk-4.0-dev
```

First, you should compile libPd with multi instance and multi threads support. The static library is expected to be in the folder *libpd/libs*. For this, you can follow the libPd documentation or run:

```
make -C libpd/ UTIL=true EXTRA=true ADDITIONAL_CFLAGS="-DPDINSTANCE=1 -DPDTHREADS=1"
```
Then you can compile the Camomile plugin. The makefile are located in the folder *Builds/LinuxMakefile*. You can specify the target with with *TARGET_ARCH* (-m32 or -m64) and the configuration with *CONFIG* (Debug, DebugFx, Releaseo r ReleaseFx). For example:
```
make -C Builds/LinuxMakefile/ TARGET_ARCH=-m64 CONFIG=Release
make -C Builds/LinuxMakefile/ TARGET_ARCH=-m64 CONFIG=ReleaseFx
```
### Windows

Coming soon... I hope

---
## Credits

[Pure Data](http://msp.ucsd.edu/software.html) by Miller Puckette and others  
[JUCE](http://www.juce.com)  by ROLI Ltd.  
[libPd](https://github.com/libpd/libpd) by the Pure Data community  
[VST PlugIn Technology](https://www.steinberg.net/en/company/developers.html) by Steinberg Media Technologies

---
### License

Copyright (C) 2017, Pierre Guillot

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
