#include<iostream>
#include "GTUIterator.cpp"
#include "GTUSet.cpp"
#include "GTUSetBase.cpp"
#include "GTUMap.cpp"

#include <string>

using namespace std;
using namespace emir;

int main(){

	//Integer Set Tests
	cout << "------------------------------"<<endl;

	GTUSet<int> integerSet;
	GTUIterator<int> integerIt;
	
	cout<<"Size of integer set is "<<integerSet.size()<<endl;

	try{
		integerSet.insert(5);
		integerSet.insert(2);
		integerSet.insert(4);
		integerSet.insert(1);
		integerSet.insert(3);
		integerSet.insert(2);	//throws exception
	}

	catch (const invalid_argument& ia) {
		cerr << "Invalid argument: " << ia.what() << endl;
 	}

	for( integerIt = integerSet.begin(); integerIt != integerSet.end(); ++integerIt)
		cout<< *integerIt << endl;

	cout << "Insert process completed!"<<endl;

	integerSet.erase(1);
	integerSet.erase(1);
	integerSet.erase(5);

	for( integerIt = integerSet.begin(); integerIt != integerSet.end(); ++integerIt)
		cout<< *integerIt << endl;

	cout << "Erase process completed!"<<endl;

	cout<<"Size of integer set is "<<integerSet.size()<<endl;
	
	integerIt = integerSet.find(5);
	cout<<"Set contains "<< *integerIt <<endl;

	cout<<"Number of 12 is "<<integerSet.count(12)<<endl;
	cout<<"Number of 2 is "<<integerSet.count(2)<<endl;
	
	integerSet.clear();
	
	if(integerSet.empty())
		cout<<"Set is empty!"<<endl;

	//String Set Tests
	cout << "------------------------------"<<endl;

	GTUSet<string> stringSet;
	GTUIterator<string> stringIt;
	
	cout<<"Size of string set is "<<stringSet.size()<<endl;

	try{
		stringSet.insert("Mustafa");
		stringSet.insert("Fatih");
		stringSet.insert("Tunalı");
		stringSet.insert("Mustafa");	//throws exception
	}

	catch (const invalid_argument& ia) {
		cerr << "Invalid argument: " << ia.what() << endl;
 	}

	for( stringIt = stringSet.begin(); stringIt != stringSet.end(); ++stringIt)
		cout<< *stringIt << endl;

	cout << "Insert process completed!"<<endl;

	stringSet.erase("Fatih");

	for( stringIt = stringSet.begin(); stringIt != stringSet.end(); ++stringIt)
		cout<< *stringIt << endl;

	cout << "Erase process completed!"<<endl;

	cout<<"Size of string set is "<<stringSet.size()<<endl;
	
	stringIt = stringSet.find("Mustafa");
	cout<<"Set contains "<< *stringIt <<endl;

	cout<<"Number of Ali is "<<stringSet.count("Ali")<<endl;
	cout<<"Number of Mustafa is "<<stringSet.count("Tunalı")<<endl;
	
	stringSet.clear();
	
	if(stringSet.empty())
		cout<<"Set is empty!"<<endl;

	//String,Integer Map Tests
	cout << "------------------------------"<<endl;

	GTUMap<string,int> strIntMap;
	GTUIterator< pair<string,int> > mapIterator;
	
	cout<<"Size of string set is "<<strIntMap.size()<<endl;

	try{
		strIntMap.insert(make_pair("Yusuf",1));
		strIntMap.insert(make_pair("Sinan",12));
		strIntMap.insert(make_pair("Akgül",123));
		strIntMap.insert(make_pair("Yusuf",45));	//throws exception
	}

	catch (const invalid_argument& ia) {
		cerr << "Invalid argument: " << ia.what() << endl;
 	}

	for( mapIterator = strIntMap.begin(); mapIterator != strIntMap.end(); ++mapIterator)
		cout<< get<1>(*mapIterator) << endl;

	cout << "Insert process completed!"<<endl;

	strIntMap.erase(make_pair("Yusuf",1));

	for( mapIterator = strIntMap.begin(); mapIterator != strIntMap.end(); ++mapIterator)
		cout<< get<1>(*mapIterator) << endl;

	cout << "Erase process completed!"<<endl;

	cout<<"Size of string set is "<<strIntMap.size()<<endl;
	
	mapIterator = strIntMap.find(make_pair("Sinan",12));
	cout<<"Set contains "<< get<1>(*mapIterator) <<endl;

	cout<<"Number of Ali is "<<strIntMap.count(make_pair("Ali",52))<<endl;
	cout<<"Number of Akgül is "<<strIntMap.count(make_pair("Akgül",123))<<endl;
	
	strIntMap.clear();
	
	if(strIntMap.empty())
		cout<<"Set is empty!"<<endl;

	//Integer Sets Intersection Tests
	cout << "------------------------------"<<endl;

	GTUSet<int> otherIntSet;

	try{
		otherIntSet.insert(5);
		otherIntSet.insert(2);
		otherIntSet.insert(4);
		otherIntSet.insert(1);
		otherIntSet.insert(3);

		integerSet.insert(5);
		integerSet.insert(2);
		integerSet.insert(4);
		integerSet.insert(7);
	}

	catch (const invalid_argument& ia) {
		cerr << "Invalid argument: " << ia.what() << endl;
 	}
 	cout << "First set is = ";
 	for(auto it = integerSet.begin(); it != integerSet.end(); ++it)
		cout<< *it << ' ';
	cout << endl;

	cout << "Second set is = ";

 	for(auto it = otherIntSet.begin(); it != otherIntSet.end(); ++it)
		cout<< *it << ' ';
	cout << endl;

 	auto other = setIntersection(integerSet,otherIntSet);

 	cout <<"Intersection of two set is = ";

 	for( auto it = other->begin(); it != other->end(); ++it)
		cout<< *it << ' ';
	cout << endl;

	//String,Integer Maps Intersection Tests
	cout << "------------------------------"<<endl;

	GTUMap<string,int> otherStrIntMap;

	try{
		strIntMap.insert(make_pair("Yusuf",1));
		strIntMap.insert(make_pair("Sinan",12));
		strIntMap.insert(make_pair("Akgül",123));

		otherStrIntMap.insert(make_pair("Yusuf",2));
		otherStrIntMap.insert(make_pair("Sinan",12));
	}

	catch (const invalid_argument& ia) {
		cerr << "Invalid argument: " << ia.what() << endl;
 	}
 	cout << "First map is = ";
 	for(auto it = strIntMap.begin(); it != strIntMap.end(); ++it)
		cout<< get<1>(*it) << ' ';
	cout << endl;

	cout << "Second map is = ";

 	for(auto it = otherStrIntMap.begin(); it != otherStrIntMap.end(); ++it)
		cout<< get<1>(*it) << ' ';
	cout << endl;

 	auto other1 = setIntersection(strIntMap,otherStrIntMap);

 	cout <<"Intersection of two map is = ";

 	for(auto it = other1->begin(); it != other1->end(); ++it)
		cout<< (*it).second << ' ';
	cout << endl;
	
	cout << "------------------------------"<<endl;

	return 0;
}