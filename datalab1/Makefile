CC = gcc
CFLAGS = -O0
LIBS = -lm

.PHONY : run clean

run : all 
	./btest

all: btest

btest: btest.c bits.c
	$(CC) $(CFLAGS) $(LIBS) -o btest btest.c bits.c

clean :
	rm btest
