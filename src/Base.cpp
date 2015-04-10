#include "Base.hpp"
#include "Entry.hpp"


void Base::set_filename(const char* name)
{
	filename = name;
	//cout << "filename is: " << filename << endl;
}

const char* Base::get_filename()
{
	return filename;
}

/*
 * Checks if the specified file is empty.
 */
//test commit-merge
bool Base::file_is_empty(ifstream& file)
{
	bool empty = false;

	// count the entries of prefixes.txt
	string line;
	Entry e;

	while( !file.eof() ) {
			getline(file, line);
	}

	file.clear();
	file.seekg(0,ios::end);
	size_t size = file.tellg();
	//cout << " size: " << size << endl;
	if( size == 0 )
	{
		cout << "EMPTY FILE" << endl;
		empty = true;
	}
	return empty;
}


/* This function writes the names of columns:
 * Prefix Meaning Examples of the wildcard file,
 * the first time we create the file
 */
void Base::make_columns(ofstream& file)
{
	cout << "Base::make_columns" << endl;
	file << "Prefix" << "\t" << "Meaning"
		 << "\t" << "Example" << endl;
}

/*
 * insert a new entry in file
 */
int Base::insert_entry(const char* filename, string prefix, string meaning, string example)
{

	int res = 1; //success
	ofstream file;

	try{
		file.open(filename, ios::app);
		cout 	<<"prefix:" <<  prefix  << endl
				<<"meaning:" << meaning << endl
				<<"example:" << example << endl;
		if(file.is_open())
		{
			file 	<< prefix <<  "\t"
					<< meaning << "\t"
					<< example << endl;
			file.flush();
		}
		else
		{
			cout << "File is closed" << endl;
		}
	}
	catch(exception& e){
		cout << "Exception upon inserting in file: " << e.what() << endl;
		res = 0;
	}
	return res;
}

void Base::delete_entry(const char* file_name)
{
	string prefix;
	ifstream file;
	int resp;
	int flag_er = 0;

	try{
		create_backup(file_name);
		file.open(file_name, ios::in);

		/* Move all entries in vector.
		 * Handle the entries in vector.
		 * Copy vector entries in file.
		 */
		vector<string> data;
		string temp;

		//transfer file entries in vector
		while(!file.eof() )
		{
			getline(file, temp);
			data.push_back(temp);
		}

		cout << "Give a prefix to delete from database:" << endl;
		getline(cin, prefix);
		do{
			resp = sure();
		}while(!resp);

		// delete operation in vector
		for(int i = 0; i < (int)data.size(); i++)
		{
			if(data[i].substr(0, prefix.length()) == prefix){
				cout << "Prefix \"" << prefix << "\" found and erased!" << endl;
				flag_er = 1;
				data.erase(data.begin()+i);
			}
		}
		if(!flag_er)
			cout << "Prefix \"" << prefix << "\" not found!"<< endl;
		//write the new prefixes entries
		ofstream out(filename, ios::out | ios::trunc);
		for(vector<string>::const_iterator i = data.begin(); i != data.end(); ++i)
		{
			out << *i << endl;
		}
		out.flush();
		out.close();
	}
	catch(exception& e){
		cout << "Error at opening file" << e.what() << endl;
	}
}

void Base::create_backup(const char* file_name)
{
	ifstream from_file;

	from_file.open(file_name, ios::in);
	const char* suffix =".bak";
	char file_bak[130] ="";
	strcat(file_bak, file_name);
	strcat(file_bak, suffix);
	ofstream to_file(file_bak, ios::out | ios::trunc);

	string temp;

	cout << "Creating backup file" << endl;
	while(!from_file.eof())
	{
		getline(from_file, temp);
		to_file << temp << endl;
	}
	to_file.flush();
	to_file.close();
	from_file.close();
	cout << "BackUp file Created." << endl;
}


void Base::manage(const char* file_name)
{
	string choice;
	do{
		cout << "SubMenu:" << endl
			 << "1 Insert prefix entry" << endl
			 << "2 Delete prefix entry" << endl
			 << "3 Search prefix" << endl
			 << "4 Create a back up" << endl
			 << "5 Return to main Menu" << endl;

		getline(cin, choice);
		int ch = atoi(choice.c_str());
		switch(ch){
			// insert a prefix along its meaning and its example
			case 1:
			{
				Entry e;
				if(e.set_prefix(file_name))
					if(e.set_meaning())
						if(e.set_example()) {
							if(Base::insert_entry(file_name, e.prefix, e.meaning, e.example))
								cout << "Successful insertion" << endl <<endl;
							else
								cout << "Unsuccessful insertion" << endl;
						}
				break;
			}
			case 2:
			{
				// Delete a prefix entry
				delete_entry(file_name);
				break;
			}
			case 3:
			{
				string prefix;
				ifstream file;
				try{
					file.open(file_name, ios::in);
					int flag = 0;
					do
					{
						cout << "Give the prefix:";
						getline(cin, prefix);
						if(check_string(prefix))
						{
							cout << "Invalid prefix ( !@#$%^&*()-=_+1234567890 )" << endl;
							flag = 1;
							continue;
						}
						if(srch_prefix(file, prefix))
							cout << "Prefix \"" << prefix << "\" exists"<< endl;
						else
							cout << "Prefix \"" << prefix << "\" doesn't exist" << endl;
					}while(flag);
				}
				catch(exception& e){
					cerr << "Error upon searching entry: " << e.what() << endl;
				}
				break;
			}
			case 4:
			{
				create_backup(file_name);
				break;
			}
			default:
				break;
		}

	}while(choice.compare("5") != 0);
}
