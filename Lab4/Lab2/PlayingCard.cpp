// PlayingCard.cpp
// Defines a card struct that has a suit and rank and can be compared to other cards.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#include "stdafx.h"
#include "PlayingCard.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;


//default constructor for a card
Card::Card()
	:rank(Card::Ranks::noRank), suit(Card::Suits::noSuit), isFaceUp(true) {};

// construct card with given rank and suit
Card::Card(Card::Suits s, Card::Ranks r)
	: suit(s), rank(r), isFaceUp(true) {};

//copy constructor for a card
Card::Card(const Card & c)
	:rank(c.rank), suit(c.suit), isFaceUp(c.isFaceUp) {};

//overrides the == operator to compare 2 cards, returning true only if the rank and suit are the same for both cards
bool Card::operator==(const Card & c) const {
	return (rank == c.rank && suit == c.suit);
}

//overrides the < operator to compare 2 cards, ranking the cards in ascending order by rank and if the ranks are the same, in ascending order by suit
bool Card::operator<(const Card & c) const {
	return (rank < c.rank) || ((rank == c.rank) && (suit < c.suit));
}

//defualt pair constructor
Pair::Pair()
	:pairRank(Card::Ranks::noRank), numDups(1) {};

//Takes in a lowercase char and returns the corresponding suit to that char, or noSuit if the char inputed does not match a valid suit
Card::Suits getSuit(char suit) {
	switch (suit) {
	case 's':
		return Card::Suits::spades;
		break;
	case 'c':
		return Card::Suits::clubs;
		break;
	case 'd':
		return Card::Suits::diamonds;
		break;
	case 'h':
		return Card::Suits::hearts;
		break;
	default:
		return Card::Suits::noSuit;
		break;
	}
}

//Takes in a lowercase char, and will return the rank equivalent, or noRank if there is no matching rank in the Ranks Enum located in PlayingCard.h
Card::Ranks getRank(char rank) {
	switch (rank) {
	case '2': return Card::Ranks::two; break;
	case '3': return Card::Ranks::three; break;
	case '4': return Card::Ranks::four; break;
	case '5': return Card::Ranks::five; break;
	case '6': return Card::Ranks::six; break;
	case '7': return Card::Ranks::seven; break;
	case '8': return Card::Ranks::eight; break;
	case '9': return Card::Ranks::nine; break;
	case 'j': return Card::Ranks::jack; break;
	case 'q': return Card::Ranks::queen; break;
	case 'k': return Card::Ranks::king; break;
	case 'a': return Card::Ranks::ace; break;
	default: return Card::Ranks::noRank; break;
	}
}

//This function is used to check if an input of size 3 has the correct rank of 10, as it is the only input with an input length of 3
Card::Ranks getRankLength3(string rank) {
	if (rank == "10") {
		return Card::Ranks::ten;
	}
	else {
		return Card::Ranks::noRank;
	}
}

//function that takes in a vector<Card> and a string that represents a file to be opened
//the function then parses that file, looking for any valid cards and if there are, adds them to the vector
int parseCard(vector<Card> & v, char * file) {
	ifstream ifs;
	ifs.open(file);
	if (!ifs.is_open()) {
		cout << "CardLab1" << " cannot open source file " << file << " to read from" << endl;
		return cannotOpenTextFile;
	}
	else {
		string definedCard, hand;
		vector<Card> holder;
		int numCardsInHand = 5;
		while (getline(ifs, hand)) {
			//create a new vector and assign it to holder, so that it clears the old cards that were pushed into holder in the previous line
			vector<Card> newV;
			holder = newV;
			istringstream iss(hand);
			bool lineBreak = false;
			while (iss >> definedCard) {
				// if input is '//', then break the while loop and continue through to the next line
				if (definedCard == "//") {
					lineBreak = true;
				}
				if (!lineBreak) {
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
							cout << "ignored card warning" << endl;
						}
						else {
							Card c;
							c.rank = inputR;
							c.suit = inputS;
							holder.push_back(c);
						}
					}
					else {
						cout << "ignored card warning" << endl;
					}
				}
			}
			//check if there are 5 valid cards in holder, which represents the valid cards in every line, and if there are, push all 5 into the passed in vector
			if (holder.size() == numCardsInHand) {
				for (size_t i = 0; i < holder.size(); i++) {
					v.push_back(holder[i]);
				}
			}
			else if (holder.size() == 0) {
				//ignore because no valid cards in set
			}
			else {
				//invalid number of cards
				cout << "Invalid number of cards warning" << endl;
			}
		}
		return Success;
	}
}

//Takes in a card and converts the rank and suit to a string output in the form of "rank of suit"
//returns an invalid input that will trigger a vectorPushedBadInput error for internal use only
//based on https://piazza.com/class/jcc6zondgla5pt?cid=310, outputs '2c' rather than 'two of clubs'
string getCard(Card c) {
	string output;
	switch (c.rank) {
	case Card::Ranks::two: output += "2"; break;
	case Card::Ranks::three: output += "3"; break;
	case Card::Ranks::four: output += "4"; break;
	case Card::Ranks::five: output += "5"; break;
	case Card::Ranks::six: output += "6"; break;
	case Card::Ranks::seven: output += "7"; break;
	case Card::Ranks::eight: output += "8"; break;
	case Card::Ranks::nine: output += "9"; break;
	case Card::Ranks::ten: output += "10"; break;
	case Card::Ranks::jack: output += "j"; break;
	case Card::Ranks::queen: output += "q"; break;
	case Card::Ranks::king: output += "k"; break;
	case Card::Ranks::ace: output += "a"; break;
	default: return "Invalid input"; break;
	}
	switch (c.suit) {
	case Card::Suits::diamonds: output += "d"; break;
	case Card::Suits::hearts: output += "h"; break;
	case Card::Suits::spades: output += "s"; break;
	case Card::Suits::clubs: output += "c"; break;
	default: return "Invalid input"; break;
	}
	return output;
}

