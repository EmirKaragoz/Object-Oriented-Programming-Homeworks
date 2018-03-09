//Author: Emirhan Karagözoğlu - 151044052

#ifndef GTUSet_H
#define GTUSet_H

using namespace std;

#include "GTUSetBase.h"

namespace emir{
	template<class T>
	class GTUSet : public GTUSetBase<T> {
	public:
		GTUSet();	//no parameter constructor
		GTUSet(int);	//takes size constructor
		GTUSet(const GTUSet<T> &);		//copy constructor
		GTUSet & operator = (const GTUSet<T> &);	//assignment operator
		virtual bool empty() const;		//tests whether container is empty
		virtual int size() const;		//returns container size
		virtual int maxSize() const;	//returns maximum size
		virtual void insert(T);			//inserts element, throws exception std::invalid_argument if the element is already in the set
		virtual void erase(T);			//erases element
		virtual void clear();			//clears all content
		virtual const GTUIterator<T> find(T) const;		//gets iterator to element
		virtual int count(T) const;						//counts elements with a specific value
		virtual const GTUIterator<T> begin() const;		//returns iterator to beginning
		virtual const GTUIterator<T> end() const;		//returns iterator to end
	protected:
		void sort();	//sorts the container
	};
}

#endif