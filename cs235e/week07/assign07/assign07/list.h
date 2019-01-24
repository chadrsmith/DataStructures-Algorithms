/***********************************************************************
 * Header:
 *    LIST
 * Summary:
 *
 *    This will contain the class definition of:
 *        Node             : A class holding data & address of the next node
 *        List             : A class holding a collection of Nodes
 *        ListIterator     : A class that iterates through the items in the list
 *
 * Author
 *    Chad Smith
 ************************************************************************/

#ifndef LIST_H
#define LIST_H
#include <cassert>

/************************************************
 * CLASS: NODE
 * A class that holds data and an address to the
 * next node.
***********************************************/
template <class T>
class Node {
    
public:
    // Default constructor for NODE
    Node() : pNext(NULL), pPrev(NULL)   { }
    
    // Non-Default constructor for NODE
    Node(T data);
    
    // member variables
    T data;
    Node<T>* pNext;
    Node<T>* pPrev;
};

/************************************************
 * NODE :: NON-DEFAULT CONSTRUCTOR
 * Takes in a data paramater and assigns the data
 * variable from the passed in data
 ***********************************************/
template <class T>
Node<T> :: Node (T data) {
    
    this->data = data;
    this->pNext = NULL;
    this->pPrev = NULL;
}

/************************************************
 * CLASS NODE :: COPY
 * Copies a node that is passed in
 ***********************************************/
