//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "ConnectFour.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

//Cell class functions
ConnectFour::Cell::Cell(){
	cell='.';
}

ConnectFour::Cell::Cell(char tmpCell){
	cell=setCell(tmpCell);
}


inline char ConnectFour::Cell::getCell() const{
	return cell;
}

bool ConnectFour::Cell::setCell(char option){
	if(option == 'X' || option == 'O' || option == '.' || option == 'x' || option == 'o'){
		cell= option;
		return true;
	}
	return false;
}

//ConnectFour class functions
ConnectFour::ConnectFour(){
	setRow();
	setColumn();
}

ConnectFour::ConnectFour(int row){
	setRow(row);
	setColumn();
}

ConnectFour::ConnectFour(int row,int column){
	setRow(row);
	setColumn(column);
}

inline int ConnectFour::getRow() const{
	return row;
}

inline int ConnectFour::getColumn() const{
	return column;
}

inline char ConnectFour::getGameOption() const{
	return gameOption;
}

inline int ConnectFour::getMovePvP() const{
	return movePvP;
}

inline int ConnectFour::getMovePvC() const{
	return movePvC;
}

int ConnectFour::livingCell(){
	return LivingCell;
}

bool ConnectFour::setRow(int tmprow){
	if(tmprow < 4){
		cerr << "Row size can not be less than 4.";
		cerr << " Please try againg!" << endl << endl;
		return (false);
	}
	row=tmprow;
	return(true);
}

bool ConnectFour::setColumn(int tmpcolumn){
	if(tmpcolumn < 4  || tmpcolumn > 26){
		cerr << "Column size can not be less than 4!";
		cerr << " Please try againg!" << endl << endl;
		return (false);
	}
	column=tmpcolumn;
	return(true);
}

void ConnectFour::setGameOption(char tmpGameOption){
	gameOption=tmpGameOption;
}

void ConnectFour::setMovePvP(int tmpMovePvP){
	movePvP=tmpMovePvP;
}

void ConnectFour::setMovePvC(int tmpMovePvC){
	movePvC=tmpMovePvC;
}

void ConnectFour::initBoard(){
	vector <Cell> temp;
	
	Cell member;
	char setValue='.';
	member.setCell(setValue);

    for(int i = 0; i < column; ++i)
    	temp.push_back(member);   
    
    for(int i = 0; i < row; ++i)
       gameCells.push_back(temp);
}

void ConnectFour::printBoard() const{
	char letter='A';

	for(int i = 0 ; i < column ; ++i, ++letter)
		cout <<"  "<< letter << "  ";
	cout << endl << endl;

	for(int i = 0 ; i < row ; ++i){
		for(int j = 0 ; j < column ; ++j){
			cout << "  " << gameCells[i][j].getCell() << "  ";
		}
		cout << "\n \n";	
	}
}

bool ConnectFour::takeInput(){
	int inpRow,inpColumn;
	bool inpState=false;
	
	while(true){
		cout << "Enter two numbers greater than 4 for row and column values of the game board" << endl;
		cout << "Row -> ";
		cin >> inpRow;
		cout << "Column ->";
		cin >> inpColumn;
		
		if(cin.fail()){				//harf girme durumu
			cin.clear();
			cin.ignore();
			cerr <<"It's not an integer!"<<endl;
		}
		else if(setRow(inpRow) && setColumn(inpColumn)){
			inpState = true;
			break;
		}
	}
	return inpState;
}

bool ConnectFour::end(){
	if(check()!=0 || fillCheck()==true)
		return true;
	else
		return false;
}

bool ConnectFour::fillCheck() const{			
	int status=true;
	
	for(int i=0 ; i<row && status ==1 ; ++i)
		for(int j=0; j<column && status == 1; ++j){
			if(gameCells[i][j].getCell()=='.')
				status = false;
		}
	return status;		
}

bool ConnectFour::isColumnFull(int fullCol) const{
	bool status=true;
	for(int i=row-1 ; i>=0 ; --i)
		if(gameCells[i][fullCol].getCell()=='.'){
			status=false;
			break;
		}
	return status;
}

int ConnectFour::findEmptyColumn() const{
	int status;
	int key=0;
	for(int i=0 ; i<column && key==0 ; ++i)
		for(int j=row-1 ; j>=0 && key==0; --j){
			if(gameCells[j][i].getCell()=='.'){
				status=i;
				key=1;
			}	
		}
	return status;
}

