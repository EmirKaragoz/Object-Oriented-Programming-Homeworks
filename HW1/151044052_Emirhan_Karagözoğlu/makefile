all: main

main: main.o
	g++ -o exe main.o

main.o: main.cpp
	g++ -c main.cpp

run:
	./exe
	
clean:
	rm *.o exe
