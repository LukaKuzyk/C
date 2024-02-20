#variables
OUTPUT=ps2
CC=gcc
CFLAGS=-std=c11 -Wall -Werror -g
LDLIBS=-lm
C_FILES=ui.c hof.c k.c

all: ps2

ps2: ui.o hof.o k.o
	echo "Building application"
	$(CC) $(CFLAGS) $(LDLIBS) $^ -o $(OUTPUT)

ui.o: ui.c
	echo "Building module.o file"
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

hof.o: hof.c
	echo "Building hof.o file"
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

k.o: k.c
	echo "Building k.o file"
	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@

clean:
	echo "Cleaning project..."
	rm -rf *.o $(OUTPUT) $(OUTPUT)_test

# main.o: main.c
# 	echo "Building main.o file"
# 	$(CC) $(CFLAGS) $(LDLIBS) -c $^ -o $@
