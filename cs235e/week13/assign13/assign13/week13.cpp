//
//  week13.cpp
//  assign13
//
//  Created by Chad Smith on 12/09/18.
//  Copyright © 2018 Chad Smith. All rights reserved.
//
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

// LIST data structure I created for this
#include "list.h"

using namespace std;

int parseGedData (string arg);

/**************************************************************
 * INT MAIN
 * Main function, takes the .ged file, and sorts it into a list
 * by generation. Prints out the results to screen and stores
 * the results in the outfile "sorted.dat"
 **************************************************************/
int main() {
    
    List familyList;
    Data familyData;
    
    bool isPerson = false;
    int child;
    int mother = 0;
    int father = 0;
    
    ifstream fin;
    ofstream fout;
    string inFileName = "/Users/chadsmith/Desktop/assign13/assign13/cameron.ged";
    string oFileName = "sorted.dat";
    
    // open the file to be read from
    fin.open(inFileName);
    if (!fin.is_open()) {
        cerr << "ERROR: Unable to open file.";
    }
    else {
        
        // get the info from the GED file
        getline(fin, inFileName);
        
        while (!fin.eof()) {
            
            // found an individual in the .ged file, read the information
            if (inFileName.substr(2, 2) == "@I") {
                
                if (isPerson == true) {
                    familyList.insertSorted(familyData);
                }
                // is an individual so set isPerson to true
                isPerson = true;
                
                familyData.personID = 0;
                familyData.personName = "";
                familyData.personSName = "";
                familyData.personDOB = "";
                
                // parse data to get the gedID for the specified person
                familyData.personID = parseGedData(inFileName.substr(4, inFileName.size() - 4));
            }
            
            // found a family in the .ged file, read the information
            else if (inFileName.substr(2, 2) == "@F") {
                
                if (isPerson == true) {
                    familyList.insertSorted(familyData);
                }
                
                // not an individual, so set isPerson to false
                isPerson = false;
                child = 0;
                mother = 0;
                father = 0;
                familyData.personID = 0;
                familyData.personName = "";
                familyData.personSName = "";
                familyData.personDOB = "";
            }
            
            // if it is an individual, grab the information, and set data's values
            if (isPerson == true) {
                
                if (inFileName.substr(2, 4) == "GIVN" ) {
                    familyData.personName = inFileName.substr(7, inFileName.size() - 7);
                }
                else if ( inFileName.substr( 2, 4 ) == "SURN") {
                    familyData.personSName = inFileName.substr(7, inFileName.size() - 7);
                }
                else if (inFileName.substr(2, 4) == "BIRT") {
                    getline(fin, inFileName);
                    
                    if (inFileName.substr(2, 4 ) == "DATE") {
                        familyData.personDOB = inFileName.substr(7, inFileName.size() - 7);
                    }
                }
            }
            
            // not an individual, so we read the family data
            else {
                if (!isPerson && inFileName.substr(2, 4) == "HUSB") {
                    father = parseGedData(inFileName.substr( 9, inFileName.size() - 9 ));
                }
                else if (!isPerson && inFileName.substr(2, 4) == "WIFE"){
                    mother = parseGedData(inFileName.substr(9, inFileName.size() - 9));
                }
                else if ( !isPerson && inFileName.substr(2, 4) == "CHIL") {
                    child = parseGedData(inFileName.substr( 9, inFileName.size() - 9 ));
                    familyList.setParents(child, father, mother);
                }
            }
            
            getline(fin, inFileName);
        }
        
        // all done with the file, close it.
        fin.close();
        
        // cout the contents of the tree
        familyList.level();
        
        // Time to print the results into the outfile!!!
        fout.open(oFileName);
        if (fout.is_open()) {
            
            // print the contents of FAMILY LIST INTO THE OUTFILE
            for (int i = 0; i < familyList.getNumitems(); i++) {
                familyData = familyList.getData(i);
                
                if (familyData.personName.size()) {
                    
                    fout << familyData.personName;
                    
                    if (familyData.personSName.size())
                        fout << " " << familyData.personSName;
                    
                    if (familyData.personDOB.size() )
                        fout << ", b. " << familyData.personDOB;
                    
                    else {
                        
                        fout << familyData.personSName;
                        
                        if (familyData.personDOB.size())
                            fout << ", b. " << familyData.personDOB;
                    }
                    
                    fout << endl;
                }
            }
        }
        
        // all done with the outfile, let's close it!
        fout.close();
    }
    
    return 0;
}

/****************************************************************
 * NONMEMBER FUNC :: PARSEGEDDATA
 * parses the string that is passed, and changes it to the
 * person's GED ID.
 ****************************************************************/
int parseGedData (string arg) {
    
    char *tempStr = new char [arg.size() + 1];
    int personID;
    
    for (int i = 0; i < arg.size(); i++) {
        
        tempStr[i] = arg[i];
        tempStr[i + 1] = '\0';
        
        if (tempStr[ i ] == '@') {
            tempStr[i] = '\0';
            break;
        }
    }
    
    personID = atoi(tempStr);
    delete [] tempStr;
    tempStr = NULL;
    
    return personID;
}
