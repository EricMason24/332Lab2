// Player.h
// Declares a player struct which has a hand, number of wins and losses, and a name.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

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