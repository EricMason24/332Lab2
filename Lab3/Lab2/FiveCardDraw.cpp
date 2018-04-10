/*
description
*/

#include "stdafx.h"

#include "Deck.h"
#include "PlayingCard.h"
#include "Player.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

FiveCardDraw::FiveCardDraw() : cDealer(0) {
	for (int s = Card::diamonds; s <= Card::clubs; ++s) {
		for (int r = Card::two; r <= Card::ace; ++r) {
			Card c((Card::Suits)s, (Card::Ranks)r);
			mainD.add_card(c);
		}
	}
}

int FiveCardDraw::before_turn(Player & p) {
	string discardstr = "";
	string cardPos = "";
	cout << "Player's name: " << p.name << endl;
	cout << "	Hand: " << p.playerHand << "\n" << endl;
	cout << "Discard any Cards from hand? y/n ?" << endl;
	//accepts a cin argument (either y or n) and then starts the discard process
	getline(cin, discardstr);
	if (discardstr == "y") {
		vector<int> posVector;
		bool invalidResponse = true;
		//will continue prompting player for cards to discard until proper values have been entered
		while (invalidResponse) {
			cout << "Enter valid card positions (0 - 4) to discard, with spaces in between." << endl;
			getline(cin, cardPos);
			istringstream iss(cardPos);
			string pos;
			invalidResponse = false;
			while (iss >> pos) {
				//if invalid response, reset the loop with an empty vector
				if (pos != "0" && pos != "1" && pos != "2" && pos != "3" && pos != "4") {
					invalidResponse = true;
					vector<int> empty;
					posVector = empty;
					cout << "Please enter a valid response." << endl;
					break;
				}
				//convert string to int and push to vector
				posVector.push_back(stoi(pos));
			}
			if (posVector.size() > 5) {
				invalidResponse = true;
				vector<int> empty;
				posVector = empty;
				cout << "Please fewer than 5 positions." << endl;
				break;
			}
			//check for repeated positions in vector, and reset loop if there are any
			bool repeateFound = false;
			for (size_t i = 0; i < posVector.size(); ++i) {
				if (repeateFound) {
					break;
				}
				for (size_t j = i+1; j< posVector.size(); ++j) {
					if (posVector[i] == posVector[j]) {
						invalidResponse = true;
						repeateFound = true;
						vector<int> empty;
						posVector = empty;
						cout << "Please do not repeat positions." << endl;
						break;
					}
				}
			}
		}
		//add cards to discard deck and then remove cards from player hand
		//done in two seperate loops because if they are in the same loop, the positions will change after removing cards from the playerHand, causing errors.
		for (size_t i = 0; i < posVector.size(); ++i) {
			discard.add_card(p.playerHand[posVector[i]]);
		}
		sort(posVector.begin(), posVector.end());
		for (auto i = posVector.rbegin(); i != posVector.rend(); ++i) { // iterate backwards so positions don't change mid-deletion
			p.playerHand.remove_card(*i);
		}
	}
	cout << endl;
	return Success;
}

int FiveCardDraw::turn(Player & p) {
	bool deckEmpty = mainD.sizeofDeck() == 0;
	int cardsNeeded = 5 - p.playerHand.sizeOfHand();
	if (deckEmpty) {
		discard.shuffleDeck();
	}
	for (int i = 0; i < cardsNeeded; ++i) {
		if (!deckEmpty) {
			p.playerHand << mainD;
			if (mainD.sizeofDeck() == 0) {
				deckEmpty = true;
				discard.shuffleDeck();
			}
		}
		else {
			if (discard.sizeofDeck() == 0) {
				return bothDecksEmpty;
			}
			p.playerHand << discard;
		}
	}
	return Success;
}

int FiveCardDraw::after_turn(Player & p) {
	cout << "Player's name: " << p.name << endl;
	cout << "	Hand: " << p.playerHand << "\n" << endl;
	return Success;
}

int FiveCardDraw::before_round() {
	mainD.shuffleDeck();
	cout << (*players[cDealer % players.size()]).name << " is dealing...\n" << endl;
	for (int i = 0; i < 5; ++i) {
		for (size_t j = 0; j < players.size(); ++j) {
			size_t pos = (cDealer + 1 + j) % players.size();
			(*players[pos]).playerHand << mainD;
		}
	}
	for (size_t j = 0; j < players.size(); ++j) {
		size_t pos = (cDealer + 1 + j) % players.size();
		before_turn(*players[pos]);
	}
	return 0;
}

