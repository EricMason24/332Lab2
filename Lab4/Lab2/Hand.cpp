// Hand.cpp
// Defines a hand class that contains five cards.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#include "stdafx.h"
#include "Hand.h"
#include "Deck.h"
#include "PlayingCard.h"
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <random>

vector<Card> emptyHand;
Pair p1;
Pair p2;
//default constructor for a hand that will create an empty hand
Hand::Hand()
	:cards(emptyHand) {}

//copy constructor for a hand that will instantiate a hand to be a copy of the inputted hand
Hand::Hand(const Hand & h)
	: cards(h.cards) {}


//assignment operator to assign a hand to be equal to another hand
//can compare two cards (vector<Card>) because the == operator for a Card is overloaded in PlayingCard.cpp
void Hand::operator=(const Hand & h) {
	if (cards == h.cards) {
		//hands are the same, ignore
	}
	else {
		cards = h.cards;
	}
}
//equivalence operator to check if two hands are equal
bool Hand::operator==(const Hand & h) const {
	if (cards == h.cards) {
		return true;
	}
	else {
		return false;
	}
}

//return the private set of cards
vector<Card> & Hand::getCards() {
	return cards;
}

//sets the cards of the hand
void Hand::setCards(vector<Card>::iterator it, int size) {
	cards = vector<Card>();
	auto finalIt = it + size;
	while (it < finalIt) {
		cards.push_back(*it);
		++it;
	}
}
//will return how many cards are currently inside the hand
size_t Hand::sizeOfHand() {
	return cards.size();
}

//overrides the < operator for two different hands, and will first compare the sizes of both hands
//in order to avoid an out of bounds exception, and then cycle through both hands to find a point where one hand is less than the other
//based on my interpretation of https://piazza.com/class/jcc6zondgla5pt?cid=266, the for the <operator, suits should be incorporated, but for poker rank they shouldn't
bool Hand::operator<(const Hand & h) const {
	auto i = cards.begin();
	for (auto j = h.cards.cbegin(); j < h.cards.cend(); ++j) {
		Card iCard = *i;
		Card jCard = *j;
		if (iCard == jCard) {
			++i;
			break;
		}
		return iCard < jCard;
	}
	return false;
}

//returns a string of the cards currently in the hand using the getCard() method in PlayingCard.cpp
const string Hand::toString() {
	string out = "";
	for (size_t i = 0; i < cards.size(); ++i) {
		out += getCard(cards.at(i)) + " ";
	}
	return out;
}

//overrides the << operator for an ostream in order to print out a hand
//will return the inputed ostream with the hand's cards written in order with a space inbetween
ostream &operator<<(ostream & out, const Hand & h) {
	for (size_t i = 0; i < h.cards.size(); ++i) {
		if (!h.cards.at(i).isFaceUp) {
			out << "** ";
		}
		else {
			out << getCard(h.cards.at(i)) + " ";
		}
	}
	return out;
}

//returns a string of all the cards, even if they are facedown
string Hand::getRealHand() {
	string s = "";
	for (size_t i = 0; i < cards.size(); ++i) {
		s += getCard(cards.at(i)) + " ";
	}
	return s;
}

//overrides the operator[] and returns the card at that location, if that location does not exist, an out of range exception will be thrown, which in turn will cause an outOfBounds Exception
Card Hand::operator[](size_t loc) {
	try {
		return cards.at(loc);
	}
	catch (out_of_range) {
		throw(outOfBoundsException);
	}

}


//remove_card will take a position in the vector and remove it from the current card vector
void Hand::remove_card(size_t loc) {
	if (loc >= cards.size() || loc < 0) {
		throw(outOfBoundsException);
	}
	try {
		auto iter = cards.begin() + loc;
		cards.erase(iter);
	}
	//sometimes erase can cause 'undefined behavior' per the cplusplus reference on erase, so catch anything just in case undefined behavoir occurs
	catch (...) {
		throw(outOfBoundsException);
	}


}

void dealFaceDown(Hand & h, Deck & d) {
	if (d.deck.size() == 0) {
		return;
	}
	Card & c = d.deck.at(d.deck.size() - 1);
	d.deck.pop_back();
	h.cards.push_back(c);
	h.cards[h.cards.size() - 1].isFaceUp = false;
}

