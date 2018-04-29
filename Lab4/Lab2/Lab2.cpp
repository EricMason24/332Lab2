// Lab2.cpp
// The main function for Lab 4, will take in 4 arguments including the program name and create a game from them.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

string programName = "";

// re-run main method with vector instead of argv[]
int runGame(vector<string> prompt) {
	size_t min_args = 3;
	if (prompt.size() < min_args) {
		usageMessage(programName, "must include name of game and 2+ players");
		return wrongNumberOfArguments;
	}
	else {
		string gameName = prompt[0];
		shared_ptr<Game> gptr = nullptr;
		//attempt to start a game with the given game name
		try {
			Game::startGame(gameName);
		}
		catch (errors e) {
			switch (e) {
			case gameAlreadyStarted:
				cout << "Game already started error" << endl;
				return gameAlreadyStarted;
				break;
			case unknownGame:
				cout << "Unknown game exception (make sure that the name of the game includes FiveCardDraw or SevenCardStud)" << endl;
				return unknownGame;
				break;
			case allocException:
				cout << "Allocation eception" << endl;
				return allocException;
				break;
			default:
				cout << "Unknown error" << endl;
				return e;
				break;
			}
			return e;
		}
		try {
			gptr = Game::instance();
		}
		catch (errors e) {
			if (e == InstanceNotAvailable) {
				cout << "Instance not available error" << endl;
				return InstanceNotAvailable;
			}
			else {
				cout << "Unknown error" << endl;
				return e;
			}
		}
		//add all of the given players to the created game
		for (size_t i = 1; i < prompt.size(); ++i) {
			try {
				(*gptr).addPlayer(prompt[i]);
			}
			catch (errors e) {
				if (e == alreadyPlaying) {
					cout << "Player " << prompt[i] << " already in game.\n" << endl;
					return alreadyPlaying;
				}
				else {
					cout << "Unknown error adding player " << prompt[i] << "\n" << endl;
				}
			}
		}
		//start the rounds process (begin the game)
		bool isRoundOver = false;
		while ((*gptr).getNumPlayers() > 1) {
			try {
				(*gptr).before_round();
			}
			catch (errors e) {
				if (e == roundOver) {
					isRoundOver = true;
				}
				else {
					cout << "Too many players in game.\n" << endl;
					break;
				}

			}
			if (!isRoundOver) {
				int res = (*gptr).round();
				if (res != 0) {
					cout << "Both main deck and discard deck have run out of cards. Stopping game.\n" << endl;
					break;
				}
				(*gptr).after_round();
			}

		}
		// reach here, game over
		Game::stopGame();
		return Success;
	}
}

int promptForGame() {
	string result, word;
	cout << "Please enter the name of the game and the players." << endl;
	getline(cin, result);
	istringstream iss(result);
	vector<string> sv;
	while (iss >> word) {
		sv.push_back(word);
	}
	return runGame(sv);
}

//main function
//will take in at least 4 arguments: program name, game name, and at least 2 player names
int main(int argc, char * argv[])
{
	int min_args = 4;
	programName = argv[0];
	if (argc < min_args) {
		usageMessage(programName, "must include name of game and 2+ players");
		return wrongNumberOfArguments;
	}
	else {
		string gameName = argv[1];
		shared_ptr<Game> gptr = nullptr;
		//attempt to start a game with the given game name
		try {
			Game::startGame(gameName);
		}
		catch (errors e) {
			switch (e) {
			case gameAlreadyStarted:
				cout << "Game already started error" << endl;
				return gameAlreadyStarted;
				break;
			case unknownGame:
				cout << "Unknown game exception (make sure that the name of the game includes FiveCardDraw or SevenCardStud)" << endl;
				return unknownGame;
				break;
			case allocException:
				cout << "Allocation exception" << endl;
				return allocException;
				break;
			default:
				cout << "Unknown error" << endl;
				return e;
				break;
			}
			return e;
		}
		try {
			gptr = Game::instance();
		}
		catch (errors e) {
			if (e == InstanceNotAvailable) {
				cout << "Instance not available error" << endl;
				return InstanceNotAvailable;
			}
			else {
				cout << "Unknown error" << endl;
				return e;
			}
		}
		//add all of the given players to the created game
		for (int i = 2; i < argc; ++i) {
			try {
				(*gptr).addPlayer(argv[i]);
			}
			catch (errors e) {
				if (e == alreadyPlaying) {
					cout << "Player " << argv[i] << " already in game.\n" << endl;
					return alreadyPlaying;
				}
				else {
					cout << "Unknown error adding player " << argv[i] << "\n" << endl;
				}
			}
		}
		//start the rounds process (begin the game)
		bool isRoundOver = false;
		while ((*gptr).getNumPlayers() > 1) {
			try {
				(*gptr).before_round();
			}
			catch (errors e) {
				if (e == roundOver) {
					isRoundOver = true;
				}
				else {
					cout << "Too many players in game.\n" << endl;
					break;
				}

			}
			if (!isRoundOver) {
				int res = (*gptr).round();
				if (res != 0) {
					cout << "Both main deck and discard deck have run out of cards. Stopping game.\n" << endl;
					break;
				}
				(*gptr).after_round();
			}

		}
		// reach here, game over
		Game::stopGame();
		bool validR = false;
		string result;
		while (!validR) {
			cout << "Game has ended, would you like to play another one? y/n" << endl;
			getline(cin, result);
			if (result != "y" && result != "n") {
				cout << "Please enter a valid response." << endl;
			}
			else {
				if (result == "n") {
					validR = true;
					return Success;
				}
				else {
					int res = promptForGame();
					if (res != 0) {
						return res;
					}
					// reach here, game over; validR still false, reprompt
				}
			}
		}
		return Success;
	}
}

