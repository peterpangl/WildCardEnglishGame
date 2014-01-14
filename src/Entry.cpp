#include "Entry.hpp"
#include "Base.hpp"

Entry::Entry()
{
	prefix = "";
	meaning = "";
	example = "";
}

Entry::~Entry()
{}

int Entry::set_prefix(const char* filename)
{
	int res = 1; // true
	int resp = 0;
	ifstream file;
	try
	{
		file.open(filename, ios::in);
	}
	catch(exception& e){
		cout << "In give_prefix:" << e.what() << endl;
	}

	do{
		cout << "Give the prefix:";

		getline(cin, prefix);

		if(check_string(prefix))
		{
			cout << "Invalid prefix contains ( !@#$%^&*()-=_+1234567890 )" << endl;
			continue;
		}
		// check if this prefix already exists
		if(srch_prefix(file, prefix)){
			cout << "Prefix: " << prefix << " exists." << endl;
			continue;
		}
		resp = sure();
	} while(!resp);

	file.close();
	return res;
}


int Entry::set_meaning()
{
	int res = 1; // true
	int resp = 0;

	do{
		cout << "Give the meaning:";

		getline(cin, meaning);
		if(check_string(meaning))
		{
			cout << "Invalid meaning, contains: !@#$%^&*()-=_+1234567890 " << endl;
			continue;
		}
		resp = sure();
	} while(!resp);
	return res;
}

int Entry::set_example()
{
	int res = 1; // true
	int resp = 0;
	do{
		cout << "Give the example:";

		getline(cin, example);
		if(check_string(example))
		{
			cout << "Invalid meaning, contains( !@#$%^&*()-=_+1234567890 )" << endl;
			continue;
		}
		resp = sure();
	} while(!resp);
	return res;
}


/*
 * Checks string for invalid chars: !@#$%^&*()_+-=
 * If contains any invalid char then returns 0
 */
int check_string(const string& str)
{
	char *str1 = new char [str.length()+1];
	strcpy (str1, str.c_str());
	char invalid[] = "!@#$%^&*()_+-=1234567890";
	int res = 1;	// invalid

	if( (strpbrk(str1, invalid) == NULL) ) // no invalid char
		res = 0;
	if(!str.compare("\n") || !str.compare("")){
		res = 1;
	}

	return res;
}


int sure(void)
{
	char sure;
	char yes = 'y';
	char no = 'n';
	do
	{
		cout << endl << "Are you sure?(y/n):";
		cin >> sure;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while(sure != yes && sure != no);
	if(sure == yes){
		return 1;	// yes
	}
	return 0; // no
}

int srch_prefix(ifstream& file, const string prefix)
{
	/*
	 * open file, getline, and check if the first word of line matches with the desired
	 */
	string sz;
	int res = 0; // unsuccessful search

	char *prfx  = new char [prefix.length()+1];
	strcpy(prfx, prefix.c_str());

	while(getline(file, sz)){
		size_t to = sz.find_first_of("\t");
		string s1 = sz.substr(0, to);

		if(!strcmp(prfx, s1.c_str())){
			return 1; // successful search
		}
	}
	return res;
}
