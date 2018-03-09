//Author: Emirhan Karagözoğlu - 151044052

#ifndef GTUMap_H
#define GTUMap_H

using namespace std;

#include "GTUSet.h"

namespace emir{
	template<class K, class V>
	class GTUMap : public GTUSet< pair<K, V> >{
	public:
		GTUMap();	//no parameter constructor
		GTUMap(int);	//takes size constructor
		GTUMap(const GTUMap<K,V> &);	//copy constructor
		GTUMap & operator = (const GTUMap<K,V> &);	//assignment operator
		V& operator [] (const K &);		//index operator
		virtual void insert(pair<K,V>);	//overloaded insert function
	};
}

#endif