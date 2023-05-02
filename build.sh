#! /bin/sh

echo "[HGE] compiling [Linux]..."

#make -f make_file.linux

echo "[HGE] compiling hfpch.h"
make hfpch_remove_debug -f make_file.linux
make hfpch -f make_file.linux
echo ""

echo "[HGE] compiling HF"
make main -f make_file.linux

echo "[HGE] done compiling [linux]"
