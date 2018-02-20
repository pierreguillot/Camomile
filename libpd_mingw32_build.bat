SET MSYS=C:\msys64
SET MINGW=%MSYS%\mingw32
SET PATH=%MINGW%\bin;%MSYS%\usr\bin
make -C Dependencies/libpd clobber
make -C Dependencies/libpd libpd MULTI=true ADDITIONAL_LDFLAGS="-static -static-libgcc"
