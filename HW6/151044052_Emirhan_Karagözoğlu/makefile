all: HW6

HW6: GTUSetBase.o GTUSet.o GTUMap.o	GTUIterator.o main.o
	g++ -o exe main.o

GTUSetBase.o: GTUSetBase.cpp
	g++ -c -std=c++11 GTUSetBase.cpp

GTUSet.o: GTUSet.cpp
	g++ -c -std=c++11 GTUSet.cpp

GTUMap.o: GTUMap.cpp
	g++ -c -std=c++11 GTUMap.cpp

GTUIterator.o: GTUIterator.cpp
	g++ -c -std=c++11 GTUIterator.cpp

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

run:
	./exe
	
clean:
	rm *.o exe
