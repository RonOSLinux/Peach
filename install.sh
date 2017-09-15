#! /bin/bash
echo "Make sure you are using Ubuntu >=16.10..."
read -p "Are you sure that you are using Ubuntu 16.10 or later? [y/n]" input;
if [ $input != 'y' ];
	then exit;
fi
echo "Installing dependancies..."
sudo apt --assume-yes install libsdl2-2.0-0
sudo apt --assume-yes install libsdl2-image-2.0-0
sudo apt --assume-yes install libsdl2-ttf-2.0-0
echo "Generating Peach Folder..."
mkdir ~/.peach/
cd ~/.peach/ 
echo "Downloading Peach master.zip..."
wget -O ./master.zip https://github.com/RonOSLinux/Peach/archive/master.zip
echo "Extracting master.zip..."
unzip ./master.zip
echo "Deleting uneccessary source files..."
rm -r ./src
rm -r ./inc
rm ./build.sh
echo "Finished!"