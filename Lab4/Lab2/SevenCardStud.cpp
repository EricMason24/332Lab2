// FiveCardDraw.cpp
// Implements the game class for a specific game of Five Card Draw.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#include "stdafx.h"

#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Player.h"
#include "Game.h"
#include "SevenCardStud.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

SevenCardStud::SevenCardStud() : cDealer(0) {
	for (int s = Card::diamonds; s <= Card::clubs; ++s) {
		for (int r = Card::two; r <= Card::ace; ++r) {
			Card c((Card::Suits)s, (Card::Ranks)r);
			mainD.add_card(c);
		}
	}
}

int SevenCardStud::before_turn(Player & p) {
	//not used in sevenCardStud
	return Success;
}

//determines how many cards the player discarded in the before_turn function, and based on that, deals them cards from either the discard or main deck to the player's hand
int SevenCardStud::turn(Player & p) {
	switch (turnNum) {
	case 0: 
		dealFaceDown(p.playerHand, mainD);
		dealFaceDown(p.playerHand, mainD);
		p.playerHand << mainD;
		break;
	case 4:
		dealFaceDown(p.playerHand, mainD);
		break;
	default:
		p.playerHand << mainD;
	}
	return Success;
}

//prints the players current name and hand
int SevenCardStud::after_turn(Player & p) {
	cout << "\n" << "Player's name: " << p.name << endl;
	string realHand = p.playerHand.getRealHand();
	cout << "	Hand: " << realHand << endl;
	return Success;
}
bool SevenCardStud::check(int playerPos) {
	Player & currP = *players[playerPos];
	bool hasBet = false;
	//cout << "No players have bet yet" << endl;
	cout << "Would you like to check? (y/n), a no will force you to bet 1 or 2 chips." << endl;
	string check;
	bool validR = false;
	while (!validR) {
		getline(cin, check);
		if (check == "y") {
			//do nothing, and proceed to next player
			validR = true;
		}
		else if (check == "n") {
			validR = true;
			bool validBet = false;
			hasBet = true;
			while (!validBet) {
				cout << "How many chips do you want to bet? (1/2)" << endl;
				string bet;
				getline(cin, bet);
				if (bet != "1" && bet != "2") {
					cout << "Please enter either 1 or 2 chips to bet." << endl;
				}
				else {
					validBet = true;
					int chips = currP.chips;
					if (chips - stoi(bet) > 0) {
						currP.chips -= stoi(bet);
						currBet = stoi(bet);
						currP.currBet = stoi(bet);
						pot += stoi(bet);
					}
					else {
						cout << currP.name << " does not have enough chips to make the bet, so they are all in." << endl;
						currBet = currP.chips;
						pot += currP.chips;
						currP.currBet = currP.chips;
						currP.outOfChips = true;
						currP.chips = 0;
					}

				}
			}
		}
		else {
			cout << "Please enter either y or n to indicate if you check or not." << endl;
		}
	}
	return hasBet;
}
void SevenCardStud::fcr(int playerPos) {
	Player & currP = *players[playerPos];
	//cout << "Current bet is " << currBet << endl;
	cout << "Would " << currP.name << " like to fold, call or raise? (f/c/r)" << endl;
	string result;
	bool resultV = false;
	while (!resultV) {
		getline(cin, result);
		if (result != "f" && result != "c" && result != "r") {
			cout << "Please enter a valid response." << endl;
		}
		else {
			resultV = true;
			if (result == "f") {
				currP.hasFolded = true;
				cout << currP.name << " has folded." << endl;
			}
			if (result == "c") {
				int newBet = currBet - currP.currBet;
				cout << "newBet: " << newBet << endl;
				cout << "cChips: " << currP.chips << endl;
				int cChips = currP.chips;
				if ((cChips - newBet) > 0) {
					currP.currBet += newBet;
					pot += newBet;
					currP.chips -= newBet;
					//cout << "current bet: " << currP.currBet << endl;
					//cout << "pot = " << pot << endl;
				}
				else {
					cout << currP.name << " does not have enough chips to make the bet, so they are all in." << endl;
					pot += currP.chips;
					currP.currBet += currP.chips;
					currP.outOfChips = true;
					currP.chips = 0;
				}

			}
			if (result == "r") {
				cout << "How many chips would " << currP.name << " like to raise? (1/2)" << endl;
				string raise;
				getline(cin, raise);
				bool validR = false;
				while (!validR) {
					if (raise != "1" && raise != "2") {
						cout << "Please enter a valid raise number (either 1 or 2)." << endl;
					}
					else {
						validR = true;
						int newRaise = currBet - currP.currBet + stoi(raise);
						int chips = currP.chips;
						if ((chips - newRaise) > 0) {
							currP.currBet += newRaise;
							currBet = currP.currBet;
							pot += newRaise;
							currP.chips -= newRaise;
						}
						else {
							cout << currP.name << " does not have enough chips to make the bet, so they are all in." << endl;
							pot += currP.chips;
							int tCurrBet = currP.currBet + currP.chips;
							if (tCurrBet > currBet) {
								currBet = tCurrBet;
							}
							currP.currBet = tCurrBet;
							currP.chips = 0;
							currP.outOfChips = true;
						}
					}
				}
			}
		}
	}
}

