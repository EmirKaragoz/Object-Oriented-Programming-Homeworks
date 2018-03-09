//Author: Emirhan Karagözoğlu - 151044052

#include <iostream>
#include <string>

const int MAX_ROW = 21; 		//maximum row 21 because of first row includes column letters
const int MAX_COLUMN = 20; 		//maximum column number

//function prototypes
bool isTable(int row, int column);
bool takeInput(int &row, int &column);
void initBoard(char board[][MAX_COLUMN],int row,int column);
void printBoard(char board[][MAX_COLUMN],int row,int column);
bool fillCheck(char board[][MAX_COLUMN],int row,int column);
bool isUsable(char board[][MAX_COLUMN],int row,int column,int coorX,int coorY);
bool isColumnFull(char board[][MAX_COLUMN],int row,int column);
int findEmptyColumn(char board[][MAX_COLUMN],int row,int column);

void playWith2User(char board[][MAX_COLUMN],int row,int column);
void playWithComputer(char board[][MAX_COLUMN],int row,int column);

int check(char board[][MAX_COLUMN],int row,int column);
int horizontalCheck(char board[][MAX_COLUMN],int row,int column);
int verticalCheck(char board[][MAX_COLUMN],int row,int column);
int rightCrossCheck(char board[][MAX_COLUMN],int row,int column);
int leftCrossCheck(char board[][MAX_COLUMN],int row,int column);

int defence3(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn);
int defence3Horizontal(char board[][MAX_COLUMN],int row,int column,char &call);
int defence3Vertical(char board[][MAX_COLUMN],int row,int column,char &call);
int defence3RightCross(char board[][MAX_COLUMN],int row,int column,char &call);
int defence3LeftCross(char board[][MAX_COLUMN],int row,int column,char &call);

int defence2_1(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn);
int defence2_1Horizontal(char board[][MAX_COLUMN],int row,int column,char &call);
int defence2_1Vertical(char board[][MAX_COLUMN],int row,int column,char &call);
int defence2_1RightCross(char board[][MAX_COLUMN],int row,int column,char &call);
int defence2_1LeftCross(char board[][MAX_COLUMN],int row,int column,char &call);

int attack3(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn);
int attack3Horizontal(char board[][MAX_COLUMN],int row,int column,char &call);
int attack3Vertical(char board[][MAX_COLUMN],int row,int column,char &call);
int attack3RightCross(char board[][MAX_COLUMN],int row,int column,char &call);
int attack3LeftCross(char board[][MAX_COLUMN],int row,int column,char &call);

int attack2(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn);
int attack2Horizontal(char board[][MAX_COLUMN],int row,int column,char &call);
int attack2Vertical(char board[][MAX_COLUMN],int row,int column,char &call);
int attack2RightCross(char board[][MAX_COLUMN],int row,int column,char &call);
int attack2LeftCross(char board[][MAX_COLUMN],int row,int column,char &call);

int attack1(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn);
int attack1Horizontal(char board[][MAX_COLUMN],int row,int column,char &call);
int attack1Vertical(char board[][MAX_COLUMN],int row,int column,char &call);
int attack1RightCross(char board[][MAX_COLUMN],int row,int column,char &call);
int attack1LeftCross(char board[][MAX_COLUMN],int row,int column,char &call);

void gameMenu(char board[][MAX_COLUMN],int row,int column);

using namespace std;

bool isColumnFull(char board[][MAX_COLUMN],int row,int column){		//checks whether a particular column is full
	bool status=true;
	for(int i=row ; i>0 ; --i)
		if(board[i][column]=='.'){
			status=false;
			break;
		}
	return status;
}

int findEmptyColumn(char board[][MAX_COLUMN],int row,int column){	//finds an playable empty column in board
	int status;
	int key=0;
	for(int i=0 ; i<column && key==0 ; ++i)
		for(int j=row ; j>0 && key==0; --j){
			if(board[j][i]=='.'){
				status=i;
				key=1;
			}	
		}
	return status;
}

bool isTable(int row, int column){	//checks whether user input is usable for creating game board
	bool table;
	if (column == row && column >= 4 && column % 2 == 0 && column <= 20)
		table = true;
	else
		table = false;
	return table;
}

