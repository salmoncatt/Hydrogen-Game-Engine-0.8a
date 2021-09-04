CC=gcc
LIBS  = -lopengl32 -lgdi32
CFLAGS = -mavx

# Should be equivalent to your list of C files, if you don't build selectively
#TODO: (salmoncatt) dont make me write * for every new sub directory added
SRC=$(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)

#precompiled header file stuff

#TODO: (salmoncatt) eyo could you make pch files work pls thanks

#PCH_SRC = src/HF/hfpch.h
#PCH_OUT = hfpch.gch
#bin\$(PCH_OUT): $(PCH_SRC)
	#gcc -o $@ $^ $(CFLAGS) $(LIBS)

#start /b /wait "" "cl" src\main.c /I..\ext\include /link opengl32.lib /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x86" /out:goober.exe

bin\goober: $(SRC)
	 $(CC) -o $@ $^ $(CFLAGS) $(LIBS)

