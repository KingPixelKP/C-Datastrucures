CC=gcc
args=-g -Wall -Wextra

all:
	$(CC) $(args) -I./include main.c -o main.o -lraylib