bool ConnectFour::isUsable(const int coorX,const int coorY) const{
	int status=false;
	
	if(coorX < row && coorX >= 0 && coorY < column && coorY >= 0){
		if(gameCells[coorX][coorY].getCell()=='.'){
			if(coorX != row-1 && coorX+1<=row-1 && gameCells[coorX+1][coorY].getCell()!='.')
				status = true;
			else if(coorX==row-1)
				status = true;
		}
	}
	return status;
}

void ConnectFour::play(const char cellPosition){
	int i=row-1,castPosition = cellPosition-'A';
	
	while(true){	//moves to the usable position in the selected column
		if(gameCells[i][castPosition].getCell()=='.'){
			if(getMovePvP()%2 == 1)
				gameCells[i][castPosition].setCell('X');
			else
				gameCells[i][castPosition].setCell('O');
			break;
		}
		else
			--i;
		
		if(i==-1){
			cerr << "You cannot make a move in this column, please choose another column!" << endl;
			--movePvP;
			break;
		}
	}
}

void ConnectFour::play(){
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
		if(gameCells[i][tempColumn].getCell()=='.'){
			gameCells[i][tempColumn].setCell('O');
			break;
		}
		else
			--i;
	}
	++movePvC;
}

void ConnectFour::save(const string & decision,const char gameType) const{
	string fileName;

	fileName.replace(0,fileName.length(),decision,5,decision.length()-5);

	ofstream saveFile;
	saveFile.open(fileName);

	if(saveFile.is_open()){
		saveFile << row << endl;
		saveFile << column << endl;
		saveFile << gameType << endl;

		if(gameType == 'P')
			saveFile << movePvP << endl;
		else
			saveFile << movePvC << endl;

		for(int i=0 ; i<row ; ++i){
			for(int j=0 ; j< column ; ++j)
				saveFile << gameCells[i][j].getCell();
			saveFile << endl;
		}
		cout << "Game Saved!"<< endl<< endl;
	}
	else
		cerr << "You can not create a file by this name!" << endl;
		
	saveFile.close();
}

bool ConnectFour::checkLoad(string & decision) const{
	bool status;
	string fileName;

	fileName.replace(0,fileName.length(),decision,5,decision.length()-5);

	ifstream loadFile;
	loadFile.open(fileName);

	if(loadFile.is_open()){
		loadFile.close();
		decision=fileName;
		status=true;
	}
	else{
		status=false;
		cerr << "There is no save file by this name!" << endl;
	}
	return status;
}

void ConnectFour::load(string & tempLoad,char gameOption,int & status,char gameType){
	cout << endl << "The current game ended!" << endl;
	cout << tempLoad << " is starting!" << endl;
	
	ifstream loadFile;
	loadFile.open(tempLoad);

	int toSetRow;
	loadFile >> toSetRow;
	setRow(toSetRow);

	int toSetColumn;
	loadFile >> toSetColumn;
	setColumn(toSetColumn);

	loadFile >> gameOption;
	setGameOption(gameOption);

	if(gameOption =='P'){
		int toSetMovePvP;
		loadFile >> toSetMovePvP;
		setMovePvP(toSetMovePvP);
	}
	else if(gameOption =='C'){
		int toSetMovePvC;
		loadFile >> toSetMovePvC;
		setMovePvC(toSetMovePvC);
	}

	gameCells.clear();
	initBoard();
	
	char temp[row][column];

	for(int i=0 ; i<row ; ++i)
		loadFile>> temp[i];

	for(int i=0 ; i<row ; ++i)
		for(int j=0 ; j<column ; ++j)
			gameCells[i][j].setCell(temp[i][j]);
	
	loadFile.close();

	if(gameType!='M')
		printBoard();

	afterLoadLivingCells();
	
	if(gameOption=='C' && gameType=='S')
		status=pvc(tempLoad);

	else if(gameOption=='C' && gameType=='M')
		status=multi(tempLoad);

	else if(gameOption=='P' && gameType=='S')
		status=pvp(tempLoad);

	else if(gameOption=='P' && gameType=='M')
		status=multi(tempLoad);

}

