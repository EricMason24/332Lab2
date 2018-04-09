// Lab2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Deck.h"
#include "PlayingCard.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char * argv[])
{
	FiveCardDraw fcd;
/*	string shuffleCmd = "-shuffle";
	char * file = "";
	int noArgs = 1;
	int argsNoShuffle = 2;
	int argsShuffle = 3;
	string programName = argv[0];
	string usageM = "In order to run this program, input 2 possible commands, one being a -shuffle, which will randomize the cards inputted and a valid text file that contains card definitions.";
	usageM += " These commands can come in any order, and the -shuffle command does not have to be inputted, so the acceptible number of arguments are either 1 or 2";
	vector<Hand> hands;
	int numEmptyHands = 9;
	int cardsPerHand = 5;

	//check that the right number of arguments are inputted
	if (argc == noArgs) {
		usageMessage(programName, usageM);
		return noArguments;
	}
	else if (argc != argsNoShuffle && argc != argsShuffle) {
		usageMessage(programName, usageM);
		return wrongNumberOfArguments;
	}
	else if (argc == argsNoShuffle && argv[1] == shuffleCmd) {
		usageMessage(programName, usageM);
		return oneArgumentNoTextFile;
	}
	else if (argc == argsShuffle && !(argv[1] == shuffleCmd || argv[2] == shuffleCmd)) {
		usageMessage(programName, usageM);
		return twoArgumentsNoShuffle;
	}
	else {

	}
	//check to see which argument to extract the deck from
	if (argc == argsNoShuffle) {
		file = argv[1];
	}
	else if(argv[1] == shuffleCmd){
		file = argv[2];
	}
	else {
		file = argv[1];
	}

	//construct the deck from the input file, catching any errors that may occur
	try {
		Deck d = Deck(file);
		if (d.sizeofDeck() == 0) {
			cout << "Deck is empty so no cards can be dealt" << endl;
			return emptyDeck;
		}
		if (argc == argsShuffle) {
			d.shuffleDeck();
		}
		for (int i = 0; i < numEmptyHands; ++i) {
			Hand h;
			hands.push_back(h);
		}
		//deal cards to all of the hands
		int numCardsDealt = numEmptyHands * cardsPerHand;
		for (int j = 0; j < numCardsDealt; ++j) {
			int currentHand = j % numEmptyHands;
			hands.at(currentHand) << d;
		}
	
		cout << "Current deck: " << endl;
		cout << d << endl;
		cout << "Hands: " << endl;
		for (int i = 0; i < numEmptyHands; ++i) {
			cout << hands.at(i) << endl;
		}

		sort(hands.begin(), hands.end());
		cout << "Sorted Hands: " << endl;
		for (int i = 0; i < numEmptyHands; ++i) {
			cout << hands.at(i) << endl;
		}

		sort(hands.begin(), hands.end(), pokerRank);
		cout << "Sorted Hands According to Rank: " << endl;
		for (int i = 0; i < numEmptyHands; ++i) {
			cout << hands.at(i) << endl;
		} 
		return Success;
	}
	catch (errors i) {
		if (i == cannotOpenTextFile) {
			return cannotOpenTextFile;
		}
	} 
	*/
}
