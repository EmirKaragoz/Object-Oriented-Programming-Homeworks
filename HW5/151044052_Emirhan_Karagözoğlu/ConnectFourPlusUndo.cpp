//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "ConnectFourPlusUndo.h"

namespace emir{

	ConnectFourPlusUndo::ConnectFourPlusUndo() : ConnectFourPlus(){
		//deliberately empty
	}

	ConnectFourPlusUndo::ConnectFourPlusUndo(int row , int column) : ConnectFourPlus(row,column){
		//deliberately empty
	} 

	ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo& other) : ConnectFourPlus(other){
		//deliberately empty
	}

	const ConnectFourPlusUndo& ConnectFourPlusUndo::operator =(const ConnectFourPlusUndo& other){
		ConnectFourPlus::operator = (other);
	}

	void ConnectFourPlusUndo::undo(){
		if(history.length()>0){
			char undoColumn = history[history.length()-1];
			int finalColumn = undoColumn - 'A';

			for(int i=0 ; i<row ; ++i){								//undo operation
				if(gameBoard[i][finalColumn].getCell()!='*'){
					gameBoard[i][finalColumn].setCell('*');
					break;
				}
			}

			history.resize(history.length()-1);
		}
		else{
			cerr << "There is no moves were made! So you can't undo." << endl;
			++move;
		}
	}

	int ConnectFourPlusUndo::pvp(string & load){
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

				else if(columnOption.compare("UNDO") == 0){		//check undo
					cout << "Undoing..."<< endl;
					undo();
					--move;
					printBoard();
				}

				else 
					key = moveValidity(columnOption,tempColumn);	//check validty of move
			}
			play(tempColumn);	//make move
			history.push_back(tempColumn);
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

	int ConnectFourPlusUndo::pvc(string & load){

		while(!end()){	//until game ended
			int key=1,undoKey=1;
			char tempColumn;
			string columnOption;
			
			if(move%2 == 0){
				play();		//computer makes move
				history.push_back(computerLastMove);
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

					else if(columnOption.compare("UNDO") == 0){		//check undo
						cout << "Undoing..."<< endl;
						undo();
						--move;
						printBoard();
						undoKey = 0;
						key = 0;
					}

					else 
						key = moveValidity(columnOption,tempColumn);	//check validity of move
				}
				if(undoKey==1){
					play(tempColumn);	//make move
					history.push_back(tempColumn);
					++move;				//update move counter

					if(!end())
						printBoard();
				}
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

	void ConnectFourPlusUndo::save(const string & decision,char gameType) const{
		ofstream saveFile;
		saveFile.open(decision);

		if(saveFile.is_open()){			//if file has been opened
			saveFile << row << endl;
			saveFile << column << endl;
			saveFile << gameType << endl;	
			saveFile << move << endl;		//write process
			saveFile << history << endl;

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

	void ConnectFourPlusUndo::load(string & tempLoad,char gameOption,int & status){
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

		getline(loadFile,history);
		
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
}