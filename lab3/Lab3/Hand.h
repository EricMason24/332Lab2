#include "PlayingCard.h"
#include <vector>
#include <string>
#include <iostream>
#include "Deck.h"

using namespace std;


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

pokerHands getPRank(const Hand &, Pair &, Pair &);