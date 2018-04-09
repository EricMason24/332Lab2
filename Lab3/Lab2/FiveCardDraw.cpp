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

int FiveCardDraw::before_Turn(Player & p) {
	string discardstr = "";
	string cardPos = "";
	cout << "Player's name: " << p.name << endl;
	cout << "Player's hand: " << p.playerHand << endl;
	cout << "Discard any Cards from hand? y/n ?" << endl;
	//accepts a cin argument (either y or n) and then starts the discard process
	getline(cin, discardstr);
	if (discardstr == "y") {
		vector<int> posVector;
		bool invalidResponse = true;
		//will continue prompting player for cards to discard until proper values have been entered
		while (invalidResponse) {
			cout << "enter valid card positions (0 - 4) to discard, with a space between each position" << endl;
			getline(cin, cardPos);
			istringstream iss(cardPos);
			string pos;
			invalidResponse = false;
			while (iss >> pos) {
				//if invalid response, reset the loop with an empty vector
				if (pos != "0" || pos != "1" || pos != "2" || pos != "3" || pos != "4") {
					invalidResponse = true;
					vector<int> empty;
					posVector = empty;
					cout << "Please enter a valid response" << endl;
					break;
				}
				//convert string to int and push to vector
				posVector.push_back(stoi(pos));
			}
			if (posVector.size() > 5) {
				invalidResponse = true;
				vector<int> empty;
				posVector = empty;
				cout << "Please less than 5 positions" << endl;
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
						cout << "Please do not repeate positions" << endl;
						break;
					}
				}
			}
		}

		//add cards to discard deck and then remove cards from player hand
		//done in two seperate loops because if they are in the same loop, the positions will change after removing cards from the playerHand, causing errors.
		for (size_t i = 0; i < posVector.size(); ++i) {
			discard.add_card(p.playerHand[i]);
		}
		for (size_t i = 0; i < posVector.size(); ++i) {
			p.playerHand.remove_card(i);
		}

	}
	return Success;
}

int FiveCardDraw::turn(Player & p) {
	bool deckEmpty = mainD.sizeofDeck() > 0;
	int cardsNeeded = 5 - p.playerHand.sizeOfHand();
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

int FiveCardDraw::after_Turn(Player & p) {
	cout << "Player's name: " << p.name << endl;
	cout << "Player's hand: " << p.playerHand << endl;
	return Success;
}

int FiveCardDraw::before_round() {
	return 0;
}

int FiveCardDraw::round() {
	return 0;
}

int FiveCardDraw::after_round() {
	return 0;
}