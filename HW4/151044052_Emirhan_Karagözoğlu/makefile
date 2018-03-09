all: main

main: main.o
	g++ -o exe main.o

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

run:
	./exe
	
clean:
	rm *.o exe
