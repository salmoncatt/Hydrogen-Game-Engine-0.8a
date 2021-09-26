@echo off

if not exist bin mkdir bin
if not exist bin\hfpch mkdir bin\hfpch

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

echo [HGE] compiling hfpch.h
make hfpch
echo[

echo [HGE] compiling HF
make main

)

echo[
echo [HGE] done compiling


pause