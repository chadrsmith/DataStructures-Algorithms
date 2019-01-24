/***********************************************************************
 * Header:
 *    Deque
 * Summary:
 *    This is a header file for the Deque ADT. It is a
 *    double-ended queue that will add and remove items
 *    from the front and the back. It allows the client
 *    see the current front and back of the deque.
 *
 *
 *    This will contain the class definition of:
 *        Deque         : A class that acts as a double-ended queue
 *
 * Author
 *    Chad Smith
 ************************************************************************/

#ifndef DEQUE_H
#define DEQUE_H

#include <cassert>

/************************************************
 * DEQUE
 * A class that acts as a double-ended queue
 ***********************************************/
template <class T>
class Deque {
    
public:
    // default constructor
    Deque() : numItems(0), cap(0), data(NULL), frontItem(0), backItem(0) {}
    
    // copy constructor
    Deque(const Deque & rhs) throw (const char *);
    
    // non-default constructor
    Deque(int cap) throw (const char *);
    
    // destructor
    ~Deque()        { if (cap) delete [] data; }
    
    // assignment operator
    Deque<T> & operator = (const Deque &rhs)throw (const char *);
    
    // returns T/F based on if the Deque is empty
    bool empty() const  { return numItems == 0;         }
    
    // removes items from deque
    void clear()        { numItems = 0;                 }
    
    // returns the number of items in deque
    int size() const    { return numItems;              }
    
    // returns the capacity of the deque
    int capacity() const { return cap;           }
    
    // adds an item to the back of the deque
    void push_back(const T & t) throw (const char *);

    // adds an item to the front of the deque
    void push_front(const T & t);
    
    // removes an item from the back of the deque
    void pop_back() throw (const char *);
    
    // removes an item from the front of the deque
    void pop_front() throw (const char *);
    
    // returns the current front item of the deque
    T & front() throw (const char *);
    
    // returns the current back item of the deque
    T & back() throw (const char *);
    
private:
    T * data;          // dynamically allocated array of data T
    int numItems;      // how many items are currently in the Deque?
    int cap;           // how many items can I put on the Deque before full?
    int frontItem;     // the front item in the deque
    int backItem;      // the back item in the deque
    
};

/*******************************************
 * DEQUE :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Deque <T> :: Deque(const Deque<T> & rhs) throw (const char *) {
    
    assert(rhs.cap >= 0);
    
    // do nothing if there is nothing to do
    if (rhs.cap == 0) {
        cap = 0;
        numItems = 0;
        frontItem = 0;
        backItem = 0;
        data = NULL;
        
        return;
    }
    
    // attempt to allocate
    try {
        data = new T[rhs.cap];
    }
    catch (std::bad_alloc) {
        throw "ERROR: Unable to allocate a new buffer for deque";
    }
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0, f = rhs.frontItem; i < rhs.numItems; i++) {
        data[i] = rhs.data[f];
        f = (f + 1) % rhs.cap;
    }
    
    numItems = rhs.numItems;
    frontItem = 0;
    backItem = rhs.numItems;
    cap = rhs.cap;

    
}

/**********************************************
 * DEQUE : NON-DEFAULT CONSTRUCTOR
 * Preallocates the container to "capacity"
 **********************************************/
template <class T>
Deque <T> :: Deque(int cap) throw (const char *) {
    
    assert(cap >= 0);
    
    // do nothing if capacity is 0
    if (cap == 0) {
        this->cap = this->numItems = 0;
        this->frontItem = 0;
        this->backItem = 0;
        this->data = NULL;
        return;
    }
    
    // attempt to allocate
    try {
        data = new T[cap];
    }
    catch (std::bad_alloc) {
        throw "ERROR: Unable to allocate a new buffer for deque";
    }
    
    // copy over items
    this->cap = cap;
    this->numItems = 0;
    
    // initialize the deque by calling the default constructor
    for (int i = 0; i < cap; i++) {
        
        data[i] = T();
    }
}

/***************************************************
 * DEQUE :: ASSIGNMENT OPERATOR
 * assign the left hand Deque to the right hand side
 * Deque
 **************************************************/
