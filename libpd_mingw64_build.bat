SET MSYS=C:\msys64
SET MINGW=%MSYS%\mingw64
SET PATH=%MINGW%\bin;%MSYS%\usr\bin
make -C libpd clobber
make -C libpd libpd MULTI=true LDFLAGS="$(MINGW_LDFLAGS) -Wl,--output-def=libs/libpd.def -static -static-libgcc -Wl,--out-implib=libs/libpd.lib" ADDITIONAL_CFLAGS='-DPD_LONGINTTYPE="long long"'
