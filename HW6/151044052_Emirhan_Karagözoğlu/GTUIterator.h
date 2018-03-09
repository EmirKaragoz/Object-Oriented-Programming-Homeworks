//Author: Emirhan Karagözoğlu - 151044052

#ifndef GTUIterator_H
#define GTUIterator_H

using namespace std;
#include <memory>

namespace emir{
	template <class T>
	class GTUIterator{
	public:
		GTUIterator();	//no parameter constructor
		GTUIterator(T *);	//takes pointer constructor
		GTUIterator(const GTUIterator &);	//copy constructor
		//operator overloadings
		GTUIterator & operator = (const GTUIterator &);
		T operator * () const;
		GTUIterator & operator ++ ();
		GTUIterator & operator -- ();
		GTUIterator & operator + (int);
		bool operator == (const GTUIterator &) const;
		bool operator != (const GTUIterator &) const;
		T * operator ->() const;
	private:
		T * data;
	};
}

#endif