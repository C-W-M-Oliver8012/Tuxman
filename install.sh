#!/bin/bash

cp Tuxman.desktop /usr/share/applications/
cp Tuxman /usr/bin/
cp -r ../Tuxman/ /usr/share/

rm /usr/share/Tuxman/Tuxman
rm /usr/share/Tuxman/Tuxman.desktop
rm /usr/share/Tuxman/Makefile
rm /usr/share/Tuxman/install.sh
rm /usr/share/Tuxman/Tuxman_logo.xcf
