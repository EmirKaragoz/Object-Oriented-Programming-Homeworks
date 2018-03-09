//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "GTUSetBase.h"
#include "GTUSet.h" 
#include <iostream>

namespace emir{
	template<class T>
	GTUSetBase<T>::GTUSetBase(){	//no parameter constructor
		data = nullptr;
		size_ = 0;
	}

	template<class T>
	GTUSetBase<T>::GTUSetBase(int inputSize){	//takes size constructor
		size_ = inputSize;
		T* contact = new T (size_);
		shared_ptr<T> contactShared (contact);

		data = contactShared;
	}

	template<class T>
	GTUSetBase<T>::GTUSetBase(const GTUSetBase & other){	//copy constructor
		size_ = other.getSize_();

		T* contact = new T (size_);
		shared_ptr<T> contactShared (contact);

		data = contactShared;

		for(int i=0 ; i < size_ ; ++i)
			data.get()[i] = other.data.get()[i];
	}

	template<class T>
	GTUSetBase<T>::~GTUSetBase(){	//destructor
		data = nullptr;
		size_ = 0;
	}

	template<class T>
	GTUSetBase<T> & GTUSetBase<T>:: operator = (const GTUSetBase & other){	//assignment operator
		if(this == &other)
			return *this;

		size_ = other.getSize_();
		T* contact = new T (size_);
		shared_ptr<T> contactShared (contact);

		data = contactShared;

		for(int i=0 ; i < size_ ; ++i)
			data.get()[i] = other.data.get()[i];

		return *this;
	}

	template<class T>
	int GTUSetBase<T>::getSize_() const{	//gets size
		return size_;
	}

	template<class T>
	shared_ptr<T> GTUSetBase<T>::getData() const{	//gets data
		return data;
	}


	//returns a set is the intersection of the two sets
	template <class T>
	shared_ptr<GTUSetBase<T> > setIntersection (const GTUSetBase<T>& first, const GTUSetBase<T>& second){		
		
		GTUSet<T> set;
		
		//finds intersection of two sets
		for(int i=0 ; i<first.getSize_() ; ++i){
			for(int j=0 ; j<second.getSize_() ; ++j){
				if((first.getData()).get()[i] == (second.getData()).get()[j]){
					set.insert((first.getData()).get()[i]);
					break;
				}
			}
		}

		shared_ptr<GTUSet<T>> temp(new GTUSet<T>[set.getSize_()],default_delete<GTUSet<T>[]>());
		
		for(auto it = set.begin(); it != set.end(); ++it)
			temp.get()->insert(*it);

		return(temp);
	}
}