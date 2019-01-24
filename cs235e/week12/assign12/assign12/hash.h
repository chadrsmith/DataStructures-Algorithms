//
//  hash.h
//  assign12
//
//  Created by Chad Smith on 12/07/18.
//  Copyright © 2018 Chad Smith. All rights reserved.
//

#ifndef HASH_HASH_H
#define HASH_HASH_H

#include <list>
#include <iostream>
using namespace std;

template <class T>
class Hash {
    
public:
    
    // default constructor
    Hash();
    
    // non-default constructer
    Hash(int numBuckets) throw (const char *);
    
    // copy constructor
    Hash(Hash<T> const &t)  { *this = t; }
    
    // destructor
    ~Hash();
    
    // overloaded assignment operator
    Hash<T>& operator = (const Hash<T> &t);
    
    // returns t/f if the hash map is empty
    bool empty()    { return (size() == 0 ? true : false); }
    
    // returns sie of the hasmap
    int size() const {  return arraySize; }
    
    // returns the capacity of the hashmap
    int capacity() const    {   return this->numBucket; }
    
    // clears contents in the hashmap
    void clear();
    
    // finds value in the hashmap
    bool find(T data);
    
    // inserts data in the hashmap
    void insert(T data);
    
    virtual int hash(const T &element) const = 0;
    
    // get arrary list of the hash
    list<T>* getArrayList() const { return arrayList; }
    
private:
    
    int numBucket;
    list<T>* arrayList;
    int arraySize;
};

/*********************************************************
 * HASH :: DEFAULT CONSTRUCTOR
 * creates a defaulkt Hash data structure
 ********************************************************/
template <class T>
Hash<T> :: Hash() {
    
    try {
        
        this->numBucket = 10;
        this->arrayList = new list<T>[numBucket];
        this->arraySize = 0;
    }
    
    catch (bad_alloc) {
        throw "ERROR: Unable to allocate memory for the hash.";
    }
}

/*********************************************************
 * HASH :: NON-DEFAULT CONSTRUCTOR
 ********************************************************/
template <class T>
Hash<T> :: Hash(int numBuckets) throw (const char *) {
    
    try {
        
        this->numBucket = numBuckets;
        this->arrayList = new list<T> [numBucket];
        this->arraySize = 0;
    }
    
    catch (bad_alloc) {
        throw "ERROR: Unable to allocate memory for the hash.";
    }
}

/*********************************************************
 * HASH :: DESTRUCTOR
 * Destroys the Hash and frees the memory
 ********************************************************/
template <class T>
Hash<T> :: ~Hash() {
    
    delete[] arrayList;
    arraySize = 0;
    arrayList = NULL;
    
}

/*********************************************************
 * HASH :: ASSIGNMENT OPERATOR
 * Overloads the assignment operator for the hash class
 ********************************************************/
template<class T>
Hash<T> &Hash<T> :: operator = (const Hash<T> &t) {
    
    this->numBucket = t.capacity();
    this->arraySize = 0;
    this->arrayList = new list<T> [numBucket];
    
    // inserts a copy of the individual nodes in the new hash
    for (int i = 0; i < t.capacity(); i++) {
        
        for (typename list<T>::iterator it = t.arrayList[i].begin(); it != t.arrayList[i].end(); it++) {
            
            arrayList[i].push_back(*it);
            this->arraySize++;
        }
    }
    
    return *this;
}

/*********************************************************
 * HASH :: CLEAR
 * Clears nodes in each linked list in the array
 ********************************************************/
template<class T>
void Hash<T> :: clear() {
    
    for (int i = 0; i < numBucket; i++) {
        arrayList[i].clear();
    }
    
    this->arraySize = 0;
}

/*********************************************************
 * HASH :: INSERT
 * Inserts a value within the hash by first hashing it
 * afterwards, its inserted in the linked list
 *********************************************************/
template<class T>
void Hash<T> :: insert (T data) {
    
    int index = hash(data);
    
    arrayList[index].push_back(data);
    this->arraySize++;
}

/*********************************************************
 * HASH :: FIND
 * returns T/F depending on if the value is in the hashmap
 ********************************************************/
template<class T>
bool Hash<T> :: find (T data) {
    
    int index = hash(data);
    
    for (typename list<T>::iterator it = arrayList[index].begin(); it != arrayList[index].end(); it++) {
        
        if (*it == data)
            return true;
    }
    return false;
}

#endif //HASH_HASH_H