int ConnectFour::pvp(string & load){
	while(!end()){
		int key=1;
		char tempColumn;
		string columnOption;

		while(key==1){
			if(movePvP%2 == 1)
				cout << "Sequence of User1." << endl;
			else
				cout << "Sequence of User2." << endl;
			cout << "Choose a column letter for your move -> ";

			getline(cin,columnOption);

			if(columnOption.compare(0,5,"SAVE ") == 0)
				save(columnOption,getGameOption());

			else if(columnOption.compare(0,5,"LOAD ") == 0){
				if(checkLoad(columnOption)){
					load=columnOption;
					return(1);
				}
			}

			else 
				key = moveValidity(columnOption,tempColumn);
		}
		play(tempColumn);
		++LivingCell;
		livingCell();
		if(!end())
			printBoard();
		if(!end() && movePvP%2 == 0)
			cout << "Living Cells = " << LivingCell<<endl;
		
		++movePvP;
	}
	printBoard();
	cout << "Living Cells = " << LivingCell<<endl;
	if(check()==2)
		cout << "User2 is Winner!" << endl;
	
	else if(check()==1)
		cout << "User1 is Winner!" << endl;

	else
		cout << "The game ended in a draw!" << endl;

	return(0);
}

int ConnectFour::moveValidity(const string & colOps, char &tmpCol) const{
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

int ConnectFour::pvc(string & load){

	while(!end()){
		int key=1;
		char tempColumn;
		string columnOption;
		
		if(movePvC%2 == 1){
			play();
			++LivingCell;
			livingCell();
			cout << "Sequence of Computer." << endl;
			if(!end()){
				printBoard();
				cout << "Living Cells = " << LivingCell<<endl;
			}
		}
		else if(movePvC%2==0 && !end()){
			while(key==1){
				cout << "Sequence of User1." << endl;
				cout << "Choose a column letter for your move -> ";
				
				getline(cin,columnOption);

				if(columnOption.compare(0,5,"SAVE ") == 0)
					save(columnOption,getGameOption());

				else if(columnOption.compare(0,5,"LOAD ") == 0){
					if(checkLoad(columnOption)){
						load=columnOption;
						return(1);
					}
				}

				else 
					key = moveValidity(columnOption,tempColumn);
			}
			play(tempColumn);
			++LivingCell;
			livingCell();
			if(!end())
				printBoard();
			++movePvC;
		}
	}
	printBoard();
	cout << "Living Cells = " << LivingCell<<endl;
	if(check()==2)
		cout << "Computer is Winner!" << endl;
	
	else if(check()==1)
		cout << "User1 is Winner!" << endl;

	else
		cout << "The game ended in a draw!" << endl;

	return(0);
}

void ConnectFour::menu(){
	string inp;
	char option=' ';

	takeInput();
	initBoard();

	while(option==' '){
		cout << "If you wanna play Player vs Player, press P" << endl;
		cout << "Or you wanna play against computer, press C -> ";
		cin >> inp;
	
		if(inp[0] == 'p' || inp[0] == 'P')			//to select pvp mode
			option = 'P';
		else if (inp[0] == 'c' || inp[0] == 'C')   //to select pvc mode
			option = 'C';
		else
			cerr << "Please enter a valid game mode!" << endl << endl; 
	}
	setGameOption(option);
	cout << endl;
}

int ConnectFour::multi(string & load){
	int saveKey=0;
	string call;
	char tmpcolumn;

	if(getGameOption()=='P'){
		printBoard();
		while(saveKey==0){
			cout << "Sequence of User1." << endl;
			cout << "Choose a column letter for your move -> ";
			
			getline(cin, call);

			if(call.compare(0,5,"SAVE ") == 0){
				save(call,getGameOption());
				saveKey=0;
			}

			else if(call.compare(0,5,"LOAD ") == 0){
				if(checkLoad(call)){
					load=call;
					return(1);
				}
			}

			else{
				while(moveValidity(call,tmpcolumn)){
					cout << "Sequence of User1." << endl;
					cout << "Choose a column letter for your move -> ";
					cin >> call;
				}
				saveKey=1;
			}

			if(saveKey!=0){
				setMovePvP(1);
				play(tmpcolumn);
				++LivingCell;
				livingCell();
				printBoard();
			}
		}

		saveKey=0;
		while(saveKey==0){
			cout << "Sequence of User2." << endl;
			cout << "Choose a column letter for your move -> ";
			
			getline(cin, call);

			if(call.compare(0,5,"SAVE ") == 0){
				save(call,getGameOption());
				saveKey=0;
			}

			else if(call.compare(0,5,"LOAD ") == 0){
				if(checkLoad(call)){
					load=call;
					return(1);
				}
			}

			else{
				while(moveValidity(call,tmpcolumn)){
					cout << "Sequence of User1." << endl;
					cout << "Choose a column letter for your move -> ";
					cin >> call;
				}
				saveKey=1;
			}

			if(saveKey!=0){
				setMovePvP(0);
				play(tmpcolumn);
				++LivingCell;
				livingCell();
				if(!end())
					printBoard();
				else{
					printBoard();
					if(check()==2)
						cout << "User2 is Winner!" << endl << endl;
					
					else if(check()==1)
						cout << "User1 is Winner!" << endl << endl;

					else
						cout << "The game ended in a draw!" << endl << endl;
				}
				cout << "Living Cells = " << LivingCell<<endl;
			}
		}
	}
	else{
		printBoard();
		setMovePvC(0);
		while(saveKey==0){
			cout << "Sequence of User1." << endl;
			cout << "Choose a column letter for your move -> ";
			
			getline(cin, call);

			if(call.compare(0,5,"SAVE ") == 0){
				save(call,getGameOption());
				saveKey=0;
			}

			else if(call.compare(0,5,"LOAD ") == 0){
				if(checkLoad(call)){
					load=call;
					return(1);
				}
			}

			else{
				while(moveValidity(call,tmpcolumn)){
					cout << "Sequence of User1." << endl;
					cout << "Choose a column letter for your move -> ";
					cin >> call;
				}
				saveKey=1;
			}

			if(saveKey!=0){
				setMovePvP(1);
				play(tmpcolumn);
				++LivingCell;
				livingCell();
				printBoard();
			}
		}
			
		cout << "Sequence of Computer." << endl;
		play();
		++LivingCell;
		livingCell();
		if(!end())
			printBoard();
		
		else{
			printBoard();
			if(check()==2)
				cout << "Computer is Winner!" << endl << endl;
			
			else if(check()==1)
				cout << "User1 is Winner!" << endl << endl;

			else
				cout << "The game ended in a draw!" << endl << endl;
		}
		cout << "Living Cells = " << LivingCell<<endl;
	}

	return 0;
}

void ConnectFour::afterLoadLivingCells(){
	int count=0;
	for(int i = 0 ; i<row ; ++i){
		for(int j = 0 ; j < column; ++j){
			if(gameCells[i][j].getCell() != '.')
				++count;
		}
	}
	LivingCell = count;
}


void ConnectFour::playGame(){
	int status;
	string tempLoad;
	char single='S';

	menu();
	printBoard();

	if(getGameOption() =='P'){
		cin.ignore();
		setMovePvP(1);
		status=pvp(tempLoad);
	}

	else if(getGameOption() =='C'){
		cin.ignore();
		setMovePvC(0);
		setMovePvP(1);
		status=pvc(tempLoad);
	}

	while(status==1){		//Load processing
		load(tempLoad,gameOption,status,single);
	}
}


bool ConnectFour::compareObject(const ConnectFour & own) const{
	if(own.toCompareThree() && !toCompareThree())	//if parameter object is better than caller object, returns true
		return true;
	
	return false;
}

bool ConnectFour::toCompareThree() const{
	//Horizontal
	for(int i=row-1 ; i>=0 ; --i){
		for(int j=0 ; j<column-2 ; ++j){
			if(gameCells[i][j].getCell()=='X' && gameCells[i][j+1].getCell()=='X' && gameCells[i][j+2].getCell()=='X'){
				if(isUsable(i,j-1) || isUsable(i,j+3))
					return true;
			}
		}
	}
	//Vertical
	for(int i=0 ; i<column ; ++i){
		for(int j=row-1 ; j>2 ; --j){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i].getCell()=='X' && gameCells[j-2][i].getCell()=='X'){
				if(isUsable(j-3,i))
					return true;
			}
		}
	}
	//Right Cross
	for(int j=row-1 ; j>2 ; --j){
		for(int i=0 ; i<column-3 ; ++i){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i+1].getCell()=='X' && gameCells[j-2][i+2].getCell()=='X'){
				if(isUsable(j-3,i+3) || isUsable(j+1,i-1))
					return true;
			}		
		}
	}
	//Left Cross
	for(int j=row-1 ; j>2 ; --j){
		for(int i=column-1 ; i>2 ; --i){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i-1].getCell()=='X' && gameCells[j-2][i-2].getCell()=='X'){
				if(isUsable(j-3,i-3) || isUsable(j+1,i+1))
					return true;
			}
		}
	}

	return false;
}