template <class T>
Node<T>* copy (Node<T>* pSource) {
    
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
 * CLASS NODE :: INSERT
 * Insert a new Node into the current
 * list
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
 * NON-MEMBER FUNCTION NODE :: FREEDATA
 * Finds a Node in a list the return is a node
 ***********************************************/
template <class T>
Node<T>* find (Node<T>* pHead, T data) {
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
 * NON-MEMBER FUNCTION NODE :: FREEDATA
 * deletes the items in the list
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

/************************************************
 * CLASS: LISTITERATOR
 *
 * A class that iterates through the doubly
 * list.
 ***********************************************/
template <class T>
class ListIterator {
    
public:
    // Default constructor for ListIterator
    ListIterator() : node(NULL) {}
    
    // Copy constructor for the ListIterator
    ListIterator(Node<T>* rhs) : node(rhs) {}
    
    // returns the current node
    Node<T>* &returnPointer() { return node; }
    
    // comparison operator to see if the LHS does NOT equal LHS
    bool operator != (const ListIterator & rhs) const {
        return rhs.node != this->node;
    }
    
    // comparison operator to see if the LHS equals RHS
    bool operator == (const ListIterator & rhs) const {
        return rhs.node == this->node;
    }
    
    // operator to return the node data in the iterator
    T & operator * () {
        return node->data;
    }
    
    // prefix decrement operator for the iterator
    ListIterator<T> & operator ++ () {
        node = node->pNext;
        return *this;
    }
    
    // postfix increment operator for the iterator
    ListIterator<T> operator ++ (int postfix) {
        ListIterator current(*this);
        node = node->pNext;
        return current;
    }
    
    // prefix decrement operator for the iterator
    ListIterator<T> & operator -- () {
        node = node->pPrev;
        return *this;
    }
    
    // postfix decrement operator for the iterator
    ListIterator<T> operator -- (int postfix) {
        ListIterator current(*this);
        node = node->pPrev;
        return current;
    }
    
private:
    Node<T>* node;
};

/************************************************
 * CLASS: LIST
 *
 * A class that contains a series of nodes that
 * make up a doubly linked list
 ***********************************************/
template <class T>
class List {
    
public:
    // DEFAULT CONSTRUCTOR for the class LIST
    List(): head(NULL), tail(NULL), numItems(0) { }
    
    // Copy Constructor for the class List
    List(List<T> & rhs);
    
    // Destructor for the class List
    ~List();
    
    // ASSIGNMENT OPERATOR for class LIST
    List & operator = (List & rhs);
    
    // Returns True if List is empty
    bool empty()    { return (numItems == 0);   }
    
    // Returns the number of items in the List
    int size()      { return numItems;          }
    
    // Returns the data in the Node at the front of the list
    T & front()     { return head->data;        }
    
    // Returns the data in the Node at the back of the list
    T & back()      { return tail->data;        }
    
    // Clears the nodes in the list
    void clear();
    
    // Inserts item in the front of the list
    void push_back(T item);
    
    // Inserts item in the back of the list
    void push_front(T item);
    
    // Removes an item from the list
    void remove(ListIterator<T> it);
    
    // Uses the list iterator class to place item in the list
    ListIterator<T> insert(ListIterator<T> it, T item);
    
    // Returns the first node in the list
    ListIterator<T> begin();
    
    // Returns null beginning node
    ListIterator<T> rbegin();
    
    //Returns the last node in the list
    ListIterator<T> end();
    
    // Returns null last node
    ListIterator<T> rend();
    
private:
    Node<T>* head;
    Node<T>* tail;
    int numItems;
};

/************************************************
 * LIST :: COPY CONSTRUCTOR
 * Creates a new list and copies the content of
 * the RHS to this (LHS)
 ***********************************************/
template<class T>
List<T> :: List(List<T> & rhs) {
    
    // If there's nothing, set it all to NULL
    if (rhs.empty()) {
        this->numItems = 0;
        this->head = NULL;
        this->tail = NULL;
        return;
    }
    
    // Try to copy the tail of the list
    try {
        head = copy(rhs.head);
    }
    catch (std::bad_alloc) {
        std::cout << "ERROR: Allocating list";
    }
    
    // Copy over the number of items
    numItems = rhs.numItems;
    
    // Copy the tail
    Node<T>* p = head;
    while (p->pNext != NULL) {
        p = p->pNext;
    }
    
    tail = p;
}

/************************************************
 * LIST :: DESTRUCTOR ~LIST()
 * Destoys the list and frees memory
 ***********************************************/
template<class T>
List<T> :: ~List()
{
    freeData(head);
    head = NULL;
    tail = NULL;
    numItems = 0;
}

/************************************************
 * LIST :: ASSIGNMENT OPERATOR =
 * assigns the data from the RHS to this (LHS)
 ***********************************************/
template<class T>
List<T> & List<T> :: operator = (List &rhs) {
    
    // set the LHS to NULL, so it's ready
    freeData(head);
    this->numItems = 0;
    this->head = NULL;
    this->tail = NULL;
    
    // If there's nothing, just set to NULL
    if (rhs.empty()) {
        return *this;
    }
    
    // Try to copy the tail
    try {
        head = copy(rhs.head);
    }
    catch (std::bad_alloc) {
        std::cout << "ERROR: Allocating list";
    }
    
    // Copy over the number of items
    numItems = rhs.numItems;
    
    // Copy the tail
    Node<T>* p = head;
    while (p->pNext != NULL) {
        p = p->pNext;
    }
    tail = p;
    
    return *this;
}

/************************************************
 * LIST :: CLEAR
 * Clears the data in the list
 ***********************************************/
template <class T>
void List<T> :: clear() {
    
    freeData(head);
    numItems = 0;
    head = NULL;
    tail = NULL;
}

/************************************************
 * LIST :: PUSH_BACK
 * Adds a node to the bakc of the list
 ***********************************************/
template <class T>
void List<T> :: push_back(T item) {
    
    Node<T>* insert = new Node<T>(item);
    
    if (numItems == 0) {
        
        head = insert;
        tail = insert;
        numItems++;
        return;
    }
    
    insert->pPrev = tail;
    tail->pNext = insert;
    insert->pNext = NULL;
    tail = insert;
    numItems++;
}

/************************************************
 * LIST :: PUSH_FRONT
 * Pushes data to the front of the list.
 ***********************************************/
template <class T>
void List<T> :: push_front(T item) {
    
    Node<T>* insert = new Node<T>(item);
    
    if (numItems == 0) {
        head = insert;
        tail = insert;
        numItems++;
        return;
    }
    
    insert->pNext = head;
    head->pPrev = insert;
    head = insert;
    numItems++;
}

/************************************************
 * LIST :: INSERT
 * inserts an item into the list
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: insert(ListIterator<T> it, T item) {
    
    ListIterator<T> currentNode;
    currentNode.returnPointer() = new Node<T>(item);
    
    currentNode.returnPointer()->pNext = it.returnPointer();
    currentNode.returnPointer()->pPrev = it.returnPointer()->pPrev;
    
    it.returnPointer()->pPrev->pNext = currentNode.returnPointer();
    it.returnPointer()->pPrev = currentNode.returnPointer();
    
    numItems++;
    
    return currentNode;
}

/************************************************
 * LIST :: REMOVE
 * Removes an item from the list.
 ***********************************************/
template <class T>
void List<T> :: remove(ListIterator<T> it)
{
    it.returnPointer()->pPrev->pNext = it.returnPointer()->pNext;
    it.returnPointer()->pNext->pPrev = it.returnPointer()->pPrev;
    numItems--;
    delete it.returnPointer();
    it.returnPointer() = NULL;
}

/************************************************
 * LIST :: BERGIN
 * Returns the first node in the list
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: begin()
{
    ListIterator<T>* begin = new ListIterator<T>(head);
    return *begin;
}

/************************************************
 * LIST :: RBEGIN
 * Returns NULL from the tail
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: rbegin()
{
    ListIterator<T>* rbeg = new ListIterator<T>(tail);
    return *rbeg;
}

/************************************************
 * LIST :: REND
 * Returns Returns the end node of the list
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: end()
{
    ListIterator<T>* end = new ListIterator<T>(NULL);
    return *end;
}

/************************************************
 * LIST :: REND
 * Returns NULL from the beginning
 ***********************************************/
template <class T>
ListIterator<T> List<T> :: rend()
{
    ListIterator<T>* rend = new ListIterator<T>(NULL);
    return *rend;
}

#endif // LIST_H
