//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "ConnectFourAbstract.h"
#include <iostream>
#include <string>
#include <fstream>

namespace emir{

	//ConnectFourAbstract class functions
	ConnectFourAbstract::ConnectFourAbstract(){		//no parameter constructor
		setRow(5);
		setColumn(5);
		initBoard();
	}

	ConnectFourAbstract::ConnectFourAbstract(int row,int column){	//row,column constructor
		setRow(row);
		setColumn(column);
		initBoard();
	}

	ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& other){		//copy constructor
		row = other.row;
		column = other.column;
		gameOption = other.gameOption;
		move = other.move;

		gameBoard = new Cell*[row];
		for(int i = 0; i < row; ++i)
			gameBoard[i] = new Cell[column];

		for(int i = 0; i < row; ++i){
	    	for(int j = 0; j < column; ++j)
	      		gameBoard[i][j] = other.gameBoard[i][j];
	    }
	}

	ConnectFourAbstract::~ConnectFourAbstract(){	//destructor
		for(int i=0 ; i<row ; ++i)
			delete [] gameBoard[i];
		delete [] gameBoard;
	}

	void ConnectFourAbstract::initBoard(){
		gameBoard = new Cell*[row];
		for(int i = 0; i < row; ++i)
			gameBoard[i] = new Cell[column];

		Cell member;
		member.setCell('*');

		for(int i = 0; i < row; ++i){
	    	for(int j = 0; j < column; ++j)
	      		gameBoard[i][j] = member;
	    }
	}

	inline int ConnectFourAbstract::getRow() const{
		return row;
	}

	inline int ConnectFourAbstract::getColumn() const{
		return column;
	}

	inline char ConnectFourAbstract::getGameOption() const{
		return gameOption;
	}

	inline int ConnectFourAbstract::getMove() const{
		return move;
	}

	bool ConnectFourAbstract::setRow(int tmprow){
		row=tmprow;
		return(true);
	}

	bool ConnectFourAbstract::setColumn(int tmpcolumn){
		column=tmpcolumn;
		return(true);
	}

	void ConnectFourAbstract::setGameOption(char tmpGameOption){
		gameOption=tmpGameOption;
	}

	void ConnectFourAbstract::setMove(int tmpMove){
		move=tmpMove;
	}

	const ConnectFourAbstract& ConnectFourAbstract::operator =(const ConnectFourAbstract& other){
		if(this == &other)	//gelen obje kendine eşitse kendini return et
			return *this;
		else{
			row = other.row;
			column = other.column;
			gameOption = other.gameOption;
			move = other.move;

			for(int i=0 ; i<row ; ++i)		// var olan yeri sil
				delete [] gameBoard[i];
			delete [] gameBoard;

			gameBoard = new Cell*[row];		// yeni yer al
			for(int i = 0; i < row; ++i)
				gameBoard[i] = new Cell[column];

			for(int i = 0; i < row; ++i){	//gelen objeyi bu yeni yere kopyala
		    	for(int j = 0; j < column; ++j)
		      		gameBoard[i][j] = other.gameBoard[i][j];
		    }
		}
		return *this;
	}

	bool ConnectFourAbstract::operator == (const ConnectFourAbstract& other) const{	//compares the all data of objects
		bool status = true;
		if(row == other.row && column == other.column && gameOption == other.gameOption && move == other.move){ //is equal return true
			for(int i = 0 ; i < row ; ++i){
				for(int j = 0 ; j < column ; ++j){
					if(gameBoard[i][j].getCell() != other.gameBoard[i][j].getCell())
						status = false;
				}
			}
		}
		else
			status = false;	//is not equal return false

		return status;
	}

	bool ConnectFourAbstract::operator != (const ConnectFourAbstract& other) const{		//vice versa of == operator
		return (!(*this == other));
	}

	void ConnectFourAbstract::printBoard() const{	
		char letter='A';

		for(int i = 0 ; i < column ; ++i, ++letter)		//aralara boşluk
			cout <<"  "<< letter << "  ";
		cout << endl << endl;

		for(int i = 0 ; i < row ; ++i){
			for(int j = 0 ; j < column ; ++j){
				cout << "  " << gameBoard[i][j].getCell() << "  ";
			}
			cout << "\n \n";	
		}
	}

	bool ConnectFourAbstract::end(){
		if(check()!=0 || fillCheck()==true)
			return true;
		else
			return false;
	}

	bool ConnectFourAbstract::fillCheck() const{			
		int status=true;
		
		for(int i=0 ; i<row && status ==1 ; ++i)
			for(int j=0; j<column && status == 1; ++j){
				if(gameBoard[i][j].getCell()=='*')
					status = false;
			}
		return status;		
	}

	bool ConnectFourAbstract::isColumnFull(int fullCol) const{
		bool status=true;
		for(int i=row-1 ; i>=0 ; --i)
			if(gameBoard[i][fullCol].getCell()=='*'){
				status=false;
				break;
			}
		return status;
	}

	int ConnectFourAbstract::findEmptyColumn() const{
		int status;
		int key=0;
		for(int i=0 ; i<column && key==0 ; ++i)
			for(int j=row-1 ; j>=0 && key==0; --j){
				if(gameBoard[j][i].getCell()=='*'){
					status=i;
					key=1;
				}	
			}
		return status;
	}

	bool ConnectFourAbstract::isUsable(const int coorX,const int coorY) const{
		int status=false;
		
		if(coorX < row && coorX >= 0 && coorY < column && coorY >= 0){
			if(gameBoard[coorX][coorY].getCell()=='*'){
				if(coorX != row-1 && coorX+1<=row-1 && gameBoard[coorX+1][coorY].getCell()!='*')
					status = true;
				else if(coorX==row-1)
					status = true;
			}
		}
		return status;
	}

	void ConnectFourAbstract::play(char cellPosition){
		int i=row-1,castPosition = cellPosition-'A';
		
		while(true){	//moves to the usable position in the selected column
			if(gameBoard[i][castPosition].getCell()=='*'){
				if(getMove()%2 == 1)
					gameBoard[i][castPosition].setCell('X');
					
				else
					gameBoard[i][castPosition].setCell('O');	
				
				break;
			}
			else
				--i;
			
			if(i==-1){	//if column is full
				cerr << "You cannot make a move in this column, please choose another column!" << endl;
				--move;
				break;
			}
		}
	}

	void ConnectFourAbstract::play(){
		int i=row-1,tempColumn;
		char tempCall;

		if(attack3(tempCall,tempColumn));
		else if(defence3(tempCall,tempColumn));																						
		else if(defence2_1(tempCall,tempColumn));				//game algorithm of computer
		else if(attack2(tempCall,tempColumn));
		else if(attack1(tempCall,tempColumn));
		else{
			tempColumn=column/2; 								//default move of computer

			if(isColumnFull(tempColumn))						//if default column is not usable(full)
				tempColumn=findEmptyColumn();					//find an usable column
		}

		while(true){
			if(gameBoard[i][tempColumn].getCell()=='*'){
				gameBoard[i][tempColumn].setCell('O');
				break;
			}
			else
				--i;
		}
		computerLastMove = (char) (tempColumn + 'A');
	}

	void ConnectFourAbstract::save(const string & decision,char gameType) const{
		ofstream saveFile;
		saveFile.open(decision);

		if(saveFile.is_open()){			//if file has been opened
			saveFile << row << endl;
			saveFile << column << endl;
			saveFile << gameType << endl;	
			saveFile << move << endl;		//write process

			for(int i=0 ; i<row ; ++i){
				for(int j=0 ; j< column ; ++j)
					saveFile << gameBoard[i][j].getCell();
				saveFile << endl;
			}
			cout << "Game Saved!"<< endl<< endl;
		}
		else
			cerr << "You can not create a file by this name!" << endl;
			
		saveFile.close();
	}

	bool ConnectFourAbstract::checkLoad(string & decision) const{
		bool status;

		ifstream loadFile;
		loadFile.open(decision);


		if(loadFile.is_open()){		//if file has been opened
			loadFile.close();
			status=true;			//close and return true
		}
		else{
			status=false;
			cerr << "There is no save file by this name!" << endl;
		}
		return status;
	}

	void ConnectFourAbstract::load(string & tempLoad,char gameOption,int & status){
		cout << endl << "The current game ended!" << endl;
		cout << tempLoad << " is starting!" << endl;

		for(int i=0 ; i<row ; ++i)
			delete [] gameBoard[i];		//delete the current alloceted place
		delete [] gameBoard;	

		ifstream loadFile;
		loadFile.open(tempLoad);

		string toReadFile;
		getline(loadFile, toReadFile);
		setRow(stoi(toReadFile));

		getline(loadFile, toReadFile);
		setColumn(stoi(toReadFile));			//read process

		getline(loadFile,toReadFile);
		setGameOption(toReadFile[0]);

		getline(loadFile,toReadFile);
		setMove(stoi(toReadFile));
		
		//init
		gameBoard = new Cell*[row];
		for(int i = 0; i < row; ++i)		//take new place for board according to new row and column numbers
			gameBoard[i] = new Cell[column];

		for(int i=0 ; i<row ; ++i){
			getline(loadFile,toReadFile);
			for(int j=0 ; j<column ; ++j)		
				gameBoard[i][j].setCell(toReadFile[j]);		//fill the board according to file's board
		}
		
		loadFile.close();
		
		if(gameOption=='C'){
			printBoard();
			status=pvc(tempLoad);
		}
			
		else if(gameOption=='P'){
			printBoard();
			status=pvp(tempLoad);
		}
	}

	int ConnectFourAbstract::pvp(string & load){
		while(!end()){		//until game ended
			int key=1;
			char tempColumn;
			string columnOption;

			while(key==1){
				if(move%2 == 1)
					cout << "Sequence of User1." << endl;
				else
					cout << "Sequence of User2." << endl;
				cout << "Choose a column letter for your move -> "<<endl;

				cin >> columnOption;
				if(columnOption.length() == 0)	//check eof
					exit(1);

				if(columnOption.compare("SAVE") == 0){	//check save
					cin >> columnOption;
					save(columnOption,getGameOption());
				}

				else if(columnOption.compare("LOAD") == 0){		//check load
					cin >> columnOption;
					if(checkLoad(columnOption)){
						load=columnOption;
						return(1);
					}
				}

				else 
					key = moveValidity(columnOption,tempColumn);	//check validty of move
			}
			play(tempColumn);	//make move
			++move;				//update move counter
			if(!end())
				printBoard();
		}
		printBoard();

		//game ending status
		if(check()==2)
			cout << "User2 is Winner!" << endl;
											
		else if(check()==1)
			cout << "User1 is Winner!" << endl;

		else
			cout << "The game ended in a draw!" << endl;

		return(0);
	}

	int ConnectFourAbstract::moveValidity(const string & colOps, char &tmpCol) const{
		int checkColumn,status;

		if((colOps[0]>='a' && colOps[0]<='z') || (colOps[0]>='A' && colOps[0]<='Z')){	// Move validity check
			if(colOps[0]>='a')
				tmpCol=(colOps[0]-'a')+'A';
			
			else
				tmpCol=colOps[0];
				
			checkColumn = tmpCol-'A';

			if(checkColumn >= column){
				cerr << "Please enter a valid letter!" << endl << endl;
				status=1;
			}
			else
				status=0;
		}
		else
			status=1;

		return status;
	}

	int ConnectFourAbstract::pvc(string & load){

		while(!end()){	//until game ended
			int key=1;
			char tempColumn;
			string columnOption;
			
			if(move%2 == 0){
				play();		//computer makes move
				++move;		//update move counter

				cout << "Sequence of Computer." << endl;

				if(!end())
					printBoard();
			}
			else if(move%2==1 && !end()){
				while(key==1){
					cout << "Sequence of User1." << endl;
					cout << "Choose a column letter for your move -> "<<endl;
					
					cin >> columnOption;

					if(columnOption.length() == 0)	//check eof
						exit(1);

					if(columnOption.compare("SAVE") == 0){	//check save
						cin >> columnOption;
						save(columnOption,getGameOption());
					}

					else if(columnOption.compare("LOAD") == 0){	  //check load
						cin >> columnOption;
						if(checkLoad(columnOption)){
							load=columnOption;
							return(1);
						}
					}

					else 
						key = moveValidity(columnOption,tempColumn);	//check validity of move
				}
				play(tempColumn);	//make move
				++move;				//update move counter

				if(!end())
					printBoard();
			}
		}
		printBoard();

		//game ending status
		if(check()==2)
			cout << "Computer is Winner!" << endl;
		
		else if(check()==1)
			cout << "User1 is Winner!" << endl;

		else
			cout << "The game ended in a draw!" << endl;

		return(0);
	}

	void ConnectFourAbstract::menu(){
		int inpRow,inpColumn;

		while(true){
			cout << "Enter two numbers for row and column values of the game board" << endl;
			cout << "Row -> " <<endl;
			cin >> inpRow;
			cout << "Column ->"<<endl;
			cin >> inpColumn;
			
			if(cin.fail()){				//harf girme durumu
				cin.clear();
				cin.ignore();
				cerr <<"It's not an integer!"<<endl;
			}
			else if(inpRow > 0 && inpColumn > 0){
				setRow(inpRow);
				setColumn(inpColumn);
				break;
			}
		}

		cout << endl;

		string inp;
		char option='v';	//to first entry to while loop
		cin.ignore();
		while(option=='v'){
			cout << "If you wanna play Player vs Player, press P" << endl;
			cout << "Or you wanna play against computer, press C -> "<<endl;
			getline(cin, inp);
		
			if(inp[0] == 'p' || inp[0] == 'P')			//to select pvp mode
				option = 'P';
			else if (inp[0] == 'c' || inp[0] == 'C')   //to select pvc mode
				option = 'C';
			else
				cerr << "Please enter a valid game mode!" << endl << endl; 
		}
		setGameOption(option);
		setMove(1);		//determine first move
	}

	void ConnectFourAbstract::playGame(){
		int status;
		string tempLoad,boardName;

		for(int i=0 ; i<row ; ++i)	
			delete [] gameBoard[i];		//constructorda alınan yeri delete eder
		delete [] gameBoard;

		menu();
		initBoard();
		printBoard();

		if(getGameOption() =='P'){		//play pvp
			setMove(1);
			status=pvp(tempLoad);
		}

		else if(getGameOption() =='C'){	//play pvc
			setMove(1);
			status=pvc(tempLoad);
		}

		while(status==1){		//Load processing
			load(tempLoad,gameOption,status);
		}
	}

	int ConnectFourAbstract::horizontalCheck(){			
		int status=0;							

		for(int i=row-1 ; i>=0 ; --i)
			for(int j=0 ; j<column-3 ; ++j){
				if((gameBoard[i][j].getCell()=='X' && gameBoard[i][j+1].getCell()=='X' && gameBoard[i][j+2].getCell()=='X' && gameBoard[i][j+3].getCell()=='X') ||
				   (gameBoard[i][j].getCell()=='x' && gameBoard[i][j+1].getCell()=='x' && gameBoard[i][j+2].getCell()=='x' && gameBoard[i][j+3].getCell()=='x')	){
					status = 1;
					gameBoard[i][j].setCell('x'); gameBoard[i][j+1].setCell('x'); gameBoard[i][j+2].setCell('x'); gameBoard[i][j+3].setCell('x');
				}
				else if((gameBoard[i][j].getCell()=='O' && gameBoard[i][j+1].getCell()=='O' && gameBoard[i][j+2].getCell()=='O' && gameBoard[i][j+3].getCell()=='O') ||
						(gameBoard[i][j].getCell()=='o' && gameBoard[i][j+1].getCell()=='o' && gameBoard[i][j+2].getCell()=='o' && gameBoard[i][j+3].getCell()=='o') ){
					status = 2;
					gameBoard[i][j].setCell('o'); gameBoard[i][j+1].setCell('o'); gameBoard[i][j+2].setCell('o'); gameBoard[i][j+3].setCell('o');
				}	
			}
		return status;
	}

	int ConnectFourAbstract::verticalCheck(){			
		int status=0;							

		for(int i=0 ; i<column ; ++i)
			for(int j=row-1 ; j>2 ; --j){
				if((gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i].getCell()=='X' && gameBoard[j-2][i].getCell()=='X' && gameBoard[j-3][i].getCell()=='X') ||
				   (gameBoard[j][i].getCell()=='x' && gameBoard[j-1][i].getCell()=='x' && gameBoard[j-2][i].getCell()=='x' && gameBoard[j-3][i].getCell()=='x') ){
					status = 1;
					gameBoard[j][i].setCell('x'); gameBoard[j-1][i].setCell('x'); gameBoard[j-2][i].setCell('x'); gameBoard[j-3][i].setCell('x');
				}
				else if((gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i].getCell()=='O' && gameBoard[j-2][i].getCell()=='O' && gameBoard[j-3][i].getCell()=='O') ||
					    (gameBoard[j][i].getCell()=='o' && gameBoard[j-1][i].getCell()=='o' && gameBoard[j-2][i].getCell()=='o' && gameBoard[j-3][i].getCell()=='o') ){ 
					status = 2;
					gameBoard[j][i].setCell('o'); gameBoard[j-1][i].setCell('o'); gameBoard[j-2][i].setCell('o'); gameBoard[j-3][i].setCell('o');
				}	
			}
		return status;
	}

	int ConnectFourAbstract::rightCrossCheck(){				
		int status=0;								
		
		for(int j=row-1 ; j>2 ; --j)
			for(int i=0 ; i<column-3 ; ++i){
				if((gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i+1].getCell()=='X' && gameBoard[j-2][i+2].getCell()=='X' && gameBoard[j-3][i+3].getCell()=='X') ||
				   (gameBoard[j][i].getCell()=='x' && gameBoard[j-1][i+1].getCell()=='x' && gameBoard[j-2][i+2].getCell()=='x' && gameBoard[j-3][i+3].getCell()=='x') ){
					status = 1;
					gameBoard[j][i].setCell('x'); gameBoard[j-1][i+1].setCell('x');  gameBoard[j-2][i+2].setCell('x'); gameBoard[j-3][i+3].setCell('x');
				}
				else if((gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i+1].getCell()=='O' && gameBoard[j-2][i+2].getCell()=='O' && gameBoard[j-3][i+3].getCell()=='O') ||
						(gameBoard[j][i].getCell()=='o' && gameBoard[j-1][i+1].getCell()=='o' && gameBoard[j-2][i+2].getCell()=='o' && gameBoard[j-3][i+3].getCell()=='o') ){
					status = 2;
					gameBoard[j][i].setCell('o'); gameBoard[j-1][i+1].setCell('o'); gameBoard[j-2][i+2].setCell('o'); gameBoard[j-3][i+3].setCell('o');
				}
			}
		return status;
	}

	int ConnectFourAbstract::leftCrossCheck(){				
		int status=0;								
		
		for(int j=row-1 ; j>2 ; --j)
			for(int i=column-1 ; i>2 ; --i){
				if((gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i-1].getCell()=='X' && gameBoard[j-2][i-2].getCell()=='X' && gameBoard[j-3][i-3].getCell()=='X') ||
				   (gameBoard[j][i].getCell()=='x' && gameBoard[j-1][i-1].getCell()=='x' && gameBoard[j-2][i-2].getCell()=='x' && gameBoard[j-3][i-3].getCell()=='x') ){
					status = 1;
					gameBoard[j][i].setCell('x'); gameBoard[j-1][i-1].setCell('x'); gameBoard[j-2][i-2].setCell('x'); gameBoard[j-3][i-3].setCell('x');	
				}
				else if((gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i-1].getCell()=='O' && gameBoard[j-2][i-2].getCell()=='O' && gameBoard[j-3][i-3].getCell()=='O') ||
						(gameBoard[j][i].getCell()=='o' && gameBoard[j-1][i-1].getCell()=='o' && gameBoard[j-2][i-2].getCell()=='o' && gameBoard[j-3][i-3].getCell()=='o') ){
					status = 2;
					gameBoard[j][i].setCell('o'); gameBoard[j-1][i-1].setCell('o'); gameBoard[j-2][i-2].setCell('o'); gameBoard[j-3][i-3].setCell('o');
				}
			}
		return status;
	}

	int ConnectFourAbstract::defence3(char call,int &tempColumn) const{
		int status=1;
		if(defence3Horizontal(call))
			tempColumn=call-'A';
		else if(defence3Vertical(call))
			tempColumn=call-'A';
		else if(defence3RightCross(call))
			tempColumn=call-'A';	
		else if(defence3LeftCross(call))
			tempColumn=call-'A';
		else 
			status=0;

		return status;
	}

	int ConnectFourAbstract::defence3Horizontal(char &call) const{		
		int status=0;																	
		char tempCall='A';
		for(int i=row-1 ; i>=0 ; --i)
			for(int j=0 ; j<column-2 ; ++j){
				if(gameBoard[i][j].getCell()=='X' && gameBoard[i][j+1].getCell()=='X' && gameBoard[i][j+2].getCell()=='X'){
					if(isUsable(i,j-1)){
						call=tempCall+j-1;
						status=1;
					}
					else if(isUsable(i,j+3)){
						call=tempCall+j+3;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::defence3Vertical(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int i=0 ; i<column ; ++i)
			for(int j=row-1 ; j>2 ; --j){
				if(gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i].getCell()=='X' && gameBoard[j-2][i].getCell()=='X'){
					if(isUsable(j-3,i)){
						call=tempCall+i;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::defence3RightCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>2 ; --j)
			for(int i=0 ; i<column-3 ; ++i){
				if(gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i+1].getCell()=='X' && gameBoard[j-2][i+2].getCell()=='X'){
					if(isUsable(j-3,i+3)){
						call=tempCall+i+3;
						status=1;
					}
					else if(isUsable(j+1,i-1)){
						call=tempCall+i-1;
						status=1;
					}		
				}
			}
		return status;
	}

	int ConnectFourAbstract::defence3LeftCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>2 ; --j)
			for(int i=column-1 ; i>2 ; --i){
				if(gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i-1].getCell()=='X' && gameBoard[j-2][i-2].getCell()=='X'){
					if(isUsable(j-3,i-3)){
						call=tempCall+i-3;
						status=1;	
					}
					else if(isUsable(j+1,i+1)){
						call=tempCall+i+1;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::defence2_1(char call,int &tempColumn) const{	
		int status=1;																		
		if(defence2_1Horizontal(call))
			tempColumn=call-'A';

		else if(defence2_1RightCross(call))
			tempColumn=call-'A';
			
		else if(defence2_1LeftCross(call))
			tempColumn=call-'A';
		
		else 
			status=0;

		return status;
	}

	int ConnectFourAbstract::defence2_1Horizontal(char &call) const{	
		int status=0;																	
		char tempCall='A';
		for(int i=row-1 ; i>=0 ; --i)
			for(int j=0 ; j<column-3 ; ++j){
				if(gameBoard[i][j].getCell()=='X' && gameBoard[i][j+1].getCell()=='X' && gameBoard[i][j+3].getCell()=='X' && isUsable(i,j+2)){
					call=tempCall+j+2;
					status=1;
				}
				else if(gameBoard[i][j].getCell()=='X' && gameBoard[i][j+2].getCell()=='X' && gameBoard[i][j+3].getCell()=='X' && isUsable(i,j+1)){
					call=tempCall+j+1;
					status=1;
				}
			}
		return status;
	}

	int ConnectFourAbstract::defence2_1RightCross(char &call) const{	
		int status=0;																	
		char tempCall='A';
		for(int j=row-1 ; j>2 ; --j)
			for(int i=0 ; i<column-3 ; ++i){
				if(gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i+1].getCell()=='X' && gameBoard[j-3][i+3].getCell()=='X' && isUsable(j-2,i+2)){
					call=tempCall+i+2;
					status=1;
				}
				else if(gameBoard[j][i].getCell()=='X' && gameBoard[j-2][i+2].getCell()=='X' && gameBoard[j-3][i+3].getCell()=='X' && isUsable(j-1,i+1)){
					call=tempCall+i+1;
					status=1;
				}		
			}
		return status;
	}

	int ConnectFourAbstract::defence2_1LeftCross(char &call) const{	
		int status=0;																	
		char tempCall='A';
		for(int j=row-1 ; j>2 ; --j)
			for(int i=column-1 ; i>2 ; --i){
				if(gameBoard[j][i].getCell()=='X' && gameBoard[j-1][i-1].getCell()=='X' && gameBoard[j-3][i-3].getCell()=='X' && isUsable(j-2,i-2)){
					call=tempCall+i-2;
					status=1;	
				}
				else if(gameBoard[j][i].getCell()=='X' && gameBoard[j-2][i-2].getCell()=='X' && gameBoard[j-3][i-3].getCell()=='X' && isUsable(j-1,i-1)){
					call=tempCall+i-1;
					status=1;
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack3(char call,int &tempColumn) const{		
		int status=1;
		if(attack3Horizontal(call))
			tempColumn=call-'A';

		else if(attack3Vertical(call))
			tempColumn=call-'A';

		else if(attack3RightCross(call))
			tempColumn=call-'A';

		else if(attack3LeftCross(call))
			tempColumn=call-'A';

		else 
			status=0;

		return status;
	}

	int ConnectFourAbstract::attack3Horizontal(char &call)  const{		
		int status=0;																	
		char tempCall='A';
		for(int i=row-1 ; i>=0 ; --i)
			for(int j=0 ; j<column-2 ; ++j){
				if(gameBoard[i][j].getCell()=='O' && gameBoard[i][j+1].getCell()=='O' && gameBoard[i][j+2].getCell()=='O'){
					if(isUsable(i,j-1)){
						call=tempCall+j-1;
						status=1;
					}
					else if(isUsable(i,j+3)){
						call=tempCall+j+3;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack3Vertical(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int i=0 ; i<column ; ++i)
			for(int j=row-1 ; j>2 ; --j){
				if(gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i].getCell()=='O' && gameBoard[j-2][i].getCell()=='O'){
					if(isUsable(j-3,i)){
						call=tempCall+i;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack3RightCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>2 ; --j)
			for(int i=0 ; i<column-3 ; ++i){
				if(gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i+1].getCell()=='O' && gameBoard[j-2][i+2].getCell()=='O'){
					if(isUsable(j-3,i+3)){
						call=tempCall+i+3;
						status=1;
					}
					else if(isUsable(j+1,i-1)){
						call=tempCall+i-1;
						status=1;
					}				
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack3LeftCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>2 ; --j)
			for(int i=column-1 ; i>2 ; --i){
				if(gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i-1].getCell()=='O' && gameBoard[j-2][i-2].getCell()=='O'){
					if(isUsable(j-3,i-3)){
						call=tempCall+i-3;
						status=1;	
					}
					else if(isUsable(j+1,i+1)){
						call=tempCall+i+1;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack2(char call,int &tempColumn) const{	
		int status = 1;
		if(attack2Horizontal(call))
			tempColumn=call-'A';

		else if(attack2Vertical(call))
			tempColumn=call-'A';

		else if(attack2RightCross(call))
			tempColumn=call-'A';

		else if(attack2LeftCross(call))
			tempColumn=call-'A';

		else 
			status=0;
		return status;
	}

	int ConnectFourAbstract::attack2Horizontal(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int i=row-1 ; i>=0 ; --i)
			for(int j=0 ; j<column-1 ; ++j){
				if(gameBoard[i][j].getCell()=='O' && gameBoard[i][j+1].getCell()=='O'){
					if(isUsable(i,j-1)){
						call=tempCall+j-1;
						status=1;
					}
					else if(isUsable(i,j+2)){
						call=tempCall+j+2;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack2Vertical(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int i=0 ; i<column ; ++i)
			for(int j=row-1 ; j>1 ; --j){
				if(gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i].getCell()=='O'){
					if(isUsable(j-2,i)){
						call=tempCall+i;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack2RightCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>1 ; --j)
			for(int i=0 ; i<column-2 ; ++i){
				if(gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i+1].getCell()=='O'){
					if(isUsable(j-2,i+2)){
						call=tempCall+i+2;
						status=1;
					}			
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack2LeftCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>1 ; --j)
			for(int i=column-1 ; i>1 ; --i){
				if(gameBoard[j][i].getCell()=='O' && gameBoard[j-1][i-1].getCell()=='O'){
					if(isUsable(j-2,i-2)){
						call=tempCall+i-2;
						status=1;	
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack1(char call,int &tempColumn) const{	
		int status = 1;
		if(attack1Vertical(call))
			tempColumn=call-'A';

		else if(attack1Horizontal(call))
			tempColumn=call-'A';

		else if(attack1RightCross(call))
			tempColumn=call-'A';

		else if(attack1LeftCross(call))
			tempColumn=call-'A';

		else 
			status=0;
		return status;
	}

	int ConnectFourAbstract::attack1Horizontal(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int i=row-1 ; i>=0 ; --i)
			for(int j=0 ; j<column ; ++j){
				if(gameBoard[i][j].getCell()=='O'){
					if(isUsable(i,j-1)){
						call=tempCall+j-1;
						status=1;
					}
					else if(isUsable(i,j+1)){
						call=tempCall+j+1;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack1Vertical(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int i=0 ; i<column ; ++i)
			for(int j=row-1 ; j>0 ; --j){
				if(gameBoard[j][i].getCell()=='O'){
					if(isUsable(j-1,i)){
						call=tempCall+i;
						status=1;
					}
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack1RightCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>0 ; --j)
			for(int i=0 ; i<column-1 ; ++i){
				if(gameBoard[j][i].getCell()=='O'){
					if(isUsable(j-1,i+1)){
						call=tempCall+i+1;
						status=1;
					}			
				}
			}
		return status;
	}

	int ConnectFourAbstract::attack1LeftCross(char &call) const{	
		int status=0;																
		char tempCall='A';
		for(int j=row-1 ; j>0 ; --j)
			for(int i=column-1 ; i>0 ; --i){
				if(gameBoard[j][i].getCell()=='O'){
					if(isUsable(j-1,i-1)){
						call=tempCall+i-1;
						status=1;	
					}
				}
			}
		return status;
	}
}