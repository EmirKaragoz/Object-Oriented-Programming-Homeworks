//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "GTUIterator.h" 
#include <iostream>

namespace emir{
	template <class T>
	GTUIterator<T>::GTUIterator() : data(nullptr)	//no parameter constructor
	{
		//empty
	}

	template <class T>
	GTUIterator<T>::GTUIterator(T * ptr) : data(ptr)	//takes pointer constructor
	{
		//empty
	}

	template <class T>
	GTUIterator<T>::GTUIterator(const GTUIterator & other) :  data(other.data)	//copy constructor
	{
		//empty
	}

	template <class T>
	GTUIterator<T>& GTUIterator<T>::operator = (const GTUIterator & other)	//assignment operator
	{
		if(this == &other)	
			return *this;

		data = other.data;
		return *this;
	}

	template <class T>
	T GTUIterator<T>::operator * () const{	//dereference operator
		return *data;
	}

	template <class T>
	GTUIterator<T>& GTUIterator<T>::operator ++ (){	//increment operator
		++data;
		return *this;
	}

	template <class T>
	GTUIterator<T>& GTUIterator<T>::operator -- (){	//decrement operator
		--data;
		return *this;
	}

	template <class T>
	GTUIterator<T>& GTUIterator<T>::operator + (int value){	//plus operator
		for(int i=0 ; i<value ; ++i)
			++data;
		
		return *this;
	}

	template <class T>
	bool GTUIterator<T>::operator == (const GTUIterator & other) const{	//is equal operator
		return(data == other.data);
	}

	template <class T>
	bool GTUIterator<T>::operator != (const GTUIterator & other) const{	//isn't equal operator
		return(data != other.data);
	}

	template <class T>
	T* GTUIterator<T>::operator -> () const{	//arrow operator
		return data;
	}
}