int ConnectFour::check(){		 
	int status;
	
	status = horizontalCheck();
	if(status==0){
		status=verticalCheck();
		if(status==0){
			status=rightCrossCheck();
			if(status==0){
				status=leftCrossCheck();
			}
		}
	}
	return status;
}

int ConnectFour::horizontalCheck(){			
	int status=0;							

	for(int i=row-1 ; i>=0 ; --i)
		for(int j=0 ; j<column-3 ; ++j){
			if((gameCells[i][j].getCell()=='X' && gameCells[i][j+1].getCell()=='X' && gameCells[i][j+2].getCell()=='X' && gameCells[i][j+3].getCell()=='X') ||
			   (gameCells[i][j].getCell()=='x' && gameCells[i][j+1].getCell()=='x' && gameCells[i][j+2].getCell()=='x' && gameCells[i][j+3].getCell()=='x')	){
				status = 1;
				gameCells[i][j].setCell('x'); gameCells[i][j+1].setCell('x'); gameCells[i][j+2].setCell('x'); gameCells[i][j+3].setCell('x');
			}
			else if((gameCells[i][j].getCell()=='O' && gameCells[i][j+1].getCell()=='O' && gameCells[i][j+2].getCell()=='O' && gameCells[i][j+3].getCell()=='O') ||
					(gameCells[i][j].getCell()=='o' && gameCells[i][j+1].getCell()=='o' && gameCells[i][j+2].getCell()=='o' && gameCells[i][j+3].getCell()=='o') ){
				status = 2;
				gameCells[i][j].setCell('o'); gameCells[i][j+1].setCell('o'); gameCells[i][j+2].setCell('o'); gameCells[i][j+3].setCell('o');
			}	
		}
	return status;
}

