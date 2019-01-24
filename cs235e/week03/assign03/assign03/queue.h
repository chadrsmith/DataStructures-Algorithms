/***********************************************************************
 * Header:
 *    Queue
 * Summary:
 *    This class contains the notion of a container: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *        Container         : A class that holds stuff
 *        ContainerIterator : An interator through Container
 * Author
 *    Br. Helfrich
 ************************************************************************/

#ifndef QUEUE_H
#define QUEUE_H

#include <cassert>

/************************************************
 * QUEUE
 * A class that holds stuff
 ***********************************************/
template <class T>
class Queue
{
public:
    // default constructor : empty and kinda useless
    Queue() : numItems(0), cap(0), data(NULL) {}
    
    // copy constructor : copy it
    Queue(const Queue & rhs) throw (const char *);
    
    // non-default constructor : pre-allocate
    Queue(int capacity) throw (const char *);
    
    // destructor : free everything
    ~Queue()        { if (cap) delete [] data; }
    
    // is the container currently empty
    bool empty() const  { return numItems == 0;         }
    
    // remove all the items from the container
    void clear()        { numItems = 0;                 }
    
    // how many items are currently in the container?
    int size() const    { return numItems;              }
    
    // overloaded assignment operator for the Queue ADT
    Queue<T> & operator = (const Queue &rhs)throw (const char *);
    
    // returns the capacity of the Queue
    int capacity() const { return cap;                  }
    
    // add an item to the container
    void push(T item) throw (const char *);
    
    // remove an item from the Queue
    void pop() throw (const char *);
    
    // reallocate array
    void reallocate();
    
    // returns the front item of the Queue
    T & front() throw (const char *);
    
    // returns the back item of the Queue
    T & back() throw (const char *);
    
    
    
private:
    T * data;          // dynamically allocated array of T
    int numItems;      // how many items are currently in the Container?
    int cap;           // how many items can I put on the Container before full?
    int frontVar;         // holds the reference of the front item of the Queue
    int backVar;          // holds the reference of the back item of the Queue
    
};

/*******************************************
 * CONTAINER :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Queue <T> :: Queue(const Queue <T> & rhs) throw (const char *)
{
    assert(rhs.cap >= 0);
    
    // do nothing if there is nothing to do
    if (rhs.cap == 0)
    {
        cap = 0;
        numItems = 0;
        data = NULL;
        frontVar = 0;
        backVar = - 1;
        return;
    }
    
    // attempt to allocate
    try
    {
        data = new T[rhs.cap];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    
    // copy over the capacity and size
    assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
    cap = rhs.cap;
    numItems = rhs.numItems;
    frontVar = 0;
    backVar = numItems - 1;
    
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
Queue <T> :: Queue(int capacity) throw (const char *)
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
        throw "ERROR: Unable to allocate buffer";
    }
    
    
    // copy over the stuff
    this->cap = capacity;
    this->numItems = 0;
    this->frontVar = 0;
    this->backVar = numItems - 1;
    
    // initialize the container by calling the default constructor
    for (int i = 0; i < capacity; i++)
        data[i] = T();
        
}




/***************************************************
 * QUEUE :: PUSH
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Queue <T> :: push(T item) throw (const char *)
{
    // checks to see if the Queue has room
    if (numItems == 0 || cap == 0) {
        data = new T[1];
        cap = 1;
        backVar = numItems;
    }
    
    if (numItems > cap || cap == numItems) {
        
        T * tempData = new T[cap * 2];
        
        for (int i = 0; i < numItems; i++) {
            tempData[i] = data[i];
        }
        delete[] data;
        data = tempData;
        cap = cap * 2;
    }
    
    data[numItems++] = item;
    backVar = numItems;
}

/***************************************************
 * QUEUE :: POP
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Queue<T> :: pop() throw (const char *)
{
    // check to see if the Queue has anything in it
    if (numItems > 0)
    {
        frontVar = (frontVar + 1) % cap;
        numItems--;
        backVar = numItems;
    }
    
    else {
        throw "ERROR: attempting to pop from an empty queue";
    }
    
}

/***************************************************
 * QUEUE :: FRONT
 * Returns the front item in the queue
 **************************************************/
template <class T>
T & Queue<T> :: front() throw (const char *) {
    
    // check to see if the Queue is NULL
    if (numItems > 0) {
        return data[frontVar];
    }
    else {
        throw "ERROR: attempting to access an item in an empty queue";
    }
}

/***************************************************
 * QUEUE :: FRONT
 * Returns the front item in the queue
 **************************************************/
template <class T>
T & Queue<T> :: back() throw (const char *) {
    
    // check to see if the Queue is NULL
    if (numItems > 0) {
        return data[backVar - 1];
    }
    else {
        throw "ERROR: attempting to access an item in an empty queue";
    }
}

/***************************************************
 * QUEUE :: REALLOCATE
 * Returns the front item in the queue
 **************************************************/
template <class T>
void Queue<T> :: reallocate() {
    
    if (cap == 0) {
        cap = 1;
        data = new T[cap];
    }
    else {
        T * tempData = new T[cap * 2];
        int f = frontVar;
        
        for (int i = 0; i < numItems; i++, f = (f + 1) % cap) {
            tempData[i] = data[i];
        }
        
        delete[] data;
        data = tempData;
        delete [] tempData;
        
        frontVar = 0;
        backVar = numItems;
        
    }
}

/***************************************************
 * Vector :: OPERATOR =
 * Assigns lhs to what the data the rhs holds.
 **************************************************/
template <class T>
Queue<T> & Queue<T> :: operator = (const Queue &rhs)throw (const char *)
{
    assert(rhs.cap >= 0);
    
    // do nothing if there is nothing to do
    if (rhs.cap == 0)
    {
        cap = 0;
        numItems = 0;
        frontVar = 0;
        backVar = -1;
        delete [] data;
        return * this;
    }
    
    // attempt to allocate
    try
    {
        data = new T[rhs.cap];
    }
    catch (std::bad_alloc)
    {
        throw "ERROR: Unable to allocate buffer";
    }
    
    // copy over the capacity and size
    assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
    cap = rhs.cap;
    numItems = rhs.numItems;
    frontVar = rhs.frontVar;
    backVar = rhs.backVar;
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < numItems; i++)
        data[i] = rhs.data[i];
        
        // the rest needs to be filled with the default value for T
        for (int i = numItems; i < cap; i++)
            data[i] = T();
            return * this;
}

#endif // QUEUE_H
