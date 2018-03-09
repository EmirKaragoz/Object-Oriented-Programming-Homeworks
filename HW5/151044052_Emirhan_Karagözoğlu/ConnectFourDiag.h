//Author: Emirhan Karagözoğlu - 151044052

#ifndef ConnectFourDiag_H
#define ConnectFourDiag_H

using namespace std;

#include "ConnectFourAbstract.h"

namespace emir{

	class ConnectFourDiag : public ConnectFourAbstract		//derived from connectfourabstract
	{
	public:
		ConnectFourDiag();
		ConnectFourDiag(int ,int );
		ConnectFourDiag(const ConnectFourDiag& );
		const ConnectFourDiag& operator =(const ConnectFourDiag&);
	private:
		int check();
		int defence3(char call,int &tempColumn) const;
		int defence2_1(char call,int &tempColumn) const;
		int attack3(char call,int &tempColumn) const;		//redefined check and AI functions
		int attack2(char call,int &tempColumn) const;	
		int attack1(char call,int &tempColumn) const;
	};
}

#endif