bool takeInput(int &row, int &column) {	//takes input from user to create a game board
	int inp;
	bool inpState=false;
	
	while(true){
		cout << "Enter an even number for game board size in range of [4,20] -> ";
		cin >> inp;
		
		if(cin.fail()){				//harf girme durumu
			cin.clear();
			cin.ignore();
			cout <<"It's not an integer!"<<endl;
		}
		else if(isTable(inp,inp)){
			inpState = true;
			row=inp;
			column=inp;
			break;
		}
		else
			cout << inp << " is not in range or not even number!" << endl;
	}
	return inpState;
}

void initBoard(char board[][MAX_COLUMN],int row,int column){	//creates a game board according to given input values
	char colName = 'A';
	
	for(int i=0 ; i<column ; ++i,++colName)
		board[0][i] = colName;

	for(int i=1 ; i<row+1 ; ++i)
		for(int j=0 ; j<column ; ++j)
			board[i][j]='.';	
}

void printBoard(char board[][MAX_COLUMN],int row,int column){	//prints game board
	for(int i=0 ; i<row+1 ; ++i){
		for(int j=0 ; j<column ; ++j)
			cout << "  " << board[i][j] << "  ";
		cout << "\n \n";	
	}
}

void playWith2User(char board[][MAX_COLUMN],int row,int column){	//plays player versus player game mode
	int i,move=1,tempColumn,key=1;
	string columnOption;
	
	while(check(board,row,column)==0 && fillCheck(board,row,column)==0)  {//until any player wins or until the game board is full
		if(move%2 == 1)
			cout << "Sequence of User1." << endl;
		else
			cout << "Sequence of User2." << endl;
		cout << "Choose a column letter for your move -> ";

		while(key==1){				//determines order of move(user1 or user2)
			cin >> columnOption;
			if((columnOption[0]>='a' && columnOption[0]<='z') || (columnOption[0]>='A' && columnOption[0]<='Z')){
				if(columnOption[0]>='a')
					tempColumn=columnOption[0]-'a';
				else
					tempColumn=columnOption[0]-'A';
			
				if(tempColumn+1>column)
					cout << "Please enter a valid letter! -> ";
				else
					key=0;
			}
			else
				cout << "Please enter a valid letter! -> ";
		}
		key=1;
		i=row;
		while(true){	//moves to the usable position in the selected column
			if(board[i][tempColumn]=='.'){
				if(move%2 == 1)
					board[i][tempColumn]='X';
				else
					board[i][tempColumn]='O';
				break;
			}
			else
				--i;
			
			if(i==0){
				cout << "You cannot make a move in this column, please choose another column!" << endl;
				--move;
				break;
			}
		}
		
		if(i!=0 && check(board,row,column)==0 && fillCheck(board,row,column)==0)
		   printBoard(board,row,column);
		
		++move;
	}
}

void playWithComputer(char board[][MAX_COLUMN],int row,int column){		//plays player versus computer game mode
	int i,move=0,tempColumn=0,key=1;
	char inp,tempCall='B';
	string columnOption;
	
	while(check(board,row,column)==0 && fillCheck(board,row,column)==0)  {	//until any player wins or until the game board is full

		if(move%2 == 1){	//determines order of move(user1 or computer)
			if(attack3(board,row,column,tempCall,tempColumn))
				cout << "Computer's choice is column " << (char)(tempColumn+'A') << endl;

			else if(defence3(board,row,column,tempCall,tempColumn))
				cout << "Computer's choice is column " << (char)(tempColumn+'A') << endl;
																								//game algorithm of computer
			else if(defence2_1(board,row,column,tempCall,tempColumn))
				cout << "Computer's choice is column " << (char)(tempColumn+'A') << endl;
			
			else if(attack2(board,row,column,tempCall,tempColumn))
				cout << "Computer's choice is column " << (char)(tempColumn+'A') << endl;
			
			else if(attack1(board,row,column,tempCall,tempColumn))
				cout << "Computer's choice is column " << (char)(tempColumn+'A') << endl;
			
			else{
				tempColumn=column/2; 								//default move of computer

				if(isColumnFull(board,row,tempColumn))				//if default column is not usable(full)
					tempColumn=findEmptyColumn(board,row,column);	//find an usable column
				
				inp=tempColumn+'A';
				cout << "Computer's choice is column " << inp << endl;
			}
			
			i=row;
			while(true){
				if(board[i][tempColumn]=='.'){
					board[i][tempColumn]='O';
					break;
				}
				else
					--i;
			}
		}
		else{
			cout << "Sequence of User1." << endl;
			cout << "Choose a column letter for your move -> ";
			while(key==1){
				cin >> columnOption;
				if((columnOption[0]>='a' && columnOption[0]<='z') || (columnOption[0]>='A' && columnOption[0]<='Z')){
					if(columnOption[0]>='a')
						tempColumn=columnOption[0]-'a';
					else
						tempColumn=columnOption[0]-'A';
			
					if(tempColumn+1>column)
						cout << "Please enter a valid letter! -> ";
					else
						key=0;
				}
				else
					cout << "Please enter a valid letter! -> ";
			}
			key=1;
			i=row;
			while(true){
				if(board[i][tempColumn]=='.'){
					board[i][tempColumn]='X';
					break;
				}
				else
					--i;
			
				if(i==0){
					cout << "You cannot make a move in this column, please choose another column!" << endl;
					--move;
					break;
				}
			}
		}
		if(i!=0 && check(board,row,column)==0 && fillCheck(board,row,column)==0)
			printBoard(board,row,column);
		
		++move;
	}
}

