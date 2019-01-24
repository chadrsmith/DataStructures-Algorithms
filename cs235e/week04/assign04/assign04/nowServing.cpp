/***********************************************************************
 * Implementation:
 *    NOW SERVING
 * Summary:
 *    This will contain the implementation for nowServing() as well as any
 *    other function or class implementations you may need
 * Author
 *    Chad Smith
 **********************************************************************/

#include <iostream>     // for ISTREAM, OSTREAM, CIN, and COUT
#include <sstream>      // for SSTREAM and parsing strings
#include <string>       // for STRING
#include <cassert>      // for ASSERT
#include <vector>
#include "nowServing.h" // for nowServing() prototype
#include "deque.h"      // for DEQUE
using namespace std;

/************************************************
 * NOW SERVING
 * The interactive function allowing the user to
 * handle help requests in the Linux lab
 ***********************************************/
void nowServing()
{

    // instructions
    cout << "Every prompt is one minute.  The following input is accepted:\n";
    cout << "\t<class> <name> <#minutes>    : a normal help request\n";
    cout << "\t!! <class> <name> <#minutes> : an emergency help request\n";
    cout << "\tnone                         : no new request this minute\n";
    cout << "\tfinished                     : end simulation\n";
    
    Deque<HelpRequest> dequeHelp;
    string userRequest;
    string studentName;
    string className;
    int minsNeeded;

    
    do
    {
        // get user input
        cin >> userRequest;
        stringstream ss(userRequest);
        
        string test;
        getline(ss, test, ' ');
        
        // on top of deque
        HelpRequest existingRequest;
        // being added to deque
        HelpRequest newHelpRequest;

        
        if (test == "!!") {
            int i = 0;
            string tempData;
            
            while (getline(ss, tempData, ' ')) {
                
                if (i == 1) className = tempData;
                if (i == 2) studentName = tempData;
                if (i == 3) minsNeeded = stoi(tempData);
                i++;
            }
            HelpRequest tempRequest(className, studentName, minsNeeded);
            newHelpRequest = tempRequest;
        }
        else if (test == "none") {
            // do nothing for now
        }
        else if (test == "finished") {
            //do nothing for nowa
        
        }
        else {
            int i = 0;
            string tempData;
            
            while (getline(ss, tempData, ' ')) {
                if (i == 0) className = tempData;
                if (i == 1) studentName = tempData;
                if (i == 2) minsNeeded = stoi(tempData);
                i++;
            }
            HelpRequest tempRequest(className, studentName, minsNeeded);
            newHelpRequest = tempRequest;
        }
        
        if (dequeHelp.capacity() <= 0) {
            
            if (test != "none" && test != "!!" && test != "finished") {
                dequeHelp.push_back(newHelpRequest);
            }
        }
        
        else {
            existingRequest = dequeHelp.front();
            if (test == "!!") {
                dequeHelp.push_front(newHelpRequest);
                if (existingRequest.getMinutesLeft() > 0) {
                    existingRequest.displayInfo();
                }
                else {
                    dequeHelp.pop_front();
                }
            }
            if (test == "none") {
                existingRequest.displayInfo();
                if (existingRequest.getMinutesLeft() > 0) {
                    existingRequest.displayInfo();
                }
                else {
                    dequeHelp.pop_front();
                }
            }
            else if (test != "finished" || test != "!!") {
                dequeHelp.push_back(newHelpRequest);
                if (existingRequest.getMinutesLeft() > 0) {
                    existingRequest.displayInfo();
                }
                else {
                    dequeHelp.pop_front();
                }
            }
            
        }
    }
    while (userRequest != "finished");
        
        // end
        cout << "End of simulation\n";
    
}
