//
//  bnode.h
//  assign09
//
//  Created by Chad Smith on 11/12/18.
//  Copyright © 2018 Chad Smith. All rights reserved.
//

#ifndef BNODE_H
#define BNODE_H

#include <cassert>

template <class T>
class BinaryNode {
    
public:
    
    //Default Constructor for the BinaryNode Class
    BinaryNode(): pLeft(NULL), pRight(NULL), pParent(NULL) { }
    
    // Non-Default Constructor for the BinaryNode class
    BinaryNode(T data): pLeft(NULL), pRight(NULL), pParent(NULL) {  this->data = data; }
    
    // returns the amount of nodes in the tree
    int size() const {
        
        return 1 +
            (pLeft == NULL ? 0 : pLeft->size()) +
            (pRight == NULL ? 0 : pRight->size());
    }
    
    // add node to the left
    void addLeft (BinaryNode<T>* pNode);
    
    // add node to the right
    void addRight (BinaryNode<T>* pNode);
    
    // creates a NEW node and adds to the left of the node
    void addLeft (const T &t) throw (const char *);
    
    // creates a NEW node and adds to the right of the node
    void addRight (const T &t) throw (const char *);
    
    BinaryNode<T>* pLeft;
    BinaryNode<T>* pRight;
    BinaryNode<T>* pParent;
    T data;
    
};

/**********************************************************
 * BINARYNODE :: ADDLEFT
 * Adds T data to the left of the
 * node as it's child.
 *********************************************************/
template <class T>
void BinaryNode<T> :: addLeft (BinaryNode<T>* pNode) {
   
    pLeft = pNode;
    if (pNode != NULL) {
        pNode->pParent = this;      // set the pNode's parent to this
    }
    else {
        return;
    }
}

/**********************************************************
 * BINARYNODE :: ADDRIGHT
 * Adds T data to the right of the node as it's child
 *********************************************************/
template <class T>
void BinaryNode<T> :: addRight (BinaryNode<T>* pNode) {
    
    pRight = pNode;
    if (pNode != NULL) {
        
        pNode->pParent = this;
    }
    else {
        return;
    }
}


/**********************************************************
 * BINARYNODE :: ADDLEFT
 * CREATES NEW NODE and adds T data to the left of the
 * node as it's child
 *********************************************************/
template <class T>
void BinaryNode<T> :: addLeft (const T & t) throw (const char *) {
    
    BinaryNode<T>* insertedNode;
    try {
         insertedNode = new BinaryNode<T>;
    }
    catch(std::bad_alloc) {
        throw "ERROR: Unable to allocate a node";
    }
    
    pLeft = insertedNode;
    if (insertedNode != NULL) {
        
        insertedNode->pParent = this;
    }
    else {
        return;
    }
    insertedNode->data = t;
}

/**********************************************************
 * BINARYNODE :: ADDRIGHT
 * CREATES NEW NODE and adds T data to the right of the
 * node as it's child
 *********************************************************/
template <class T>
void BinaryNode<T> :: addRight (const T & t) throw (const char *) {
    
    BinaryNode<T>* insertedNode ;
    try {
        insertedNode = new BinaryNode<T>;
    }
    catch(std::bad_alloc) {
        throw "ERROR: Unable to allocate a node";
    }
    
    pRight = insertedNode;
    if (insertedNode != NULL) {
        
        insertedNode->pParent = this;
    }
    else {
        return;
    }
    insertedNode->data = t;
}

/**********************************************************
 * NONMEMBER FUNCTION :: OPERATOR <<
 * prints out the contents of the binary tree
 *********************************************************/
template <class T>
std::ostream & operator << (std::ostream & out, const BinaryNode<T> rhs) {
    
    if (rhs != NULL) {
        out << rhs->pLeft;
        out << rhs->data;
        out << " ";
        out << rhs->pRight;
    }
}

/**********************************************************
 * NONMEMBER FUNCTION :: DELETEBINARYTREE
 * deletes the elements of the binary tree
 * RECURSIVE ALGORITHM
 *********************************************************/
template <class T>
void deleteBinaryTree (BinaryNode<T>* bTreeNode) {
    
    if (bTreeNode != NULL) {
        
        deleteBinaryTree(bTreeNode->pLeft);
        deleteBinaryTree(bTreeNode->pRight);
        delete bTreeNode;
        bTreeNode = NULL;
    }
}


#endif // BNODE_H
