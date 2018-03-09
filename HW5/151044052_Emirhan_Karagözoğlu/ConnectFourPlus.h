//Author: Emirhan Karagözoğlu - 151044052

#ifndef ConnectFourPlus_H
#define ConnectFourPlus_H

using namespace std;

#include "ConnectFourAbstract.h"

namespace emir{

	class ConnectFourPlus : public ConnectFourAbstract	//derived from connectfourabstract
	{
	public:
		ConnectFourPlus();
		ConnectFourPlus(int ,int );
		ConnectFourPlus(const ConnectFourPlus& );
		const ConnectFourPlus& operator =(const ConnectFourPlus&);
	protected:
		int check();
		int defence3(char call,int &tempColumn) const;
		int defence2_1(char call,int &tempColumn) const;
		int attack3(char call,int &tempColumn) const;			//redefined check and AI functions
		int attack2(char call,int &tempColumn) const;
		int attack1(char call,int &tempColumn) const;
	};
}

#endif