int ConnectFour::verticalCheck(){			
	int status=0;							

	for(int i=0 ; i<column ; ++i)
		for(int j=row-1 ; j>2 ; --j){
			if((gameCells[j][i].getCell()=='X' && gameCells[j-1][i].getCell()=='X' && gameCells[j-2][i].getCell()=='X' && gameCells[j-3][i].getCell()=='X') ||
			   (gameCells[j][i].getCell()=='x' && gameCells[j-1][i].getCell()=='x' && gameCells[j-2][i].getCell()=='x' && gameCells[j-3][i].getCell()=='x') ){
				status = 1;
				gameCells[j][i].setCell('x'); gameCells[j-1][i].setCell('x'); gameCells[j-2][i].setCell('x'); gameCells[j-3][i].setCell('x');
			}
			else if((gameCells[j][i].getCell()=='O' && gameCells[j-1][i].getCell()=='O' && gameCells[j-2][i].getCell()=='O' && gameCells[j-3][i].getCell()=='O') ||
				    (gameCells[j][i].getCell()=='o' && gameCells[j-1][i].getCell()=='o' && gameCells[j-2][i].getCell()=='o' && gameCells[j-3][i].getCell()=='o') ){ 
				status = 2;
				gameCells[j][i].setCell('o'); gameCells[j-1][i].setCell('o'); gameCells[j-2][i].setCell('o'); gameCells[j-3][i].setCell('o');
			}	
		}
	return status;
}

int ConnectFour::rightCrossCheck(){				
	int status=0;								
	
	for(int j=row-1 ; j>2 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if((gameCells[j][i].getCell()=='X' && gameCells[j-1][i+1].getCell()=='X' && gameCells[j-2][i+2].getCell()=='X' && gameCells[j-3][i+3].getCell()=='X') ||
			   (gameCells[j][i].getCell()=='x' && gameCells[j-1][i+1].getCell()=='x' && gameCells[j-2][i+2].getCell()=='x' && gameCells[j-3][i+3].getCell()=='x') ){
				status = 1;
				gameCells[j][i].setCell('x'); gameCells[j-1][i+1].setCell('x');  gameCells[j-2][i+2].setCell('x'); gameCells[j-3][i+3].setCell('x');
			}
			else if((gameCells[j][i].getCell()=='O' && gameCells[j-1][i+1].getCell()=='O' && gameCells[j-2][i+2].getCell()=='O' && gameCells[j-3][i+3].getCell()=='O') ||
					(gameCells[j][i].getCell()=='o' && gameCells[j-1][i+1].getCell()=='o' && gameCells[j-2][i+2].getCell()=='o' && gameCells[j-3][i+3].getCell()=='o') ){
				status = 2;
				gameCells[j][i].setCell('o'); gameCells[j-1][i+1].setCell('o'); gameCells[j-2][i+2].setCell('o'); gameCells[j-3][i+3].setCell('o');
			}
		}
	return status;
}

