/***********************************************************************
 * Program:
 *    Week 11, Sorting
 *    Brother Ercanbrack, CS 235
 *
 * Author:
 *   Chad Smith
 * Summary:
 *   This performs a Heap sort. First we take a Vector and transform it
 *   into something similar to a Binary tree data structure. After
 *   that we compare the parent and the children and make sure that the
 *   parent is always the greater than the children. After we make sure
 *   we move upwards in the tree.
 ************************************************************************/
#include <vector>
using namespace std;

template<class T>
void heapify();

template<class T>
void percolateDown();

template<class T>
void heapify(vector<T> &data, int size);

template<class T>
void percolateDown(vector<T> &data, int index, int size);

/*************************************************************************
 * Takes the vector passed into it and changes it into a heap
 **************************************************************************/
template<class T>
void heapify(vector<T> &data, int size) {
    for (int r = size / 2; r > 0; --r) {
        
        percolateDown(data, r, size);
    }
}

/*************************************************************************
 * Takes a heap and orders the heap from that index down
 **************************************************************************/
template<class T>
void percolateDown(vector<T> &data, int index, int size) {
    
    int child = index * 2;
    
    while (child <= size) {
        if (child < size && data[child] < data[child + 1])
            child++;
        
        if (data[index] < data[child]) {
            
            T placeHolder = data[index];
            data[index] = data[child];
            data[child] = placeHolder;
            index = child;
            child = child * 2;
        }
        
        else
            break;
    }
}

/*************************************************************************
 * This function sorts a vector using a heap sort.
 * Input:  data -  Vector to be sorted.
 * Output: data -  Vector sorted
 **************************************************************************/
template<class T>
void heapSort(vector<T> &data) {
    
    int size = data.size() - 1;
    heapify(data, size);
    
    for (int i = data.size() - 1; i > 1; --i) {
        
        T placeHolder = data[1];
        data[1] = data[i];
        data[i] = placeHolder;
        size--;
        heapify(data, size);
    }
}
