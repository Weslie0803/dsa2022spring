all: main.cpp Queap.cpp Queap.h
	g++ -o main main.cpp Queap.cpp
tar: main.cpp Queap.cpp Queap.h makefile
	tar -zcvf Risk.tar $^
debug: main.cpp Queap.cpp Queap.h
	g++ -g -o main main.cpp Queap.cpp
clean:
	rm main