/***********************************************************************
 * Header:
 *    HelpRequest
 * Summary:
 *    Header file for the class HelpRequest. This class contains the
 *    definition of a request for help.
 *
 *
 *    This will contain the class definition of:
 *        HelpRequest         : A class that defines the info needed for a request
 *
 * Author
 *    Chad Smith
 ************************************************************************/

#ifndef HELPREQUEST_H
#define HELPREQUEST_H

#include <cassert>

/************************************************
 * HELPREQUEST
 * A class that defines the info needed for a
 * request
 ***********************************************/
class HelpRequest {
    
public:
    // Default constructor for HelpRequest class
    HelpRequest() : studentName("DEFAULT NAME"), className("DEFAULT CLASS"), numMinutes(400) {}
    
    // Non-default constructor for HelpRequest class
    HelpRequest(std::string arg1, std::string arg2, int arg3) {
        className = arg1;
        studentName = arg2;
        numMinutes = arg3;
    }
    
    int getMinutesLeft()    {   return numMinutes;  }
    void decrementMinutes() {   numMinutes--;   }
    
    void displayInfo() {
        std::cout << "Currently serving " << studentName << " for class " << className << ". Time left: " << numMinutes << std::endl;
    }
    
    
private:
    std::string studentName;
    std::string className;
    bool isUrgent;
    int numMinutes;
    
};


#endif /* HELPREQUEST_H */
