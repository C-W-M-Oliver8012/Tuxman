# Tuxman
Hangman for linux and windows (maybe mac os? but I don't have any way to develop for this platform)

## Installing on Linux

* Instructions
    * First make sure that you have make, gcc, bash, and ncurses installed on your distro
    * Download the latest release
    * Run the 'make' command in the Tuxman directory
    * (Optional) Add the directory to your bash path and run the Tuxman sh package from any directory

## Installing on Windows

* Download the latest release
* Run the Tuxman.exe file (you may be prompted to not run the program but ignore as the program is not malware)

## Compiling on Linux

Refer to the same instructions for Installing

## Compiling on Windows

* Instructions
    * Properly install and setup msys2 on Windows
    * Install the 'mingw-w64-gcc' and 'make' packages
    * Download the latest stable code for pdcurses from https://pdcurses.org/
    * Compile the code for windows and place the curses.h, pdcurses.a, pdcurses.dll in their proper (mingw64) directories
