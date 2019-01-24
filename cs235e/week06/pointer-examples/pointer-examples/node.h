/***********************************************************************
 * Header:
 *    Node
 * Summary:
 *
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
struct Node
{
public:
    Node<T> *pNext;          // pointer variable, points to next item in linked list
    T data;                // data that is stored in the node
    
    // default constructor for NODE
    Node() : data(), pNext(NULL) {}
    
    // non-default constructor for NODE
    Node(T data) throw (const char *);
    
    // copy constructor for NODE
    Node(const Node & rhs) throw (const char *);
    
    friend std::ostream& operator << (std::ostream& out, const Node<T>& node);
    
private:
    
    
};

/************************************************
 * NODE :: NON-DEFAULT CONSTRUCTOR
 *
 ***********************************************/
template <class T>
Node<T> :: Node (T data) throw (const char *) {
    
    this->data = data;
    this->pNext = NULL;
}

/************************************************
 * EXTRACTION OPERATOR FUNCTION
 *
 ***********************************************/
template <class T>
std::ostream & operator << (std::ostream & out, const Node<T> node) {
    Node<T>* currentNode = node.pNext;
    
    out << "I SHOULD GET PRINTED OUT NOW!!!! :)";
    
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
Node<T>* copy(Node<T>* pSource) throw (const char *) {
    
    Node<T>* currentNode = pSource;
    Node<T>* copyNode = new Node<T>(currentNode->data);
    
    currentNode = currentNode->pNext;
    
    // copy the rest of the nodes in the linked list
    while (currentNode != NULL) {
        insert(currentNode->data, copyNode);
        currentNode = currentNode->pNext;
    }
    
    
    return copyNode;
}

/************************************************
 * NODE :: FREEDATA
 *
 ***********************************************/
template <class T>
void freeData(Node<T> *pHead) {
    while (pHead != NULL) {
        Node<T>* pTemp = new Node<T>;
        pTemp = pHead;
        pHead = pHead->pNext;
        delete pTemp;
    }
}

#endif // NODE_H
