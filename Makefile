LIBS  = -lopengl32 -lgdi32
CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard src/*.c) $(wildcard src/*/*.c)

bin\goober: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)
