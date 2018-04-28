// Deck.h
// Declares a deck class that is filled with cards.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#pragma once


#include "PlayingCard.h"
#include "Hand.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
//forward declaration of hand so that deck can friend the << operator and pokerRank
class Hand;

class Deck {
	friend ostream &operator<<(ostream &, const Deck &);
	friend void operator<<(Hand &, Deck &);
	friend void dealFaceDown(Hand &, Deck &);
	friend void dealFaceUp(Hand &, Deck &);
	friend bool pokerRank(const Hand &, const Hand &);
private:
	vector<Card> deck;
public:
	Deck(char *);
	Deck();
	//No destructor is needed because the compiler will create one for us
	void load(char *);
	void shuffleDeck();
	size_t const sizeofDeck();
	void add_card(Card);

};

ostream &operator<<(ostream &, const Deck &);