int SevenCardStud::bettingPhase() {
	//have players bet before round begins
	bool hasBet = false;
	bool allSet = false;
	int numBettingPlayers = 0;
	for (size_t i = 0; i < players.size(); ++i) {
		if (!(*players[i]).outOfChips) {
			++numBettingPlayers;
		}
	}
	if (numBettingPlayers == 1) {
		cout << "Only one player can bet, so moving on" << endl;
		return Success;
	}
	while (!allSet) {
		for (size_t j = 0; j < players.size(); ++j) {
			size_t pos = (cDealer + 1 + j) % players.size();
			Player & currP = *players[pos];
			if (!currP.hasFolded && !currP.outOfChips) {
				cout << "\n" << currP.name << " is currently betting with " << currP.chips << " chips." << endl;
				printHands(currP);
				if (!hasBet) {
					hasBet = check(pos);
				}
				else {
					//cout << "Player current bet: " << currP.currBet << endl;
					if (currBet != currP.currBet) {
						fcr(pos);
					}
					else {
						cout << currP.name << " already holds the max bet." << endl;
					}
				}
			}

		}
		allSet = true;
		if (hasBet) {
			for (size_t j = 0; j < players.size(); ++j) {
				Player & currP = *players[j];
				/* cout << "name " << currP.name << endl;
				cout << "folded " << currP.hasFolded << endl;
				cout << "outofC " << currP.outOfChips << endl;
				cout << "currbet " << currP.currBet << endl;
				cout << "round bet " << currBet << endl; */
				if (!currP.hasFolded && !currP.outOfChips && currBet != currP.currBet) {
					allSet = false;
				}
			}
			int holderPos = 0;
			int nonFoldPlayers = 0;
			for (size_t j = 0; j < players.size(); ++j) {
				Player & currP = *players[j];
				if (!currP.hasFolded) {
					++nonFoldPlayers;
					if (nonFoldPlayers > 1) {
						break;
					}
					holderPos = j;
				}
			}
			if (nonFoldPlayers == 1) {
				Player & p = *players[holderPos];
				cout << "\n" << p.name << " is the last player left in game, so they have won the round." << endl;
				p.chips += pot;
				++p.wins;
				cout << "\n" << "Player's name: " << p.name <<
					endl << "	Wins: " << p.wins <<
					endl << "	Losses: " << p.losses <<
					endl << "	Chips: " << p.chips <<
					endl << "	Hand: " << p.playerHand << endl;
				for (size_t i = 0; i < players.size(); ++i) {
					if (i != holderPos) {
						Player & loser = *players[i];
						++loser.losses;
						cout << "\n" << "Player's name: " << loser.name <<
							endl << "	Wins: " << loser.wins <<
							endl << "	Losses: " << loser.losses <<
							endl << "	Chips: " << loser.chips <<
							endl << "\t" << loser.name << " folded." << endl;
					}
				}
				recycleDeck();
				checkChips();
				askLeave();
				askJoin();
				if (players.size() != 0) {
					cDealer = (cDealer + 1) % players.size();
				}
				throw roundOver;
			}
		}

	}
	return 0;
}

