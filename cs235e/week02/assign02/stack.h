/***********************************************************************
 * Header:
 *    Stack
 * Summary:
 *    This class contains the notion of a Stack: a bucket to hold
 *    data for the user. This is just a starting-point for more advanced
 *    constainers such as the vector, set, stack, queue, deque, and map
 *    which we will build later this semester.
 *
 *    This will contain the class definition of:
 *        Stack        : A class that holds stuff
 *
 * Author
 *    Chad Smith
 ************************************************************************/

#ifndef STACK_H
#define STACK_H

#include <cassert>

/************************************************
 * STACK
 * A class that holds stuff
 ***********************************************/
template <class T>
class Stack
{
public:
    // default constructor : empty and kinda useless
    Stack() : numItems(0), cap(0), data(NULL) {}
    
    // copy constructor : copy it
    Stack(const Stack & rhs) throw (const char *);
    
    // non-default constructor : pre-allocate
    Stack(int capacity) throw (const char *);
    
    // destructor : free everything
    ~Stack()        { if (cap) delete [] data; }
    
    // assignment operator: assigns elemets in a stack to data
    Stack<T> & operator = (const Stack &rhs) throw (const char *);
    
    // is the container currently empty
    bool empty() const  { return numItems == 0;         }
    
    // remove all the items from the container
    void clear()        { numItems = 0;                 }
    
    // how many items are currently in the container?
    int size() const    { return numItems;              }
    
    // the current capacity of the Stack
    int capacity() const    { return cap;               }
    
    // add an item to the container
    void push(const T & t) throw (const char *);
    
    // remove an item from the Stack
    void pop() throw (const char *);
    
    // returns the top item from the Stack
    const T & top() throw (const char *);
    
private:
    T * data;          // dynamically allocated array of T
    int numItems;      // how many items are currently in the Container?
    int cap;           // how many items can I put on the Container before full?
};



/*******************************************
 * STACK :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Stack <T> :: Stack(const Stack <T> & rhs) throw (const char *)
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
        throw "ERROR: Unable to allocate buffer";
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
 * STACK : NON-DEFAULT CONSTRUCTOR
 * Preallocate the container to "capacity"
 **********************************************/
template <class T>
Stack <T> :: Stack(int capacity) throw (const char *)
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
    
    // initialize the container by calling the default constructor
    for (int i = 0; i < capacity; i++)
        data[i] = T();
        }

/***************************************************
 * STACK :: OPERATOR =
 * Insert an item on the end of the container
 **************************************************/
template <class T>
Stack<T> & Stack<T> :: operator = (const Stack &rhs)throw (const char *)
{
    assert(rhs.cap >= 0);
    
    // do nothing if there is nothing to do
    if (rhs.cap == 0)
    {
        cap = 0;
        numItems = 0;
        delete [] data;
        data = NULL;
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
    
    // copy the items over one at a time using the assignment operator
    for (int i = 0; i < numItems; i++)
        data[i] = rhs.data[i];
        
        // the rest needs to be filled with the default value for T
        for (int i = numItems; i < cap; i++)
            data[i] = T();
            return * this;
}

/***************************************************
 * STACK :: PUSH
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Stack<T> :: push(const T & t) throw (const char *)
{
    // check if the vector is empty.
    if (cap == 0 && numItems == 0) {
        cap = 1;
        data = new T[1];
    }
    // if vector is full reallocate memory
    else if (cap == numItems || cap <= numItems) {
        T * tempData = new T[cap * 2];
        for ( int i = 0; i < numItems; i++) {
            tempData[i] = data[i];
        }
        
        delete [] data;
        data = tempData;
        cap *= 2;
    }
    
    // add item to the end of the vector.
    data[numItems++] = t;
}

/***************************************************
 * STACK :: POP
 * Insert an item on the end of the container
 **************************************************/
template <class T>
void Stack <T> :: pop() throw (const char *)
{
    if (numItems == 0)
        throw "ERROR: Unable to pop from an empty Stack";
    
    numItems--;
}

/***************************************************
 * STACK :: TOP
 * Insert an item on the end of the container
 **************************************************/
template <class T>
const T & Stack<T> :: top() throw (const char *)
{
     if (numItems <= 0)
     {
         throw "ERROR: Unable to reference the element from an empty Stack";
     }
    
    return data[numItems - 1];
}



#endif // STACK_H
