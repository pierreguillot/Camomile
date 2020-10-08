<p align="center">
  <a href="https://github.com/pierreguillot/Camomile/wiki">
    <img src="https://user-images.githubusercontent.com/1409918/37906678-2b998b0a-3103-11e8-946a-10df0f3d2eca.png" alt="Logo" width=72 height=72>
  </a>
  <h1 align="center">Camomile-ELSE</h1>
  <p align="center">
    A plugin that loads and controls Pure Data patches.
  </p>
  <p align="center">
    <a href="https://travis-ci.org/pierreguillot/Camomile"><img src="https://img.shields.io/travis/pierreguillot/Camomile.svg?label=travis" alt="Travis CI"></a>
    <a href="https://ci.appveyor.com/project/pierreguillot/camomile/history"><img src="https://img.shields.io/appveyor/ci/pierreguillot/Camomile.svg?label=appveyor" alt="Appveyor CI"></a>
    <a href="https://www.codacy.com/app/pierreguillot/Camomile?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=pierreguillot/Camomile&amp;utm_campaign=Badge_Grade"><img src="https://api.codacy.com/project/badge/Grade/3396e70b99fd4144aa26df2ce98d7e66"/></a>
  </p>
  <p align="center">
    <a href="https://github.com/pierreguillot/Camomile/releases/latest"><img src="https://img.shields.io/github/downloads/pierreguillot/Camomile/total.svg?colorB=007ec6" alt="Downloads"></a>
    <a href="https://github.com/pierreguillot/Camomile/releases/latest"><img src="https://img.shields.io/github/release/pierreguillot/Camomile.svg" alt="Release"></a>
    <a href="https://github.com/pierreguillot/Camomile/blob/master/LICENSE"><img src="https://img.shields.io/badge/license-GPL--v3-blue.svg" alt="License"></a>
  </p>
  <p align="center">
    <a href="https://github.com/pierreguillot/Camomile/wiki"><img src="https://img.shields.io/badge/@-documentation-blue.svg" alt="Documentation"></a>
    <a href="https://github.com/pierreguillot/Camomile/wiki/Credits"><img src="https://img.shields.io/badge/@-credits-blue.svg" alt="Credits"></a>
    <a href="https://vimeo.com/album/4639971"><img src="https://img.shields.io/badge/@-videos-blue.svg" alt="Videos"></a>
  </p>
</p>

