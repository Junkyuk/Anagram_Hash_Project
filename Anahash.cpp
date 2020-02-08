/***********************************************************************
** File: Anahash.cpp
** Name: Junkyu Kwon
** CMSC 341 Project 5
** Email: junkyuk1@umbc.edu
** This file contains the member functions of Anahash.h
**
***************************************************************************/
#include <iostream>
#include "Anahash.h"

//Anahash(int)
//Constructor of Anahash object
Anahash::Anahash(int htSize) {

  //Error check for range of the htSize
  if (htSize > HT_SIZE_LIMIT || htSize < 1) {
    throw std::range_error("htSize cannot be greater than HT_SIZE_LIMIT or less than 1 \n");
  }
  
  m_htSize = htSize;
  m_ht = new set<string>[m_htSize];
}

//Anahash(const Anahash&)
//Copy constructor for Anahash object
Anahash::Anahash(const Anahash& rhs) {
  m_htSize = rhs.m_htSize;
  m_ht = new set<string>[m_htSize];

  //for loop to plug the rhs into this object
  for (int i = 0; i < m_htSize; i++) {
    m_ht[i] = rhs.m_ht[i];
  }
}

//operator=(const Anahash&)
//overloaded operator for Anahash
Anahash& Anahash::operator=(const Anahash& rhs) {
  delete[] m_ht;

  m_htSize = rhs.m_htSize;
  m_ht = new set<string>[m_htSize];

  //for loop to plug the rhs into this object
  for (int i = 0; i < m_htSize; i++) {
    m_ht[i] = rhs.m_ht[i];
  }
}

//~Anahash()
//Destructor of Anahash object
Anahash::~Anahash() {
  delete [] m_ht;
}

//insert(string)
//Insert a string into m_ht array
bool Anahash::insert(string line) {
  unsigned int hashVal;
  hashVal = anaHash(line);

  //If m_ht[hashVal] exists
  if (1) {

    //If m_ht[hashVal] has some strings in it
    if (m_ht[hashVal].size() > 0) {

      //If m_ht[hashVal] has the string in it
      if (search(line) == true) {
	//Do nothing

	return false;
      }

      //Otherwise, sort, compare, and plug in
      else {
	string newstr = line;
	sort(newstr.begin(), newstr.end());

	string cmstr = *m_ht[hashVal].begin();
	sort(cmstr.begin(), cmstr.end());

	//If it is a anagram of m_ht[hashVal]
	if (newstr.compare(cmstr) == 0) {
	  m_ht[hashVal].insert(line);
	  return true;
	}

	//If it is not a anagram of m_ht[hashVal], do linear probing
	else {
	  int linprob = hashVal;
	  int i = 0;
	  
	  while (i = 0) {
	    string newstr = line;
	    string cmstr = *m_ht[linprob].begin();

	    //sort each strings to compare
	    sort(newstr.begin(), newstr.end());
	    sort(cmstr.begin(), cmstr.end());

	    //If find anagram after linear probing
	    if (newstr.compare(cmstr) == 0) {
	      m_ht[linprob].insert(line);
	      linprob++;
	    }

	    //If the set is empty after linear probing
	    else if (m_ht[linprob].empty()) {
	      m_ht[linprob].insert(line);
	      linprob++;
	    }
	    
	    else {
	      //Go over the loop again
	    }
	  }
	}
      }
    }

    //Otherwise, push the string in it
    else {
      m_ht[hashVal].insert(line);

      return true;
    }
  }

  //Otherwise, print error
  else {
    cout << "Cannot add string: Error\n";

    return false;
  }
}

//search(string)
//See if there is the string or not
bool Anahash::search(string line) {
  unsigned int hashVal = anaHash(line);

  if (m_ht[hashVal].count(line) > 0) {
    return true;
  }

  else {
    return false;
  }
}

//getAnagrams(string)
//return sets if the set has desired string
set<string> Anahash::getAnagrams(string line) {

  unsigned int hashVal = anaHash(line);
  
  //if line is in the table
  if (search(line) == true) {
    return m_ht[hashVal];
  }

  //if not in the table, return empty set
  else {
    set<string> emptySet;
    return emptySet;
  }
}

//void dump()
//
void Anahash::dump() {
  for (int i = 0; i < m_htSize; i++) {
    //Print out only if m_ht[] is not empty
    if (!m_ht[i].empty()) {

      std::cout << i << '\n';
      
      for (std::set<string>::iterator it = m_ht[i].begin(); it != m_ht[i].end(); ++it) {
	std::cout << ' ' << *it;
	std::cout << '\n';
      }

      cout << '\n';
    }
  }
}


//Hash function goes here

//unsigned int anaHash(string)
//Hash function. Compute hash value by adding ASCII codes of each members of string
unsigned int Anahash::anaHash(string line) {
  char *c_line;
  int ascii = 0;

  int count = 0;
  int cstlen = 0;
  
  c_line = new char[line.length() + 1];

  //Convert string line to Cstring
  for (int index = 0; index < line.length(); index++) {
    c_line[index] = line[index];
  }

  c_line[line.length() + 1] = '\0';

  //remove spaces from the line
  for (int i = 0; c_line[i]; i++) {
    if (c_line[i] != ' ') {
      c_line[count++] = c_line[i];
    }
  }

  //Count Cstring length
  while (c_line[cstlen] != '\0') {
    cstlen++;
  }
  
  //Calculate Ascii value
  for (int i = 0; i < cstlen; i++) {
    ascii = ascii + (int)c_line[i];
  }

  //Release c_line
  delete c_line;

  return ascii;
}
