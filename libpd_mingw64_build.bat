SET MSYS=C:\msys64
SET MINGW=%MSYS%\mingw64
SET PATH=%MINGW%\bin;%MSYS%\usr\bin
make -C Dependencies/libpd clobber
make -C Dependencies/libpd libpd MULTI=true ADDITIONAL_LDFLAGS="-static -static-libgcc" ADDITIONAL_CFLAGS='-DPD_LONGINTTYPE="long long"'
