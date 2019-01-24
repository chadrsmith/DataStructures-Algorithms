//
//  list.h
//  assign13
//
//  Created by Chad Smith on 12/14/18.
//  Copyright © 2018 Chad Smith. All rights reserved.
//

#ifndef list_h
#define list_h

#include <string>
using namespace std;
const int MAX = 500;

/****************************************************************
 * STRUCT :: DATA
 * Container for holding data
 ****************************************************************/
struct Data {
    int personID;
    string personName;
    string personSName;
    string personDOB;
};

/****************************************************************
 * CLASS :: NODE
 * container for holding data
 ****************************************************************/
class Node {
public:
    // default constructor for the node class
    Node();
    
    Data getData() {
        if (this->data.personID != -1)
            return this->data;
        else {
            Data err;
            err.personID = -1;
            return err;
        }
    }
    void setDepth (int depth)   {   if (this) this->treeDepth = depth; }
    int getDepth()  { if (this) return this->treeDepth; else return 0; }
    void setData (Data data)    {   this->data = data;      }   // set the node data, data struct properties
    void nextNode (Node *node)  {   this->pNext = node;     }   // create the next node
    void setFather (Node *node) {   this->pFather = node;   }   // set father node
    void setMother (Node *node) {   this->pMother = node;   }   // set mother node
    Node *getNextNode() {   return this->pNext;     }           // return Next Nodes pointer
    Node *getfather()   {   return this->pFather;   }           // returns the father node
    Node *getmother()   {   return this->pMother;   }           // returns the mother node
    
private:
    Data data;
    Node *pNext;
    Node *pMother;
    Node *pFather;
    int treeDepth;
};

/****************************************************************
 * CLASS :: LIST
 * Linked list container for storing data
 ****************************************************************/
class List {
    
public:
    // default constructor
    List(): numItems(0), pHead(NULL) {}
    
    // returns if list is empty or not
    bool empty()        {   return !this->numItems; }
    
    // returns the number of items in the list
    int getNumitems()   {   return this->numItems; }
    
    // finds a node by the gedID
    int find(int gedID);
    
    // returns data from a node in the list
    Data getData(int index);
    
    // returns the node at a specific index
    Node *getNode(int index);
    
    // inserts node at a location
    void insert(int pos, Node *data);
    
    // inserts at the sorted location
    void insertSorted(Data data);
    
    // sets the data at a specific location in the list
    void setData(Data data, int index);
    
    //set relationships
    void setParents(int child,  int mother, int father);
    
    // prints the list by level
    void level();
    
    // deletes node at a specific index
    void deleteNode(int index);
    
private:
    int numItems;           // holds the number of items in the list
    void setTreeDepth();    // sets the tree's depth
    Node *pHead;            // head node of the list
};

/****************************************************************
 * LIST :: SETTREEDEPTH
 * Sets the trees depth
 ****************************************************************/
void List :: setTreeDepth() {
    
    Node *stack [MAX];
    Node *temp;
    int currentTop = 0;
    
    // start with "cAMerOn" O_o
    stack[currentTop++] = this->getNode(this->find(1));
    
    while (currentTop != 0) {
        
        temp = stack [--currentTop];
        temp->getfather()->setDepth(temp->getDepth() + 1);
        temp->getmother()->setDepth(temp->getDepth() + 1);
        
        // push data onto the stack
        if (temp->getfather() != NULL) {
            stack[currentTop++] = temp->getfather();
        }
        if (temp->getmother() != NULL) {
            stack[ currentTop++ ] = temp->getmother();
        }
    }
}

/****************************************************************
 * LIST :: SETDATA
 * Sets the data for the node at the given index
 ****************************************************************/
void List :: setData (Data data, int index) {
    Node *currentNode = this->pHead;
    int count = 0;
    
    while (currentNode) {
        if (count == index) {
            currentNode->setData(data);
            return;
        }
        count++;
        currentNode = currentNode->getNextNode();
    }
}

/****************************************************************
 * LIST :: INSERTSORTED
 * INSERTS INTO A SORTED LIST
 ****************************************************************/
