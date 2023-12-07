main: main.cpp hash.h hash.cpp
	g++ -o main main.cpp hash.cpp crc32.cpp
debug: main
	g++ -g -o main main.cpp hash.cpp crc32.cpp
clear:
	rm main
tar: main.cpp hash.h hash.cpp makefile
	tar -zcvf Hacker.tar $^