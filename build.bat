@echo off

if not exist bin mkdir bin
if not exist bin\hfpch mkdir bin\hfpch

if not exist bin\freetype.dll (

echo [HGE] copying freetype.dll to bin
copy "ext\lib\freetype.dll" "bin\freetype.dll"
echo[

)


set compileType=gcc

echo [HGE] compiling...



if %compileType%==cl (

echo [ERROR] cl has been buggy and not setup, please use gcc

call vcvars32

make

echo start /b /wait "" "cl" src\main.c /I..\ext\include /link opengl32.lib /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x86" /out:goober.exe

)

IF %compileType%==gcc (

echo[
echo [HGE] compiling resources
windres res.rc -O coff -o bin/hf_res.res

echo[

echo [HGE] compiling hfpch.h
make hfpch_remove_debug
make hfpch
echo[

echo [HGE] compiling HF
make main

)

echo[
echo [HGE] done compiling


pause