//Author: Emirhan Karagözoğlu - 151044052

#ifndef Cell_H
#define Cell_H

using namespace std;

#include <iostream>
#include <string>
#include <fstream>

namespace emir{

	enum CellType{
		empty,
		user1,
		user2,
		computer
	};

	class Cell{
	public:
		/*Constructors*/
		Cell(char tmpCell='*');

		/*Getter*/
		char getCell() const;
		/*Setter*/
		bool setCell(char option);
		/*Overloding operators*/
		bool operator ==(const Cell&)const;
		const Cell& operator ++();
		const Cell operator ++(int);
		const Cell& operator --();
		const Cell operator --(int);
		friend ostream& operator << (ostream&, const Cell&);
		friend istream& operator >> (istream&, Cell&);

	private:
		int rowNumber = 0;
		char position = 'A';
		char cell;
	};
}
#endif