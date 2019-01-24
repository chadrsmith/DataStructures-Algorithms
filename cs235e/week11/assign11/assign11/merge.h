/***********************************************************************
* Program:
*    Week 11, Sorting
*    Brother Ercanbrack, CS 235
*
* Author:
*   Chad Smith
* Summary:
*   This is the MergeSort function that takes a list and performs a
*   merge sort to sort the data. It performs this by splitting the
*   list into sublists and dividing them between two copies. Then
*   we perform a merge and compare the two sublists by current
*   iterators. We do this until it is sorted.
*
************************************************************************/
#include <list>

using namespace std;
template<class T>
void split(list<T> &data, list<T> &copy1, list<T> &copy2);
template<class T>
void merge(list<T> &data, list<T> &copy1, list<T> &copy2);

/*************************************************************************
 * This function sorts a linked list using a Natural Merge Sort.
 * Input:  data -  linked list of data to be sorted.
 * Output: data -  sorted linked list
 **************************************************************************/
template<class T>
void mergeSort(list<T> &data) {
    
    list<T> copy1;
    list<T> copy2;
    bool isSorted = false;
    
    while (isSorted == false) {
        split(data, copy1, copy2);
        merge(data, copy1, copy2);
        
        typename list<T>::iterator it = data.begin();
        
        while (it != data.end()) {
            if (*it < *it++) {
                it++;
                if (it == data.end())
                    isSorted = true;
            }
            else {
                return;
            }
        }
        
    }

    
}

/*************************************************************************
 * SPLIT
 * Splits the data into two copies: copy1 and copy2
 **************************************************************************/
template<class T>
void split(list<T> &data, list<T> &copy1, list<T> &copy2) {
    
    typename list<T>::iterator it = data.begin();
    typename list<T>::iterator itNext = it++;
    int current = 0;
    
    while (it != data.end()) {
        
        while (*it < *itNext) {
            if (current == 0) {
                copy1.push_back(*it);
                it++;
            }
            else {
                copy2.push_back(*it);
                it++;
            }
        }
        if (it++ == data.end()) {
            return;
        }
        else {
            if (current == 1)
                current = 0;
            else
                current = 1;
        }
    }
    
    // clear contents inside data while keeping its size
    data.clear();
}

/*************************************************************************
 * MERGE
 * Merges the contents of copy1 and copy2 back into data
 **************************************************************************/
template<class T>
void merge(list<T> &newFile, list<T> &data1, list<T> &data2) {
    
    typename list<T> :: iterator itData1 = data1.begin();    // iterator for copy1
    typename list<T> :: iterator itData2 = data2.begin();    // iterator for copy2
    
    while (itData1 != data1.end() || itData2 != data2.end()) {
        
        if (*itData1 <= *itData2) {
            newFile.push_back(*itData1);
            itData1++;
        }
        else {
            newFile.push_back(*itData2);
            itData2++;
        }
    }
    
    if (itData1 == data1.end()) {
        return;
    }
    else {
        while (itData1 != data1.end()) {
            newFile.push_back(*itData1);
            itData1++;
        }
        return;
    }
    if (itData2 == data2.end()) {
        return;
    }
    else {
        while (itData2 != data2.end()) {
            newFile.push_back(*itData2);
            itData2++;
        }
        return;
    }
}
