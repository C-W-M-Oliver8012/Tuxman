#!/bin/bash

cp Tuxman.desktop /usr/share/applications/
cp tuxman /usr/bin/
cp -r ../tuxman/ /usr/share/

rm /usr/share/tuxman/tuxman
rm /usr/share/tuxman/Tuxman.desktop
rm /usr/share/tuxman/Makefile
rm /usr/share/tuxman/install.sh
rm /usr/share/tuxman/tuxman_logo.xcf