int FiveCardDraw::round() {
	for (size_t j = 0; j < players.size(); ++j) {
		size_t pos = (cDealer + 1 + j) % players.size();
		int res = turn(*players[pos]);
		if (res != 0) {
			return res;
		}
		after_turn(*players[pos]);
	}
	return 0;
}

int FiveCardDraw::after_round() {
	winsLosses();
	recycleDeck();
	askLeave();
	askJoin();
	if (players.size() != 0) {
		cDealer = (cDealer + 1) % players.size();
	}
	return 0;
}

void FiveCardDraw::winsLosses() {
	vector<shared_ptr<Player>> temp = players;
	sort(temp.begin(), temp.end(), poker_rank);
	for (size_t i = 0; i < temp.size(); ++i) {
		++(*temp[i]).losses;
	}
	++(*temp[0]).wins;
	--(*temp[0]).losses;
	size_t i = 0;
	while (!pokerRank((*temp[i]).playerHand, (*temp[i + 1]).playerHand)) {
		++(*temp[i + 1]).wins;
		--(*temp[i + 1]).losses;
		++i;
		if (i >= temp.size() - 1) {
			break;
		}
	}
	for (i = 0; i < temp.size(); ++i) {
		cout << "Player's name: " << (*temp[i]).name <<
			endl << "	Wins: " << (*temp[i]).wins <<
			endl << "	Losses: " << (*temp[i]).losses <<
			endl << "	Hand: " << (*temp[i]).playerHand << "\n" << endl;
	}
}

bool poker_rank(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	if (p1 == nullptr) {
		return false;
	}
	else if (p2 == nullptr) {
		return true;
	}
	else {
		return pokerRank((*p1).playerHand, (*p2).playerHand);
	}
}

void FiveCardDraw::recycleDeck() {
	while (discard.sizeofDeck() > 0) { // add all cards in discard deck to first player's hand
		(*players[0]).playerHand << discard;
	};
	for (size_t i = 0; i < players.size(); ++i) { // loop through players
		for (size_t j = 0; j < (*players[i]).playerHand.sizeOfHand(); ++j) { // add player's hand to main deck
			mainD.add_card((*players[i]).playerHand[j]);
		}
		while ((*players[i]).playerHand.sizeOfHand() != 0) { // remove all cards from player's hand
			(*players[i]).playerHand.remove_card(0);
		}
	}
}

void FiveCardDraw::askLeave() {
	string s = "";
	cout << "Would any players like to leave the game at this point? y/n ?" << endl;
	getline(cin, s);
	while (s != "n") {
		if (s == "y") {
			cout << "Insert player's name, or 'n' to bypass: " << endl;
			getline(cin, s);
			while (s != "n") {
				bool found = false;
				for (size_t i = 0; i < players.size(); ++i) {
					if ((*players[i]).name == s) {
						found = true;
						ofstream ofs(s + ".txt");
						ofs << (*players[i]);
						ofs.close();
						auto iter = players.begin() + i;
						players.erase(iter);
						cout << "Player '" << s << "' has left the game." << endl;
						break;
					}
				}
				if (!found) {
					cout << "Player '" << s << "' not found." << endl;
				}
				cout << "Insert player's name, or 'n' to bypass: " << endl;
				getline(cin, s);
			}
		}
		cout << "Would any players like to leave the game at this point? y/n ?" << endl;
		getline(cin, s);
	}
	cout << endl;
}

void FiveCardDraw::askJoin() {
	string s = "";
	cout << "Would any players like to join the game at this point? y/n ?" << endl;
	getline(cin, s);
	while (s != "n") {
		if (s == "y") {
			cout << "Insert player's name, or 'n' to bypass: " << endl;
			getline(cin, s);
			while (s != "n") {
				try {
					addPlayer(s);
				}
				catch (errors & e) {
					if (e == alreadyPlaying) {
						cout << "Player already in game." << endl;
					}
				}
				cout << "Insert player's name, or 'n' to bypass: " << endl;
				getline(cin, s);
			}
		}
		cout << "Would any players like to join the game at this point? y/n ?" << endl;
		getline(cin, s);
	}
	cout << endl;
}