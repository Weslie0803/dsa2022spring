hashtable:
	g++ -g hashtable.cpp -o hashtable.o -c
main: hashtable
	g++ main.cpp hashtable.o -o main

%: %.cpp hashtable
	g++ -g $< hashtable.o -o $@

