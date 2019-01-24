/***********************************************************************
 * Header:
 *    Set
 * Summary:
 *
 *
 *    This will contain the class definition of:
 *        Set        : A class that holds data
 *        SetIterator : An interator through Set
 * Author
 *    Chad Smith
 ************************************************************************/

#ifndef CONTAINER_H
#define CONTAINER_H

#include <cassert>

// forward declaration for SetIterator
template <class T>
class SetIterator;

/************************************************
 * SET
 * A class that holds stuff
 ***********************************************/
template <class T>
class Set
{
    
public:
    // default constructor : empty and kinda useless
    Set() : numItems(0), cap(0), data(NULL) {}
    
    // copy constructor : copy it
    Set(const Set & rhs) throw (const char *);
    
    // non-default constructor : pre-allocate
    Set(int capacity) throw (const char *);
    
    // destructor : free everything
    ~Set()        { if (cap) delete [] data; }
    
    // assignment operator
    Set<T>& operator = (const Set &rhs) throw (const char *);
    
    // intersection operator
    Set<T>& operator || (const Set &rhs) throw (const char *);
    
    // union operator
    Set<T>& operator && (const Set &rhs) throw (const char *);
    
    // is the container currently empty
    bool empty() const  { return numItems == 0;         }
    
    // returns the capacity of the Set
     int capacity() const    { return cap;          }
    
    // remove all the items from the container
    void clear()        { numItems = 0;                 }
    
    // removes an element from the set
    void erase(int arg);
    
    // how many items are currently in the container?
    int size() const    { return numItems;              }
    
    // add an item to the set
    void insert(const T & t) throw (const char *);
    
    // finds an item in the set
    int find(const T &t);
    
    // return an iterator to the beginning of the list
    SetIterator <T> begin() { return SetIterator<T>(data); }
    
    // return an iterator to the end of the list
    SetIterator <T> end() { return SetIterator<T>(data + numItems);}
    
private:
    T * data;          // dynamically allocated array of T
    int numItems;      // how many items are currently in the Container?
    int cap;           // how many items can I put on the Container before full?
};

/**************************************************
 * CONTAINER ITERATOR
 * An iterator through Container
 *************************************************/
template <class T>
class SetIterator
{
public:
    // default constructor
    SetIterator() : p(NULL) {}
    
    // initialize to direct p to some item
    SetIterator(T * p) : p(p) {}
    
    
    // not equals operator
    bool operator != (const SetIterator & rhs) const
    {
        return rhs.p != this->p;
    }
    
    // dereference operator
    T & operator * ()
    {
        return *p;
    }
    
    // prefix increment
    SetIterator <T> & operator ++ ()
    {
        p++;
        return *this;
    }
    
    // postfix increment
    SetIterator <T> operator++(int postfix)
    {
        SetIterator tmp(*this);
        p++;
        return tmp;
    }
    
private:
    T * p;
};

/*******************************************
 * SET:: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
{
    assert(rhs.cap >= 0);
    
    // do nothing if there is nothing to do
    if (rhs.cap == 0)
    {
        cap = 0;
        numItems = 0;
        data = NULL;
        return;
    }
    
    // attempt to allocate
    try
    {
        data = new T[rhs.cap];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for Set";
    }
    
    // copy over the capacity and size
    assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
    cap = rhs.cap;
    numItems = rhs.numItems;
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < numItems; i++)
        data[i] = rhs.data[i];
        
        // the rest needs to be filled with the default value for T
        for (int i = numItems; i < cap; i++)
            data[i] = T();
            }

/**********************************************
 * CONTAINER : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Set <T> :: Set(int capacity) throw (const char *)
{
    assert(capacity >= 0);
    
    // do nothing if there is nothing to do
    if (capacity == 0)
    {
        this->cap = this->numItems = 0;
        this->data = NULL;
        return;
    }
    
    // attempt to allocate
    try
    {
        data = new T[capacity];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate a new buffer for Set";
    }
    
    
    // copy over the stuff
    this->cap = capacity;
    this->numItems = 0;
    
    // initialize the container by calling the default constructor
    for (int i = 0; i < capacity; i++)
        data[i] = T();
        }

/***************************************************
 * SET :: ASSIGNMENT OPERATOR
 * Insert an item at the end of the set
 **************************************************/
template <class T>
Set<T> & Set<T> :: operator = (const Set &rhs) throw (const char *)
{
    if (cap == 0) {
        this->cap = 0;
        this->numItems = 0;
        this->data = NULL;
        
        return * this;
    }
    
    try {
        data = new T[rhs.cap];
    }
    catch (std::bad_alloc) {
        throw "ERROR: Unable to allocate a new buffer for Set.";
    }
    
    // copy over data in rhs' Set
    for (int i = 0; i < rhs.numItems; i++) {
        this->data[i] = rhs.data[i];
    }
    this->cap = rhs.cap;
    this->numItems = rhs.numItems;
    
    // return the newly assigned Set
    return * this;
}

