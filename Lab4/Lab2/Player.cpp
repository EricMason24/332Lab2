// Player.cpp
// Defines a player struct which has a hand, number of wins and losses, and a name.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Player.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

//global variables to be accessed in player constructor logic
string n = "name";
string w = "wins";
string l = "losses";
string c = "chips";

//constructor for a Player given a file, it will open the file and parse wins and losses
Player::Player(char * inputName) : name(inputName), chips(20), wins(0), losses(0), playerHand(), bestHand(),hasFolded(false), outOfChips(false), currBet(0) {
	ifstream ifs;
	string fileName(inputName);
	ifs.open(fileName + ".txt");
	if (!ifs.is_open()) {
		cout << "Cannot open source file '" << inputName << ".txt'.\n" << endl;
	}
	else {
		string line, word, wordtype;
		bool nCheck = false, wCheck = false, lCheck = false, cCheck = false;
		while (getline(ifs, line)) {
			istringstream iss(line);
			if (!(iss >> word >> wordtype)) {
				wins = 0;
				losses = 0;
				chips = 20;
				return;
			}
			if (word == n) {
				name = wordtype;
				nCheck = true;
			}
			else if (word == w) {
				wins = stoi(wordtype);
				wCheck = true;
			}
			else if (word == l) {
				losses = stoi(wordtype);
				lCheck = true;
			}
			else if (word == c) {
				chips = stoi(wordtype);
				cCheck = true;
			}
		}
		//name, wins and losses don't exist in file, reset wins and losses
		if (!nCheck || !wCheck || !lCheck || !cCheck) {
			wins = 0;
			losses = 0;
			chips = 20;
		}
	}
};

ostream & operator<<(ostream & o, const Player & p) {
	o << n << " " << p.name << endl << w << " " << p.wins << endl << l << " " << p.losses << endl << c << " " << p.chips << endl;
	return o;
}