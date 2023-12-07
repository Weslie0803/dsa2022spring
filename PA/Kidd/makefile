main: Segment.cpp main.cpp Segment.h
	g++ -o main main.cpp Segment.cpp
debug: Segment.cpp main.cpp Segment.h
	g++ -g -o main main.cpp Segment.cpp
tar: main.cpp Segment.h Segment.cpp makefile
	tar -zcvf Kidd.tar $^