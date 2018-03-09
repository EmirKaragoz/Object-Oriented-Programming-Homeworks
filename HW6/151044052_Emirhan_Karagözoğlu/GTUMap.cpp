//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "GTUMap.h" 
#include <iostream>

namespace emir{
	template<class K,class V>
	GTUMap<K,V>::GTUMap() : GTUSet< pair<K,V> >::GTUSet()	//no parameter constructor
	{
		//empty
	}

	template<class K,class V>
	GTUMap<K,V>::GTUMap(int inputSize) : GTUSet< pair<K,V> >::GTUSet(inputSize)	//takes size constructor
	{
		//empty
	}

	template<class K,class V>
	GTUMap<K,V>::GTUMap(const GTUMap & other) : GTUSet< pair<K,V> >::GTUSet(other)	//copy constructor
	{
		//empty
	}

	template<class K,class V>
	GTUMap<K,V> & GTUMap<K,V>:: operator = (const GTUMap & other){	//assignment operator
		GTUSet< pair<K,V> >::operator = (other);
	}

	template<class K,class V>
	V& GTUMap<K,V>::operator [] (const K & k){	//index operator
		for(int i=0 ;i<this->size_;++i){
			if(get<0>(this->data.get()[i]) == k)
				return (get<1>(this->data.get()[i]));
		}
	}

	template<class K,class V>
	void GTUMap<K,V>::insert(pair<K,V> element){	//overloaded insert function
		int equalityKey = 0;
		
		//difference between base class' function is checking same element operation
		{
			for(int i = 0 ; i < this -> size_ ; ++i){
				if(get<0>(this->data.get()[i]) == get<0> (element)){	//keys can't be same
					equalityKey = 1;
					break;
				}
			}
		}

		if(equalityKey == 1)
			throw invalid_argument("This element already exists!");

		else{
			shared_ptr<pair<K,V>> tmp_shared_ptr = this->data;

			shared_ptr<pair<K,V>> contactShared (new pair<K,V> [this->size_+1],default_delete<pair<K,V>[]>());

			this->data = contactShared;

			for(int i=0 ; i < this->size_ ; ++i)
				this->data.get()[i] = tmp_shared_ptr.get()[i];
			
			this->data.get()[this->size_] = element;

			this->size_ +=1;	
		}

		this->sort();
	}
}