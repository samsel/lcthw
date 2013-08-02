CFLAGS=-Wall -g

all:
	make ex1

run:
	valgrind --track-origins=yes ./ex1

clean:
	rm -f ex1