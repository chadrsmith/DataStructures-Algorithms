###############################################################
# Program:
#     Week 02, STACK
#     Brother Ercanbrack, CS235
# Author:
#     Chad Smith
# Summary:
#     This is a program that contains the Stack ADT
#     data structure. It is similar to the Stack
#     data structure found in the std library.
# Time:
#     14 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: stack.h week02.o infix.o
    g++ -o a.out week02.o infix.o
    tar -cf week02.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week02.o       : the driver program
#      infix.o        : the logic for the infix --> postfix program
##############################################################
week02.o: stack.h infix.h week02.cpp
    g++ -c week02.cpp

infix.o: stack.h infix.h infix.cpp
    g++ -c infix.cpp

