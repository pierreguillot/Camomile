SET MSYS=C:\msys64
SET MINGW=%MSYS%\mingw64
SET PATH=%MINGW%\bin;%MSYS%\usr\bin
make clobber
make -C libpd csharplib ADDITIONAL_CFLAGS='-DPD_LONGINTTYPE="long long" -DPDINSTANCE=1 -DPDTHREADS=1'
