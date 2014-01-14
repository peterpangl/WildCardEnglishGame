#ifndef BASE_HPP_
#define BASE_HPP_

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

class Base{

public:

	void make_columns(ofstream&);
	bool file_is_empty(ifstream&);
	void manage(const char* filename);
	int insert_entry(const char*, string, string, string);
	void delete_entry(const char*);
	void search_entry(const char*);
	void create_backup(const char*);
	void set_filename(const char* name);
	const char* get_filename();

private:
	const char* filename;
};

#endif
