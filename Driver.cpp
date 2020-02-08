/**********************************************************************
** File: Driver.cpp
** Name: Junkyu Kwon
** CMSC 341 Project 5
** This file contains test drivers for Anahash.h file
**
***************************************************************************/

#include "Anahash.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {

  //Declare a Anahash object
  Anahash aNa( 1 << 16 );

  //Insert some examples
  aNa.insert("June");
  aNa.insert("Juen");
  aNa.insert("Crush");
  aNa.insert("Haven");
  aNa.insert("I did it");
  aNa.insert("it dId i");
  aNa.insert("Cat");
  aNa.insert("taC");
  aNa.insert("I am hungry");
  aNa.insert("h ma Iungyr");
  aNa.dump();

  cout << "Dump before getting file\n\n";

  //Code to get file
  string fileName = "anagrams_single.txt";
  ifstream myfile(fileName.c_str());

  if (myfile.is_open()) {
    string line;
    while (getline(myfile, line)) {
      if (line.size() > 0) {
	aNa.insert(line);
      }
    }
    myfile.close();
  }

  else {
    cout << "File " << fileName << " could not be opened\n";
    }

  aNa.dump();

  //Declare new Anahash object, and use copy constructor
  Anahash aNa2(aNa);

  cout << "Print out aNa2\n\n";
  aNa2.dump();

  //Declare new object aNa3
  Anahash aNa3( 1 << 16 );

  aNa3.insert("plush");
  aNa3.insert("lpuhs");
  aNa3.insert("time runs fast");
  aNa3.insert("runs time fast");
  aNa3.insert("Save time");

  cout << "Print out aNa3 \n\n";
  aNa3.dump();

  //Test out = operator
  aNa2 = aNa3;

  cout << "Print out aNa2 after operation\n";
  aNa2.dump();
}
