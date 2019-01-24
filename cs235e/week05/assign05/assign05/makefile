###############################################################
# Program:
#     Week 05, SET
#     Brother Ercanbrack, CS235
# Author:
#     Chad Smith
# Summary:
#     An ADT similar to the Set data structure that is found in
#     the standard library. It adds items to the Set and orders
#     them in ascending order. goFish.cpp is an application that
#     demonstrates the functionability of the Set data structure.
# Time:
#     12.0 hours
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week05.o goFish.o card.o
	g++ -o a.out week05.o goFish.o card.o -std=c++11
	tar -cf week05.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week05.o       : the driver program
#      goFish.o       : the logic for the goFish game
#      card.o         : a single playing card
##############################################################
week05.o: set.h goFish.h week05.cpp
    g++ -c week05.cpp

goFish.o: set.h goFish.h goFish.cpp card.h
    g++ -c goFish.cpp

card.o: card.h card.cpp
	g++ -c card.cpp
