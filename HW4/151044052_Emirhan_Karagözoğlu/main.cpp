//Author: Emirhan Karagözoğlu - 151044052
using namespace std;

#include "ConnectFour.cpp"
#include <iostream>
#include <string>
#include <fstream>

int main(){
	string gameMode,boardName;
	cout << "Welcome to Connect 4!" << endl;

	while(gameMode[0]!='S' && gameMode[0]!='s' && gameMode[0]!='M' && gameMode[0]!='m'){	//Oyun Modu Seçme
		cout << "Choose a game mode(S/M) ->"<<endl;
		cin >> gameMode;
	}
	cin.ignore();
	if(gameMode[0]=='S' || gameMode[0]=='s'){	// single play
		ConnectFour objeSingle;
		objeSingle.playGame();
	}

	else{									//multi play
		ConnectFour obje1(boardName);
		obje1.menu();
	
		ConnectFour obje2(boardName);
		obje2.menu();
		
		ConnectFour obje3(boardName);
		obje3.menu();
		
		ConnectFour obje4(boardName);
		obje4.menu();
		
		ConnectFour obje5(boardName);
		obje5.menu();

		int status1,status2,status3,status4,status5;	// for load operation
		int objeNum;
		char multiple='M';
		string tempLoad;
		
		while(!obje1.end() || !obje2.end() || !obje3.end() || !obje4.end() || !obje5.end()){	//until all games finished
			cout << "Choose an object number ->"<<endl;
			cin >> objeNum;

			if(cin.fail()){		//check validty of object number
				cin.clear();
				cin.ignore();
				cerr <<"Invalid object number!"<<endl;
			}

			//multiplay for objects
			if(objeNum==1 && !obje1.end())			
				status1 = obje1.multi(tempLoad);
			
			else if(objeNum==2 && !obje2.end())
				status2 = obje2.multi(tempLoad);
			
			else if(objeNum==3 && !obje3.end())
				status3 = obje3.multi(tempLoad);
			
			else if(objeNum==4 && !obje4.end())
				status4 = obje4.multi(tempLoad);
			
			else if(objeNum==5 && !obje5.end())
				status5 = obje5.multi(tempLoad);

			else
				cout << "Invalid object number!"<<endl;

			while(status1==1)	//Load processing
				obje1.load(tempLoad,obje1.getGameOption(),status1,multiple);
			while(status2==1)
				obje2.load(tempLoad,obje2.getGameOption(),status2,multiple);
			while(status3==1)
				obje3.load(tempLoad,obje3.getGameOption(),status3,multiple);
			while(status4==1)
				obje4.load(tempLoad,obje4.getGameOption(),status4,multiple);
			while(status5==1)
				obje5.load(tempLoad,obje5.getGameOption(),status5,multiple);
			
			//equality
			if(obje1 == obje2)
				cout << "obje1 and obje2 are same!" <<endl;
			if(obje1 != obje2)
				cout << "obje1 and obje2 are different!" <<endl;
		}
		cout << "All games finished!"<< endl;
	}

	return 0;
}