###############################################################
# Program:
#     Week 06, NODE
#     Brother Ercanbrack, CS235
# Author:
#     Chad Smith
# Summary:
#     This is a program that contains the Node class. the Node
#     class contains the definition for a Nod that contains
#     data and a pointer of the address to the next node.
#     The application demonstrates and shoes the functionability
#     of my class.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: node.h week06.o 
	g++ -o a.out week06.o  -g
	tar -cf week06.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week06.o      : the driver program
#      <anything else?>
##############################################################
week06.o: node.h week06.cpp sortInsertion.h
	g++ -c week06.cpp -g
