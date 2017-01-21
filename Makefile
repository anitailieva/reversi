CC=gcc
DEPS = board.h
CFLAGS = -Wall -Wextra -std=c11
all: boardmake

%.o: %c $(DEPS)
	$(CC) -c -o $@ $<$(CFLAGS)

boardmake: board.o
	$(CC) -o board board.o $(CFLAGS)
	
clean:
	rm -f board *.o
	
remake: clean board