//prints out all hands, with your hand being faceup
void SevenCardStud::printHands(Player & p) {
	cout << p.name << "'s Hand: " << p.playerHand.getRealHand() << endl;
	cout << "\n" << "Other Player Hands: " << endl;
	for (int i = 0; i < players.size(); ++i) {
		if ((*players[i]).name != p.name) {
			cout << "\n" << "Player's name: " << p.name <<
				endl << "	Hand: " << p.playerHand << endl;
		}
	}
}
//shuffles the deck, prints out the current dealer, deals 5 cards to all players and calls before turn on all of the players to determine what they discard
int SevenCardStud::before_round() {
	pot = 0;
	currBet = 0;
	turnNum = 0;
	mainD.shuffleDeck();
	for (size_t i = 0; i < players.size(); ++i) {
		Player & currP = *players[i];
		currP.hasFolded = false;
		currP.outOfChips = false;
		currP.currBet = 0;
	}
	cout << "\n" << (*players[cDealer % players.size()]).name << " is dealing..." << endl;
	for (size_t j = 0; j < players.size(); ++j) {
		--(*players[j]).chips;
		++pot;
	}
	return 0;
}

//calls turn on all players, refilling their hand with the right amount of cards depending on what they discarded, and then prints out all current hands through after turn
int SevenCardStud::round() {
	int turnNum = 0;
	for (int i = 0; i < 5; ++i) {
		for (size_t j = 0; j < players.size(); ++j) {
			size_t pos = (cDealer + 1 + j) % players.size();
			Player & currP = *players[pos];
			if (!currP.hasFolded) {
				int res = turn(*players[pos]);
				if (res != 0) {
					return res;
				}
				after_turn(*players[pos]);
			}
		}
		for (size_t i = 0; i < players.size(); ++i) {
			Player & currP = *players[i];
			currP.currBet = 0;
		}
		currBet = 0;
		bettingPhase();
		++turnNum;
	}
	return 0;
}

//gives the wins and losses of each player,shuffles the deck and prompts if anyone wants to leave or join the game, and assigning the next dealer as appropiate
int SevenCardStud::after_round() {
	winsLosses();
	recycleDeck();
	checkChips();
	askLeave();
	askJoin();
	if (players.size() != 0) {
		cDealer = (cDealer + 1) % players.size();
	}
	return 0;
}

void SevenCardStud::winsLosses() {
	int finalPosOfWinner = 0;
	vector<shared_ptr<Player>> temp = players;
	sort(temp.begin(), temp.end(), poker_rank);
	for (size_t i = 0; i < temp.size(); ++i) {
		++(*temp[i]).losses;
	}
	++(*temp[0]).wins;
	--(*temp[0]).losses;
	size_t i = 0;
	while (!pokerRank((*temp[i]).playerHand, (*temp[i + 1]).playerHand)) {
		++(*temp[i + 1]).wins;
		--(*temp[i + 1]).losses;
		++i;
		++finalPosOfWinner;
		if (i >= temp.size() - 1) {
			break;
		}
	}
	int winnings = pot / (finalPosOfWinner + 1);
	for (int i = 0; i <= finalPosOfWinner; ++i) {
		(*temp[i]).chips += winnings;
	}
	for (i = 0; i < temp.size(); ++i) {
		cout << "\n" << "Player's name: " << (*temp[i]).name <<
			endl << "	Wins: " << (*temp[i]).wins <<
			endl << "	Losses: " << (*temp[i]).losses <<
			endl << "	Chips: " << (*temp[i]).chips << endl;
		if (!(*temp[i]).hasFolded) {
			cout << "	Hand: " << (*temp[i]).playerHand << endl;
		}
		else {
			cout << "\t" << (*temp[i]).name << " folded." << endl;
		}
	}
}

