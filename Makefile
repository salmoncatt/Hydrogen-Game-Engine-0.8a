LIBS  = -lopengl32 -lgdi32
CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
#TODO: (salmoncatt) dont make me write * for every new sub directory added
SRC=$(wildcard src/*.c) $(wildcard src/*/*.c) $(wildcard src/*/*/*.c)

bin\goober: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
