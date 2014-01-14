#ifndef ENTRY_HPP_
#define ENTRY_HPP_

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <stdlib.h>
#include <string>
#include <limits>
#include <exception>
#include <stdio.h>
#include <vector>


using namespace std;

class Entry
{

public:
	string prefix;
	string meaning;
	string example;

	int set_prefix(const char*);	// filename as argument
	int set_meaning();
	int set_example();

	Entry();
	~Entry();
};


int check_string(const string&);
int sure(void);
int srch_prefix(ifstream& , const string);


#endif /* ENTRY_HPP_ */
