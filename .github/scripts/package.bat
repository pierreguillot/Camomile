@echo off
del Camomile-%1.zip /Q
xcopy Plugins Camomile /E /I
copy README.md Camomile\README.md
copy ChangeLog.md Camomile\ChangeLog.md
copy LICENSE Camomile\LICENSE.txt
7z a Camomile-%1.zip Camomile
@echo on
