/***********************************************************************
 * Module:
 *    Week 09, Sort Binary
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the Binary Tree Sort
 ************************************************************************/

#ifndef SORT_BINARY_H
#define SORT_BINARY_H

#include "bst.h"
#include "bnode.h"

/*****************************************************
 * SORT BINARY
 * Perform the binary tree sort
 ****************************************************/
template <class T>
void sortBinary(T array[], int num) {
    
    BST<T>* sortedBST = new BST<T>;
    for (int i = 0; i < num; i++)
    {
        T writeData = array[i];
        sortedBST->insert(writeData);
    }
    BSTIterator<T> it = sortedBST->begin();
    for (int i = 0; i < num; i++) {
        
        T writeData = *it;
        array[i] = writeData;
        it++;
    }

}


#endif // SORT_BINARY_H