template <class T>
Deque<T> & Deque<T> :: operator = (const Deque & rhs) throw (const char *) {
    assert(rhs.cap >= 0);
    
    // do nothing if there is nothing to do
    if (rhs.cap == 0) {
        cap = 0;
        numItems = 0;
        frontItem= 0;
        data = NULL;
        
        return * this;
    }
    
    // check to see if the buffer size is efficient
    if (cap < rhs.numItems) {
        // create a new array in order to hold the capacity of the rhs
        T * tempData = new T[rhs.cap];
        
        for (int i = 0, f = rhs.frontItem; i < rhs.numItems; i++) {
            
            tempData[i] = rhs.data[f];
            f = (f + 1) % rhs.cap;
        }
        delete [] data;
        data = tempData;
        cap = rhs.cap;
    }
    else {
        // the left hand side's buffer is efficient so we just copy items over
        for (int i = 0, f = rhs.frontItem; i < rhs.numItems; i++) {
            data[i] = rhs.data[f];
            f = (f + 1) % cap;
        }
    }
    
    numItems = rhs.numItems;
    backItem = rhs.numItems;
    frontItem = 0;
    
    return * this;
}

/***************************************************
 * DEQUE :: PUSH_BACK
 * Insert an item on the end of the deque
 **************************************************/
template <class T>
void Deque <T> :: push_back(const T & t) throw (const char *) {
    
    // is there space?
    if (cap == 0) {
        // init a new deque with the capacity of 1
        data = new T[1];
        cap = 1;
        frontItem = 0;
        backItem = 0;
    }
    if (cap == numItems) {
        // reallocate the deque
        T * tempData = new T[cap * 2];
        for (int i = 0, f = frontItem; i < numItems; i++) {
            // if necessary wrap using mod
            tempData[i] = data[f % cap];
            f = (f + 1) % cap;
        }
        delete [] data;
        data = tempData;
        cap = cap * 2;
        backItem = numItems;
        frontItem = 0;
    }
    
    // add an item to the end
    data[backItem] = t;
    backItem = (backItem + 1) % cap;
    numItems++;
    
}

/***************************************************
 * DEQUE :: PUSH_FRONT
 * Insert an item on the front of the deque
 **************************************************/
template <class T>
void Deque <T> :: push_front(const T & t) {
    
    // is there space?
    if (cap == 0) {
        // init a new deque with the capacity of 1
        data = new T[1];
        cap = 1;
        backItem = 0;
        frontItem = 0;
    }
    if (cap <= numItems) {
        // reallocate the deque
        T * tempData = new T[cap * 2];
        for (int i = 0, f = frontItem; i < numItems; i++) {
            // if necessary wrap using mod
            tempData[i] = data[f % cap];
            f = (f + 1) % cap;
        }
        delete [] data;
        data = tempData;
        cap = cap * 2;
        backItem = numItems;
    }
    
    // add an item to the front
    frontItem -= 1;
    if (frontItem < 0) {
        frontItem = cap - 1;
    }
    data[frontItem] = t;
    
    numItems++;
}

/***************************************************
 * DEQUE :: POP_BACK
 * Removes an item from the back of the deque
 **************************************************/
template <class T>
void Deque <T> :: pop_back() throw (const char *) {
    
    // check to see if the Deque has any items to pop
    if (numItems > 0) {
        backItem = backItem - 1;
        if ( backItem < 0) {
            backItem += cap;
        }
        numItems--;
    }
    else {
        throw "ERROR: unable to pop from the front of an empty deque";
    }
}

/***************************************************
 * DEQUE :: POP_FRONT
 * removes an item from the back of the deque
 **************************************************/
template <class T>
void Deque <T> :: pop_front() throw (const char *) {
    
    // check to see if the Deque has any items to pop
    if (numItems > 0) {
        
        // reallocating the front of the deque
        frontItem = (frontItem + 1) % cap;
        // reduces the number of items by one
        numItems--;
    }
    else {
        throw "ERROR: unable to pop from the front of an empty deque";
    }
}

/***************************************************
 * DEQUE :: FRONT
 * returns the current front item in the deque
 **************************************************/
template <class T>
T & Deque<T> :: front() throw (const char *) {
    
    // check to see if the Deque is empty
    if (cap == 0 || numItems == 0) {
        throw "ERROR: unable to access data from empty deque";
    }
    else {
        // returns the first item in the deque
        return data[frontItem];
    }
}

/***************************************************
 * DEQUE :: BACK
 * returns the current back item in the deque
 **************************************************/
template <class T>
T & Deque<T> :: back() throw (const char *) {
    
    // check to see if the Deque is empty
    if (cap == 0 || numItems == 0) {
        throw "ERROR: unable to access data from empty deque";
    }
    else {
        // returns the back item in the deque
        return data[(backItem - 1 + cap) % cap];
    }
}

#endif // CONTAINER_H