int check(char board[][MAX_COLUMN],int row,int column){	 //includes all check funtions
	int status;
	
	status = horizontalCheck(board,row,column);
	if(status==0){
		status=verticalCheck(board,row,column);
		if(status==0){
			status=rightCrossCheck(board,row,column);
			if(status==0){
				status=leftCrossCheck(board,row,column);
			}
		}
	}
	return status;
}

int horizontalCheck(char board[][MAX_COLUMN],int row,int column){	//checks whether a quadruple combination 
	int status=0;													//in the horizontal axis is occured

	for(int i=row ; i>0 ; --i)
		for(int j=0 ; j<column-3 ; ++j){
			if((board[i][j]=='X' && board[i][j+1]=='X' && board[i][j+2]=='X' && board[i][j+3]=='X') ||
			   (board[i][j]=='x' && board[i][j+1]=='x' && board[i][j+2]=='x' && board[i][j+3]=='x')	){
				status = 1;
				board[i][j]='x'; board[i][j+1]='x'; board[i][j+2]='x'; board[i][j+3]='x';
			}
			else if((board[i][j]=='O' && board[i][j+1]=='O' && board[i][j+2]=='O' && board[i][j+3]=='O') ||
					(board[i][j]=='o' && board[i][j+1]=='o' && board[i][j+2]=='o' && board[i][j+3]=='o') ){
				status = 2;
				board[i][j]='o'; board[i][j+1]='o'; board[i][j+2]='o'; board[i][j+3]='o';
			}	
		}
	return status;
}

int verticalCheck(char board[][MAX_COLUMN],int row,int column){		//checks whether a quadruple combination
	int status=0;													//in the vertical axis is occured

	for(int i=0 ; i<column ; ++i)
		for(int j=row ; j>3 ; --j){
			if((board[j][i]=='X' && board[j-1][i]=='X' && board[j-2][i]=='X' && board[j-3][i]=='X') ||
			   (board[j][i]=='x' && board[j-1][i]=='x' && board[j-2][i]=='x' && board[j-3][i]=='x') ){
				status = 1;
				board[j][i]='x'; board[j-1][i]='x'; board[j-2][i]='x'; board[j-3][i]='x';
			}
			else if((board[j][i]=='O' && board[j-1][i]=='O' && board[j-2][i]=='O' && board[j-3][i]=='O') ||
				    (board[j][i]=='o' && board[j-1][i]=='o' && board[j-2][i]=='o' && board[j-3][i]=='o') ){ 
				status = 2;
				board[j][i]='o'; board[j-1][i]='o'; board[j-2][i]='o'; board[j-3][i]='o';
			}	
		}
	return status;
}

