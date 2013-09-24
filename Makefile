CFLAGS=-Wall -g

# last_modified_c_file =
# 	echo ls -t *.c | tail -1

# get:
# 	last_modified_c_file

all:
	make ex17

run:
	valgrind --track-origins=yes ./ex9

# clean:
# 	rm -f ex1