###############################################################
# Program:
#     Week 12, Hash
#     Brother Ercanrack, CS235
# Author:
#     Chad Smith
# Summary:
#     ADT of the hash data type. it uses the linked list.
#     The application demonstrates it's functionability.
###############################################################

##############################################################
# The main rule
##############################################################
a.out: week12.o spellCheck.o
	g++ -o a.out week12.o spellCheck.o -g
	tar -cf week12.tar *.h *.cpp makefile

##############################################################
# The individual components
#      week12.o     : the driver program
#      spellCheck.o   : the spell-check program and driver
##############################################################
week12.o: hash.h week12.cpp list.h
	g++ -c week12.cpp -g

spellCheck.o: hash.h spellCheck.h spellCheck.cpp
	g++ -c spellCheck.cpp -g