//put in as a substituion to the operator<< of hand so that the hand does not sort
void dealFaceUp(Hand & h, Deck & d) {
	if (d.deck.size() == 0) {
		return;
	}
	Card & c = d.deck.at(d.deck.size() - 1);
	d.deck.pop_back();
	h.cards.push_back(c);
}

//sorts cards to be used in sevenCardStud so that pokerRank can run correctly
void Hand::sortCards() {
	sort(cards.begin(), cards.end());
}

//overloads the << operator to unload the last card in the inputted deck into the designated hand, and then sorts that hand afterwards to ensure that the cards in the hand are in the correct order
void operator<<(Hand & h, Deck & d) {
	if (d.deck.size() == 0) {
		return;
	}
	Card c = d.deck.at(d.deck.size() - 1);
	d.deck.pop_back();
	h.cards.push_back(c);
	sort(h.cards.begin(), h.cards.end());
}

//helper function to pokerRank that will return the rank of the hand using the enum of possible ranks from PokerHands
//way to get ranks is rewritten because my implemenation in PlayingCard.cpp (poker()) doesn't work all the time
//Pair is a struct implemented in PlayinCard.cpp and contains a rank and number of dupes
pokerHands getPRank(const Hand & h, Pair & p1, Pair & p2) {
	bool flush = isFlush(h.cards);
	bool straight = isStraight(h.cards);
	//find any pairs in the hand and set the pair ranks of the hand to the appropriate values
	bool alreadyCheckedP1 = false;
	bool alreadyCheckedP2 = false;
	for (size_t i = 0; i < h.cards.size() - 1; ++i) {
		if (p1.pairRank != Card::Ranks::noRank) {
			alreadyCheckedP1 = true;
		}
		if (p2.pairRank != Card::Ranks::noRank) {
			alreadyCheckedP2 = true;
		}
		for (size_t j = i + 1; j < h.cards.size(); ++j) {
			Card iCard = h.cards.at(i);
			Card jCard = h.cards.at(j);
			if (iCard.rank == jCard.rank) {
				if (p1.pairRank == iCard.rank && !alreadyCheckedP1) {
					++p1.numDups;
				}
				else if (p2.pairRank == iCard.rank && !alreadyCheckedP2) {
					++p2.numDups;
				}
				else if (p1.pairRank == Card::Ranks::noRank) {
					p1.pairRank = iCard.rank;
					++p1.numDups;

				}
				else if (p2.pairRank == Card::Ranks::noRank) {
					p2.pairRank = iCard.rank;
					++p2.numDups;
				}

			}
		}
	}
	if (flush && straight) {
		return pokerHands::straightF;
	}
	if (p1.numDups == 4 || p2.numDups == 4) {
		return pokerHands::fourOKind;
	}
	if ((p1.numDups == 3 && p2.numDups == 2) || (p1.numDups == 2 && p2.numDups == 3)) {
		return pokerHands::fullHouse;
	}
	if (flush) {
		return pokerHands::flush;
	}
	if (straight) {
		return pokerHands::straight;
	}
	if (p1.numDups == 3 || p2.numDups == 3) {
		return pokerHands::threeOKind;
	}
	if (p1.numDups == 2 && p2.numDups == 2) {
		return pokerHands::twoPair;
	}
	if (p1.numDups == 2 || p2.numDups == 2) {
		return pokerHands::Pair;
	}
	return pokerHands::noRank;
}

//checks if a hand has a flush
bool isFlush(const vector<Card> & cards) {
	Card c = cards.at(0);
	for (size_t i = 1; i < cards.size(); ++i) {
		if (c.suit != cards.at(i).suit) {
			return false;
		}
	}
	return true;
}

//checks if a hand has a straight, getRankNum is located in PlayingCard.cpp and will return the numerical value of the given rank
bool isStraight(const vector<Card> & cards) {
	Card first = cards.at(0);
	Card last = cards.at(cards.size() - 1);
	int diff = getRankNum(last) - getRankNum(first);
	if (diff == 4) {
		return true;
	}
	else {
		return false;
	}
}

