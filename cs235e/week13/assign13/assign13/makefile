###############################################################
# Program:
#     Week 13, Geneology
#     Brother Ercanbrack, CS235
# Author:
#     Chad Smith
# Summary:
#     A demonstration of the concepts I've learned in the
#     CS235 course. This application reads a .GED file of
#     an individual, and parses the information, stores it
#     into a Linked list where it then prints it to the
#     console, and writes it to the sorted.dat file.
# Time:
#     16 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week13.o
    g++ -o a.out week13.o
    tar -cf week13.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week13.o     : the driver program
##############################################################
week11.o: list.h week13.cpp
    g++ -c week13.cpp
##############################################################
# Makes clean
##############################################################
clean:
rm a.out *.o *.tar
all : a.out
