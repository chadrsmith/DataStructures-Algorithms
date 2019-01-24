###############################################################
# Program:
#     Week 10, Map
#     Brother Ercanbrack, CS235
# Author:
#     Chad Smith
# Summary:
#     This usesthe MAP ADT from the standard template
#     library. It will count the usages of words in the files
#     To demonstrate this in the application you will be
#     prompted to enter a filename. We will read and sort
#     the data from the file into the map.
# Time:
#     10 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: pair.h week10.o
    g++ -o a.out week10.o
    tar -cf week10.tar *.h *.cpp makefile

##############################################################
# The individual components
#      lesson10.o     : the driver program
##############################################################
week10.o: pair.h week10.cpp
    g++ -c week10.cpp

