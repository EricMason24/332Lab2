#pragma once
 
#include <string>
#include "Deck.h"

using namespace std;

struct Player {
	string name;
	Hand playerHand;
	unsigned int wins;
	unsigned int losses;
	Player(char *);
};

ostream & operator<< (ostream &, const Player &);