int rightCrossCheck(char board[][MAX_COLUMN],int row,int column){	//checks whether a quadruple combination
	int status=0;													//in the right cross axis is occured
	
	for(int j=row ; j>3 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if((board[j][i]=='X' && board[j-1][i+1]=='X' && board[j-2][i+2]=='X' && board[j-3][i+3]=='X') ||
			   (board[j][i]=='x' && board[j-1][i+1]=='x' && board[j-2][i+2]=='x' && board[j-3][i+3]=='x') ){
				status = 1;
				board[j][i]='x'; board[j-1][i+1]='x';  board[j-2][i+2]='x'; board[j-3][i+3]='x';
			}
			else if((board[j][i]=='O' && board[j-1][i+1]=='O' && board[j-2][i+2]=='O' && board[j-3][i+3]=='O') ||
					(board[j][i]=='o' && board[j-1][i+1]=='o' && board[j-2][i+2]=='o' && board[j-3][i+3]=='o') ){
				status = 2;
				board[j][i]='o'; board[j-1][i+1]='o'; board[j-2][i+2]='o'; board[j-3][i+3]='o';
			}
		}
	return status;
}

int leftCrossCheck(char board[][MAX_COLUMN],int row,int column){	//checks whether a quadruple combination
	int status=0;													//in the left cross axis is occured
	
	for(int j=row ; j>3 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if((board[j][i]=='X' && board[j-1][i-1]=='X' && board[j-2][i-2]=='X' && board[j-3][i-3]=='X') ||
			   (board[j][i]=='x' && board[j-1][i-1]=='x' && board[j-2][i-2]=='x' && board[j-3][i-3]=='x') ){
				status = 1;
				board[j][i]='x'; board[j-1][i-1]='x'; board[j-2][i-2]='x'; board[j-3][i-3]='x';	
			}
			else if((board[j][i]=='O' && board[j-1][i-1]=='O' && board[j-2][i-2]=='O' && board[j-3][i-3]=='O') ||
					(board[j][i]=='o' && board[j-1][i-1]=='o' && board[j-2][i-2]=='o' && board[j-3][i-3]=='o') ){
				status = 2;
				board[j][i]='o'; board[j-1][i-1]='o'; board[j-2][i-2]='o'; board[j-3][i-3]='o';
			}
		}
	return status;
}

bool fillCheck(char board[][MAX_COLUMN],int row,int column){		//checks whether board is full
	int status=true;
	
	for(int i=1 ; i<=row && status ==1 ; ++i)
		for(int j=0; j<column && status == 1; ++j){
			if(board[i][j]=='.')
				status = false;
		}
	return status;		//returns 1 when board is full
}

bool isUsable(char board[][MAX_COLUMN],int row,int column,int coorX,int coorY){	  //checks whether given coordination is playable
	int status=false;
	
	if(coorX<=row && coorX>0 && coorY<column && coorY>=0){
		if(board[coorX][coorY]=='.'){
			if(coorX != row && coorX+1<=row && board[coorX+1][coorY]!='.')
				status = true;
			else if(coorX==row)
				status = true;
		}
	}
	return status;
}

int defence3(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn){	//includes all triple defence functions
	int status=1;
	if(defence3Horizontal(board,row,column,call))
		tempColumn=call-'A';
	else if(defence3Vertical(board,row,column,call))
		tempColumn=call-'A';
	else if(defence3RightCross(board,row,column,call))
		tempColumn=call-'A';	
	else if(defence3LeftCross(board,row,column,call))
		tempColumn=call-'A';
	else 
		status=0;

	return status;
}

int defence3Horizontal(char board[][MAX_COLUMN],int row,int column,char &call){		// if there is a triple 'X' combination
	int status=0;																	// in horizontal axis,blocks that
	char tempCall='A';
	for(int i=row ; i>0 ; --i)
		for(int j=0 ; j<column-2 ; ++j){
			if(board[i][j]=='X' && board[i][j+1]=='X' && board[i][j+2]=='X'){
				if(isUsable(board,row,column,i,j-1)){
					call=tempCall+j-1;
					status=1;
				}
				else if(isUsable(board,row,column,i,j+3)){
					call=tempCall+j+3;
					status=1;
				}
			}
		}
	return status;
}

