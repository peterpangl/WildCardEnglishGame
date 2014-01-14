#include "Player.hpp"
#include "Base.hpp"
#include <string>
#include <iostream>

/*  A player is a real Player who plays with prefixes!
	There is Prefix - Meaning - Example
	One kind of playing is:
	the meaning is being appeared and you have to give the right prefix so as to gain points.
	There is no negative point in case of invalid value.
*/
vector<string> entry;
vector<string> prefix;
vector<string> meaning;

void Player::play(const char* filename){
	cout << "Username: ";

	string playerName;
	getline(cin, this->playerName);
	cout << "Your name: " << this->playerName << endl;
	cout << "Your score: " << this->score << endl;

	this->start_playing(filename,this->playerName, this->score);
}


void construct_prefix_meaning_vectors(vector<string> en)
{
	vector<string>::iterator it = en.begin();
	string delimiter_tab = "\t";
	string token1, token2;

	while(it != en.end())
	{
		token1 = *it;
		prefix.push_back(token1.substr(0, token1.find(delimiter_tab)));
		token2 = token1.substr(token1.find(delimiter_tab) + 1);
		meaning.push_back(token2.substr(0, token2.find(delimiter_tab)));
		++it;
	}

	/*
	 *for(int i = 0; i < meaning.size(); i++){
		cout << "meaning: " << meaning[i] << endl;
	}*/
}


void Player::find_meaning()
{
	/*
	 * we will show the meaning and we will ask the prefix.
	 * if it's a match then we raise the score. If not show the right and go to the next one.
	 */
	cout << "\nPress enter to start!" << endl;
	cin.get();
	int n = prefix.size();
	string input;

	for(int i = 1; i < n; i++)
	{
		cout << "\nWhich is the meaning of prefix: '" << prefix[i] << "' ?-------------> " ;
		getline(cin, input);

		if(input.compare(meaning[i]) != 0)
		{
			cout << "Wrong. Right answer is:" << meaning[i] << endl;
			continue;
		}
		else
		{
			cout << "That's right!" << endl;
			this->score++;
		}
	}
	cout << this->playerName << ", your score is: " << this->score << " out of " << n-1 << endl;
}


void Player::find_prefix()
{
	/*
	 * we will show the meaning and we will ask the prefix.
	 * if it's a match then we raise the score. If not show the right and go to the next one.
	 */
	cout << "Press a key to start!" << endl;
	cin.get();
	int n = prefix.size();
	string input;

	for(int i = 1; i < n; i++)
	{
		cout << "\nWhich is the prefix of meaning: '" << meaning[i] << "' ?-------------> " ;
		getline(cin, input);

		if(input.compare(prefix[i]) != 0)
		{
			cout << "Wrong. Right answer is:" << prefix[i] << endl;
			continue;
		}
		else
		{
			cout << "That's right!" << endl;
			this->score++;
		}
	}
	cout << this->playerName << ", your score is: " << this->score << " out of " << n-1 << endl;
}


/*
 * Load the entries of prefixes file in a vector.
 */

void Player::start_playing(const char* filename, string name, int score)
{
	/* handle file */
	ifstream file;
	file.open(filename, ios::app | ios::in);

	if(Base::file_is_empty(file)) {
		cout << "File is empty.Suggest you to manage the file, import entries and try again to play." << endl;
		return;
	}
	file.close();

	// vector<string> rest_meaning_example;
	file.open(filename, ios::app | ios::in);
	string temp;

	// transfer file entries in vector
	while(!file.eof())
	{
		getline(file, temp, '\n');
		entry.push_back(temp);
	}

	construct_prefix_meaning_vectors(entry);

	string choice;
	do{
		cout << "Make a choice: " << endl;
		cout << "1.Guess the meaning given the prefix." << endl;
		cout << "2.Guess the prefix given the meaning." << endl;
		cout << "3.Exit" << endl;

		// convert string to int
		getline(cin, choice);
		int ch = atoi(choice.c_str());
		const char* cstr = choice.c_str();
		//.. checks for invalid input: such as: 2 3
		for(unsigned int i = 0; i < choice.length(); i++) {
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
				cout << "1.Guess the meaning given the prefix." << endl;
				this->score = 0;
				this->find_meaning();
				cout << "Play again? " << endl;
				break;
			}
			case 2:
			{
				cout << "2.Guess the prefix given the meaning." << endl;
				this->score = 0;
				this->find_prefix();
				cout << "Play again? " << endl;
				break;
			}
			case 3:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}while(choice.compare("3") != 0);
}
