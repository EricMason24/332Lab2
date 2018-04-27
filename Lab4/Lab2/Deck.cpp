// Deck.cpp
// Defines a deck class that is filled with cards.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>

using namespace std;

//constructor definiton for deck that takes in a file
Deck::Deck(char * file) {
	try {
		load(file);
	}
	catch (errors i) {
		if (i == cannotOpenTextFile) {
			//assign deck to an empty vector since the file could not be opened
			vector<Card> emptyDeck;
			deck = emptyDeck;
		}
		throw(cannotOpenTextFile);
	}
}

//default constructor
vector<Card> emptyDeck2;
Deck::Deck() : deck(emptyDeck2) {};

void Deck::add_card(Card c) {
	c.isFaceUp = true;
	deck.push_back(c);
}


//given a file name, will parse the file for valid cards and add them to the deck
void Deck::load(char * file) {
	ifstream ifs;
	ifs.open(file);
	if (!ifs.is_open()) {
		cout << "DeckHandLab2" << " cannot open source file " << file << " to read from" << endl;
		throw(cannotOpenTextFile);
	}
	else {
		string definedCard, line;
		while (getline(ifs, line)) {
			istringstream iss(line);
			while (iss >> definedCard) {
				//if a '//' is detected, break the current iteration of the while loop and continue onto the next line
				if (definedCard == "//") {
					break;
				}
				int size = definedCard.length();
				//check if length of input is the right length
				if (size == 2 || size == 3) {
					char suit = definedCard.at(size - 1);
					suit = char(tolower(suit));
					Card::Suits inputS = getSuit(suit);
					Card::Ranks inputR;
					if (size == 3) {
						string s = definedCard.substr(0, 2);
						inputR = getRankLength3(s);
					}
					else {
						char rank = definedCard.at(0);
						rank = char(tolower(rank));
						inputR = getRank(rank);
					}
					if (inputR == Card::Ranks::noRank || inputS == Card::Suits::noSuit) {
						//not valid card input, ignore
					}
					else {
						Card c;
						c.rank = inputR;
						c.suit = inputS;
						//add the defined card to the deck
						deck.push_back(c);
					}
				}
			}
		}
	}
}

//takes the deck and uses the shuffle algorithm to randomize the order of the cards in the deck
void Deck::shuffleDeck() {
	//creating a random number generator, code found here: http://en.cppreference.com/w/cpp/algorithm/random_shuffle
	random_device rd;
	mt19937 g(rd());
	shuffle(deck.begin(), deck.end(), g);
}

//function that returns the current size of the deck
size_t const Deck::sizeofDeck() {
	return deck.size();
}

//overrides the << operator in order to print out all of the cards in the deck
ostream &operator<< (ostream &out, const Deck &d) {
	for (size_t i = 0; i < d.deck.size(); ++i) {
		Card c;
		c = d.deck.at(i);
		//getCard is taken from PlayingCard.h, which will just return a string of the appropiate card value
		string s = getCard(c);
		out << s << endl;
	}
	return out;
}
