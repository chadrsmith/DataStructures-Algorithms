/***********************************************************************
 * Header:
 *    INSERTION SORT
 * Summary:
 *    This will contain just the prototype for insertionSortTest(). You may
 *    want to put other class definitions here as well.
 * Author
 *    Chad Smith
 ************************************************************************/

#ifndef INSERTION_SORT_H
#define INSERTION_SORT_H

#include "node.h"
#include <iostream>
#include <fstream>

using namespace std;

/***********************************************
 * INSERTION SORT
 * Sort the items in the array
 **********************************************/
template <class T>
void sortInsertion(T array[], int num) {
    
    // assign the first node to the first item in the array
    Node<T>* sortedNode = new Node<T>(array[0]);  
    
    // iterate through the array and sort the node
    for (int i = 1; i < num; i++) {
        
        Node<T>* currentNode = sortedNode;
        Node<T>* prevNode;
        
        while (currentNode != NULL) {
            // head insert
            if (array[i] < sortedNode->data) {
                
                insert(array[i], sortedNode, true);
                currentNode = NULL;
            }
            // insert in the middle of the linked list
            else if (array[i] < currentNode->data) {
                
                insert(array[i], prevNode);
                currentNode = NULL;
            }
            
            // place node at the end of the linked list
            else if (currentNode->pNext == NULL) {
                
                insert(array[i], currentNode);
                currentNode = NULL;
            }
            // just iterate
            else {
                
                prevNode = currentNode;
                currentNode = currentNode->pNext;
            }
        }
    }
    
    // placce the sorted linked list back into the array
    array[0] = sortedNode->data;
    for (int i = 1; i < num; i++) {
        
        array[i] = sortedNode->data;
        sortedNode = sortedNode->pNext;
    }
}

#endif // INSERTION_SORT_H

