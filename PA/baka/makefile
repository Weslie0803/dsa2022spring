all: main.cpp List.h List.cpp
	g++ -o main main.cpp List.cpp
clean:
	rm main
debug: main.cpp List.h List.cpp
	g++ -g -o main main.cpp List.cpp
run: all
	./main
tar: main.cpp List.h List.cpp makefile
	tar -zcvf baka.tar $^
test: main.cpp List.h List.cpp
	g++ -o test main.cpp List.cpp
bm:
	python3 check.py ./main ./test "python3 makedata.py"