/***************************************************
 * SET :: UNION OPERATOR
 * Returns the commonality of the two sets
 **************************************************/
template <class T>
Set<T> & Set<T> :: operator || (const Set &rhs) throw (const char *)
{
    // integers to iterate through the LHS and RHS
    int itLeft = 0;
    int itRight = 0;
    Set setReturn;
    
    while (itLeft < this->numItems || itRight < rhs.numItems) {
        if (itLeft == this->numItems) {
            setReturn.insert(rhs.data[itRight++]);
        }
        else if (itRight == rhs.numItems) {
            setReturn.insert(this->data[itLeft++]);
        }
        else if (this->data[itLeft] == rhs.data[itRight]) {
            setReturn.insert(this->data[itLeft]);
            itLeft++;
            itRight++;
        }
        else if (this->data[itLeft] < rhs.data[itRight]) {
            setReturn.insert(this->data[itLeft++]);
        }
        else {
            setReturn.insert(rhs.data[itRight++]);
        }
    }
    * this = setReturn;
    
    
    return * this;
}

/***************************************************
 * SET :: INSTERSECTION OPERATOR
 * Returns the difference of the two sets
 **************************************************/
template <class T>
Set<T> & Set<T> :: operator && (const Set &rhs) throw (const char *)
{
    // integers to iterate through the LHS and RHS
    int itLeft = 0;
    int itRight = 0;
    Set setReturn;
    
    while (itLeft < this->numItems || itRight < rhs.numItems) {
        if (itLeft == this->numItems) {
            * this = setReturn;
            return * this;
        }
        else if (itRight == rhs.numItems) {
            * this = setReturn;
            return * this;
        }
        else if (this->data[itLeft] == rhs.data[itRight]) {
            setReturn.insert(this->data[itLeft]);
            itLeft++;
            itRight++;
        }
        else if (this->data[itLeft] < rhs.data[itRight]) {
            itLeft++;
        }
        else {
            itRight++;
        }
    }
    
    * this = setReturn;
    return * this;
}

/***************************************************
 * SET :: INSERT
 * Insert an item in the order of the set
 **************************************************/
template <class T>
void Set <T> :: insert(const T & t) throw (const char *)
{
    // check to see if the Set contains anything
    if (cap == 0) {
        cap = 1;
        data = new T[1];
    }
    // if vector is full reallocate memory
    if (cap == numItems || cap <= numItems) {
        T * tempData = new T[cap * 2];
        for ( int i = 0; i < numItems; i++) {
            tempData[i] = data[i];
        }
        delete [] data;
        data = NULL;
        data = tempData;
        cap = cap * 2;
    }
    
    // check to see if the item passed already exists
    int foundIndex = find(t);
    // not found so just adding the item to the Set for now
    if (foundIndex < 0) {
        
        data[numItems++] = t;
        // order the set by ascending order
        for (int i = 0; i < numItems; i++) {
            
            // add an item to the beginning, shifts the rest of the array by one
            if (t < data[0] && i == 0) {
                T * tempData = new T[cap];
                tempData[0] = t;
                for (int x = 1; x < numItems; x++) {
                    tempData[x] = data[x - 1];
                }
                data = tempData;
            }
            
            // add item anywhere in the middle, only shifts the part of the set that needs to be shifted
            if (t > data[i] && t < data[i+ 1]) {
                int shiftStartPoint = i + 1;
                int tempSize = (numItems - 1) - (shiftStartPoint - 1);
                
                T * tData = new T[tempSize];
                for (int x = shiftStartPoint, p = 0; x < numItems - 1; x++, p++) {
                    tData[p] = data[x];
                }
                for (int x = shiftStartPoint + 1, p = 0; p < tempSize; p++, x++) {
                    data[x] = tData[p];
                }
                data[shiftStartPoint] = t;
            }
        }
    }
}

/***************************************************
 * SET :: FIND
 * Insert an item at the end of the set
 **************************************************/
template <class T>
int Set <T> :: find(const T &t) {
    
    int itBegin = 0;
    int itEnd = numItems - 1;
    
    while (itBegin <= itEnd) {
        
        int itMiddle = (itBegin + itEnd) / 2;
        if (t == data[itMiddle]) {
            return itMiddle;
        }
        if (t < data[itMiddle]) {
            itEnd = itMiddle - 1;
        }
        else {
            itBegin = itMiddle + 1;
        }
    }
    return - 1;
}

/***************************************************
 * SET :: ERASE
 * Erases data that is at the passed index
 **************************************************/
template <class T>
void Set<T> :: erase(int arg) {
    
    for (int i = arg; i < numItems; i++) {
        // shifts the array by one
        data[i] = data[i + 1];
    }
    numItems--;
}


#endif // CONTAINER_H
