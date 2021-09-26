CC=gcc
LIBS  = -lopengl32 -lgdi32
CFLAGS = -mavx -m64 -Ibin\hfpch
#TODO: (salmoncatt) dont make me write * for every new sub directory added
SRC=$(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)
OBJS = $(SRC:.c=.o)


PCH_SRC = src/HF/hfpch.h
PCH_OUT = bin\hfpch\hfpch.h.gch

#main: $(OBJS)
#	 $(CC) -o bin\goober $^ $(CFLAGS) $(LIBS)
#	 $(CC) -include $(PCH_SRC) -o bin\goober $^ $(CFLAGS) $(LIBS)


main: $(SRC)
	 $(CC) -include $(PCH_SRC) -o bin\goober $^ $(CFLAGS) $(LIBS)

#obj: $(SRC)
#	 $(CC) -include $(PCH_SRC) -o $^ $(CFLAGS) $(LIBS)


# compile precompiled header file here
hfpch: $(PCH_SRC)
	$(CC) -c -o $(PCH_OUT) $< $(CFLAGS) $(LIBS)

















#start /b /wait "" "cl" src\main.c /I..\ext\include /link opengl32.lib /libpath:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.18362.0\um\x86" /out:goober.exe


