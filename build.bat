@echo off

if not exist bin mkdir bin
pushd bin

set compileType=cl

echo [HGE] compiling  main.c with compiler: [%compileType%]

if %compileType%==cl (

call vcvars32

start /b /wait "" "cl" ..\src\main.c /I..\ext\include /link opengl32.lib /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x86" /out:goober.exe

)

IF %compileType%==gcc (
	
gcc ..\src\main.c -o goober.exe -I..\ext\include -lopengl32

)

popd