//takes in a constant vector and prints the cards in that vector onto the output stream
int printVector(const vector<Card> & v) {
	for (size_t i = 0; i < v.size(); ++i) {
		Card c;
		c = v.at(i);
		string s = getCard(c);
		if (s == "Invalid input") {
			return vectorPushedBadInput; //vector was pushed bad input, for internal use only as invalid input should be ignored in ParseCard()
		}
		cout << s << endl;

	}
	return Success;
}

//Outputs the name of the program and the way to correctly execute the program onto the output stream
int usageMessage(string name, string usage) {
	cout << name << " " << usage << endl;
	return UsageMessageRequested;
}

//gets the rank of a card and returns and integer, used in order to evaluate the rank of a poker hand.
int getRankNum(Card c) {
	switch (c.rank) {
		case Card::Ranks::two: return 2; break;
		case Card::Ranks::three: return 3; break;
		case Card::Ranks::four: return 4; break;
		case Card::Ranks::five: return 5; break;
		case Card::Ranks::six: return 6; break;
		case Card::Ranks::seven: return 7; break;
		case Card::Ranks::eight: return 8; break;
		case Card::Ranks::nine: return 9; break;
		case Card::Ranks::ten: return 10; break;
		case Card::Ranks::jack: return 11; break;
		case Card::Ranks::queen: return 12; break;
		case Card::Ranks::king: return 13; break;
		case Card::Ranks::ace: return 14; break;
		default: return 0; break;
	}
}

//gets the rank of a pair and returns and integer, used in order to evaluate the rank of a poker hand.
int getPairNum(Pair p) {
	switch (p.pairRank) {
	case Card::Ranks::two: return 2; break;
	case Card::Ranks::three: return 3; break;
	case Card::Ranks::four: return 4; break;
	case Card::Ranks::five: return 5; break;
	case Card::Ranks::six: return 6; break;
	case Card::Ranks::seven: return 7; break;
	case Card::Ranks::eight: return 8; break;
	case Card::Ranks::nine: return 9; break;
	case Card::Ranks::ten: return 10; break;
	case Card::Ranks::jack: return 11; break;
	case Card::Ranks::queen: return 12; break;
	case Card::Ranks::king: return 13; break;
	case Card::Ranks::ace: return 14; break;
	default: return 0; break;
	}
}

//evaluate pairs, flush and straight and print out results as neccessary and return success so as to not repeat different hands;
string evaluateHand(bool isFlush, bool isStraight, const Pair & pair, const Pair & pair2) {
	if (isFlush && isStraight) {
		return "Hand is a straight flush!";
	}
	if (pair.numDups == 4 || pair2.numDups == 4) {
		return "Hand has a four of a kind";
	}
	if ((pair.numDups == 3 && pair2.numDups == 2) || (pair.numDups == 2 && pair2.numDups == 3)) {
		return "Hand has a full house";
	}
	if (isFlush) {
		return "Hand has a flush";
	}
	if (isStraight) {
		return "Hand has a straight";
	}
	if ((pair.numDups == 3 && pair2.numDups == 1) || (pair.numDups == 1 && pair2.numDups == 3)) {
		return "Hand has a three of a kind";
	}
	if (pair.numDups == 2 && pair2.numDups == 2) {
		return "Hand has two pairs";
	}
	if (pair.numDups == 2 || pair2.numDups == 2) {
		return "Hand has one pair";
	}
	return "Hand has no rank";
}

//method that takes in a const vector of Cards and will print out the ranks of every hand(five sequential cards) present in the vector
int poker(const vector<Card> & v) {
	for (unsigned int i = 0; i < v.size(); i += 5) {
		vector<Card> hand;
		unsigned int x = i;
		//get all five cards in one vector
		while (x < (i + 5)) {
			hand.push_back(v[x]);
			++x;
		}
		sort(hand.begin(), hand.end());
		//initialize variables to be used in evaluation logic
		bool isflush = true;
		bool isStraight = false;
		Pair pair;
		Pair pair2;
		//for a straight, the rank difference between the largest and smallest card will always be 4
		int rankDiff = getRankNum(hand[4]) - getRankNum(hand[0]);
		if (rankDiff == 4) {
			isStraight = true;
		}
		//check for flush and pairs
		for (size_t x = 0; x < hand.size()-1; ++x) {
			//check for flush
			if (hand[x].suit != hand[x + 1].suit) {
				isflush = false;
			}
			//check for pairs, as in a hand of five cards, there will be a maximum of two pairs
			if (pair.pairRank == Card::Ranks::noRank) {
				int z = 1;
				if (hand[x + z].rank == hand[x].rank) {
					pair.pairRank = hand[x].rank;
					++pair.numDups;
					++z;
					while (x + z < hand.size()) {
						if (hand[x].rank != hand[x + z].rank) {
							break;
						}
						else {
							++z;
							++pair.numDups;
						}
					}
				}
			}
			else if (pair2.pairRank == Card::Ranks::noRank && pair.pairRank != hand[x].rank) {
				int z = 1;
				if (hand[x + z].rank == hand[x].rank) {
					pair2.pairRank = hand[x].rank;
					++pair2.numDups;
					++z;
					while (x + z < hand.size()) {
						if (hand[x].rank != hand[x + z].rank) {
							break;
						}
						else {
							++z;
							++pair2.numDups;
						}
					}
				}
			}		
		}
	string pokerHand = evaluateHand(isflush, isStraight, pair, pair2);

	cout << pokerHand << endl;
	}
	return Success;
}

