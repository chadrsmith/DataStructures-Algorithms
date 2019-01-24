###############################################################
# Program:
#     Week 11, Sorts
#     Brother Ercanbrack, CS235
# Author:
#     Chad Smith
# Summary:
#     This program will complete a heap merge and merge sort 
#     on files filled with intergers.
# Time:
#     13 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week11.o
	g++ -o a.out week11.o 
	tar -cf week11.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week11.o     : the driver program
##############################################################
week11.o: merge.h heap.h week11.cpp
	g++ -c week11.cpp
##############################################################
# Makes clean 
##############################################################
clean:
	rm a.out *.o *.tar
all : a.out
