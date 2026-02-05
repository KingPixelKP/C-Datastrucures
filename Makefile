CC=gcc
args=-g -Wall -Wextra 
paths=./include

all:
	$(CC) $(args) -I${paths} main.c -o main.o -lraylib

all_tests: clean
	$(CC) $(args) -I${paths} ./test/hash_map_tests.c -o test.o \
	 ./test.o >> hash_map_results.test

extended:
	$(CC) $(args) -I./include main.c -E -o main.o -lraylib

clean:
	rm -rf *.o \
	rm -rf *.test \