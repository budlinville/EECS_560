STUDENT_ID=2819130
LAB_NAME=doubly-linked-list-lab-1
GCC=g++
CFLAGS=-Wall -g -pedantic --std=c++11

FILES=Makefile main.cpp list.hpp list.cpp util.cpp util.hpp data.txt Node.cpp Node.hpp README.txt

ARCHIVE_FOLDER=$(STUDENT_ID)-$(LAB_NAME)

all: tar build

build: list util Node main
	$(GCC) $(CFLAGS) -o main list.o util.o Node.o main.o

test:
	./main

util:
	$(GCC) $(CFLAGS) -c util.cpp -o util.o

list: list.hpp
	$(GCC) $(CFLAGS) -c list.cpp -o list.o

Node: Node.hpp
	$(GCC) $(CFLAGS) -c Node.cpp -o Node.o

main:
	$(GCC) $(CFLAGS) -c main.cpp -o main.o

clean:
	rm -rf main *.o rm $(ARCHIVE_FOLDER) $(ARCHIVE_FOLDER).tar.gz

tar:
	make clean
	mkdir $(ARCHIVE_FOLDER)
	cp -r $(FILES) $(ARCHIVE_FOLDER)
	tar cvzf $(ARCHIVE_FOLDER).tar.gz $(ARCHIVE_FOLDER)
	#rm -rf $(ARCHIVE_FOLDER)
