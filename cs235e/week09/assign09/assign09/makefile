###############################################################
# Program:
#     Week 09, Binary Search Tree
#     Brother Ercanbrack, CS235
# Author:
#     Chad Smith
# Summary:
#     Binary Search Tree data type. This makes a binary search
#     tree that will sort the data being inserted into it.
#     That will be demonstrated in the sortBinary header file.
*
# Time:
#     14.0 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week09.o
	g++ -o a.out week09.o 
	tar -cf week09.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson08.o     : the driver program
##############################################################
week09.o: bnode.h bst.h stack.h week09.cpp sortBinary.h
	g++ -c week09.cpp

