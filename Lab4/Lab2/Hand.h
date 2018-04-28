// Hand.h
// Declares a hand class that contains five cards.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#pragma once


#include "PlayingCard.h"
#include "Deck.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;
class Deck;
enum struct pokerHands { noRank, Pair, twoPair, threeOKind, straight, flush, fullHouse, fourOKind, straightF };


class Hand {
	friend ostream &operator<<(ostream &, const Hand &);
	friend void operator<<(Hand &, Deck &);
	friend bool pokerRank(const Hand &, const Hand &);
	friend void dealFaceDown(Hand &, Deck &);
	friend void dealFaceUp(Hand &, Deck &);
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
	string getRealHand();
	void remove_card(size_t);
	vector<Card> & getCards();
	void sortCards();
	void setCards(vector<Card>::iterator, int);
};

ostream &operator<<(ostream &, const Hand &);

void operator<<(Hand &, Deck &);

void dealFaceDown(Hand &, Deck &);

void dealFaceUp(Hand &, Deck &);

pokerHands getPRank(const Hand &, Pair &, Pair &);

bool isFlush(const vector<Card> &);

bool isStraight(const vector<Card> &);

bool pokerRank(const Hand &, const Hand &);

