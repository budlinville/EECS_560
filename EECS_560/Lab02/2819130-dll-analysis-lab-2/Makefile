STUDENT_ID=2819130
LAB_NAME=dll-analysis-lab-2
GCC=g++
GCCFLAGS=-Wall -g -pedantic --std=c++11

FILES=Makefile main.cpp list.hpp list.cpp util.hpp data.txt timer.hpp\
	sparse-matrix.hpp sparse-matrix.cpp analyzeEquals.cpp analyzeTranspose.cpp\
	analyzeAdd.cpp analyzeDelete.cpp analyzeGetPositionList.cpp\
	modNode.hpp modNode.cpp

ARCHIVE_FOLDER=$(STUDENT_ID)-$(LAB_NAME)

build:
	echo "Please use build-list or build-matrix"

build-list: list  main modNode
	$(GCC) $(GCCFLAGS) -o main list.o modNode.o main.o

build-matrix: list
	$(GCC) $(GCCFLAGS) -c sparse-matrix.cpp -o sparse-matrix.o

test-list:
	./main

list:
	$(GCC) $(GCCFLAGS) -c list.cpp -o list.o

main:
	$(GCC) $(GCCFLAGS) -c main.cpp -o main.o

sparse-matrix: list
	$(GCC) $(GCCFLAGS) -c sparse-matrix.cpp -o sparse-matrix.o

modNode: modNode.hpp
	$(GCC) $(GCCFLAGS) -c modNode.cpp -o modNode.o

clean:
	rm -rf main *.o #rm $(ARCHIVE_FOLDER) $(ARCHIVE_FOLDER).tar.gz

analyze-add-tail: clean list modNode
	echo "implement the main function to analyze add at tail"
	$(GCC) $(GCCFLAGS) -c analyzeAdd.cpp -o analyzeAdd.o
	$(GCC) $(GCCFLAGS) -o analyzeAdd analyzeAdd.o list.o modNode.o
	./analyzeAdd

analyze-delete: clean list modNode
	echo "implement the main function to analyze delete"
	$(GCC) $(GCCFLAGS) -c analyzeDelete.cpp -o analyzeDelete.o
	$(GCC) $(GCCFLAGS) -o analyzeDelete analyzeDelete.o list.o modNode.o
	./analyzeDelete

analyze-getPositionList: clean list modNode
	echo "implement the main function to analyze getPostionList"
	$(GCC) $(GCCFLAGS) -c analyzeGetPositionList.cpp -o analyzeGetPositionList.o
	$(GCC) $(GCCFLAGS) -o analyzeGetPositionList analyzeGetPositionList.o list.o modNode.o
	./analyzeGetPositionList

analyze-matrix-equality: clean sparse-matrix modNode
	echo "implement the main function to analyze equals on sparse-matrix"
	$(GCC) $(GCCFLAGS) -c analyzeEquals.cpp -o analyzeEquals.o
	$(GCC) $(GCCFLAGS) -o analyzeEquals analyzeEquals.o sparse-matrix.o list.o modNode.o
	./analyzeEquals

analyze-matrix-transpose: clean sparse-matrix modNode
	echo "implement the main function to analyze transpose on sparse-matrix"
	$(GCC) $(GCCFLAGS) -c analyzeTranspose.cpp -o analyzeTranspose.o
	$(GCC) $(GCCFLAGS) -o analyzeTranspose analyzeTranspose.o sparse-matrix.o list.o modNode.o
	./analyzeTranspose

tar:
	rm *.o
	mkdir $(ARCHIVE_FOLDER)
	cp -r $(FILES) $(ARCHIVE_FOLDER)
	tar cvzf $(ARCHIVE_FOLDER).tar.gz $(ARCHIVE_FOLDER)
	rm -rf $(ARCHIVE_FOLDER)
