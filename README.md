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
    * Properly install and setup msys2 on Windows (be sure to add Mingw64 to path)(it is found in the msys64 folder in the C Directory
	* Download the latest release or just clone the master branch
    * Install the 'mingw-w64-gcc', 'make', and 'mingw-w64-x86_64-pdcurses' packages
    * Comment out '#include <curses.h>' and uncomment '#include <pdcurses/curses.h>' in the functions.h file found in the headers folder
	* Copy and paste the 'libpdcurses.a' file from the Mingw64/lib/ Directory to the Tuxman Directory
	* Open up cmd.exe and cd into the Tuxman Directory
	* Run 'make'
