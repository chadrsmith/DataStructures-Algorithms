/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Br. Helfrich
 *    Modified by Scott Ercanbrack - removed most of the the BST class functions,
 *                                   but left BST Iterator class.
 * Summary:
 *    Create a binary search tree
 ************************************************************************/

#ifndef BST_H
#define BST_H

#include "bnode.h"    // for BinaryNode
#include "stack.h"    // for Stack


// forward declaration for the BST iterator
template <class T>
class BSTIterator; 

/*****************************************************************
 * BINARY SEARCH TREE
 * Create a Binary Search Tree
 *****************************************************************/
template <class T>
class BST
{
public:
   // Constructor
   BST(): root(NULL){};
   
   // Copy constructor
   BST(const BST & rhs);    
   
    // Destructor
   ~BST();

    // Returns the size of the BST
   int size() const  {
       return empty() ? 0 : root->size();
   }
   
   
   // returns true if the root contains data
    bool empty() const { return(root == NULL) ? true : false; }

   // remove all the nodes from the tree.  Makes an empty tree.
    void clear() {
        recursiveClear(root);
        root = NULL;
    }
    
    void recursiveClear (BinaryNode<T>* clearNode);

   // overloaded assignment operator
   BST & operator = (const BST & rhs) throw (const char *) {
       
       copyBinaryNodes(rhs.root, this->root);
       return * this;
   }
      
   // Insert an item into the BST
   void insert(const T & t) throw (const char * );

   // Removes an item into the BST
   void remove(BSTIterator <T> & it);

   // Find the passed item in BST
   BSTIterator <T> find(const T & t);

   // Iterations to help with searches in the BST
   BSTIterator <T> begin() const;
   BSTIterator <T> end() const  { return BSTIterator <T> (NULL) ; }
   BSTIterator <T> rbegin() const;
   BSTIterator <T> rend() const  { return BSTIterator <T> (NULL); }
   
private:

   BinaryNode <T> * root;
};

/*********************************************************
* copy constructor
**********************************************************/
template <class T>
BST<T> :: BST (const BST &rhs) {
   
    copyBinaryNodes (rhs.root, this->root);
}

/*****************************************************
* Destructor
*******************************************************/
template <class T>
BST<T>::~BST() {
    recursiveClear(root);
}


/*****************************************************
 * BST :: BEGIN
 * Return the first node (left-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: begin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pLeft)
      nodes.push(nodes.top()->pLeft);

   return BSTIterator<T>(nodes);   
}

/*****************************************************
 * BST :: RBEGIN
 * Return the last node (right-most) in a binary search tree
 ****************************************************/
template <class T>
BSTIterator<T> BST <T> :: rbegin() const
{
   Stack < BinaryNode <T> * > nodes;

   nodes.push(NULL);
   nodes.push(root);
   while (nodes.top() != NULL && nodes.top()->pRight)
      nodes.push(nodes.top()->pRight);

   return BSTIterator<T>(nodes);
}  

/*****************************************************
 * BST :: INSERT
 * Insert a node at a given location in the tree
 ****************************************************/
template <class T>
void BST<T> :: insert (const T & t) throw (const char *) {
    
    BinaryNode<T>* insertNode;
    try {
        insertNode = new BinaryNode<T>;
    }
    catch (std::bad_alloc) {
        throw "ERROR: unable to allocate new memory.";
    }
    insertNode->data = t;
    
    
    BinaryNode<T>* currentNode = root;
    
    if (currentNode == NULL) {
        // std::cout<< "inserting the root node to " << t << " ." << std::endl;
        root = insertNode;
        return;
    }
    
    while (true) {
        // std::cout<< "inserting the pLeft node to " << t << " ." << std::endl;
        
        if (t <= currentNode->data) {
            
            if (currentNode->pLeft != NULL)
                currentNode = currentNode->pLeft;
                
            else {
                
                currentNode->pLeft = insertNode;
                insertNode->pParent = currentNode;
                break;
            }
        }
        
        else if (t > currentNode->data) {
            
            if (currentNode->pRight != NULL)
                currentNode = currentNode->pRight;
                
            else {
                
                currentNode->pRight = insertNode;
                insertNode->pParent = currentNode;
                break;
            }
        }
        else
            break;
    }
}

/*************************************************
 * BST :: REMOVE
 * Remove a given node as specified by the iterator
 ************************************************/
template <class T>
void BST <T> :: remove(BSTIterator <T> & it) {
    
    BinaryNode<T>* deleteNode = it.getNode();
    
    // case if Node has two children
    if (deleteNode->pLeft != NULL && deleteNode->pRight != NULL) {
        
        BinaryNode<T>* successor = deleteNode->pRight;
        while (successor->pLeft != NULL) {
            successor = successor->pLeft;
        }
        deleteNode->data = successor->data;
        
        deleteNode = successor;
    }
    
    // case if there is no Children or one child
    BinaryNode<T> * subtree = deleteNode->pLeft;
    
    if (subtree == NULL)
        subtree = deleteNode->pRight;
    if (deleteNode->pParent == NULL)
        root = subtree;
    else if (deleteNode->pParent->pLeft == deleteNode)
        deleteNode->pParent->pLeft = subtree;
    else
        deleteNode->pParent->pRight = subtree;
    
    delete deleteNode;
    deleteNode = NULL;
}

template <class T>
void BST<T> :: recursiveClear(BinaryNode<T> *clearNode) {
    if (clearNode != NULL) {
        
        recursiveClear(clearNode->pLeft);
        recursiveClear(clearNode->pRight);
        delete clearNode;
    }
    
}

/****************************************************
 * BST :: FIND
 * Returns the node corresponding to a given value
 ****************************************************/
