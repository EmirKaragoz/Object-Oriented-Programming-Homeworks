package HW7;

import java.security.InvalidParameterException;

/**
 * Set Interface
 * @author Emirhan Karagözoğlu
 * @param <T> type of the container
 */
public interface GTUSetInt<T>{

    /**
     * @return true or false according to the fullness of the container
     */
    boolean empty();

    /**
     * @return current size  of container
     */
    int size();

    /**
     * @return current capacity of set
     */
    int maxSize();

    /**
    *@param element element to insert
    *@throws InvalidParameterException if element already exists in container
    *if conteinar doesn't already include element, it inserts element to the container
    */
    void insert(T element);

    /**
    *@param element element to erase
    *erases the element from container
    */
    void erase(T element);

    /**
     * clears the container
     */
    void clear();

    /**
    *@param element element to find
    *@return an iterator that includes position of element
    */
    GTUSet<T>.GTUIterator find(T element);
					
    /**
    *@param element element to count
    *@return number of element
    */
    int count(T element);					

    /**
     * @return an iterator that shows begin of container
     */
    GTUSet<T>.GTUIterator begin();

    /**
     *
     * @return an iterator that shows end of container
     */
    GTUSet<T>.GTUIterator end();

    /**
     * @param other incoming container object
     * @return a container is the intersection of this container and the incoming container.
     */
    GTUSetInt<T> intersection(GTUSetInt<T> other);
}