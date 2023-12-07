all: main.o AVL.o BBST.o Node.o
	g++ -o main BBST.o Node.o AVL.o main.o 
main.o: main.cpp
	g++ -c main.cpp 

AVL.o: BBST.o AVL.cpp AVL.h
	g++ -c AVL.cpp 

BBST.o: BBST.cpp BBST.h
	g++ -c BBST.cpp

Node.o: Node.cpp Node.h
	g++ -c Node.cpp

debug:
	g++ -o main main.cpp AVL.cpp BBST.cpp Node.cpp AVL.h BBST.h Node.h

clean:
	rm main
	rm *.o

tar: main.cpp Node.h Node.cpp AVL.cpp AVL.h BBST.h BBST.cpp makefile report.md
	tar -zcvf BBST.tar $^