void SevenCardStud::checkChips() {
	for (size_t i = 0; i < players.size(); ++i) {
		Player & p = (*players[i]);
		if (p.chips == 0) {
			bool goodR = false;
			while (!goodR) {
				cout << p.name << " is out of chips! Reset chip count to 20? y/n (n will have you leave the game)" << endl;
				string s = "";
				getline(cin, s);
				if (s == "y") {
					p.chips = 20;
					goodR = true;
				}
				else if (s == "n") {
					ofstream ofs(p.name + ".txt");
					ofs << (p);
					ofs.close();
					auto iter = players.begin() + i;
					players.erase(iter);
					cout << "Player '" << p.name << "' has left the game." << endl;
					--i;
					goodR = true;
				}
				else {
					cout << "Please enter y or n" << endl;
				}
			}

		}
	}

}
bool poker_rank(shared_ptr<Player> p1, shared_ptr<Player> p2) {
	if (p1 == nullptr) {
		return false;
	}
	else if (p2 == nullptr) {
		return true;
	}
	else {
		return pokerRank((*p1).playerHand, (*p2).playerHand);
	}
}

void SevenCardStud::recycleDeck() {
	while (discard.sizeofDeck() > 0) { // add all cards in discard deck to first player's hand
		(*players[0]).playerHand << discard;
	};
	for (size_t i = 0; i < players.size(); ++i) { // loop through players
		for (size_t j = 0; j < (*players[i]).playerHand.sizeOfHand(); ++j) { // add player's hand to main deck
			mainD.add_card((*players[i]).playerHand[j]);
		}
		while ((*players[i]).playerHand.sizeOfHand() != 0) { // remove all cards from player's hand
			(*players[i]).playerHand.remove_card(0);
		}
	}
}

void SevenCardStud::askLeave() {
	string s = "";
	cout << "\nWould any players like to leave the game at this point? y/n ?" << endl;
	getline(cin, s);
	while (s != "n") {
		if (s == "y") {
			cout << "\nInsert player's name, or 'n' to bypass: " << endl;
			getline(cin, s);
			while (s != "n") {
				bool found = false;
				for (size_t i = 0; i < players.size(); ++i) {
					if ((*players[i]).name == s) {
						found = true;
						ofstream ofs(s + ".txt");
						ofs << (*players[i]);
						ofs.close();
						auto iter = players.begin() + i;
						players.erase(iter);
						cout << "Player '" << s << "' has left the game." << endl;
						break;
					}
				}
				if (!found) {
					cout << "Player '" << s << "' not found." << endl;
				}
				cout << "\nInsert player's name, or 'n' to bypass: " << endl;
				getline(cin, s);
			}
		}
		cout << "\nWould any players like to leave the game at this point? y/n ?" << endl;
		getline(cin, s);
	}
}

void SevenCardStud::askJoin() {
	string s = "";
	cout << "\nWould any players like to join the game at this point? y/n ?" << endl;
	getline(cin, s);
	while (s != "n") {
		if (s == "y") {
			cout << "\nInsert player's name, or 'n' to bypass: " << endl;
			getline(cin, s);
			while (s != "n") {
				try {
					addPlayer(s);
				}
				catch (errors & e) {
					if (e == alreadyPlaying) {
						cout << "Player " << s << " already in game.\n" << endl;
					}
				}
				cout << "\nInsert player's name, or 'n' to bypass: " << endl;
				getline(cin, s);
			}
		}
		cout << "\nWould any players like to join the game at this point? y/n ?" << endl;
		getline(cin, s);
	}
}