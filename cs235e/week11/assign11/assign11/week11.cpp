/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
* Author:
*    Chad Smith
* Summary: 
*
************************************************************************/

#include <iostream>        // for CIN and COUT
#include <cstring>         // for strcmp
#include <iomanip>         // for SETW
#include "heap.h"
#include "merge.h"
#include <fstream>

using namespace std;

/**********************************************************************
 * MAIN
 * Gets the sort type and filename from the command line. If the sort type
 * or filename are not entered on the command line, the user will be
 * prompted for the sort type and/or filename.
 * Call the appropriate sort to sort the data contained in the vector or
 * linked list and display the sorted data to the console.
 ***********************************************************************/



int main(int argc, const char* argv[]) {
    
    char sortType[10];
    char filePath[50];
    
    if (argc == 1) {
        
        cout << "Which sort merge or heap? ";
        cin >> sortType;
        cout << "Enter name of file to sort: ";
        cin >> filePath;
    }
    
    else if (argc == 2) {
        
        strcpy(sortType,argv[1]);
        cout << "Enter name of file to sort: ";
        cin >> filePath;
    }
    
    else if (argc == 3) {
        
        strcpy(sortType,argv[1]);
        strcpy(filePath,argv[2]);
    }
    
    if (strcmp(sortType, "heap") == 0) {
        
        vector<int> myVector;
        int num;
        
        ifstream fin;
        fin.open(filePath);
        if (fin.fail()) {
            
            cerr << "ERROR: Reading file from vector\n";
        }
        
        myVector.push_back(-1);
        while (fin >> num) {
            
            myVector.push_back(num);
        }
        
        heapSort(myVector);
        
        // display contents!
        for (int i = 1; i < myVector.size(); i++) {
            
            if (i % 10 == 0 && i != 0) {
                
                cout << setw(3) << myVector[i];
                cout << endl;
            }
            else {
                cout << setw(3) << myVector[i];
            }
        }
    }
    
    else if (strcmp(sortType, "merge") == 0) {
        
        list<int> myList;
        int num;
        ifstream fin;
        fin.open(filePath);
        
        if (fin.fail()) {
            
            cerr << "ERROR: Reading file from vector\n";
        }
        
        while (fin >> num) {
            
            myList.push_back(num);
        }
        
        mergeSort(myList);
        
        int count = 0;
        
        // displaying the contents of the list
        for (list<int> :: iterator it = myList.begin(); it != myList.end(); it++) {
            count++;
            if (count % 10 == 0 && count != 0) {
                
                cout << endl;
                cout << endl << setw(3) << *it;
            }
            else {

                cout << setw(3) << *it;
            }
        }
    }
    else {
        
        cout << "\nInvalid sort name - must be 'heap' or 'merge'" << endl;
    }
    
    return 0;
}
