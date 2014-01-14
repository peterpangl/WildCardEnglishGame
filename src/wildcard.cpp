#include "Entry.hpp"
#include "Base.hpp"
#include "Player.hpp"
#include <cstdlib>

/* Menu:
* The Menu is divided in 3 categories:
* 1 Play:
*	Guess the prefix given the meaning and vice versa
*
* 2 Manage the base/file:
*
* 	2.1 Insert a new prefix entry along its meaning and an example
* 	2.2 Search for a prefix entry in the file
* 	2.3 Delete a prefix entry from the file
* 	2.4 Create a back up of the file
*
* 3 Exit from the menu
*
*/

int main(int argc, char *argv[])
{
	// stream to file
	ifstream file;
	Base dataBase;
	Player player;

	/*if(argc == 1) {
		cout << "You must provide the prefix file directory." << endl;
		return 0;
	}
	dataBase.set_filename(argv[1]);*/

	dataBase.set_filename("D://EclipseWorkspace//wildcard//src//prefixes.txt");

	try{
		file.open(dataBase.get_filename(), ios::app | ios::in);

		// if the file that you wish to create/read/write is empty, then
		// write the column's name: Prefix, Meaning, Example
		// otherwise these columns already exist.
		if(dataBase.file_is_empty(file))
		{
			file.close();
			ofstream file;
			file.open(dataBase.get_filename(), ios::app | ios::out);
			cout <<" File is Empty...Let's make some columns" << endl;
			dataBase.make_columns(file);
			file.flush();
			file.close();
		}
	}
	catch(exception& e){
		cout <<"Exception: " << e.what() << endl;
	}

	string choice;
	do
	{
		cout << "Menu:" << endl
			 << "1 Play" << endl
			 << "2 Manage file (insert prefix meaning example)" << endl
			 << "3 Exit" << endl;

		// convert string to int
		getline(cin, choice);

		int ch = atoi(choice.c_str());

		const char* cstr = choice.c_str();
		//.. checks for invalid input: such as: 2 3
		for(unsigned int i = 0; i < choice.length(); i++)	{
			if(cstr[i] == ' ') {
				for(unsigned int j = i; j < choice.length(); j++) {
					if(cstr[j] != ' ') {
						cout << "INVALID INPUT!!!" << endl;
						ch = 100;
					}
				}
			}
		}

		switch(ch)
		{
			case 1:
			{
				// let's start a game
				player.play(dataBase.get_filename());
				break;
			}
			case 2:
			{
				// manage the file-base
				dataBase.manage(dataBase.get_filename());
				break;
			}
			case 3:
			{
				cout <<endl << "GoodBye and have fun" << endl;
				break;
			}
			default:
				cout << "Invalid choice!" << endl;
		}
	} while(choice.compare("3") != 0);

	return 0;
}
