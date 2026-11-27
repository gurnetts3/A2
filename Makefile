CC = gcc
CFLAGS = -Wall -std=c99

make: main.o packInv.o readInv.o
	$(CC) $(CFLAGS) main.o packInv.o readInv.o

main.o: main.c sharedInv.h
	$(CC) $(CFLAGS) -c main.c 

packInv.o: packInv.c packInv.h sharedInv.h
	$(CC) $(CFLAGS) -c packInv.c 

readInv.o: readInv.c readInv.h sharedInv.h
	$(CC) $(CFLAGS) -c readInv.c

PHONY: Clean

Clean:
	rm *.o a.out