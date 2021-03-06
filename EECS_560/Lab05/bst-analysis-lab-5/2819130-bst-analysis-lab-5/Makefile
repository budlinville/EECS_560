# please change the XXXX to your username eg. j453h432
STUDENT_ID=2819130
LAB_NAME=bst-analysis-lab-5
GCC=g++
GCCFLAGS=-Wall -g -pedantic --std=c++11

# PLEASE ADD THE NAME OF ALL THE FILES YOU WANT TO GET ARCHIVED
FILES=Makefile main.cpp bst.hpp bst.cpp \
	BinaryNode.h BinaryNode.cpp\
	util.hpp util.cpp \
	timer.hpp \
	data.txt \
	analyzeAdd.cpp analyzeDelete.cpp analyzeExists.cpp \
	$(STUDENT_ID)-bst-analysis-writeup.pdf \
	$(STUDENT_ID)-bst-analysis-report.pdf

ARCHIVE_FOLDER=$(STUDENT_ID)-$(LAB_NAME)

all: install analyze-add analyze-delete analyze-exists
	echo "building all executables"

install: bst main util
	$(GCC) $(GCCFLAGS) -o main bst.o main.o util.o
build:
	echo "Please use `make install`"
test:
	./main
bst:
	$(GCC) $(GCCFLAGS) -c bst.cpp -o bst.o

main:
	$(GCC) $(GCCFLAGS) -c main.cpp -o main.o

util:
	$(GCC) $(GCCFLAGS) -c util.cpp -o util.o

clean:
	rm -rf main analyzeAdd analyzeDelete analyzeExists *.o $(ARCHIVE_FOLDER) $(ARCHIVE_FOLDER).tar.gz

analyze-add: bst util
	echo "implement the main function to analyze add element to BST"
	$(GCC) $(GCCFLAGS) -c analyzeAdd.cpp -o analyzeAdd.o
	$(GCC) $(GCCFLAGS) -o analyzeAdd analyzeAdd.o bst.o util.o
	./analyzeAdd

analyze-delete: bst util
	echo "implement the main function to analyze delete element to BST"
	$(GCC) $(GCCFLAGS) -c analyzeDelete.cpp -o analyzeDelete.o
	$(GCC) $(GCCFLAGS) -o analyzeDelete analyzeDelete.o bst.o util.o
	./analyzeDelete

analyze-exists: bst util
	echo "implement the main function to analyze delete element to BST"
	$(GCC) $(GCCFLAGS) -c analyzeExists.cpp -o analyzeExists.o
	$(GCC) $(GCCFLAGS) -o analyzeExists analyzeExists.o  bst.o util.o
	./analyzeExists

debug: install
	gdb ./main

mem-check: install
	valgrind --tool=memcheck \
		--leak-check=full \
		--show-leak-kinds=all \
		--track-origins=yes \
		./main

tar: clean
	mkdir $(ARCHIVE_FOLDER)
	cp -r $(FILES) $(ARCHIVE_FOLDER)
	tar cvzf $(ARCHIVE_FOLDER).tar.gz $(ARCHIVE_FOLDER)
	rm -rf $(ARCHIVE_FOLDER)
