CC=gcc
args=-g -Wall -Wextra
paths=./include

all:
	$(CC) $(args) -I${paths} main.c -o main.o -lraylib

all_tests: clean
	$(CC) $(args) -I${paths} ./test/hash_map_tests.c -o hash.o 
	 ./hash.o >> hash_map_results.test
	$(CC) $(args) -I${paths} ./test/unordered_list_tests.c -o ulist.o 
	 ./ulist.o >> unordered_list_results.test
	$(CC) $(args) -I${paths} ./test/ordered_list_tests.c -o olist.o 
	 ./olist.o >> ordered_list_results.test

extended:
	$(CC) $(args) -I./include main.c -E -o main.o -lraylib

clean:
	rm -rf *.o \
	rm -rf *.test \