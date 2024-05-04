.POSIX:

CC = gcc
CFLAGS = -W -Wall -std=c11


SRC = main.c aes.c rng.c exponentiation.c protocol.c

all: tp6


tp6: ${SRC} 
	-${CC} ${CFLAGS} -o $@ ${SRC}

