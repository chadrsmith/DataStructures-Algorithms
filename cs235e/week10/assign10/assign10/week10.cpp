/***********************************************************************
 * WEEK10 MAP:
 *    MAIN FUNCTION
 * Summary:
 *    This usesthe MAP ADT from the standard template
 *    library. It will count the usages of words in the files
 *    To demonstrate this in the application you will be
 *    prompted to enter a filename. We will read and sort
 *    the data from the file into the map.
 * Author
 *    Chad Smith
 ************************************************************************/

#include <iostream>
#include <map>
#include <fstream>
#include "pair.h"
#include <list>
#include <iomanip>
using namespace std;

// reads the strings that are in the file
void readIn(map<string, int> &m);

// switches
void sortMap(map<string, int> main, list<Pair<int, string> > &newCopy);

// count for the sorting of the list
int countWordUsage(list<Pair<int, string> > newCopy);

// Displays the top 100 words in the file that is read
void displayTopUsedStrings(list<Pair<int, string> > newCopy);

/****************************************************************
 * MAIN FUNCTION :: MAIN
 *
 * Calls the functions declared above to read a file, sort the
 * file, and to display the top 100 most used strings that are
 * in the file.
****************************************************************/
int main() {
    
    // create map to hold the data being read in from file
    map<string, int> mapOfStrings;
    
    // read and store the words from the file
    readIn(mapOfStrings);
    
    // create a list holding the top 100 words
    list<Pair<int, string> > newCopy;
    
    // sort the map
    sortMap(mapOfStrings, newCopy);
    
    // display output
    cout << "Number of words processed: " << countWordUsage(newCopy) << endl;
    displayTopUsedStrings(newCopy);
    
    return 0;
}

/****************************************************************
 * MAIN FUNCTION :: READ FILE
 *
 * Aske the user to enter a file to read contents from
 * and inserts them into a map
 ****************************************************************/
void readIn(map<string, int> &m) {
    
    // get the file name from the user
    cout << "Enter filename: ";
    string filename;
    cin >> filename;
    cout << endl;
    
    // usual error catching
    ifstream fin;
    fin.open(filename.c_str());
    if (fin.fail()) {
        
        cerr << "ERROR: Unable to open data file." << endl;
        return;
    }
    
    // opened the file, now let's read the data
    string stringRead;
    
    // reads until the end of the file
    while (fin >> stringRead) {
        
        // let's get rid of the punctuation now before we store it
        for (int i = 0, len = stringRead.size(); i < len; i++) {
            
            if (ispunct(stringRead[i]) && stringRead[i] != '-') {
                
                stringRead.erase(i--, 1);
                len = stringRead.size();
            }
        }
        
        // Let's change all the data so it's all lower-case
        for (int i = 0; i < stringRead.size(); i++) {
            
            stringRead[i] = tolower(stringRead[i]);
        }
        
        // now let's store the data
        m[stringRead]++;
    }
    
    // ALL DONE!!! Let's close the file now
    fin.close();
}

/****************************************************************
 * MAIN FUNCTION :: SWITCH MAP
 *
 * Takes the map's data that was read from the file and places it
 * into a list to be sorted
 ****************************************************************/
void sortMap(map<string, int> mapFromFile, list<Pair<int, string> > &sortedCopy) {
    
    // takes the map from file and places it into a list, so we can sort it!
    for (map<string, int>::iterator it = mapFromFile.begin(); it != mapFromFile.end(); ++it) {
        
        Pair<int, string>* temp = new Pair<int, string>(it->second, it->first);
        list<Pair<int, string> >::iterator itt = sortedCopy.begin() ;
        sortedCopy.insert(itt, *temp);
    }
    
    sortedCopy.sort();
    
    sortedCopy.reverse();
}

/****************************************************************
 * MAIN FUNCTION :: PROCESS NUMBERS
 *
 * Counts the number of the times the word has been processed
 ****************************************************************/
int countWordUsage(list<Pair<int, string> > newCopy)
{
    int count = 0;
    
    for (list<Pair<int, string> >::iterator it = newCopy.begin(); it != newCopy.end(); ++it) {
        count += it->first;
    }
    return count;
}

/****************************************************************
 * AMIN FUNCTION :: DISPLAYTOPUSEDSTRINGS
 *
 * Displays the top 100 words that where given from
 * the text file given
 ****************************************************************/
void displayTopUsedStrings(list<Pair<int, string>> copyToDisplay) {
    
    cout << "100 most common words found and their frequencies:\n";
    
    // variable to make sure only top 100 get displayed
    int count = 0;
    for (list<Pair<int, string>> :: iterator it = copyToDisplay.begin(); it != copyToDisplay.end() && count < 100; ++it) {
        
        cout << setw(23) << it->second << " - " << it->first << endl;
        count++;
    }
}
