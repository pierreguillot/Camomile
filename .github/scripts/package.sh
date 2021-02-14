#!/bin/bash

rm -f Camomile-$1.zip
cp -r Plugins Camomile
cp README.md Camomile/README.md
cp ChangeLog.md Camomile/ChangeLog.md
cp LICENSE Camomile/LICENSE.txt
zip -r -q Camomile-$1.zip Camomile
rm -r Camomile
