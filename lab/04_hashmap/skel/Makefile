CC=clang
CFLAGS=-Wall -Wextra
DEBUG=-g -ggdb -O0 -march=native

build: TestHashtable

TestHashtable: src/TestHashtable.o src/Hashtable.o src/LinkedList.o
	$(CC) $(CFLAGS) src/TestHashtable.o src/Hashtable.o src/LinkedList.o -o TestHashtable

src/Hashtable.o: src/Hashtable.h src/Hashtable.c
	$(CC) $(CFLAGS) src/Hashtable.c -c -o src/Hashtable.o

src/LinkedList.o: src/LinkedList.h src/LinkedList.c
	$(CC) $(CFLAGS) src/LinkedList.c -c -o src/LinkedList.o

src/TestHashtable.o: src/TestHashtable.c
	$(CC) $(CFLAGS) src/TestHashtable.c -c -o src/TestHashtable.o

run:
	./TestHashtable

clean:
	rm src/*.o
	rm TestHashtable
