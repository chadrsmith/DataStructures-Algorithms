#ifndef BNODE_H
#define BNODE_H

#include <iostream> 
#include <cassert>

/*****************************************************************
 * BINARY NODE
 * A single node in a binary tree.  Note that the node does not know
 * anything about the properties of the tree so no validation can be done.
 *****************************************************************/
template <class T>
class BinaryNode {
    
public:
    // Default Constructor
    BinaryNode(): pLeft(NULL), pRight(NULL), pParent(NULL)  {}
    
    // Non-Default Constructor
    BinaryNode(T data): pLeft(NULL), pRight(NULL), pParent(NULL) {  this->data = data;  }
    
   // return size (i.e. number of nodes in tree)
   int size() const {
       return 1 + (pLeft== NULL? 0 : pLeft->size()) + (pRight == NULL ? 0 : pRight->size());
   }
   
   // add a node to the left/right
   void addLeft (BinaryNode <T> * pNode);
   void addRight(BinaryNode <T> * pNode);

   // create a node and add it to the left/right
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   // since no validation is done, everything is public
   BinaryNode <T> * pLeft;
   BinaryNode <T> * pRight;
   BinaryNode <T> * pParent;
   T data;
};

/*****************************************************************
 * BINARY NODE :: ADDLEFT
 * adds a node as a child to the left of the parent node
 *****************************************************************/
template <class T>
void BinaryNode<T> :: addLeft(BinaryNode<T> *pNode) {
    
    if (pNode == NULL ) {
        this->pLeft = NULL;
    }
    else {
        pNode->pParent = this;
        this->pLeft = pNode;
    }
}

/*****************************************************************
 * BINARY NODE :: ADDRIGHT
 * adds a node as a child to the right of the parent node
 *****************************************************************/
template <class T>
void BinaryNode<T> :: addRight(BinaryNode<T> *pNode) {
    
    if (pNode == NULL ) {
        this->pRight = NULL;
    }
    else {
        pNode->pParent = this;
        this->pRight = pNode;
    }
}
/*****************************************************************
 * BINARY NODE :: ADDLEFT
 * create a node and add it to the left
 *****************************************************************/
template <class T>
void BinaryNode<T> :: addLeft(const T & t) throw (const char *) {
    
    try {
        
        BinaryNode<T>* tempNode = new BinaryNode<T>(t);
        tempNode->pParent = this;
        this->pLeft = tempNode;
    }
    catch (std::bad_alloc) {
        
        throw "ERROR: Unable to allocate a node";
    }
}

/*****************************************************************
 * BINARY NODE :: ADDRIGHT
 * create a node and add it to the right
 *****************************************************************/
template <class T>
void BinaryNode<T> :: addRight (const T & t) throw (const char *) {
    
    try {
        
        BinaryNode<T>* tempNode = new BinaryNode<T>(t);
        tempNode->pParent = this;
        this->pRight = tempNode;
    }
    catch (std::bad_alloc) {
        
        throw "ERROR: Unable to allocate a node";
    }
}

/*****************************************************************
 * BINARY NODE :: DELETEBINARYTREE
 * deletes the nodes in the binary tree
 *****************************************************************/
template <class T>
void deleteBinaryTree (BinaryNode<T>* nodePassedIn) {
    
    if (nodePassedIn == NULL) {
        return;
    }
    else {
        deleteBinaryTree(nodePassedIn->pLeft);
        deleteBinaryTree(nodePassedIn->pRight);
        delete nodePassedIn;
        nodePassedIn = NULL;
    }
}

/*****************************************************************
 * NON-NEMBER FUNCTION OPERATOR :: <<
 * prints out the contents of the binary tree
 *****************************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, const BinaryNode<T>* printNode) {
    
    if (printNode != NULL) {
        
        out << printNode->pLeft;
        out << printNode->data;
        out << " ";
        out << printNode->pRight;
    }
    return out;
}

#endif // BNODE_H
