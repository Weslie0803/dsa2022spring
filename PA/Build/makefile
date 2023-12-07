main: main.cpp tree.cpp tree.h
	g++ -o main main.cpp tree.cpp

debug: main.cpp tree.cpp tree.h
	g++ -g -o main main.cpp tree.cpp

clean:
	rm main

tar: main.cpp tree.h tree.cpp makefile
	tar -zcvf Build.tar $^