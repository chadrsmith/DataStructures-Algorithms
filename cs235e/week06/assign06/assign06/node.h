/***********************************************************************
 * Header:
 *    Node
 * Summary:
 *    This class is the definition of a Node in a linked list. It
 *    contains a data variable and a Node<T> pointer to the next item
 *    in the linked list. This file also contains non-member functions
 *    for copying a linked list, freeing data, insertion, ostream, and
 *    finding an item in a linked list.
 *
 *    This will contain the class definition of:
 *        Node         : A class holding data & address of the next node
 *
 * Author
 *    Chad Smith
 ************************************************************************/

#ifndef NODE_H
#define NODE_H

#include <cassert>



/************************************************
 * NODE
 * A class that holds data and an address to the
 * next node.
 ***********************************************/
template <class T>
class Node
{
public:
    Node<T> *pNext;          // pointer variable, points to next item in linked list
    T data;                // data that is stored in the node
    
    // default constructor for NODE
    Node() : data(), pNext(NULL) {          }
    
    // non-default constructor for NODE
    Node(T data);
    
    // copy constructor for NODE
    Node(const Node & rhs) throw (const char *);
};

/************************************************
 * NON-DEFAULT CONSTRUCTOR
 *
 ***********************************************/
template <class T>
Node<T> :: Node(T data) {
    this->data = data;
    this->pNext = NULL;
}


/************************************************
 * EXTRACTION OPERATOR FUNCTION
 *
 ***********************************************/
template <class T>
std::ostream& operator << (std::ostream& out, const Node<T>* const &node)
{
    const Node<T>* pTemp = node;
    
    while (pTemp != NULL) {
        out << pTemp->data;
        if (pTemp->pNext != NULL) {
            out << ", ";
        }
        pTemp = pTemp->pNext;
    }
    
    return out;
}

/************************************************
 * NONMEMBER NODE :: INSERT
 *
 ***********************************************/
template <class T>
void insert (T data, Node<T>* & afterMe, bool headInsert = false) {
    
    // create new node
    Node<T> *pNew = new Node<T>(data);
    
    // place the new node in the linked list
    if (!afterMe || headInsert) {
        pNew->pNext = afterMe;
        afterMe = pNew;
    }
    else if (!headInsert) {
        pNew->pNext = afterMe->pNext;
        afterMe->pNext = pNew;
    }
}

/************************************************
 * NONMEMBER NODE :: FIND
 *
 ***********************************************/
template <class T>
Node<T>* find(Node<T> *pHead, const T & data) {
    // checks if list is empty
    if (pHead == NULL) {
        return NULL;
    }
    
    // if data is found
    if (data == pHead->data) {
        return pHead;
    }
    
    return find(pHead->pNext, data);
}

/************************************************
 * NONMEMBER NODE :: COPY
 *
 ***********************************************/
template <class T>
Node<T>* copy(Node<T>* pSource) {
    
    Node<T>* newNode = new Node<T>;
    Node<T>* newHead = newNode;
    Node<T>* currentNode = pSource;
    
    while (currentNode != NULL) {
        // assigns the copy linked list to the current node's data
        newNode->data = currentNode->data;
        
        if (currentNode->pNext == NULL) {
            newNode->pNext = NULL;
        }
        else {
            newNode->pNext = new Node<T>;
        }
        // iterates through the linked lists.
        newNode = newNode->pNext;
        currentNode = currentNode->pNext;
    }
    
    // returns the new head of the linked list
    return newHead;
}

/************************************************
 * NODE :: FREEDATA
 *
 ***********************************************/
template <class T>
void freeData(Node<T>* &pHead) {
    
    Node<T>* pTemp;
    while (pHead != NULL) {
        pTemp = pHead->pNext;
        delete pHead;
        pHead = pTemp;
    }
}

#endif // NODE_H
