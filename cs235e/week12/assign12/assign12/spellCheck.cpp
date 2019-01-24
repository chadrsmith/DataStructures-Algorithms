/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Chad Smith
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include "spellCheck.h"
#include "hash.h"
using namespace std;

void displayMispelledWords (list<string> mispelledWords);
void readFileIntoHash (string fileName, SHash stringHash);

/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck() {
    
    SHash stringHash(500);
    
    string filename;
    cout << "What file do you want to check? ";
    cin >> filename;
    ifstream fin("/home/cs235e/week12/dictionary.txt");
    if (!fin) {
        cerr << "Unable to open dictionary.txt";
    }
    string word;
    
    while (fin >> word) {
        stringHash.insert(word);
    }
    fin.close();
    
    ifstream fin2(filename.c_str());
    if (!fin2) {
        
        cerr << "Unable to open given filename";
    }
    
    list<string> mispelledWords;
    while (fin2 >> word) {
        
        string temp = word;
        for (int i = 0; i < word.size(); i++) {
            
            temp[i] = tolower(word[i]);
        }
        
        if (!stringHash.find(temp)) {
            
            mispelledWords.push_back(word);
        }
    }
    fin2.close();
    
    
}

void displayedMispelledWords (list<string> mispelledWords) {
    
    if (mispelledWords.empty())
        cout << "File contains no spelling errors\n";
    
    else {
        
        cout << "Misspelled: ";
        
        for (list<string>::iterator it = mispelledWords.begin(); it != mispelledWords.end(); it++) {
            cout << *it;
            
            if (*it != mispelledWords.back())
                cout << ", ";
        }
        cout << endl;
        mispelledWords.clear();
    }
}
