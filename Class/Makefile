CC=gcc
CFLAGS=-I.
DEPS = c_class.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mainmake: main.o c_class.o 
	$(CC) -o mainmake main.o c_class.o -lm
