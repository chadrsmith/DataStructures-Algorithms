/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include "hash.h"

class SHash : public Hash <string> {
    
public:
    
    SHash(int numBuckets) throw (const char *) : Hash <string> (numBuckets) { }
    
    SHash(const SHash & rhs) throw(const char *) : Hash <string> (rhs) { }
    
    int hash(const string &element) const {     return element[0] % capacity(); }
};

void spellCheck();

#endif // SPELL_CHECK_H