void List :: insertSorted (Data data) {
    
    int index = 0;
    string sName;
    string name;
    string dob;
    
    Node *currentNode = this->pHead;
    Node *temp = new Node;
    Data tempData = data;
    temp->setData(tempData);
    
    // find the position to insert data at
    for (int i = 0; i < this->numItems; i++) {
        
        sName = currentNode->getData().personSName;
        name = currentNode->getData().personName;
        dob = currentNode->getData().personDOB;
        
        // check the name, last, first, and birth date, if found we break out
        // and insert the index
        if (tempData.personSName == sName) {
            if (tempData.personName == name) {
                if (tempData.personDOB < dob) {
                    index = i;
                    break;
                }
            }
            else if (tempData.personName < name) {
                index = i;
                break;
            }
        }
        else if (tempData.personSName < sName) {
            index = i;
            break;
        }
        
        if (currentNode->getNextNode() == NULL) {
            index = this->numItems;
            break;
        }
        else {
            currentNode = currentNode->getNextNode();
        }
    }
    
    this->insert(index, temp);
}

/****************************************************************
 * LIST :: INSERT
 * Inserts a node at the given index
 ****************************************************************/
void List :: insert (int index, Node *passedNode) {
    // list is empty, insert at head
    if ( index == 0 || this->empty() ) {
        
        if (this->empty()) {
            this->pHead = passedNode;
        }
        else {
            passedNode->nextNode(this->pHead);
            this->pHead = passedNode;
        }
    }
    else {
        // insert later in the record set
        Node *currentNode = this->pHead;
        
        for (int i = 0; i < index - 1; i++) {
            
            if (currentNode->getNextNode() == NULL)
                break;
            else {
                currentNode = currentNode->getNextNode();
            }
        }
        passedNode->nextNode(currentNode->getNextNode());
        currentNode->nextNode(passedNode);
    }
    
    this->numItems++;
}

/****************************************************************
 * LIST :: SETPARENTS
 * Sets the parents of the child node
 ****************************************************************/
void List :: setParents (int child, int father, int mother) {
    
    Node *childNode = this->getNode(this->find(child));
    
    if (childNode != NULL) {
        
        Node *fatherNode;
        Node *motherNode;
        
        // find the father node
        fatherNode = this->getNode(this->find(father));
        
        // find the mother node
        motherNode = this->getNode(this->find(mother));
        
        // set the father node if one was found
        if (fatherNode != NULL)
            childNode->setFather(fatherNode);
        
        // set the mother node if one was found
        if (motherNode != NULL)
            childNode->setMother(motherNode);
    }
}

/****************************************************************
 * LIST :: DELETENODE
 * deletes the node at a specific index
 ****************************************************************/
void List :: deleteNode (int index) {
    // do nothing if the list is empty
    if (this->empty()) {
        return;
    }
    
    int count = 0;
    Node *currentNode = this->pHead;
    Node *prevNode = currentNode;
    
    // handles first element in the list
    if (index == 0) {
        
        this->pHead = currentNode->getNextNode();
        this->numItems--;
        currentNode = currentNode->getNextNode();
        delete prevNode;
        prevNode = NULL;
        
        return;
    }
    
    while (currentNode != NULL) {
        if (currentNode && !currentNode->getNextNode()) {
            // delete a record
            delete currentNode;
            currentNode = NULL;
            prevNode->nextNode(NULL);
            this->numItems--;
    
            return;
        }
        else if (index == count) {
            // remove a record from the middle of the list
            prevNode->nextNode(currentNode->getNextNode());
            delete currentNode;
            currentNode = NULL;
            currentNode = prevNode->getNextNode();
            this->numItems--;
            
            return;
        }
        
        count++;
        prevNode = currentNode;
        currentNode = currentNode->getNextNode();
    }
    return;
}

/****************************************************************
 * LIST :: FIND
 * Finds node if it matches the passed ID
 ****************************************************************/
int List :: find (int personID) {
    // quit if the list is empty
    if (this->empty())
        return -1;
    
    int count = 0;
    Node *currentNode = this->pHead;
    
    while (currentNode) {
        // find a location at the given item
        if (currentNode->getData().personID == personID)
            return count;
        
        count++;
        currentNode = currentNode->getNextNode();
    }
    // not found
    return -1;
}

