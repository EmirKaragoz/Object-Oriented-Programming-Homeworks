//Author: Emirhan Karagözoğlu - 151044052
#ifndef ConnectFour_H
#define ConnectFour_H

using namespace std;

#include <iostream>
#include <string>
#include <fstream>

enum CellType{
	empty,
	user1,
	user2,
	computer
};

class ConnectFour{
private:
	/*data members*/
	int row,column,gameOption,move;
	static int LivingCell;

	class Cell{
	public:
		/*Constructors*/
		Cell(char tmpCell='*');

		/*Getter*/
		char getCell() const;
		/*Setter*/
		bool setCell(char option);
		/*Overloding operators*/
		bool operator ==(const Cell&)const;
		const Cell& operator ++();
		const Cell operator ++(int);
		const Cell& operator --();
		const Cell operator --(int);
		friend ostream& operator << (ostream&, const Cell&);
		friend istream& operator >> (istream&, Cell&);

	private:
		int rowNumber = 0;
		char position = 'A';
		char cell;
	};

	Cell **gameBoard;	//Game Board

	friend ostream& operator << (ostream&, const Cell&);
	friend istream& operator >> (istream&, Cell&);

	void play(char cellPosition);			//plays player versus player game mode for a single time step
	void play();							//plays player versus computer game mode for a single time step
	int pvp(string & load);					//plays player versus player game mode
	int pvc(string & load);					//plays player versus computer game mode

	bool fillCheck() const;			//checks whether board is full
	bool isColumnFull(int fullCol) const;	//checks whether a particular column is full
	int findEmptyColumn() const;			//finds an playable empty column in board
	bool isUsable(int coorX,int coorY) const;	//checks whether given coordination is playable
	int moveValidity(const string & colOps, char &tmpCol) const;	// checks whether the move is valid

	void printBoard() const;	//prints game board

	void save(const string & decision,const char gameType) const;	//saves current game
	bool checkLoad(string & decision) const;						//checks whether given file name is valid to load

	static int livingCell();	//returns current number of living cells
	void afterLoadLivingCells() const ;	//updates number of living cells according to new loading game

	int check();		//includes all check funtions
	int horizontalCheck();		//checks whether a quadruple combination in the horizontal axis is occured
	int verticalCheck();		//checks whether a quadruple combination in the vertical axis is occured
	int rightCrossCheck();		//checks whether a quadruple combination in the right cross axis is occured
	int leftCrossCheck();		//checks whether a quadruple combination in the left cross axis is occured

	int defence3(char call,int &tempColumn) const;		//includes all triple defence functions
	int defence3Horizontal(char &call) const;			// if there is a triple 'X' combination in horizontal axis,blocks that
	int defence3Vertical(char &call) const;				// if there is a triple 'X' combination in vertical axis,blocks that
	int defence3RightCross(char &call) const;			// if there is a triple 'X' combination in right cross axis,blocks that
	int defence3LeftCross(char &call) const;			// if there is a triple 'X' combination in left cross axis,blocks that

	int defence2_1(char call,int &tempColumn) const;	//include all 2_1 defence functions,'2_1' means  XX.X or X.XX
	int defence2_1Horizontal(char &call) const;			//if there is a 2_1 'X' combination in horizontal axis,blocks that
	int defence2_1RightCross(char &call) const;			//if there is a 2_1 'X' combination in right cross axis,blocks that
	int defence2_1LeftCross(char &call) const;			//if there is a 2_1 'X' combination in left cross axis,blocks that

	int attack3(char call,int &tempColumn) const;		//include all triple attack functions
	int attack3Horizontal(char &call) const;			//if there is a triple 'O' combination in horizontal axis, completes to four
	int attack3Vertical(char &call) const;				//if there is a triple 'O' combination in vertical axis, completes to four
	int attack3RightCross(char &call) const;			//if there is a triple 'O' combination in right cross axis, completes to four
	int attack3LeftCross(char &call) const;				//if there is a triple 'O' combination in left cross axis, completes to four

	int attack2(char call,int &tempColumn) const;		//include all double attack functions
	int attack2Horizontal(char &call) const;			//if there is a double 'O' combination in horizontal axis, completes to three
	int attack2Vertical(char &call) const;				//if there is a double 'O' combination in verical axis, completes to three
	int attack2RightCross(char &call) const;			//if there is a double 'O' combination in right cross axis, completes to three
	int attack2LeftCross(char &call) const;				//if there is a double 'O' combination in left cross axis, completes to three

	int attack1(char call,int &tempColumn) const;		//includes all single attack functions
	int attack1Horizontal(char &call) const;			//if there is a single 'O' combination in horizontal axis, completes to two
	int attack1Vertical(char &call) const;				//if there is a single 'O' combination in vertical axis, completes to two
	int attack1RightCross(char &call) const;			//if there is a single 'O' combination in right cross axis, completes to two
	int attack1LeftCross(char &call) const;				//if there is a single 'O' combination in left cross axis, completes to two

public:
	/*Constructors*/
	ConnectFour();
	ConnectFour(int row,int column);
	ConnectFour(string & filename);
	ConnectFour(const ConnectFour&);
	~ConnectFour();

	/*Getters*/
	int getRow() const;
	int getColumn() const;
	char getGameOption() const;
	int getMove() const;

	/*Setters*/
	bool setRow(int tmprow);
	bool setColumn(int tmpcolumn);
	void setGameOption(char tmpGameOption);
	void setMove(int tmpMove);

	/*Member functions*/
	void load(string & tempLoad,char gameOption,int & status,char gameType);	//loads the desired game
	void menu();				//takes input,initializes game board and sets game option via calling needed functions
	int multi(string & load);	//plays multiple game mode
	void playGame();			//plays single game mode
	bool end();		//returns true if the game ended

	const ConnectFour& operator =(const ConnectFour&);
	bool operator == (const ConnectFour&) const;
	bool operator != (const ConnectFour&) const;

	void takeBoardName(string&);
};

int ConnectFour::LivingCell = 0;	//initialize living cell


#endif