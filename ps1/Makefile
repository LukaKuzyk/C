# variables
OUTPUT=ps1
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
C_FILES=playfair.c bmp.c main.c

all: ps1

ps1: main.o playfair.o bmp.o
	echo "Building application"
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o  $(OUTPUT)

main.o: main.c
	echo "Building main.c file"
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

playfair.o: playfair.c
	echo "Building playfair.c file"
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

bmp.o: bmp.c
	echo "Building bmp.c file"
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

clean:
	echo "Cleaning project..."
	rm -rf *.o $(OUTPUT) $(OUTPUT)