/****************************************************************
 * LIST :: GETDATA
 * Returns the Data of the passed index
 ****************************************************************/
Data List :: getData (int index) {
    
    int count = 0;
    Node *currentNode = this->pHead;
    Data err;
    err.personID = -1;
    
    if (this->empty()) {
        return err;
    }
    while (currentNode != NULL) {
        // find item at given location
        if (count == index) {
            return currentNode->getData();
        }
        
        count++;
        currentNode = currentNode->getNextNode();
    }
    // item not found
    return err;
}

/****************************************************************
 * LIST :: GETNODE
 * returns the node of the lists index
 ****************************************************************/
Node *List :: getNode (int index) {
    // if list is empty, do nothing
    if (this->empty()) {
        return NULL;
    }
    
    int count = 0;
    Node *currentNode = this->pHead;
    
    while (currentNode != NULL) {
        // item was found at given index
        if (count == index) {
            return currentNode;
        }
        count++;
        currentNode = currentNode->getNextNode();
    }
    // item not found
    return NULL;
}

/****************************************************************
 * LIST :: LEVEL
 * Prints the tree by level
 ****************************************************************/
void List :: level() {
    
    Node *queue [MAX];
    Node *temp;
    int front = 0;
    int back = 0;
    int depth = 0;
    Data gedData;
    this->setTreeDepth();
    
    // StaRtiNg wItH TeH BeGinnInG: brOtHeR CaMErOn O_o
    queue[back++] = this->getNode(this->find(1));
    
    while (front != back) {
        
        temp = queue[ front ];
        front = ( front + 1 ) % MAX;
        
        // use treeDepth to determine the level for printing ancestors
        if (depth == temp->getDepth() && temp->getDepth() == 0) {
            cout << "The Ancestors of " << temp->getData().personName << " " << temp->getData().personSName << ":" << endl;
            depth++;
        }
        else if ( depth == temp->getDepth() && temp->getDepth() == 1 ) {
            cout << "Parents:" << endl;
            depth++;
        }
        else if ( depth == temp->getDepth() && temp->getDepth() == 2 ) {
            cout << "Grandparents:" << endl;
            depth++;
        }
        else if ( depth == temp->getDepth() && temp->getDepth() == 3 ) {
            cout << "Great Grandparents:" << endl;
            depth++;
        }
        else if (depth == temp->getDepth() && temp->getDepth() == 4) {
            cout << (temp->getDepth() - 2) << "nd Great Grandparents:" << endl;
            depth++;
        }
        else if (depth == temp->getDepth() && temp->getDepth() == 5) {
            cout << (temp->getDepth() - 2) << "rd Great Grandparents:" << endl;
            depth++;
        }
        else if (depth == temp->getDepth() && temp->getDepth() > 5) {
            cout << (temp->getDepth() - 2) << "th Great Grandparents:" << endl;
            depth++;
        }
        
        if (temp != NULL) {
            if (depth != 1) {
                gedData = temp->getData();
                
                // format the data for screen display
                if (gedData.personName.size() > 0) {
                    cout << "        " << gedData.personName;
                    
                    if (gedData.personSName.size() > 0) {
                        cout << " " << gedData.personSName;
                    }
                    if (gedData.personDOB.size() > 0) {
                        cout << ", b. " << gedData.personDOB;
                    }
                }
                else {
                    cout << "        " << gedData.personSName;
                    if (gedData.personDOB.size())
                        cout << ", b. " << gedData.personDOB;
                }
                cout << endl;
            }
            
            queue [back] = temp->getfather();
            back = (back+ 1) % MAX;
            queue [back] = temp->getmother();
            back = (back + 1) % MAX;
        }
    }
}

/****************************************************************
 * NODE :: DEFAULT CONSTRUCTOR
 * Default constructor for the node class
 ****************************************************************/
Node :: Node() {
    
    this->data.personID = 0;
    this->data.personName = "";
    this->data.personSName = "";
    this->data.personDOB = "";
    this->pNext = NULL;
    this->pFather = NULL;
    this->pMother = NULL;
    this->treeDepth = 0;
}
#endif /* list_h */
