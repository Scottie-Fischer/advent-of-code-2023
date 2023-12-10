CC=gcc
CFLAGS=-I -g -Wall

cubes: cubes.o
	$(CC) -fsanitize=address cubes.c -o cubes

clean:
	rm *.o cubes