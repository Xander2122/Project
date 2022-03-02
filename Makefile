CC=gcc
CFLAGS=-std=c99 -lcurses
OUTPUT=program

all: $(OUTPUT)

$(OUTPUT): program.o
	$(CC) $(CFLAGS) program.o -o $(OUTPUT)

program.o: program.c
	$(CC) $(CFLAGS) -c program.c -o program.o
clean:
	rm -rf $(OUTPUT) *.o
