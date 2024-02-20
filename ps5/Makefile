# variables
OUTPUT=ps5
CC=gcc
CFLAGS=-std=c11 -Wall -Werror 
C_FILES=main.c
#targets
all: ps5

ps5: main.o
	echo "Building application"
	$(CC) $(CFLAGS) $^ -o  $(OUTPUT)

main.o: main.c
	echo "Building main.c file"
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	echo "Cleaning project..."
	rm -rf *.o $(OUTPUT) $(OUTPUT)