//Deck declarations which declares a deck class that is filled with cards
#pragma once


#include "PlayingCard.h"
#include <vector>
#include <string>
#include <iostream>
#include "Hand.h"

using namespace std;
//forward declaration of hand so that deck can friend the << operator and pokerRank


class Deck {
	friend ostream &operator<<(ostream &, const Deck &);
	friend void operator<<(Hand &, Deck &);
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
enum struct pokerHands { noRank, Pair, twoPair, threeOKind, straight, flush, fullHouse, fourOKind, straightF };



ostream &operator<<(ostream &, const Hand &);

void operator<<( Hand &, Deck &);



bool isFlush(const vector<Card> &);

bool isStraight(const vector<Card> &);

bool pokerRank(const Hand &, const Hand &);