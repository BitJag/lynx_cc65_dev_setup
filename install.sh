
REDBK='\033[0;31;5m'
RED='\033[0;31m'
WHITE='\033[1;37m'
WHITEUL='\033[1;37;4m'
ORANGE='\033[0;33m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'



echo "\n\n\

${ORANGE}****LYNX CC65 DEV ENVIRONEMENT SETUP SCRIPT****${NC}

by Will Thorup of Bit${RED}Jag${NC}

${WHITEUL}DESCRIPTION${NC}

${WHITE}This script is used to install a working development environmentfor the Atari Lynx 
within any distribution of linux that has access to the Ubuntu repositories.  

This script will check to make sure that you have gcc, make, and git installed first.
Afterwards, the CC65 (c library and compiler for the lynx) is cloned, built, and installed
from the git repository.  

The script will then install mednafen, the \"lynxboot.img\" (required to run lynx games
in the emulator), gcc, and git.

The script will then create a file structure in your home folder for lynx programing
called \"lynx\" where a \"blank_project\" template will be copied to.  You can choose
whether or not you want to work out of this folder.

The last thing done by this script is building and installing \"sprpck\" and installing
it at \"/usr/bin\".  This program is for converting images into sprite files that can be
built by cc65 into object files that can be linked with your program.

${REDBK}There is no warrantee for this script, so please use it at your own risk.\n${NC}
Tested successfully in Kubuntu 16.10 - Jan 4th, 2017\n"


echo -n "\n${GREEN}Do you wish to install the Atari Lynx CC65 developement environment? (y/n)?${NC}\n"
read answer
if echo "$answer" | grep -iq "^y" ;then

    #update repos and install mednafen, gcc, and git.

    sudo apt-get update

    sudo apt-get install -y --allow-unauthenticated make gcc git mednafen
    
    mkdir -v ~/.mednafen

    # Git clone cc65 build, install, and then remove src
    
    sudo rm -rv /usr/local/src/cc65
    
    git clone https://github.com/cc65/cc65.git
    
    sudo mv ./cc65 /usr/local/src/
    
    make -j9 -C /usr/local/src/cc65/
    
    sudo make install prefix=/usr/ -C /usr/local/src/cc65/
    
    #Get the Lynx boot image unzip and install for mednafen
    
    rm -v LynxBoot.zip 
    
    wget https://atariage.com/Lynx/roms/LynxBoot.zip
    
    unzip LynxBoot.zip -d ~/.mednafen  
    
    rm -v LynxBoot.zip  
    
    mednafen
    
    echo "\n${CYAN}Finished insalling cc65 and mednafen.\n${NC}"
    
    # Create a directory to do lynx dev in, and a blank project
    
    echo "\n${CYAN}Making Lynx project directories and blank project files in users home folder\n${NC}"
    
    mkdir -v ~/lynx
    
    mkdir -v ~/lynx/projects
    
    cp -r ./blank_project ~/lynx/projects/
    
    #Build and install sprpck program
    
    echo "\n${CYAN}Downloading, building and installing \"sprpck\" to \"/usr/bin/\".\n${NC}"
    
    wget https://github.com/kateflower/sprpck/archive/master.zip
    
    unzip master.zip
    
    rm -v master.zip
    
    cd sprpck*
    
    make
    
    sudo cp -v sprpck /usr/bin
    
    cd ..
    
    sudo rm -rv ./sprpck*
    
    cd ..
    
    cd ~/lynx/projects/blank_project/
    
    echo "\n${CYAN}Install finished.  Type \"make run\" in your home directory in \"~/lynx/projects/blank_project/\" folder to build and run your first lynx program.\n${NC}"
    
    echo "\n${CYAN}Type \"make all\" to just build the .lnx file.\n${NC}"
    
else
    echo "${RED}\nYou have chosen not to install.  Exiting...\n${NC}"
fi
