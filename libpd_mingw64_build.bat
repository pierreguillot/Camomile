SET MSYS=C:\msys64
SET MINGW=%MSYS%\mingw64
SET PATH=%MINGW%\bin;%MSYS%\usr\bin
make  -C libpdclobber
make -C libpd libpd ADDITIONAL_CFLAGS='-DPD_LONGINTTYPE="long long" MULTI=true'
