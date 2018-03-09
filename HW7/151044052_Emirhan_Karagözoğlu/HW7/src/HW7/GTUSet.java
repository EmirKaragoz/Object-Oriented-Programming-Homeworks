package HW7;

import java.lang.reflect.Array;
import java.security.InvalidParameterException;

/**
 * Set Class
 * @author Emirhan Karagözoğlu
 * @param <T> type of set
 */
public class GTUSet<T> implements GTUSetInt<T>{

    /**
     *generic type array to keep set or map data
     */
    protected T [] data;   

    /**
     *type of the parameter class type
     */
    protected Class<T[]> type; 

    /**
     *capacity of set or map
     */
    protected int dataCapacity;

    /**
     *size of set or map
     */
    protected int dataSize;     

    /**
    * Iterator class to keep and represent one element of set or map data
    */
    public class GTUIterator{
        /**
         * position of iterator
         */
        private int position = 0 ;

        /**
        *@return current position
        */
        public int getPosition(){
            return position;
        }

        /**
        *Sets position according to incoming parameter if its possible
        *@param value incoming position value
        */
        public void setPosition(int value){
            if(value>=0 && value<size())
                position = value;
        }

        /**
        *@return true or false according to it has or has not next element
        */
        public boolean hasNext(){
            if(position < size()-1)
                return true;
            else
                return false;
        }
        
        /**
        *@return true or false according to it has or has not previous element
        */
        public boolean hasPrevious(){
            if(position > 0)
                return true;
            else
                return false;
        }
        
        /**
        *@return next element of iterator if it has
        */
        public T next(){
            if(hasNext())
                return getData()[position++];

            else{
                position = size()-1;
                return getData()[position];
            }
        }

        /**
         *
         * @return previous element of iterator if it has
         */
        public T previous(){
            if(hasPrevious())	
                return getData()[position--];

            else
                return getData()[0];
        }	
    }
    
    
    /**
    *@return a string that includes the set to formatted
    */
    @Override
    public String toString(){
        String set="";
        for(int i=0 ; i<dataSize ;++i)
            set+=data[i]+" ";
        return set;
    }
    
    /**
    * Constructor
    *@param cls type of incoming class
    */
     public GTUSet(Class<T[]>cls){
        type = cls; 
        data = cls.cast(Array.newInstance(cls.getComponentType(),10));
        dataSize = 0;
        dataCapacity = 10;
    }

    /**
    * Constructor
    *@param cls type of incoming class
    *@param capacity capacity of set
    */
    public GTUSet(Class<T[]>cls, int capacity){
        data = cls.cast(Array.newInstance(cls.getComponentType(),capacity));
        type = cls;
        dataSize = 0;
        dataCapacity = capacity;
    }
    
    /**
     * @return current data of set
     */
    public T [] getData(){
        return data;
    }
    
    /**
     *@return type of class
     */
    public Class<T[]> getType(){
        return type;
    }
    
    /**
     * @return true or false according to the fullness of the set
     */
    @Override
    public boolean empty(){
        if(dataSize == 0)
            return true;
        return false;
    }   
    
    /**
     * @return current size  of set
     */
    @Override
    public int size(){
        return(dataSize);
    }

    /**
     * @return current capacity of set
     */
    @Override
    public int maxSize(){
        return(dataCapacity);
    }

    
    /**
    *@param element element to insert
    *@throws InvalidParameterException if element already exists in set
    *if set doesn't already include element, it inserts element to the set
    */
    @Override
    public void insert(T element){
        int equalityKey = 0;

        //checks whether element already exists in container
        {		
            for(int i = 0 ; i < dataSize ; ++i){
                if(data[i].equals(element)){
                    equalityKey = 1;
                    break;
                }
            }
        }

        if(equalityKey == 1){
            throw new InvalidParameterException("This element already exists!");
        }

        else{
            T [] tempData = data;
            
            if(dataSize == dataCapacity){   //kapasiteye ulaşıldıysa kapasiteyi büyüt
                @SuppressWarnings("unchecked")
                T [] toNewCapacity = (T[])new Object[dataCapacity*2];
                data = toNewCapacity;
                dataCapacity = toNewCapacity.length;
            }
            ++dataSize;
            
            for(int i=0; i<dataSize-1; ++i) //eski datayı kopyala
                data[i] = tempData[i];

            data[dataSize-1] = element;     //gelen elemanı ekle
        }
        sort();
    }
    /**
    *@param element element to erase
    *erases the element from set
    */
    @Override
    public void erase(T element){
        int newSize=0;
        T [] tempData = data;

        for(int i=0,j=0; i<dataSize ; ++i, ++j){
            if(data[i] != element){
                tempData[j] = data[i];
                ++newSize;
            }
            else
                --j;
        }
        
        dataSize = newSize;

        for(int i=0; i<dataSize; ++i)
            data[i] = tempData[i];
    }

    /**
     *clears the set
     */
    @Override
    public void clear(){
        dataSize = 0;
    }

    /**
    *@param element element to find
    *@return an iterator that includes position of element
    */
    @Override
    public GTUIterator find(T element){
        GTUIterator it = new GTUIterator ();
        for(int i=0; i<dataSize; ++i){
            if(data[i].equals(element))
                break;
            it.setPosition(it.getPosition()+1);
        }
        return it;
    }

    /**
    *@param element element to count
    *@return number of element
    */
    @Override
    public int count(T element){
        int counter=0;
        for(int i=0; i<dataSize; ++i){
            if(data[i].equals(element))
                ++counter;
        }
        return counter;
    }

    /**
     * @return an iterator that shows begin of set or map
     */
    @Override
    public GTUIterator begin(){
        GTUIterator  tmp = new GTUIterator ();
        return tmp;
    }

    /**
     * @return an iterator that shows end of set or map
     */
    @Override
    public GTUIterator end(){
        GTUIterator  tmp = new GTUIterator ();
        tmp.setPosition(dataSize);
        return tmp;
    }

    /**
     * sorts the set
     */
    @SuppressWarnings("unchecked")
    public void sort(){		//sorts the set
        int first;
        T temp;

        for (int i = dataSize-1; i>0; --i)
        {
            first = 0;                
            for (int j=1; j<=i; ++j){
                
                if (((Comparable)data[j]).compareTo((Comparable)data[first]) > 0)
                    first = j;
            }
            temp = data[first];  
            data[first] = data[i];
            data[i] = temp;
        }
    }
    
    /**
     * @param other incoming container object
     * @return a set is the intersection of this set and the incoming set.
     */
    @Override
    public GTUSetInt<T> intersection(GTUSetInt<T> other){
        
        @SuppressWarnings("unchecked")
        GTUSet<T> returnSet = new GTUSet<>(type,dataCapacity);
        
        if(other instanceof GTUSet){    
            GTUSet<T> castedOther = (GTUSet<T>)other;   //downcast
            
            for(int i=0 ; i<dataSize ; ++i){
                for(int j=0 ; j<castedOther.size() ; ++j){
                    if(data[i].equals(castedOther.data[j])){
                        returnSet.insert(data[i]);
                        break;
                    }        
                }
            }
        }
               
        return returnSet;
    }
}