## WARNING
This repository is a simple fork with some little edits to compile Camomile with support to [ELSE library](https://github.com/porres/pd-else).
- Issues about the support of ELSE library in Camomile are welcomed.
- Issues about Camomile itself, please fill your issue in https://github.com/pierreguillot/Camomile/issues for better support.

## Presentation

Camomile is a plugin with Pure Data embedded that offers to load and to control patches inside a digital audio workstation. The plugin is available as VST, VST3, LV2 and Audio Unit for Windows, Linux and MacOS. Downloads, documentation and further information are available on the [wiki](https://github.com/pierreguillot/Camomile/wiki) pages of the project.

<p align="center">
<img src="https://user-images.githubusercontent.com/1409918/35470969-05182302-0353-11e8-90b5-d37450206adf.png" alt="Examples" width=425 height=325>
</p>

### Download

The last stable release of the plugin is directly downloadable [here](https://github.com/pierreguillot/Camomile/releases/latest) and a list of all the releases is available [here](https://github.com/pierreguillot/Camomile/releases).

### Instruction

As for the examples given within the distribution, most of the time plugins created with Camomile must be generated. Generating plugins does not require any development skill and is pretty easy and straightforward if your read carefully the [documentation](https://github.com/pierreguillot/Camomile/wiki/How-to-generate-plugins). This operation requires only 6 basic actions (copy/past/rename) and, since the version 1.0.6, a script is offered for Linux and MacOS to speed up the workflow.

To use the plugins, just copy the packages/folders in the audio plugins' location. If you are not familiar with plugins and/or the digital audio workstations, please read this [documentation](https://github.com/pierreguillot/Camomile/wiki/How-to-install-plugins).

At last, this [part](https://github.com/pierreguillot/Camomile/wiki/How-to-create-new-plugins) of the documentation presents how to create new plugins with Camomile.

### Compilation

Download Camomile and its dependencies using git:

```
git clone --recursive https://github.com/pierreguillot/Camomile.git
```

Generate the libpd project using [CMake](https://cmake.org) and compile the libpd library and the plugins:

- **Linux**  
```
cd Camomile-ELSE
cd Dependencies/LibPdBuild/LinuxMakefile && cmake .. -DCMAKE_BUILD_TYPE=Release && cd ../../..
make
```
Important: JUCE requires a set of pre-installed libraries: libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libfreetype6-dev alsa libasound2-dev. Before building Camomile you can run to install everything:
```
sudo apt-get -qq update
sudo apt-get install -y libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libfreetype6-dev alsa libasound2-dev
```
- **Mac**
```
cd Camomile-ELSE
cd Dependencies/LibPdBuild/MacOSX && cmake .. -GXcode && cd ../../..
xcodebuild -workspace Camomile.xcworkspace -scheme Camomile-libpd -configuration Release
```
- **Windows**  
Important: libpd requires the static [pthread](https://github.com/GerHobbelt/pthread-win32.git) library for windows with multithread static runtime library (MT).
```
cd Camomile-ELSE
mkdir Dependencies\LibPd\build && mkdir Dependencies\LibPd\build\msvc && cd Dependencies\LibPd\build\msvc
cmake -G "Visual Studio 14 2015 Win64" -DPD_MULTI=ON -DPD_UTILS=OFF -DMSVC_STATIC_RUNTIME=ON -DMSVC_PTHREAD_LIB="pthread.lib" ../..
msbuild libpd.sln /t:libpdstatic /nologo /verbosity:quiet /p:Configuration=Release /p:Platform=x64
cd ..\..\..
msbuild Instrument/Builds/VisualStudio2015/Camomile.sln /nologo /p:Configuration=Release /p:Platform=x64
msbuild Effect/Builds/VisualStudio2015/Camomile.sln /nologo /p:Configuration=Release /p:Platform=x64
msbuild LV2/Builds/VisualStudio2015/Camomile.sln /nologo /p:Configuration=Release /p:Platform=x64
```

### Organization

- [CICM](http://cicm.mshparisnord.org)
- [Université Paris 8](https://www.univ-paris8.fr)

### Author

- [Pierre Guillot](https://github.com/pierreguillot)

### Credits

- [Pure Data](http://msp.ucsd.edu/software.html) by Miller Puckette and others
- [libpd](http://libpd.cc) by the Peter Brinkmann, Dan Wilcox and others
- [Juce](https://github.com/WeAreROLI/JUCE) by ROLI Ltd.
- [MoodyCamel](https://github.com/cameron314/concurrentqueue) by Cameron Desrochers
- [LV2 PlugIn Technology](http://lv2plug.in) by Steve Harris, David Robillard and others
- [VST PlugIn Technology](https://www.steinberg.net/en/company/technologies/vst3.html) by Steinberg Media Technologies
- [Audio Unit PlugIn Technology](https://developer.apple.com/documentation/audiounit) by Apple
- [Juce LV2 interface](http://www.falktx.com) by Filipe Coelho
- [Console icons](https://www.flaticon.com/authors/gregor-cresnar) by Gregor Cresnar
- [CMake](https://cmake.org/) by Andy Cedilnik, Bill Hoffman, Brad King, Ken Martin, Alexander Neundorf
- Images of the plugin's examples are copyrighted by their respective comics publishers. [Dupuis](https://www.dupuis.com/) for the Bulgroz and AlmondOrgan plugins and [Casterman](https://www.casterman.com/) for the Castafiore plugin. For further information, read this [issue](https://github.com/pierreguillot/Camomile/issues/177).

### Papers

- [LAC 2018 - Camomile: Creating audio plugins with Pure Data](http://lac.linuxaudio.org/2018/pdf/44-paper.pdf)
- [JIM 2018 - Camomile, enjeux et développements d’un plugiciel audio embarquant Pure Data](https://hal.archives-ouvertes.fr/hal-01791392/document).
