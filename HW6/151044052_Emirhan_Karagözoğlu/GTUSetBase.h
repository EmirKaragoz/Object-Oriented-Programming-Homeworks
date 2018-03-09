//Author: Emirhan Karagözoğlu - 151044052

#ifndef GTUSetBase_H
#define GTUSetBase_H

using namespace std;

#include "GTUIterator.h"
#include <memory>		//for shared_ptr

namespace emir{
	template<class T>
	class GTUSetBase{
	public:
		GTUSetBase();		//no parameter constructor
		GTUSetBase(int);	//takes size constructor
		GTUSetBase(const GTUSetBase &);		//copy constructor
		virtual ~GTUSetBase();		//destructor
		GTUSetBase & operator = (const GTUSetBase &);	//assignment operator
		virtual bool empty() const = 0;		//tests whether container is empty
		virtual int size() const = 0;		//returns container size
		virtual int maxSize() const = 0;	//returns maximum size
		virtual void insert(T) = 0;			//inserts element, throws exception std::invalid_argument if the element is already in the set
		virtual void erase(T) = 0;			//erases element
		virtual void clear() = 0;			//clears all content
		virtual const GTUIterator<T> find(T) const = 0;		//gets iterator to element
		virtual int count(T) const = 0;						//counts elements with a specific value
		virtual const GTUIterator<T> begin() const = 0;		//returns iterator to beginning
		virtual const GTUIterator<T> end() const = 0;		//returns iterator to end
		int getSize_() const;			//gets size
		shared_ptr<T> getData() const;	//gets data
	protected:
		shared_ptr<T> data;
		int size_;
	};

	//returns a set is the intersection of the two sets
	template <class T>
	shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>&, const GTUSetBase<T>&);
}

#endif