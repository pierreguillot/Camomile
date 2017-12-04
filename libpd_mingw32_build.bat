SET MSYS=C:\msys64
SET MINGW=%MSYS%\mingw32
SET PATH=%MINGW%\bin;%MSYS%\usr\bin
make -C libpd clobber
make -C libpd libpd MULTI=true
