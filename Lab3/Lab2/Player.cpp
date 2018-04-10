// Player.cpp : Implements the struct that represents a player in a poker game
// Created by Eric Mason on 4/4/2018

#include "stdafx.h"
#include "Deck.h"
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

//constructor for a Player given a file, it will open the file and parse wins and losses
Player::Player(char * inputName) : name(inputName), wins(0), losses(0), playerHand() {
	ifstream ifs;
	string fileName(inputName);
	ifs.open(fileName + ".txt");
	if (!ifs.is_open()) {
		cout << "Cannot open source file '" << inputName << "'." << endl;
	}
	else {
		string line, word, wordtype;
		bool nCheck = false, wCheck = false, lCheck = false;
		while (getline(ifs, line)) {
			istringstream iss(line);
			if (!(iss >> word >> wordtype)) {
				wins = 0;
				losses = 0;
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
		}
		//name, wins and losses don't exist in file, reset wins and losses
		if (!nCheck || !wCheck || !lCheck) {
			wins = 0;
			losses = 0;
		}
	}
};

ostream & operator<<(ostream & o, const Player & p) {
	o << n << " " << p.name << " " << w << " " << p.wins << " " << l << " " << p.losses << endl;
	return o;
}