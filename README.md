****LYNX CC65 DEV ENVIRONEMENT SETUP SCRIPT****


----------------------------------------------------

DESCRIPTION
----------------------------------------------------

This script is used to install a working development environmentfor the Atari Lynx 
within any distribution of linux that has access to the Ubuntu repositories.  

This script will check to make sure that you have gcc, make, and git installed first.
Afterwards, the CC65 (c library and compiler for the lynx) is cloned, built, and installed
from the git repository.  

The script will then install mednafen, the "lynxboot.img" (required to run lynx games
in the emulator), gcc and git.

The script will then create a file structure in your home folder for lynx programing
called "lynx" where a \"blank_project\" template will be copied to.  You can choose
whether or not you want to work out of this folder.

The last thing done by this script is building and installing "sprpck" and installing
it at "/usr/bin".  This program is for converting images into sprite files that can be
built by cc65 into object files that can be linked with your program.

There is no warrantee for this script, so please use it at your own risk.

Tested successfully in Kubuntu 16.10 - May 7th, 2017

----------------------------------------------------

INSTALL
To Install just run the "sh ./install.sh" in the same directory as the script file.  You will 
need to enter your user password once. The process is mostly automatic, with just one
comfirmation at the beginning.

UNINSTALL
Uninstall is similar to install except that after removing cc64 and other previously installed
programs, it will want to comfirm that you want to delete the "lynx" directory in your home
folder.  If you have been working out of this folder we suggest that you backup any data there
before letting the script remove it.

----------------------------------------------------

Credits
----------------------------------------------------

sprpck - Is included in this archive because the current version we are using is currently not
hosted anywhere else on the internet.  Originally written by Bastian Schick, then clean up for
linux was done by Wookie on Atari Age.

Murcho (on Atari Age) - Created a wonderful set of tutorials using CC65, and is how we got
started doing this.  https://atarilynxdeveloper.wordpress.com/series/atarilynxprogrammingtutorial/


----------------------------------------------------

TODO
----------------------------------------------------
Add Chipper to finish a basic music/sfx creation pipeline.
