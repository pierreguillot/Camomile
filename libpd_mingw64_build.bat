SET MSYS=C:\msys64
SET MINGW=%MSYS%\mingw64
SET PATH=%MINGW%\bin;%MSYS%\usr\bin
make -C libpd clobber
make -C libpd libpd MULTI=true ADDITIONAL_CFLAGS='-DPD_LONGINTTYPE="long long"'
