CC=clang
CFLAGS=-Wall -Wextra -pedantic
DEBUG=-g -ggdb -O0 -march=native

build: TestLinkedList

TestLinkedList: src/TestLinkedList.o src/LinkedList.o
	$(CC) $(CFLAGS) src/TestLinkedList.o src/LinkedList.o -o TestLinkedList

src/LinkedList.o: src/LinkedList.h src/LinkedList.c
	$(CC) $(CFLAGS) src/LinkedList.c -c -o src/LinkedList.o

src/TestLinkedList.o: src/TestLinkedList.c
	$(CC) $(CFLAGS) src/TestLinkedList.c -c -o src/TestLinkedList.o

run:
	./TestLinkedList

clean:
	rm src/*.o
	rm TestLinkedList

