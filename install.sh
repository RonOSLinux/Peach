#! /bin/bash
echo "Make sure you are using Ubuntu >=16.10..."
read -p "Are you sure that you are using Ubuntu 16.10 or later? [y/n]: " input;
if [ $input != 'y' ];
	then exit;
fi
sudo apt --assume-yes install libsdl2-2.0-0
sudo apt --assume-yes install libsdl2-image-2.0-0
sudo apt --assume-yes install libsdl2-ttf-2.0-0
mkdir ~/.peach/
cd ~/.peach/ 
wget -O ./master.zip https://github.com/RonOSLinux/Peach/archive/master.zip
unzip ./master.zip
mv ./Peach-master/* ./
chmod +x ./bin/apps
chmod +x ./bin/desktop
chmod +x ./bin/panel
chmod +x ./bin/peach
chmod +x ./bin/restart
chmod +x ./bin/settings
chmod +x ./bin/shutdown
chmod +x ./bin/software-action
chmod +x ./bin/software-explorer
chmod +x ./bin/tutorial
chmod +x ./bin/upgrade
chmod +x ./bin/upgrade-action
chmod +x ./bin/update-sources
sudo mv ./bin/update-sources /bin/
rm -r ./Peach-master
rm -r ./src
rm -r ./inc
rm ./build.sh
rm ./install.sh
rm ./master.zip
read -p "Do you want to create an autostart? [y/n]: " input
if [ $input != 'y' ];
  then exit;
fi
cd ~/.config/autostart/
echo "[Desktop Entry]" > ./Peach.desktop
echo "Encoding=UTF-8" >> ./Peach.desktop
echo "Version=0.0.0" >> ./Peach.desktop
echo "Type=Application" >> ./Peach.desktop
echo "Name=Peach" >> ./Peach.desktop
echo "Comment=" >> ./Peach.desktop
echo "Exec=sh -c \"~/.peach/bin/peach\"" >> ./Peach.desktop
echo "StartupNotify=false" >> ./Peach.desktop
echo "Terminal=false" >> ./Peach.desktop
echo "Hidden=true" >> ./Peach.desktop
