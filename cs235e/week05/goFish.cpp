/***********************************************************************
* Program:
*    Assignment 05, Go Fish
*    Brother Ercanbrack, CS 235
* Author:
*    Chad Smith
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  10.0 hrs
*    Actual:     12.0 hrs
*      I was having difficulty in the insert operator, I kept getting
*      a seg fault in my insert operator when I would shift an element
*      in the middle of the Set. I added a few delete statements to the
*      pointer data. It seemed to be working good in Xcode. However, in
*      the Linux lab it isn't working. Can't quite put my finger on what
*      is going on.
************************************************************************/

#include <iostream>
#include <fstream>      // used for reading cards from the hand.txt
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;

// readFile function Declaration
void readFile(Set<string> newHand) throw (const char *);

/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
    Set<string> newHand;
    string userGuess;
    int guessedRight = 0;
    
    // reads the file and returns a new hand
    //readFile(newHand);
    ifstream readData;
    readData.open("/home/smi17075/CS235/week05/hand.txt");
    
    if (readData.is_open()) {
        string word;
        while (readData >> word)
        {
            newHand.insert(word);
            word = "";
        }
    }
    else {
        throw "ERROR: File did NOT open, check the file path!";
    }
    
    // Opening prompt for the game
    cout << "We will play 5 rounds of Go Fish. Guess the card in the hand" << endl;
    
    // goes through five turns to let the user guess
    for (int i = 0; i < 5; i++) {
        cout << "round " << i + 1 << ": ";
        cin >> userGuess;
    
        int isFound;
        isFound = newHand.find(userGuess);
        
        if (isFound >= 0) {
            cout << "You got a match!" << endl;
            newHand.erase(isFound);
            guessedRight++;
        }
        else {
            cout << "Go Fish!" << endl;
        }
    }
    
    // prints out the results of the game
    cout << "You have " << guessedRight << " matches!" << endl;
    cout << "The remaining cards: ";
    SetIterator <string> it;
    for (it = newHand.begin(); it != newHand.end(); it++) {
        if (it != newHand.begin())
            cout << ", ";
        cout << *it;
    }
    cout << endl;
    
   return ;
}

/**********************************************************************
 * READFILE
 * this function will read a file and place it into the players hand
 ***********************************************************************/
void readFile(Set<string> newHand) throw (const char *){
    
    ifstream readData;
    readData.open("/home/smi17075/CS235/week05/hand.txt");
    
    if (readData.is_open()) {
        string word;
        while (readData >> word)
        {
            newHand.insert(word);
            word = "";
        }
    }
    else {
        throw "ERROR: File did NOT open, check the file path!";
    }
}
