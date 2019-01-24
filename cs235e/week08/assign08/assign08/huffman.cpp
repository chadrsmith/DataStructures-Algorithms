/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Chad Smith
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#include "huffman.h"       // for HUFFMAN() prototype
#include "bnode.h"         // for the BST data structure
#include "pair.h"          // for the BST data structure
#include <iostream>        // for extravtion/insertion operator
#include <fstream>         // for reading the huffman.txt files
#include <list>            // for the data pairing that's being saved

using namespace std;


// prototype the functions that are used in the "Driver Program"
void executeHuffman(BinaryNode<Pair<string, float> >* bnode, string code, list<Pair<string, string> > &table);
void sortTheList(list<BinaryNode<Pair<string, float> >*> &listOfNodes, BinaryNode<Pair<string, float> >* bnode);

/*******************************************
 * HUFFMAN
 * Driver program to exercise the huffman generation code
 *******************************************/
void huffman(string fileName) {
    
    list<BinaryNode<Pair<string, float> >*> listOfNodes;
    Pair<string, float> dataPair;
    BinaryNode<Pair<string, float> >* bNode = new BinaryNode<Pair<string, float> >();
    
    
    // reading from a file, error if file won't open
    ifstream fin;
    fin.open(fileName);
    if (!fin) {
        cerr << "ERROR: Unable to open data file.";
        return;
    }
    
    while (fin >> dataPair) {
        
        BinaryNode<Pair<string, float> >* newNode = new BinaryNode<Pair<string, float> >(dataPair);
        sortTheList(listOfNodes, newNode);
    }
    fin.close();
    
    
    // making new nodes
    while (listOfNodes.size() > 1) {
        
        BinaryNode<Pair<string, float> >* tempPair = new BinaryNode<Pair<string, float> >();
        tempPair->addLeft(listOfNodes.front());
        listOfNodes.pop_front();
        tempPair->addRight(listOfNodes.front());
        listOfNodes.pop_front();
        Pair<string, float> sumData;
        tempPair->data.second = tempPair->pLeft->data.second + tempPair->pRight->data.second;
        sortTheList(listOfNodes, tempPair);
    }
    
    bNode = listOfNodes.front();
    list<Pair<string, string> > table;
    string code = NULL;
    executeHuffman(bNode, code, table);
    
    // cout-ing the contents of huffman code
    for (list<Pair<string, string> >::iterator it = table.begin(); it != table.end(); ++it) {
        
        cout << it->first << " = " << it->second << endl;
    }
    
    return;
}

/*******************************************
 * SORT LIST
 * Inserts the node into the list in ascending
 * order.
 *******************************************/
void sortTheList(list<BinaryNode<Pair<string, float> >*> &listOfNodes, BinaryNode<Pair<string, float> >* bNode) {
    
    for (list<BinaryNode<Pair<string, float> >*>::iterator it = listOfNodes.begin(); it != listOfNodes.end(); ++it) {
        
         // bnode is smaller than a node in the list insert before the iterator
        if ((*it)->data.first >= bNode->data.first) {
            
            listOfNodes.insert(it, bNode);
            return;
        }
    }
    listOfNodes.push_back(bNode);
}

/*******************************************
 * HUFFMAN CODE
 * A recursive algorithm that traverses the
 * nodes in an INFIX order.
 *******************************************/
void executeHuffman(BinaryNode<Pair<string, float> >* bNode, string code, list<Pair<string, string> > &table) {
    
    // the node is a leaf node
    if (bNode->pLeft == NULL && bNode->pRight == NULL) {
        
        Pair<string, string> newPair(bNode->data.first, code);
        table.push_front(newPair);
    }
    else {
        
        executeHuffman(bNode->pLeft, code + "0", table);
        executeHuffman(bNode->pRight, code + "1", table);
    }
}

