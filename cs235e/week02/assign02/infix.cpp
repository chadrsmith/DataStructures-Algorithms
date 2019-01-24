/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Ercanbrack, CS 235
 * Author:
 *    Chad Smith
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>    // for ISTREAM and COUT
#include <sstream>
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stack.h"     // for STACK
using namespace std;

/***********************************************************************
 * checks to see if the character passed is an operator
 ************************************************************************/
bool isOperator(string arg) {
    
    if (arg == "(") return true;
    if (arg == ")") return true;
    if (arg == "^") return true;
    if (arg == "*") return true;
    if (arg == "/") return true;
    if (arg == "+") return true;
    if (arg == "-") return true;
    
    return false;
}

/***********************************************************************
 * assigns a priority level to the arg that is passed
 ************************************************************************/
int getOperatorPriority(char arg) throw (const char *) {
    
    int priorityLevel = -3;
    
    switch (arg) {
        case '+':
            priorityLevel = 1;
            break;
        case '-':
            priorityLevel = 1;
            break;
        case '*':
            priorityLevel = 3;
            break;
        case '/':
            priorityLevel = 3;
            break;
        case '^':
            priorityLevel = 4;
            break;
        default:
            priorityLevel = -3;
            break;
    }
    return priorityLevel;
}

/***********************************************************************
 * will compare the priority level of the top of the stack and
 
 ************************************************************************/
bool isHigherPriority(char topStack, char onDeck) {
    
    int topStackPriority = getOperatorPriority(topStack);
    int onDeckPriority = getOperatorPriority(onDeck);
    
    cout << "the priority of the top of the stack is: " << topStack
    << " " << topStackPriority << " ." << endl;
    
    cout << "the priority of the charOp variable is: " << onDeck << " "
    << onDeckPriority << " ." << endl;
    
    if (topStackPriority == onDeckPriority) {
    
        return true;
    }
    if (topStackPriority > onDeckPriority) {
        return true;
    }
    
    
    return false;
}

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
    string postfix = "";
    string subStr = "";
    string tempData;
    Stack<char> operatorStack;
    
    istringstream parser(infix);
    
    do
    {
        string data;
        parser >> data;
        
        cout << "the data being evaluated is: " << data << endl;
        if (isOperator(data)) {
            char charOp = data[0];
            if (!operatorStack.empty() && isHigherPriority(operatorStack.top(), charOp)) {
                postfix += " ";
                postfix += operatorStack.top();
                operatorStack.pop();
                cout << "the OPERATOR being added to the postfix string is: " << operatorStack.top() << endl;
                
                operatorStack.push(charOp);
            }
            else {
                operatorStack.push(charOp);
            }
        }
        else if (data != "(" || data != ")") {
            
            cout << "the OPERAND being added to the postfix string is: " << data << endl;
            postfix += " ";
            postfix += data;
        }
        else if (data[0] == '(') {
            operatorStack.push('(');
            cout << "the parenthesis data: " << data << endl;
    
            postfix += " ";
            for (int i = 1; i < data.length(); i++) {
                postfix += data[i];
            }
            
            
        }
        else if (subStr[subStr.length() - 1] == ')') {
            
            postfix += " ";
            for (int i = 1; i < (data.length() - 1); i++) {
                postfix += data[i];
            }
            
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix += " ";
                postfix += operatorStack.top();
                operatorStack.pop();
            }
            operatorStack.pop();
        }
    }
    while (parser);
    
    while (!operatorStack.empty()) {
        postfix += " ";
        postfix += operatorStack.top();
        operatorStack.pop();
    }

    return postfix;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
    string input;
    cout << "Enter an infix equation.  Type \"quit\" when done.\n";
    
    do
    {
        // handle errors
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
        }
        
        // prompt for infix
        cout << "infix > ";
        getline(cin, input);
        
        // generate postfix
        if (input != "quit")
        {
            string postfix = convertInfixToPostfix(input);
            cout << "\tpostfix: " << postfix << endl << endl;
        }
    }
    while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
    string assembly;
    
    return assembly;
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
    string input;
    cout << "Enter an infix equation.  Type \"quit\" when done.\n";
    
    do
    {
        // handle errors
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(256, '\n');
        }
        
        // prompt for infix
        cout << "infix > ";
        getline(cin, input);
        
        // generate postfix
        if (input != "quit")
        {
            string postfix = convertInfixToPostfix(input);
            cout << convertPostfixToAssembly(postfix);
        }
    }
    while (input != "quit");
    
}
