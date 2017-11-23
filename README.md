# Camomile
![](https://cloud.githubusercontent.com/assets/1409918/13611206/9433a744-e561-11e5-8b30-7def4dd19cdd.png)  
**Camomile is a dynamic plugin made with [Juce](http://www.juce.com) that allows to load and to control [Pure Data](http://msp.ucsd.edu/software.html) patches inside a digital audio workstation.**

![](https://cloud.githubusercontent.com/assets/1409918/13610631/ebdacae8-e55e-11e5-903c-fb3ad342adb8.png)

**The plugin is available as VST, VST3 and Audio Unit for Windows, Linux and Mac.**  
**See the documentation for further informations and download.**


[![Travis](https://img.shields.io/travis/pierreguillot/Camomile.svg?label=travis)](https://travis-ci.org/pierreguillot/Camomile)  
[![Appveyor](https://img.shields.io/appveyor/ci/pierreguillot/Camomile.svg?label=appveyor)](https://ci.appveyor.com/project/pierreguillot/camomile/history)  
[![Release](https://img.shields.io/github/release/pierreguillot/Camomile.svg)](https://github.com/pierreguillot/Camomile/releases/latest)  
[![Documentation](https://img.shields.io/badge/wiki-documentation-blue.svg)](https://github.com/pierreguillot/Camomile/wiki)  
[![License](https://img.shields.io/badge/License-GPL--v3-blue.svg)](https://github.com/pierreguillot/Camomile/blob/master/LICENSE)

### Build

#### MacOSX
```
cd libpd
xcodebuild -project libpd.xcodeproj -scheme libpd-osx -configuration Release -arch x86_64 ONLY_ACTIVE_ARCH=NO BUILT_PRODUCTS_DIR="./libs" PDINSTANCE=1 PDTHREADS=1
```
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
