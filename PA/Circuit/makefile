tree:
	g++ -o main main.cpp Node.cpp Tree.cpp

debug:
	g++ -g -o main main.cpp Node.cpp Tree.cpp

clear:
	rm main

tar: main.cpp Node.h Node.cpp Tree.cpp
	tar -zcvf Circuit.tar $^