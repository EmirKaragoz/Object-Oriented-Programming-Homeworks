package HW7;

import java.security.InvalidParameterException;
import java.lang.reflect.Array;
import javafx.util.Pair;

/**
 * Map Class Derived from Set Class
 * @author Emirhan Karagözoğlu 
 * @param <K> type of key of pair
 * @param <V> type of value of pair
 */

public class GTUMap<K,V> extends GTUSet<Pair<K,V>> {
    /**
    *@return a string that includes the set to formatted
    */
    @Override
    public String toString(){
        String map="";
        for(int i=0 ; i<dataSize ;++i)
            map+=data[i].getKey()+"-"+data[i].getValue()+"  ";
        return map;
    }
    
    /**
    * Constructor
    *@param cls type of incoming class
    */
    public GTUMap(Class<Pair<K,V>[]>cls){
        super(cls);
    }
    
    /**
    * Constructor
    *@param cls type of incoming class
    *@param capacity capacity of set
    */
     public GTUMap(Class<Pair<K,V>[]>cls, int capacity){
        super(cls,capacity);
    }
    
    @Override
     /**
    *@param element element to insert
    *@throw InvalidParameterException if element already exists in map
    *if map doesn't already include element, it inserts element to the map
    */
    public void insert(Pair<K,V> element){
        int equalityKey = 0;

        //checks whether element already exists in container
        {       
            for(int i = 0 ; i < super.size() ; ++i){
                if(data[i].getKey().equals(element.getKey())){
                    equalityKey = 1;
                    break;
                }
            }
        }
        
        if(equalityKey == 1){
            throw new InvalidParameterException("This element already exists!");
        }
        
        else{ 
            Pair<K,V> [] tempData = data;
            
            if(dataSize == dataCapacity){   //kapasiteye ulaşıldıysa kapasiteyi büyüt
                @SuppressWarnings("unchecked")
                GTUMap<K,V> toNewCapacity = new GTUMap<>(type,dataCapacity*2);
                data = toNewCapacity.getData();
                dataCapacity = toNewCapacity.maxSize();
            }
            ++dataSize;
            
            for(int i=0; i<dataSize-1; ++i)  //eski datayı kopyala
                data[i] = tempData[i];

            data[dataSize-1] = element;     //gelen elemanı ekle
        }
        sort();
        
    }
    
    @Override
     /**
    *@param element element to erase
    *erases the element from map
    */
    public void erase(Pair<K,V> element){
        int newSize=0;
        Pair<K,V> [] tempData = data;

        for(int i=0,j=0; i<dataSize ; ++i, ++j){
            if(data[i].getKey() != element.getKey()){
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
    
    @Override
    /**
    *@param element element to find
    *@return an iterator that includes position of element
    */
    public GTUIterator find(Pair<K,V> element){
        GTUIterator it = new GTUIterator ();
        for(int i=0; i<dataSize; ++i){
            if(data[i].getKey().equals(element.getKey()))
                break;
            it.setPosition(it.getPosition()+1);
        }
        return it;
    }
    
    /**
     * sorts the set
     */
    @Override
    @SuppressWarnings("unchecked")
    public void sort(){		//sorts the container
        int first;
        Pair<K,V> temp;

        for (int i = dataSize-1; i>0; --i)
        {
            first = 0;                
            for (int j=1; j<=i; ++j){
                if (((Comparable)data[j].getKey()).compareTo((Comparable)data[first].getKey()) > 0)
                    first = j;
            }
            temp = data[first];  
            data[first] = data[i];
            data[i] = temp;
        }
    }
    
    /**
     * 
     * @param k a value of key
     * @return the value that has k key
     */
    public V at(K k){
        int result=super.size()-1;
        for(int i=0; i<super.size() ; ++i){
            if(data[i].getKey().equals(k)){
                result = i;
            }
        }
        return(data[result].getValue());
    }
    
    /**
     *
     * @param other incoming container object
     * @return a map is the intersection of this map and the incoming map.
     */
    @Override
    public GTUSetInt<Pair<K,V>> intersection(GTUSetInt<Pair<K,V>> other){
        @SuppressWarnings("unchecked")
        GTUMap<K,V> returnMap = new GTUMap<>(type,dataCapacity);
        
        if(other instanceof GTUMap){
            GTUMap<K,V> castedOther = (GTUMap<K,V>)other;   //downcast
            
            for(int i=0 ; i<dataSize ; ++i){
                for(int j=0 ; j<castedOther.size() ; ++j){
                    if(data[i].equals(castedOther.data[j])){
                        returnMap.insert(data[i]);
                        break;
                    }        
                }
            }
        }
               
        return returnMap;
    }
}