//takes in two hands, computes thier ranks and then compares the rank of both hands, returning true only if hand 1 has a higher rank than hand 2
bool pokerRank(const Hand & h1, const Hand & h2) {
	Pair h1Pair1;
	Pair h1Pair2;
	Pair h2Pair1;
	Pair h2Pair2;
	pokerHands h1Rank = getPRank(h1, h1Pair1, h1Pair2);
	pokerHands h2Rank = getPRank(h2, h2Pair1, h2Pair2);
	if (h1Rank > h2Rank) {
		return true;
	}
	else if (h1Rank == h2Rank) {
		Card::Ranks highCard1 = Card::Ranks::noRank;
		Card::Ranks highCard2 = Card::Ranks::noRank;
		Card::Ranks highPair1 = Card::Ranks::noRank;
		Card::Ranks highPair2 = Card::Ranks::noRank;
		Card::Ranks lowPair1 = Card::Ranks::noRank;
		Card::Ranks lowPair2 = Card::Ranks::noRank;
		switch (h1Rank) {
		case pokerHands::straightF:
			highCard1 = h1.cards.at(h1.cards.size() - 1).rank;
			highCard2 = h1.cards.at(h2.cards.size() - 1).rank;
			return highCard1 > highCard1;
			break;
		case pokerHands::fourOKind:
			if (h1Pair1.numDups == 4) {
				highPair1 = h1Pair1.pairRank;
			}
			else {
				highPair1 = h1Pair2.pairRank;
			}
			if (h2Pair1.numDups == 4) {
				highPair2 = h2Pair1.pairRank;
			}
			else {
				highPair2 = h2Pair2.pairRank;
			}
			return highPair1 > highPair2;
			break;
		case pokerHands::fullHouse:
			if (h1Pair1.numDups == 3) {
				highPair1 = h1Pair1.pairRank;
				lowPair1 = h1Pair2.pairRank;
			}
			else {
				highPair1 = h1Pair2.pairRank;
				lowPair1 = h1Pair1.pairRank;
			}
			if (h2Pair1.numDups == 3) {
				highPair2 = h2Pair1.pairRank;
				lowPair2 = h2Pair2.pairRank;
			}
			else {
				highPair2 = h2Pair2.pairRank;
				lowPair2 = h2Pair1.pairRank;
			}
			return (highPair1 > highPair2) || ((highPair1 == highPair2) && (lowPair1 > lowPair2));
			break;
		case pokerHands::flush:
			for (int i = 4; i >= 0; --i) {
				if (h2.cards[i].rank < h1.cards[i].rank) {
					return true;
				}
				if (h2.cards[i].rank > h1.cards[i].rank) {
					return false;
				}
			}
			return false;
			break;
		case pokerHands::straight:
			highCard1 = h1.cards.at(h1.cards.size() - 1).rank;
			highCard2 = h1.cards.at(h2.cards.size() - 1).rank;
			return highCard1 > highCard2;
			break;
		case pokerHands::threeOKind:
			if (h1Pair1.numDups == 3) {
				highPair1 = h1Pair1.pairRank;
			}
			else {
				highPair1 = h1Pair2.pairRank;
			}
			if (h2Pair1.numDups == 3) {
				highPair2 = h2Pair1.pairRank;
			}
			else {
				highPair2 = h2Pair2.pairRank;
			}
			return highPair1 > highPair2;
			break;
		case pokerHands::twoPair:
			if (h1Pair1.pairRank > h1Pair2.pairRank) {
				highPair1 = h1Pair1.pairRank;
				lowPair1 = h1Pair2.pairRank;
			}
			else {
				highPair1 = h1Pair2.pairRank;
				lowPair1 = h1Pair1.pairRank;
			}
			if (h2Pair1.pairRank > h2Pair2.pairRank) {
				highPair2 = h2Pair1.pairRank;
				lowPair2 = h2Pair2.pairRank;
			}
			else {
				highPair2 = h2Pair2.pairRank;
				lowPair2 = h2Pair1.pairRank;
			}
			return (highPair1 > highPair2) || ((highPair1 == highPair2) && (lowPair1 > lowPair2));
			break;
		case pokerHands::Pair:
			highPair1 = h1Pair1.pairRank;
			highPair2 = h2Pair1.pairRank;
			return highPair1 > highPair2;
			break;
		case pokerHands::noRank:
			for (int i = 4; i >= 0; --i) {
				if (h2.cards[i].rank < h1.cards[i].rank) {
					return true;
				}
				if (h2.cards[i].rank > h1.cards[i].rank) {
					return false;
				}
			}
			return false;
			break;
		default:
			return false;
			break;
		}
	}
	return false;
}