int defence3Vertical(char board[][MAX_COLUMN],int row,int column,char &call){	// if there is a triple 'X' combination
	int status=0;																// in vertical axis,blocks that
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row ; j>3 ; --j){
			if(board[j][i]=='X' && board[j-1][i]=='X' && board[j-2][i]=='X'){
				if(isUsable(board,row,column,j-3,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int defence3RightCross(char board[][MAX_COLUMN],int row,int column,char &call){	// if there is a triple 'X' combination
	int status=0;																// in right cross axis,blocks that
	char tempCall='A';
	for(int j=row ; j>3 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if(board[j][i]=='X' && board[j-1][i+1]=='X' && board[j-2][i+2]=='X'){
				if(isUsable(board,row,column,j-3,i+3)){
					call=tempCall+i+3;
					status=1;
				}
				else if(isUsable(board,row,column,j+1,i-1)){
					call=tempCall+i-1;
					status=1;
				}		
			}
		}
	return status;
}

int defence3LeftCross(char board[][MAX_COLUMN],int row,int column,char &call){	// if there is a triple 'X' combination
	int status=0;																// in left cross axis,blocks that
	char tempCall='A';
	for(int j=row ; j>3 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if(board[j][i]=='X' && board[j-1][i-1]=='X' && board[j-2][i-2]=='X'){
				if(isUsable(board,row,column,j-3,i-3)){
					call=tempCall+i-3;
					status=1;	
				}
				else if(isUsable(board,row,column,j+1,i+1)){
					call=tempCall+i+1;
					status=1;
				}
			}
		}
	return status;
}

int defence2_1(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn){	//include all 2_1 defence functions
	int status=1;																		//'2_1' means  XX.X or X.XX
	if(defence2_1Horizontal(board,row,column,call))
		tempColumn=call-'A';

	else if(defence2_1RightCross(board,row,column,call))
		tempColumn=call-'A';
		
	else if(defence2_1LeftCross(board,row,column,call))
		tempColumn=call-'A';
	
	else 
		status=0;

	return status;
}

int defence2_1Horizontal(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a 2_1 'X' combination
	int status=0;																	//in horizontal axis,blocks that
	char tempCall='A';
	for(int i=row ; i>0 ; --i)
		for(int j=0 ; j<column-3 ; ++j){
			if(board[i][j]=='X' && board[i][j+1]=='X' && board[i][j+3]=='X' && isUsable(board,row,column,i,j+2)){
				call=tempCall+j+2;
				status=1;
			}
			else if(board[i][j]=='X' && board[i][j+2]=='X' && board[i][j+3]=='X' && isUsable(board,row,column,i,j+1)){
				call=tempCall+j+1;
				status=1;
			}
		}
		
	return status;
}

int defence2_1RightCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a 2_1 'X' combination
	int status=0;																	//in right cross axis,blocks that
	char tempCall='A';
	for(int j=row ; j>3 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if(board[j][i]=='X' && board[j-1][i+1]=='X' && board[j-3][i+3]=='X' && isUsable(board,row,column,j-2,i+2)){
				call=tempCall+i+2;
				status=1;
			}
			else if(board[j][i]=='X' && board[j-2][i+2]=='X' && board[j-3][i+3]=='X' && isUsable(board,row,column,j-1,i+1)){
				call=tempCall+i+1;
				status=1;
			}		
			
		}
	return status;
}

int defence2_1LeftCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a 2_1 'X' combination
	int status=0;																	//in left cross axis,blocks that
	char tempCall='A';
	for(int j=row ; j>3 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if(board[j][i]=='X' && board[j-1][i-1]=='X' && board[j-3][i-3]=='X' && isUsable(board,row,column,j-2,i-2)){
				call=tempCall+i-2;
				status=1;	
			}
			else if(board[j][i]=='X' && board[j-2][i-2]=='X' && board[j-3][i-3]=='X' && isUsable(board,row,column,j-1,i-1)){
				call=tempCall+i-1;
				status=1;
			}
			
		}
	return status;
}

int attack3(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn){		//include all triple attack functions
	int status=1;
	if(attack3Horizontal(board,row,column,call))
		tempColumn=call-'A';

	else if(attack3Vertical(board,row,column,call))
		tempColumn=call-'A';

	else if(attack3RightCross(board,row,column,call))
		tempColumn=call-'A';

	else if(attack3LeftCross(board,row,column,call))
		tempColumn=call-'A';

	else 
		status=0;

	return status;
}

int attack3Horizontal(char board[][MAX_COLUMN],int row,int column,char &call){		//if there is a triple 'O' combination
	int status=0;																	//in horizontal axis, completes to four
	char tempCall='A';
	for(int i=row ; i>0 ; --i)
		for(int j=0 ; j<column-2 ; ++j){
			if(board[i][j]=='O' && board[i][j+1]=='O' && board[i][j+2]=='O'){
				if(isUsable(board,row,column,i,j-1)){
					call=tempCall+j-1;
					status=1;
				}
				else if(isUsable(board,row,column,i,j+3)){
					call=tempCall+j+3;
					status=1;
				}
			}
		}
	return status;
}

int attack3Vertical(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a triple 'O' combination
	int status=0;																//in vertical axis, completes to four
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row ; j>3 ; --j){
			if(board[j][i]=='O' && board[j-1][i]=='O' && board[j-2][i]=='O'){
				if(isUsable(board,row,column,j-3,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int attack3RightCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a triple 'O' combination
	int status=0;																//in right cross axis, completes to four
	char tempCall='A';
	for(int j=row ; j>3 ; --j)
		for(int i=0 ; i<column-3 ; ++i){
			if(board[j][i]=='O' && board[j-1][i+1]=='O' && board[j-2][i+2]=='O'){
				if(isUsable(board,row,column,j-3,i+3)){
					call=tempCall+i+3;
					status=1;
				}
				else if(isUsable(board,row,column,j+1,i-1)){
					call=tempCall+i-1;
					status=1;
				}				
			}
		}
	return status;
}

int attack3LeftCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a triple 'O' combination
	int status=0;																//in left cross axis, completes to four
	char tempCall='A';
	for(int j=row ; j>3 ; --j)
		for(int i=column-1 ; i>2 ; --i){
			if(board[j][i]=='O' && board[j-1][i-1]=='O' && board[j-2][i-2]=='O'){
				if(isUsable(board,row,column,j-3,i-3)){
					call=tempCall+i-3;
					status=1;	
				}
				else if(isUsable(board,row,column,j+1,i+1)){
					call=tempCall+i+1;
					status=1;
				}
			}
		}
	return status;
}

int attack2(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn){		//include all double attack functions
	int status = 1;
	if(attack2Horizontal(board,row,column,call))
		tempColumn=call-'A';

	else if(attack2Vertical(board,row,column,call))
		tempColumn=call-'A';

	else if(attack2RightCross(board,row,column,call))
		tempColumn=call-'A';

	else if(attack2LeftCross(board,row,column,call))
		tempColumn=call-'A';

	else 
		status=0;
	return status;
}

int attack2Horizontal(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a double 'O' combination
	int status=0;																//in horizontal axis, completes to three
	char tempCall='A';
	for(int i=row ; i>0 ; --i)
		for(int j=0 ; j<column-1 ; ++j){
			if(board[i][j]=='O' && board[i][j+1]=='O'){
				if(isUsable(board,row,column,i,j-1)){
					call=tempCall+j-1;
					status=1;
				}
				else if(isUsable(board,row,column,i,j+2)){
					call=tempCall+j+2;
					status=1;
				}
			}
		}
	return status;
}

int attack2Vertical(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a double 'O' combination
	int status=0;																//in vertical axis, completes to three
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row ; j>2 ; --j){
			if(board[j][i]=='O' && board[j-1][i]=='O'){
				if(isUsable(board,row,column,j-2,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int attack2RightCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a double 'O' combination
	int status=0;																//in right cross axis, completes to three
	char tempCall='A';
	for(int j=row ; j>2 ; --j)
		for(int i=0 ; i<column-2 ; ++i){
			if(board[j][i]=='O' && board[j-1][i+1]=='O'){
				if(isUsable(board,row,column,j-2,i+2)){
					call=tempCall+i+2;
					status=1;
				}			
			}
		}
	return status;
}

int attack2LeftCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a double 'O' combination
	int status=0;																//in left cross axis, completes to three
	char tempCall='A';
	for(int j=row ; j>2 ; --j)
		for(int i=column-1 ; i>1 ; --i){
			if(board[j][i]=='O' && board[j-1][i-1]=='O'){
				if(isUsable(board,row,column,j-2,i-2)){
					call=tempCall+i-2;
					status=1;	
				}
			}
		}
	return status;
}

int attack1(char board[][MAX_COLUMN],int row,int column,char call,int &tempColumn){	//includes all single attack functions
	int status = 1;
	if(attack1Vertical(board,row,column,call))
		tempColumn=call-'A';

	else if(attack1Horizontal(board,row,column,call))
		tempColumn=call-'A';

	else if(attack1RightCross(board,row,column,call))
		tempColumn=call-'A';

	else if(attack1LeftCross(board,row,column,call))
		tempColumn=call-'A';

	else 
		status=0;
	return status;
}

int attack1Horizontal(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a single 'O' combination
	int status=0;																//in horizontal axis, completes to two
	char tempCall='A';
	for(int i=row ; i>0 ; --i)
		for(int j=0 ; j<column ; ++j){
			if(board[i][j]=='O'){
				if(isUsable(board,row,column,i,j-1)){
					call=tempCall+j-1;
					status=1;
				}
				else if(isUsable(board,row,column,i,j+1)){
					call=tempCall+j+1;
					status=1;
				}
			}
		}
	return status;
}

int attack1Vertical(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a single 'O' combination
	int status=0;																//in vertical axis, completes to two
	char tempCall='A';
	for(int i=0 ; i<column ; ++i)
		for(int j=row ; j>1 ; --j){
			if(board[j][i]=='O'){
				if(isUsable(board,row,column,j-1,i)){
					call=tempCall+i;
					status=1;
				}
			}
		}
	return status;
}

int attack1RightCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a single 'O' combination
	int status=0;																//in right cross axis, completes to two
	char tempCall='A';
	for(int j=row ; j>1 ; --j)
		for(int i=0 ; i<column-1 ; ++i){
			if(board[j][i]=='O'){
				if(isUsable(board,row,column,j-1,i+1)){
					call=tempCall+i+1;
					status=1;
				}			
			}
		}
	return status;
}

int attack1LeftCross(char board[][MAX_COLUMN],int row,int column,char &call){	//if there is a single 'O' combination
	int status=0;																//in left cross axis, completes to two
	char tempCall='A';
	for(int j=row ; j>1 ; --j)
		for(int i=column-1 ; i>0 ; --i){
			if(board[j][i]=='O'){
				if(isUsable(board,row,column,j-1,i-1)){
					call=tempCall+i-1;
					status=1;	
				}
			}
		}
	return status;
}

void gameMenu(char board[][MAX_COLUMN],int row,int column){
	int key=0;	
	string inp;
	cout << "Welcome to Connect 4!" << endl;

	if(takeInput(row,column)){
		initBoard(board,row,column);
		
		while(key==0){
			cout << "If you wanna play Player vs Player, press P" << endl;
			cout << "Or you wanna play against computer, press C -> ";
			cin >> inp;
		
			if(inp[0] == 'p' || inp[0] == 'P')			//to select pvp mode
				key = 1;
			else if (inp[0] == 'c' || inp[0] == 'C')   //to select pvc mode
				key = 2;
			else
				cout << "Please enter a valid game mode!" << endl; 
		}

		if(key==1){									//plays pvp mode
			printBoard(board,row,column);
			playWith2User(board,row,column);
			printBoard(board,row,column);
			if(check(board,row,column)==1)
				cout << "User1 is Winner!" << endl;

			else if(check(board,row,column)==2)
				cout << "User2 is Winner!" << endl;

			else
				cout << "The game ended in a draw!" << endl;
		}
		else{									//play pvc mode
			printBoard(board,row,column);
			playWithComputer(board,row,column);
			printBoard(board,row,column);
			if(check(board,row,column)==2)
				cout << "Computer is Winner!" << endl;

			else if(check(board,row,column)==1)
				cout << "User1 is Winner!" << endl;

			else
				cout << "The game ended in a draw!" << endl;
		}
	}
}

int main(){
	int row=MAX_ROW,column=MAX_COLUMN;
	char board[MAX_ROW][MAX_COLUMN];

	gameMenu(board,row,column);

	return 0;
}