CC=gcc
CFLAGS=-I -g -Wall

decoder: decoder.o
	$(CC) -fsanitize=address decoder.c -o decoder

clean:
	rm *.o decoder