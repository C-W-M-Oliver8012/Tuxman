#!/bin/bash

mkdir /usr/share/tuxman/
cp Tuxman.desktop /usr/share/applications/
cp tuxman /usr/bin/
cp -r data/ /usr/share/tuxman/
cp -r graphics/ /usr/share/tuxman/
cp -r include/ /usr/share/tuxman/
cp -r src/ /usr/share/tuxman/
cp README.md /usr/share/tuxman/
cp LICENSE.md /usr/share/tuxman/
cp tuxman_logo.png /usr/share/tuxman/

chmod 755 /usr/share/tuxman/
chmod 755 /usr/share/tuxman/data/
chmod 755 /usr/share/tuxman/graphics/
chmod 755 /usr/share/tuxman/include/
chmod 755 /usr/share/tuxman/src/
