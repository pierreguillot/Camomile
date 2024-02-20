<p align="center">
  <a href="https://github.com/pierreguillot/Camomile/wiki">
    <img src="https://user-images.githubusercontent.com/1409918/37906678-2b998b0a-3103-11e8-946a-10df0f3d2eca.png" alt="Logo" width=72 height=72>
  </a>
  <h1 align="center">Camomile</h1>
  <p align="center">
    Create audio plugins with Pure Data patches.
  </p>
  <p align="center">
    <a href="https://github.com/pierreguillot/Camomile/actions/workflows/cmake.yml"><img src="https://github.com/pierreguillot/Camomile/actions/workflows/cmake.yml/badge.svg" alt="Workflows"></a>
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


## Presentation

Camomile is a meta plugin with Pure Data embedded that allows creating audio plugins that load and control Pure Data patches inside digital audio workstations. Camomile supports the VST3, LV2 and Audio Unit plugin formats on Windows, Linux and macOS.

<p align="center">
<img src="https://user-images.githubusercontent.com/1409918/35470969-05182302-0353-11e8-90b5-d37450206adf.png" alt="Examples" width=425 height=325>
</p>

## Instruction

The [latest stable release](https://github.com/pierreguillot/Camomile/releases/latest) of Camomile is available for download along with all previous versions on the [releases page](https://github.com/pierreguillot/Camomile/releases). The Camomile distribution provides sample plugins that can be used directly in digital audio workstations. The [wiki pages](https://github.com/pierreguillot/Camomile/wiki) offer documentation to [install plugins](https://github.com/pierreguillot/Camomile/wiki/How-to-install-plugins) on your computer, [generate plugins](https://github.com/pierreguillot/Camomile/wiki/How-to-generate-plugins) with patches and [create patches](https://github.com/pierreguillot/Camomile/wiki/How-to-create-new-plugins) for audio plugins.

## Compilation

```
git clone --recursive https://github.com/pierreguillot/Camomile.git
cd Camomile
mkdir build && cd build
cmake .. (the generator can be specified using -G"Unix Makefiles", -G"Xcode" or -G"Visual Studio 16 2019" -A x64)
cmake --build .
```

**Important:**
- Please ensure that the git submodules are initialized and updated! You can use the `--recursive` option while cloning or `git submodule update --init --recursive` in the Camomile repository .
- On Linux OS, Juce framework requires to install dependencies, please refer to [Linux Dependencies.md](https://github.com/juce-framework/JUCE/blob/master/docs/Linux%20Dependencies.md) and use the full command.
- The CMake build system have been tested with *Unix Makefiles*, *XCode* and *Visual Studio 16 2019*.

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
