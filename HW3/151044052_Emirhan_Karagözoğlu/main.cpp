using namespace std;

#include "ConnectFour.cpp"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(){
	
	string gameMode;

	cout << "Welcome to Connect 4!" << endl;

	while(gameMode[0]!='S' && gameMode[0]!='s' && gameMode[0]!='M' && gameMode[0]!='m'){
		cout << "Choose a game mode(S/M) ->";
		cin >> gameMode;
	}

	if(gameMode[0]=='S' || gameMode[0]=='s'){
		ConnectFour objeSingle;
		objeSingle.playGame();
	}

	else{
		int objeNum;
		char multiple='M';
		string tempLoad;
		ConnectFour obje1,obje2,obje3,obje4,obje5;
		int status1,status2,status3,status4,status5;
		obje1.menu();
		obje2.menu();
		obje3.menu();	
		obje4.menu();
		obje5.menu();
		while(!obje1.end() || !obje2.end() || !obje3.end() || !obje4.end() || !obje5.end()){	//until all games finished
			cout << "Choose an object number ->";
			cin >> objeNum;
			if(cin.fail()){				//harf girme durumu
				cin.clear();
				cin.ignore();
				cerr <<"It's not an integer!"<<endl;
			}
			else{
				if(objeNum==1 && !obje1.end()){
					cin.ignore();
					status1 = obje1.multi(tempLoad);
				}
				else if(objeNum==2 && !obje2.end()){
					cin.ignore();
					status2 = obje2.multi(tempLoad);
				}
				else if(objeNum==3 && !obje3.end()){
					cin.ignore();
					status3 = obje3.multi(tempLoad);
				}
				else if(objeNum==4 && !obje4.end()){
					cin.ignore();
					status4 = obje4.multi(tempLoad);
				}
				else if(objeNum==5 && !obje5.end()){
					cin.ignore();
					status5 = obje5.multi(tempLoad);
				}
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
			}
			if(obje1.compareObject(obje2)){		//obje1 and obje2, if obje is better than obje1, returns true
				cout << "obje2 is better than obje1"<<endl;
			}
		}
		cout << "All games finished!"<< endl;
	}

	return 0;
}