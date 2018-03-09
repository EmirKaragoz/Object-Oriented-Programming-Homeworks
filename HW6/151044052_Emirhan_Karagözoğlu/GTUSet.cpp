//Author: Emirhan Karagözoğlu - 151044052

using namespace std;

#include "GTUSet.h" 
#include <iostream>

namespace emir{
	template<class T>
	GTUSet<T>::GTUSet() : GTUSetBase<T>::GTUSetBase()	//no parameter constructor
	{
		//empty
	}

	template<class T>
	GTUSet<T>::GTUSet(int inputSize) : GTUSetBase<T>::GTUSetBase(inputSize)	//takes size constructor
	{
		//empty
	}

	template<class T>
	GTUSet<T>::GTUSet(const GTUSet & other) : GTUSetBase<T>::GTUSetBase(other)	//copy constructor
	{
		//empty
	}

	template<class T>
	GTUSet<T> & GTUSet<T>:: operator = (const GTUSet & other){	//assignment operator
		GTUSetBase<T>::operator = (other);
	}

	template<class T>
	bool GTUSet<T>::empty() const{	//tests whether container is empty
		if(this->size_ == 0)
			return true;
		return false;
	}

	template<class T>
	int GTUSet<T>::size() const{	//returns container size
		return(this->size_);
	}

	template<class T>
	int GTUSet<T>::maxSize() const{	//returns maximum size
		return 1000000;
	}

	template<class T>
	void GTUSet<T>::insert(T element){	//inserts element, throws exception std::invalid_argument if the element is already in the set
		int equalityKey = 0;
		
		//checks whether element already exists in container
		{
			T * temp_ptr = this->data.get();
		
			for(int i = 0 ; i < this -> size_ ; ++i , ++temp_ptr){
				if(*temp_ptr == element){
					equalityKey = 1;
					break;
				}
			}
		}

		if(equalityKey == 1)
			throw invalid_argument("This element already exists!");	//throws exception

		//inserts element
		else{
			shared_ptr<T> tmp_shared_ptr = this->data;

			shared_ptr<T> contactShared (new T [this->size_+1],default_delete<T[]>());

			this->data = contactShared;

			for(int i=0 ; i < this->size_ ; ++i)
				this->data.get()[i] = tmp_shared_ptr.get()[i];
			
			this->data.get()[this->size_] = element;

			this->size_ +=1;	
		}

		this->sort();	//sorts
	}

	template<class T>
	void GTUSet<T>::sort(){		//sorts the container
		int first;
		T temp;
	  
	    for (int i= this->size_-1; i>0; --i)
	    {
	        first = 0;                
	        for (int j=1; j<=i; j++)  
	        {
	            if (this->data.get()[j] > this->data.get()[first])
	            first = j;
	        }
	        temp = this->data.get()[first];  
	        this->data.get()[first] = this->data.get()[i];
	        this->data.get()[i] = temp;
	    }
	}

	template<class T>
	void GTUSet<T>::erase(T element){	//erases element
		int newSize=0;
		T * temp(new T [this->size_]);

		for(int i=0,j=0 ; i < this->size_ ; ++i,++j){
			if(element != this->data.get()[i]){
				temp[j] = this->data.get()[i];
				++newSize;
			}
			else
				--j;
		}

		shared_ptr<T> contactShared (new T [newSize],default_delete<T[]>());

		this->data = contactShared;

		for(int i=0 ; i < newSize ; ++i)
			this->data.get()[i] = temp[i];

		this->size_ = newSize;
	}

	template<class T>
	void GTUSet<T>::clear(){	//clears all content
		this->data = nullptr;
		this->size_ = 0;
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::find(T element) const{	//gets iterator to element
		GTUIterator<T> it(this->data.get());

		while(it != this->end()){
			if(*it != element)
				++it;
			else
				break;
		}
	
		return it;
	}

	template<class T>
	int GTUSet<T>::count(T element) const{	//counts elements with a specific value
		GTUIterator<T> it(this->end());

		if(find(element) == it)
			return 0;
		else
			return 1;
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::begin() const{	//returns iterator to beginning
		return (GTUIterator<T> ((this->data).get()));
	}

	template<class T>
	const GTUIterator<T> GTUSet<T>::end() const{	//returns iterator to end
		GTUIterator<T> it((this->data).get());
		it= it + this->size_;
		return (GTUIterator<T> (it));
	}
}