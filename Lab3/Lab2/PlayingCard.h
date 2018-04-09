// PlayingCard.h : Defines the struct that represents a playing card that is to be used throughout the Cards lab 
// Created by Eric Mason on 2/4/2018

#pragma once
#include <vector>
#include <string>

using namespace std;
struct Card {
	enum Suits { noSuit, diamonds, hearts, spades, clubs };
	enum Ranks { noRank, two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace };
	Suits suit;
	Ranks rank;
	bool operator< (const Card &) const;
	bool operator== (const Card &) const;
	Card();  
	Card(Card::Suits, Card::Ranks);
	Card(const Card &);
};

struct Pair {
	Card::Ranks pairRank;
	int numDups;
	Pair();
};

enum errors {
	wrongNumberOfArguments = -1, cannotOpenTextFile = -2, vectorPushedBadInput = -3, oneArgumentNoTextFile = -4, twoArgumentsNoShuffle = -5, noArguments = -6, emptyDeck = -7, badInput = -9, InstanceNotAvailable = -10,
	gameAlreadyStarted = -11, unknownGame = -12, allocException = -13, noGameInProgress = -14, alreadyPlaying = -15, bothDecksEmpty = -16, outOfBoundsException = -8, Success = 0, UsageMessageRequested = 3
};

Card::Suits getSuit(char);

Card::Ranks getRank(char);

Card::Ranks getRankLength3(string);

int parseCard(vector<Card> &, char *);

string getCard(Card);

int printVector(const vector<Card> &);

int usageMessage(string, string);

int getRankNum(Card);

int getPairNum(Pair);

string evaluateHand(bool, bool, const Pair &, const Pair &);

int poker(const vector<Card> &);