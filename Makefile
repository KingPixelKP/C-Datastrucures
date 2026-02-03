CC=gcc
args=-g -Wall -Wextra

all:
	$(CC) $(args) -I./src/dts main.c -o main.o -lraylib