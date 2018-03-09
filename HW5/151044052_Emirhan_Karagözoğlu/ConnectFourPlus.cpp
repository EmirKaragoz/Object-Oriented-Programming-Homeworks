//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "ConnectFourPlus.h"

namespace emir{

	ConnectFourPlus::ConnectFourPlus() : ConnectFourAbstract(){
		//deliberately empty
	}

	ConnectFourPlus::ConnectFourPlus(int row , int column) : ConnectFourAbstract(row,column){
		//deliberately empty
	} 

	ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus& other) : ConnectFourAbstract(other){
		//deliberately empty
	}

	const ConnectFourPlus& ConnectFourPlus::operator =(const ConnectFourPlus& other){
		ConnectFourAbstract::operator = (other);
	}

	int ConnectFourPlus::check(){	//checks plus
		int status;
		
		status = horizontalCheck();
		if(status==0)
			status=verticalCheck();

		return status;
	}

	int ConnectFourPlus::defence3(char call,int &tempColumn) const{		//defences plus
		int status=1;
		if(defence3Horizontal(call))
			tempColumn=call-'A';
		else if(defence3Vertical(call))
			tempColumn=call-'A';
		else 
			status=0;

		return status;
	}

	int ConnectFourPlus::defence2_1(char call,int &tempColumn) const{	//defences horizontal
		int status=1;																		
		
		if(defence2_1Horizontal(call))
			tempColumn=call-'A';
		else 
			status=0;

		return status;
	}

	int ConnectFourPlus::attack3(char call,int &tempColumn) const{	//attack3 plus
		int status=1;
		if(attack3Horizontal(call))
			tempColumn=call-'A';

		else if(attack3Vertical(call))
			tempColumn=call-'A';

		else 
			status=0;

		return status;
	}

	int ConnectFourPlus::attack2(char call,int &tempColumn) const{	//attack2 plus
		int status = 1;
		if(attack2Horizontal(call))
			tempColumn=call-'A';

		else if(attack2Vertical(call))
			tempColumn=call-'A';

		else 
			status=0;
		return status;
	}

	int ConnectFourPlus::attack1(char call,int &tempColumn) const{	//attack1 plus
		int status = 1;
		if(attack1Vertical(call))
			tempColumn=call-'A';

		else if(attack1Horizontal(call))
			tempColumn=call-'A';

		else 
			status=0;
		return status;
	}
}