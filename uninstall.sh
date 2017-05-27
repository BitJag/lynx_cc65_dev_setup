
REDBK='\033[0;31;5m'
RED='\033[0;31m'
WHITE='\033[1;37m'
WHITEUL='\033[1;37;4m'
ORANGE='\033[0;33m'
GREEN='\033[0;32m'
CYAN='\033[0;36m'
NC='\033[0m'

echo "\n${CYAN}Removing cc65, mednafen, sprpck, and updating repositories...\n${NC}"

sudo apt-get remove -y mednafen

sudo rm -rv /usr/share/cc65

sudo rm -rv /usr/local/src/cc65

sudo apt-get update

sudo rm -rv ~/.mednafen

sudo rm -v /usr/bin/sprpck

#remove project directories

echo -n "\n${GREEN}Do you wish to keep your Lynx project directories at ~/Lynx (and possibly all your Lynx work to date)? (y/n)?\n${NC}"
read answer
if echo "$answer" | grep -iq "^y" ;then

    echo "${CYAN}\nOkay, we will keep the Lynx project directory.\n${NC}"

else

    echo "${CYAN}\nRemoving project directories\n${NC}"
    
    rm -rv ~/lynx
    
fi

echo "${RED}\nUninstall finished...\n${NC}"

