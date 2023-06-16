 
#!

echo "[HGE] installing needed libraries...\n"


echo "[HGE] updating system..."
echo

sudo pacman -Syu --noconfirm

echo
echo "[HGE] installing gcc"
echo

sudo pacman -S gcc --noconfirm

echo
echo "[HGE] installing make"
echo

sudo pacman -S make --noconfirm

echo
echo "[HGE] installing OpenGL"
echo

sudo pacman -S libglu1-mesa-dev --noconfirm

echo
echo "[HGE] installing X11"
echo

sudo pacman -S libx11-dev xserver-xorg-dev xorg-dev --noconfirm

echo
echo "[HGE] installed all libraries (probably)"
