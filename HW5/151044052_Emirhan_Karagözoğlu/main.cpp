//Author: Emirhan Karagözoğlu - 151044052

#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace std;
using namespace emir;

int main(){
	char mode;
	cout << "Welcome to Connect 4!" << endl;

	while(1){
		cout << "Select a game mode(Plus,Diagonal,Undo)"<<endl;
		cin >> mode;

		if(mode == 'P' || mode == 'p'){		//plus mode
			ConnectFourPlus objePlus;
			objePlus.playGame();
			break;
		}
		
		else if(mode == 'D' || mode == 'd'){	//diagonal mode
			ConnectFourDiag objeDiag;	
			objeDiag.playGame();
			break;
		}
		else if(mode == 'U' || mode == 'u'){	//undo mode
			ConnectFourPlusUndo objeUndo;
			objeUndo.playGame();
			break;
		}
		else
			cerr << "Invalid game mode! Please try againg!" <<endl;
	}

	return 0;
}