int ConnectFour::leftCrossCheck(){				
	int status=0;								
	
	for(int j=row-1 ; j>2 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if((gameCells[j][i].getCell()=='X' && gameCells[j-1][i-1].getCell()=='X' && gameCells[j-2][i-2].getCell()=='X' && gameCells[j-3][i-3].getCell()=='X') ||
			   (gameCells[j][i].getCell()=='x' && gameCells[j-1][i-1].getCell()=='x' && gameCells[j-2][i-2].getCell()=='x' && gameCells[j-3][i-3].getCell()=='x') ){
				status = 1;
				gameCells[j][i].setCell('x'); gameCells[j-1][i-1].setCell('x'); gameCells[j-2][i-2].setCell('x'); gameCells[j-3][i-3].setCell('x');	
			}
			else if((gameCells[j][i].getCell()=='O' && gameCells[j-1][i-1].getCell()=='O' && gameCells[j-2][i-2].getCell()=='O' && gameCells[j-3][i-3].getCell()=='O') ||
					(gameCells[j][i].getCell()=='o' && gameCells[j-1][i-1].getCell()=='o' && gameCells[j-2][i-2].getCell()=='o' && gameCells[j-3][i-3].getCell()=='o') ){
				status = 2;
				gameCells[j][i].setCell('o'); gameCells[j-1][i-1].setCell('o'); gameCells[j-2][i-2].setCell('o'); gameCells[j-3][i-3].setCell('o');
			}
		}
	return status;
}

