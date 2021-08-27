LIBS  = -lopengl32 -lgdi32
CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
#TODO: (salmoncatt) dont make me write * for every new sub directory added
SRC=$(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)

#precompiled header file stuff

#TODO: (salmoncatt) eyo could you make pch files work pls thanks

#PCH_SRC = src/HF/hfpch.h
#PCH_OUT = hfpch.gch
#bin\$(PCH_OUT): $(PCH_SRC)
	#gcc -o $@ $^ $(CFLAGS) $(LIBS)

bin\goober: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

