 
#!

echo "[HGE] installing needed libraries..."

sudo apt-get -y update
sudo apt-get -y upgrade
sudo apt-get -y install gcc
sudo apt-get -y install make
sudo apt-get -y install libglu1-mesa-dev
sudo apt-get -y install libx11-dev xserver-xorg-dev xorg-dev


echo "[HGE] installed all libraries (probably)"
