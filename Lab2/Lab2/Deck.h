//Deck declarations which declares a deck class that is filled with cards
#pragma once


#include "PlayingCard.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
//forward declaration of hand so that deck can friend the << operator and pokerRank
class Hand;

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


class Hand {
	friend ostream &operator<<(ostream &, const Hand &);
	friend void operator<<(Hand &, Deck &);
	friend bool pokerRank(const Hand &, const Hand &);
	friend pokerHands getPRank(const Hand &, Pair &, Pair &);
private:
	vector<Card> cards;
public:
	Hand();
	Hand(const Hand &);
	//No destructor is needed because the compiler will create one for us
	void operator= (const Hand &);
	size_t sizeOfHand();
	bool operator== (const Hand &) const;
	bool operator< (const Hand &) const;
	const string toString();
	Card operator[] (size_t);
	void remove_card(size_t);
};

ostream &operator<<(ostream &, const Hand &);

void operator<<( Hand &, Deck &);

pokerHands getPRank(const Hand &, Pair &, Pair &);

bool isFlush(const vector<Card> &);

bool isStraight(const vector<Card> &);

bool pokerRank(const Hand &, const Hand &);