template <class T>
BSTIterator <T> BST <T> :: find (const T & t)
{
    BinaryNode<T>* currentNode = root;
    BinaryNode<T>* nodeLocation = NULL;
    
    
    if (currentNode == NULL) {
        BSTIterator<T> it = end();
        return it;
    }
    
    while (currentNode != NULL) {
        
        if (t <= currentNode->data) {
            if (currentNode->data == t) {
                
                nodeLocation = currentNode;
                BSTIterator<T> it(nodeLocation);
                return it;
            }
            
            currentNode = currentNode->pLeft;
        }
        
        else if (t > currentNode->data) {
            currentNode = currentNode->pRight;
        }
        else
            break;
    }
    
    BSTIterator<T> it;
    return it;
    
}


/**********************************************************
 * BINARY SEARCH TREE ITERATOR
 * Forward and reverse iterator through a BST
 *********************************************************/
template <class T>
class BSTIterator
{
public:
   // constructors
   BSTIterator(BinaryNode <T> * p = NULL)    { nodes.push(p);  }
   BSTIterator(Stack <BinaryNode <T> *> & s) { nodes = s;         }
   BSTIterator(const BSTIterator <T> & rhs)  { nodes = rhs.nodes; }

   // assignment
   BSTIterator <T> & operator = (const BSTIterator <T> & rhs)
   {
      // need an assignment operator for the Stack class.
      nodes = rhs.nodes;
      return *this;
   }

   // compare
   bool operator == (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() == nodes.const_top();
   }
   bool operator != (const BSTIterator <T> & rhs) const
   {
      // only need to compare the leaf node 
      return rhs.nodes.const_top() != nodes.const_top();
   }

   // de-reference. Cannot change because it will invalidate the BST
   T & operator * ()  
   {
      return nodes.top()->data;
   }

   // iterators
   BSTIterator <T> & operator ++ ();
   BSTIterator <T>   operator ++ (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      ++(*this);
      return itReturn;
   }
   BSTIterator <T> & operator -- ();
   BSTIterator <T>   operator -- (int postfix)
   {
      BSTIterator <T> itReturn = *this;
      --(*this);
      return itReturn;
   }

    // must give friend status to remove so it can call getNode() from it
    friend void BST <T> :: remove(BSTIterator <T> & it);

private:
   
   // get the node pointer
   BinaryNode <T> * getNode() { return nodes.top(); }
   
   // the stack of nodes
   Stack < BinaryNode <T> * > nodes;
};


/**************************************************
 * BST ITERATOR :: INCREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator ++ ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;
   
   // if there is a right node, take it
   if (nodes.top()->pRight != NULL)
   {
      nodes.push(nodes.top()->pRight);

      // there might be more left-most children
      while (nodes.top()->pLeft)
         nodes.push(nodes.top()->pLeft);
      return *this;
   }

   // there are no right children, the left are done
   assert(nodes.top()->pRight == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the left-child, got to the parent.
   if (pSave == nodes.top()->pLeft)
      return *this;

   // we are the right-child, go up as long as we are the right child!
   while (nodes.top() != NULL && pSave == nodes.top()->pRight)
   {
      pSave = nodes.top();
      nodes.pop();
   }
      
   return *this;      
}

/**************************************************
 * BST ITERATOR :: DECREMENT PREFIX
 * advance by one
 *************************************************/
template <class T>
BSTIterator <T> & BSTIterator <T> :: operator -- ()
{
   // do nothing if we have nothing
   if (nodes.top() == NULL)
      return *this;

   // if there is a left node, take it
   if (nodes.top()->pLeft != NULL)
   {
      nodes.push(nodes.top()->pLeft);

      // there might be more right-most children
      while (nodes.top()->pRight)
         nodes.push(nodes.top()->pRight);
      return *this;
   }

   // there are no left children, the right are done
   assert(nodes.top()->pLeft == NULL);
   BinaryNode <T> * pSave = nodes.top();
   nodes.pop();

   // if the parent is the NULL, we are done!
   if (NULL == nodes.top())
      return *this;

   // if we are the right-child, got to the parent.
   if (pSave == nodes.top()->pRight)
      return *this;

   // we are the left-child, go up as long as we are the left child!
   while (nodes.top() != NULL && pSave == nodes.top()->pLeft)
   {
      pSave = nodes.top();
      nodes.pop();
   }

   return *this;
}


/**************************************************
 * NONMEMBER FUNCTION :: COPYBINARYNODES
 * makes a copy of the binary nodes in the BST
 *************************************************/
template <class T>
void copyBinaryNodes (const BinaryNode<T>* rootNode, BinaryNode<T>* &copyOfNodes) throw (const char *) {
    
    try {
        
        if (rootNode != NULL) {                                     // we have data in the rootNode, lets copy it!
            
            BinaryNode<T>* currentNode = new BinaryNode<T>(rootNode->data);
            copyOfNodes = currentNode;                              // set the root node to the currentNode
            
            copyBinaryNodes (rootNode->pLeft, copyOfNodes->pLeft);      // recursively copy the left children nodes
            if (rootNode->pLeft != NULL)
                copyOfNodes->pLeft->pParent = copyOfNodes;
            
            copyBinaryNodes (rootNode->pRight, copyOfNodes->pRight);    // recursively copy the left children nodes
            if (rootNode->pRight != NULL)
                copyOfNodes->pRight->pParent = copyOfNodes;
        }
        
        else {
            
            copyOfNodes = NULL;     // rootNode is null so set the copyOfNodes to NULL
        }
    }
    catch (std::bad_alloc) {        // unable to allocate memory, so throw an error
        
        throw "ERROR: Cannot allocate new memory in copy";
    }
}

#endif // BST_H
