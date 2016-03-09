# ![](https://cloud.githubusercontent.com/assets/1409918/13611206/9433a744-e561-11e5-8b30-7def4dd19cdd.png) Camomile

Camomile is a dynamic plugin made with [Juce](http://www.juce.com) that allows to load and control [Pure Data](http://msp.ucsd.edu/software.html) patches inside a digital audio workstation.

![](https://cloud.githubusercontent.com/assets/1409918/13610631/ebdacae8-e55e-11e5-903c-fb3ad342adb8.png)

#### Feature :
 - Support for multiple plugin instances
 - Automatic creation of GUIs (toggle, slider, radio, comment and numbox)
 - Automatic recognition of parameters (name, label, range, size, etc.)
 - Up to 16 channels
 - Up to 32 parameters
 - Support for Midi

#### Operating Systems :
 - [x] Mac Os support
 - [ ] Linux support
 - [ ] Windows support

#### Tested DAW :
 - [x] Reaper 32-bit v5.16 (Mac Os)
 - [x] Reaper 64-bit v5.16 (Mac Os)
 - [x] Ableton Live 9.2.3 32-bit (Mac Os)
 - [ ] Ableton Live 9 64-bit
 - [ ] Steinberg Cubase
 - [ ] Studio One 3
 - [x] Cycling'74 Max 5 (Mac Os)
 - [x] Cycling'74 Max 6 (Mac Os)
 - [x] OhmStudio (Mac Os)
 - [x] Ardour (Linux)

#### Known Issues :
 - The VST3 plugin is limited to 14 channels due to the new channel management offered by Juce. We'll try to fix it later, but for the moment we suggest to use the VST2 plugin.
 - The names and the labels of the parameters shouldn't change after the plugin creation. Since the parameters depend on the patches and that the plugin loads the patches after its creation, some DAW don't display the name and the label in their own GUI.

### How to use the Camomile plugin:

1. Download the [plugin](https://github.com/pierreguillot/Camomile/releases/download/v0.0.3-beta/Camomile_v0.0.3.zip) (*vst*, *vst3*) for Mac.
2. Put the binaries in the folders :  
 * /Users/"user name"/Library/Audio/Plug-Ins/VST for the vst.
 * /Users/"user name"/Library/Audio/Plug-Ins/VST3 for the vst3.
3. Open your DAW and load the plugin.
4. Click on the camomile flower. Open one of the Pure Data patches given with the binaries. Create your own Camomile patch is very easy, follow the next section.

### How to create a patch for the Camomile plugin:

* Use the *adc~* and the *dac~* objects to receive and send the signal from the plugin.    
![](https://cloud.githubusercontent.com/assets/1409918/13610984/91081d12-e560-11e5-8abb-f924367ab6eb.png)    

* Add a label (the first word is the name of the parameter and the second word is the label of the parameter) and a receive symbol to a GUI object (only the *toggle*, the *slider*, the *radio* and the *numbox* are available for the moment) to create a parameter. The minimum and maximum values will be used for the range of the parameter.  
![](https://cloud.githubusercontent.com/assets/1409918/13611062/eb6348a4-e560-11e5-8c62-b41803183783.png)

* Add only a receive symbol to a GUI object if you want to use a second interfaces to control a parameter.  
![](https://cloud.githubusercontent.com/assets/1409918/13611063/eb74e08c-e560-11e5-8d34-4df8559bbb8d.png)

* Activate the  "Graph-On-Parent" option in your patch as and use the size and the offset to define the visible area of the patch.  
![](https://cloud.githubusercontent.com/assets/1409918/13611033/c48b69fa-e560-11e5-9ab8-3950adba08f0.png)

> You should always ensure that the send and receive symbols are specifics to the patch instance by using *$0*.

#### Author:
 - Pierre Guillot  

#### Organizations:
 - CICM
 - Université Paris 8
 - Labex Arts H2H  

#### Credits:
 - Pure Data by Miller Puckette
 - Juce by ROLI Ltd.
 - VST PlugIn Technology by Steinberg Media Technologies

### Compilation
 - On Linux:
  - you should have *x11* installed:
    - sudo apt-get install libx11-dev
    - sudo apt-get install libxrandr-dev
    - sudo apt-get install libxinerama-dev
    - sudo apt-get install libxcursor-dev
  - you should have *freetype* installed
    - sudo apt-get install python-dev libfreetype6-dev
  - Available architectures:
    - m32
    - m64
    - arm v6
    - arm v7
  - Available configurations:
    - Debug
    - Release
  - Instructions example:
    - cd Builds/LinuxMakefile
    - make (default) or make TARGET_ARCH=-m64 CONFIG=Release

> If you want to compile the plugin as a VST, you should put the VST SDK in the *ThirdParty/Vst* folder. VST is a trademark of Steinberg Media Technologies GmbH. Please register the SDK via the 3rd party developper license on Steinberg site.
