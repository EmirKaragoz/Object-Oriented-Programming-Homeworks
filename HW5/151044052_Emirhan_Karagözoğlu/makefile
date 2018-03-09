all: HW5

HW5: ConnectFourAbstract.o ConnectFourPlusUndo.o ConnectFourPlus.o	ConnectFourDiag.o main.o Cell.o
	g++ -o exe main.o ConnectFourAbstract.o Cell.o ConnectFourPlus.o ConnectFourDiag.o ConnectFourPlusUndo.o

ConnectFourAbstract.o: ConnectFourAbstract.cpp
	g++ -c -std=c++11 ConnectFourAbstract.cpp

ConnectFourPlusUndo.o: ConnectFourPlusUndo.cpp
	g++ -c -std=c++11 ConnectFourPlusUndo.cpp

ConnectFourPlus.o: ConnectFourPlus.cpp
	g++ -c -std=c++11 ConnectFourPlus.cpp

ConnectFourDiag.o: ConnectFourDiag.cpp
	g++ -c -std=c++11 ConnectFourDiag.cpp

main.o: main.cpp
	g++ -c -std=c++11 main.cpp

Cell.o: Cell.cpp
	g++ -c -std=c++11 Cell.cpp

run:
	./exe
	
clean:
	rm *.o exe
