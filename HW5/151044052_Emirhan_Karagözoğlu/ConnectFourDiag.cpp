//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "ConnectFourDiag.h"

namespace emir{

	ConnectFourDiag::ConnectFourDiag() : ConnectFourAbstract(){
		//deliberately empty
	}

	ConnectFourDiag::ConnectFourDiag(int row , int column) : ConnectFourAbstract(row,column){
		//deliberately empty
	} 

	ConnectFourDiag::ConnectFourDiag(const ConnectFourDiag& other) : ConnectFourAbstract(other){
		//deliberately empty
	}

	const ConnectFourDiag& ConnectFourDiag::operator =(const ConnectFourDiag& other){
		ConnectFourAbstract::operator = (other);
	}

	int ConnectFourDiag::check(){	//checks cross
		int status;

		status=rightCrossCheck();
		if(status==0)
			status=leftCrossCheck();
			
		return status;
	}

	int ConnectFourDiag::defence3(char call,int &tempColumn) const{	//defences3 cross
		int status=1;
		
		if(defence3RightCross(call))
			tempColumn=call-'A';	
		else if(defence3LeftCross(call))
			tempColumn=call-'A';
		else 
			status=0;

		return status;
	}

	int ConnectFourDiag::defence2_1(char call,int &tempColumn) const{	//defences2_1 cross
		int status=1;																		
		
		if(defence2_1RightCross(call))
			tempColumn=call-'A';
			
		else if(defence2_1LeftCross(call))
			tempColumn=call-'A';
		
		else 
			status=0;

		return status;
	}

	int ConnectFourDiag::attack3(char call,int &tempColumn) const{	//attacks3 cross
		int status=1;
		
		if(attack3RightCross(call))
			tempColumn=call-'A';

		else if(attack3LeftCross(call))
			tempColumn=call-'A';

		else 
			status=0;

		return status;
	}

	int ConnectFourDiag::attack2(char call,int &tempColumn) const{	//attacks2 cross
		int status = 1;
		
		if(attack2RightCross(call))
			tempColumn=call-'A';

		else if(attack2LeftCross(call))
			tempColumn=call-'A';

		else 
			status=0;
		return status;
	}

	int ConnectFourDiag::attack1(char call,int &tempColumn) const{	//attacks1 cross
		int status = 1;

		if(attack1RightCross(call))
			tempColumn=call-'A';

		else if(attack1LeftCross(call))
			tempColumn=call-'A';

		else 
			status=0;
		return status;
	}
}