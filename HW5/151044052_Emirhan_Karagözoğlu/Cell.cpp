//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "Cell.h"
#include <iostream>
#include <string>
#include <fstream>

namespace emir{

	Cell::Cell(char tmpCell){
		setCell(tmpCell);
	}

	char Cell::getCell() const{
		return cell;
	}

	bool Cell::setCell(char option){
		if(option == 'X' || option == 'O' || option == '*' || option == 'x' || option == 'o' || option == ' '){
			cell= option;
			return true;
		}
		return false;
	}

	//Cell class operators overloading
	bool Cell::operator == (const Cell& other) const{
		if(cell == other.cell && rowNumber == other.rowNumber && position == other.position)
			return true;
		return false;
	}

	const Cell& Cell::operator ++(){		//prefix increment
		if(cell == empty)
			cell = user1;
		else if(cell == user1)
			cell = user2;
		else if(cell == user2)
			cell = computer;
		else if(cell == computer)
			cell = empty;

		return *this;
	}

	const Cell Cell::operator ++(int ignoreMe){	//postfix increment
		char tempCell = cell;
		if(cell == empty)
			cell = user1;
		else if(cell == user1)
			cell = user2;
		else if(cell == user2)
			cell = computer;
		else if(cell == computer)
			cell = empty;

		return Cell(tempCell);
	}

	const Cell& Cell::operator --(){	//prefix decrement
		if(cell == empty)
			cell = computer;
		else if(cell == user1)
			cell = empty;
		else if(cell == user2)
			cell = user1;
		else if(cell == computer)
			cell = user2;

		return *this;
	}

	const Cell Cell::operator --(int ignoreMe){	//postfix decrement
		char tempCell = cell;
		if(cell == empty)
			cell = computer;
		else if(cell == user1)
			cell = empty;
		else if(cell == user2)
			cell = user1;
		else if(cell == computer)
			cell = user2;

		return Cell(tempCell);
	}

	ostream& operator <<(ostream& out, const Cell& obje){		//stream insertion
		cout << obje.rowNumber << endl;
		cout << obje.position << endl;
		cout << obje.cell;
		return out;
	}

	istream& operator >>(istream& in, Cell& obje){				//stream extraction
		cin >> obje.rowNumber;
		cin >> obje.position;
		cin >> obje.cell;
		return in;
	}
}