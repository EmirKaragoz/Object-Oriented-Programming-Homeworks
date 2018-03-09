#ifndef ConnectFour_H
#define ConnectFour_H

using namespace std;

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

class ConnectFour{
private:

	int row,column,gameOption,movePvP,movePvC;
	static int LivingCell;

	class Cell{
	public:
		/*Constructors*/
		Cell();
		Cell(char tmpCell);

		/*Getter*/
		char getCell() const;
		/*Setter*/
		bool setCell(char option);

	private:
		int rowNumber;
		char position;
		char cell;
	};

	vector< vector<Cell> > gameCells;	//Game Board

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

	void printBoard() const;	//prints game board
	void initBoard();			//creates a game board according to given input values
	bool takeInput();			//takes input from user to create a game board

	int check();		//includes all check funtions
	int horizontalCheck();		//checks whether a quadruple combination in the horizontal axis is occured
	int verticalCheck();		//checks whether a quadruple combination in the vertical axis is occured
	int rightCrossCheck();		//checks whether a quadruple combination in the right cross axis is occured
	int leftCrossCheck();		//checks whether a quadruple combination in the left cross axis is occured

	bool fillCheck() const;			//checks whether board is full
	bool isColumnFull(int fullCol) const;	//checks whether a particular column is full
	int findEmptyColumn() const;			//finds an playable empty column in board
	bool isUsable(const int coorX,const int coorY) const;	//checks whether given coordination is playable

	int moveValidity(const string & colOps, char &tmpCol) const;	// checks whether the move is valid
	void save(const string & decision,const char gameType) const;	//saves current game
	bool checkLoad(string & decision) const;						//checks whether given file name is valid to load
	static int livingCell();	//returns current number of living cells
	void afterLoadLivingCells();	//updates number of living cells according to new loading game
	void play(const char cellPosition);		//plays player versus player game mode for a single time step
	void play();							//plays player versus computer game mode for a single time step
	int pvp(string & load);		//plays player versus player game mode
	int pvc(string & load);		//plays player versus computer game mode
	bool toCompareThree() const;	//checks whether a triple 'X' combination in all axis is occured

public:
	/*Constructors*/
	ConnectFour();
	ConnectFour(int row);
	ConnectFour(int row,int column);

	/*Getters*/
	int getRow() const;
	int getColumn() const;
	char getGameOption() const;
	int getMovePvP() const;
	int getMovePvC() const;	

	/*Setters*/
	bool setRow(int tmprow=8);
	bool setColumn(int tmpcolumn=8);
	void setGameOption(char tmpGameOption);
	void setMovePvP(int tmpMovePvP);
	void setMovePvC(int tmpMovePvC);

	/*Member functions*/
	
	bool end();		//returns true if the game ended
	bool compareObject(const ConnectFour & own) const;	//compare two objects
	void load(string & tempLoad,char gameOption,int & status,char gameType);	//loads the desired game
	void menu();				//takes input,initializes game board and sets game option via calling needed functions
	int multi(string & load);	//plays multiple game mode
	void playGame();			//plays single game mode
};

int ConnectFour::LivingCell = 0;	//initialize living cell


#endif