int ConnectFour::defence3(char call,int &tempColumn) const{
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

int ConnectFour::defence3Horizontal(char &call) const{		
	int status=0;																	
	char tempCall='A';
	for(int i=row-1 ; i>=0 ; --i)
		for(int j=0 ; j<column-2 ; ++j){
			if(gameCells[i][j].getCell()=='X' && gameCells[i][j+1].getCell()=='X' && gameCells[i][j+2].getCell()=='X'){
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

int ConnectFour::defence3Vertical(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row-1 ; j>2 ; --j){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i].getCell()=='X' && gameCells[j-2][i].getCell()=='X'){
				if(isUsable(j-3,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int ConnectFour::defence3RightCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>2 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i+1].getCell()=='X' && gameCells[j-2][i+2].getCell()=='X'){
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

int ConnectFour::defence3LeftCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>2 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i-1].getCell()=='X' && gameCells[j-2][i-2].getCell()=='X'){
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

int ConnectFour::defence2_1(char call,int &tempColumn) const{	
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

int ConnectFour::defence2_1Horizontal(char &call) const{	
	int status=0;																	
	char tempCall='A';
	for(int i=row-1 ; i>=0 ; --i)
		for(int j=0 ; j<column-3 ; ++j){
			if(gameCells[i][j].getCell()=='X' && gameCells[i][j+1].getCell()=='X' && gameCells[i][j+3].getCell()=='X' && isUsable(i,j+2)){
				call=tempCall+j+2;
				status=1;
			}
			else if(gameCells[i][j].getCell()=='X' && gameCells[i][j+2].getCell()=='X' && gameCells[i][j+3].getCell()=='X' && isUsable(i,j+1)){
				call=tempCall+j+1;
				status=1;
			}
		}
	return status;
}

int ConnectFour::defence2_1RightCross(char &call) const{	
	int status=0;																	
	char tempCall='A';
	for(int j=row-1 ; j>2 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i+1].getCell()=='X' && gameCells[j-3][i+3].getCell()=='X' && isUsable(j-2,i+2)){
				call=tempCall+i+2;
				status=1;
			}
			else if(gameCells[j][i].getCell()=='X' && gameCells[j-2][i+2].getCell()=='X' && gameCells[j-3][i+3].getCell()=='X' && isUsable(j-1,i+1)){
				call=tempCall+i+1;
				status=1;
			}		
		}
	return status;
}

int ConnectFour::defence2_1LeftCross(char &call) const{	
	int status=0;																	
	char tempCall='A';
	for(int j=row-1 ; j>2 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if(gameCells[j][i].getCell()=='X' && gameCells[j-1][i-1].getCell()=='X' && gameCells[j-3][i-3].getCell()=='X' && isUsable(j-2,i-2)){
				call=tempCall+i-2;
				status=1;	
			}
			else if(gameCells[j][i].getCell()=='X' && gameCells[j-2][i-2].getCell()=='X' && gameCells[j-3][i-3].getCell()=='X' && isUsable(j-1,i-1)){
				call=tempCall+i-1;
				status=1;
			}
		}
	return status;
}

int ConnectFour::attack3(char call,int &tempColumn) const{		
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

int ConnectFour::attack3Horizontal(char &call)  const{		
	int status=0;																	
	char tempCall='A';
	for(int i=row-1 ; i>=0 ; --i)
		for(int j=0 ; j<column-2 ; ++j){
			if(gameCells[i][j].getCell()=='O' && gameCells[i][j+1].getCell()=='O' && gameCells[i][j+2].getCell()=='O'){
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

int ConnectFour::attack3Vertical(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row-1 ; j>2 ; --j){
			if(gameCells[j][i].getCell()=='O' && gameCells[j-1][i].getCell()=='O' && gameCells[j-2][i].getCell()=='O'){
				if(isUsable(j-3,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int ConnectFour::attack3RightCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>2 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if(gameCells[j][i].getCell()=='O' && gameCells[j-1][i+1].getCell()=='O' && gameCells[j-2][i+2].getCell()=='O'){
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

int ConnectFour::attack3LeftCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>2 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if(gameCells[j][i].getCell()=='O' && gameCells[j-1][i-1].getCell()=='O' && gameCells[j-2][i-2].getCell()=='O'){
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

int ConnectFour::attack2(char call,int &tempColumn) const{	
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

int ConnectFour::attack2Horizontal(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int i=row-1 ; i>=0 ; --i)
		for(int j=0 ; j<column-1 ; ++j){
			if(gameCells[i][j].getCell()=='O' && gameCells[i][j+1].getCell()=='O'){
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

int ConnectFour::attack2Vertical(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row-1 ; j>1 ; --j){
			if(gameCells[j][i].getCell()=='O' && gameCells[j-1][i].getCell()=='O'){
				if(isUsable(j-2,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int ConnectFour::attack2RightCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>1 ; --j)
		for(int i=0 ; i<column-2 ; ++i){
			if(gameCells[j][i].getCell()=='O' && gameCells[j-1][i+1].getCell()=='O'){
				if(isUsable(j-2,i+2)){
					call=tempCall+i+2;
					status=1;
				}			
			}
		}
	return status;
}

int ConnectFour::attack2LeftCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>1 ; --j)
		for(int i=column-1 ; i>1 ; --i){
			if(gameCells[j][i].getCell()=='O' && gameCells[j-1][i-1].getCell()=='O'){
				if(isUsable(j-2,i-2)){
					call=tempCall+i-2;
					status=1;	
				}
			}
		}
	return status;
}

int ConnectFour::attack1(char call,int &tempColumn) const{	
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

int ConnectFour::attack1Horizontal(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int i=row-1 ; i>=0 ; --i)
		for(int j=0 ; j<column ; ++j){
			if(gameCells[i][j].getCell()=='O'){
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

int ConnectFour::attack1Vertical(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row-1 ; j>0 ; --j){
			if(gameCells[j][i].getCell()=='O'){
				if(isUsable(j-1,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int ConnectFour::attack1RightCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>0 ; --j)
		for(int i=0 ; i<column-1 ; ++i){
			if(gameCells[j][i].getCell()=='O'){
				if(isUsable(j-1,i+1)){
					call=tempCall+i+1;
					status=1;
				}			
			}
		}
	return status;
}

int ConnectFour::attack1LeftCross(char &call) const{	
	int status=0;																
	char tempCall='A';
	for(int j=row-1 ; j>0 ; --j)
		for(int i=column-1 ; i>0 ; --i){
			if(gameCells[j][i].getCell()=='O'){
				if(isUsable(j-1,i-1)){
					call=tempCall+i-1;
					status=1;	
				}
			}
		}
	return status;
}