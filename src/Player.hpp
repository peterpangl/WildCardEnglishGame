#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <iostream>
#include <string>
#include <stdio.h>
#include "Base.hpp"

using namespace std;



class Player : public Base {

public:
	string playerName;
	int score;
	void play(const char *);
	void start_playing(const char*,string , int );
	void find_meaning();
	void find_prefix();
	Player(){
		score = 0;
	}
	//~Player();


};

#endif
