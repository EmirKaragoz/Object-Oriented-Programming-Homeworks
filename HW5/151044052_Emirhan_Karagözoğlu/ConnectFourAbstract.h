//Author: Emirhan Karagözoğlu - 151044052

#ifndef ConnectFourAbstract_H
#define ConnectFourAbstract_H

using namespace std;

#include "Cell.h"
#include <iostream>
#include <string>
#include <fstream>

namespace emir{
	class ConnectFourAbstract{
	protected:
		/*data members*/
		int row,column,gameOption,move;
		char computerLastMove;
		Cell **gameBoard;	//Game Board

		/*Member functions*/
		virtual void load(string &,char ,int &);						//loads the desired game
		virtual int pvp(string & load);									//plays player versus player game mode
		virtual int pvc(string & load);									//plays player versus computer game mode
		virtual void save(const string & decision,char gameType) const;	//saves current game
		virtual int check() = 0;											//includes all check funtions
		virtual int defence3(char call,int &tempColumn) const;			//includes all triple defence functions
		virtual int defence2_1(char call,int &tempColumn) const;		//include all 2_1 defence functions,'2_1' means  XX.X or X.XX
		virtual int attack3(char call,int &tempColumn) const;			//include all triple attack functions
		virtual int attack2(char call,int &tempColumn) const;			//include all double attack functions
		virtual int attack1(char call,int &tempColumn) const;			//includes all single attack functions

		void menu();									//takes input,initializes game board and sets game option via calling needed functions
		bool fillCheck() const;			//checks whether board is full
		bool end();														//returns true if the game ended
		bool isColumnFull(int fullCol) const;	//checks whether a particular column is full
		int findEmptyColumn() const;			//finds an playable empty column in board
		bool isUsable(int coorX,int coorY) const;	//checks whether given coordination is playable
		int moveValidity(const string & colOps, char &tmpCol) const;	// checks whether the move is valid
		void initBoard();
		void play(char cellPosition);			//plays player versus player game mode for a single time step
		void play();							//plays player versus computer game mode for a single time step
		void printBoard() const;	//prints game board
		bool checkLoad(string & decision) const;						//checks whether given file name is valid to load

		int horizontalCheck();		//checks whether a quadruple combination in the horizontal axis is occured
		int verticalCheck();		//checks whether a quadruple combination in the vertical axis is occured
		int rightCrossCheck();		//checks whether a quadruple combination in the right cross axis is occured
		int leftCrossCheck();		//checks whether a quadruple combination in the left cross axis is occured

		int defence3Horizontal(char &call) const;			// if there is a triple 'X' combination in horizontal axis,blocks that
		int defence3Vertical(char &call) const;				// if there is a triple 'X' combination in vertical axis,blocks that
		int defence3RightCross(char &call) const;			// if there is a triple 'X' combination in right cross axis,blocks that
		int defence3LeftCross(char &call) const;			// if there is a triple 'X' combination in left cross axis,blocks that
		
		int defence2_1Horizontal(char &call) const;			//if there is a 2_1 'X' combination in horizontal axis,blocks that
		int defence2_1RightCross(char &call) const;			//if there is a 2_1 'X' combination in right cross axis,blocks that
		int defence2_1LeftCross(char &call) const;			//if there is a 2_1 'X' combination in left cross axis,blocks that

		int attack3Horizontal(char &call) const;			//if there is a triple 'O' combination in horizontal axis, completes to four
		int attack3Vertical(char &call) const;				//if there is a triple 'O' combination in vertical axis, completes to four
		int attack3RightCross(char &call) const;			//if there is a triple 'O' combination in right cross axis, completes to four
		int attack3LeftCross(char &call) const;				//if there is a triple 'O' combination in left cross axis, completes to four
		
		int attack2Horizontal(char &call) const;			//if there is a double 'O' combination in horizontal axis, completes to three
		int attack2Vertical(char &call) const;				//if there is a double 'O' combination in verical axis, completes to three
		int attack2RightCross(char &call) const;			//if there is a double 'O' combination in right cross axis, completes to three
		int attack2LeftCross(char &call) const;				//if there is a double 'O' combination in left cross axis, completes to three

		int attack1Horizontal(char &call) const;			//if there is a single 'O' combination in horizontal axis, completes to two
		int attack1Vertical(char &call) const;				//if there is a single 'O' combination in vertical axis, completes to two
		int attack1RightCross(char &call) const;			//if there is a single 'O' combination in right cross axis, completes to two
		int attack1LeftCross(char &call) const;				//if there is a single 'O' combination in left cross axis, completes to two
	public:
		/*Constructors*/
		ConnectFourAbstract();
		ConnectFourAbstract(int ,int );
		ConnectFourAbstract(const ConnectFourAbstract&);
		~ConnectFourAbstract();

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

		void playGame();			//plays single game mode
		
		const ConnectFourAbstract& operator =(const ConnectFourAbstract&);
		bool operator == (const ConnectFourAbstract&) const;
		bool operator != (const ConnectFourAbstract&) const;
	};
}

#endif