//Author: Emirhan Karagözoğlu - 151044052

#ifndef ConnectFourPlusUndo_H
#define ConnectFourPlusUndo_H

using namespace std;

#include "ConnectFourPlus.h"

namespace emir{

	class ConnectFourPlusUndo : public ConnectFourPlus 		//derived from connectfourplus
	{
	public:
		ConnectFourPlusUndo();
		ConnectFourPlusUndo(int ,int );
		ConnectFourPlusUndo(const ConnectFourPlusUndo& );
		const ConnectFourPlusUndo& operator =(const ConnectFourPlusUndo&);
	private:
		string history;
		
		void undo();							//gets back last move
		int pvp(string & load);					//plays player versus player game mode
		int pvc(string & load);					//plays player versus computer game mode
		void save(const string & decision,char gameType) const;	//saves current game
		void load(string & tempLoad,char gameOption,int & status);	//loads the desired game
	};
}

#endif