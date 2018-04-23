// Lab2.cpp
// The main function for Lab 3, will take in 4 arguments including the program name and create a Five Card Draw game from them.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

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

//main function
//will take in at least 4 arguments, Program name, game name, and player names (at least 2)
int main(int argc, char * argv[])
{
	int min_args = 4;
	string programName = argv[0];
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
				cout << "Game Already started error" << endl;
				return gameAlreadyStarted;
				break;
			case unknownGame:
				cout << "Unknown game exception (make sure that the name of the game includes FiveCardDraw)" << endl;
				return unknownGame;
				break;
			case allocException:
				cout << "Allowlocation eception" << endl;
				return allocException;
				break;
			default:
				cout << "unknown error" << endl;
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
				}
				else {
					cout << "Unknown error adding player " << argv[i] << "\n" << endl;
				}
			}
		}
		//start the rounds process (begin the game)
		while ((*gptr).getNumPlayers() > 1) {
			try {
				(*gptr).before_round();
			}
			catch (errors & e) {
				cout << "Too many players to deal everyone 5 cards.\n" << endl;
				break;
			}
			int res = (*gptr).round();
			if (res != 0) {
				cout << "Both main deck and discard deck have run out of cards. Stopping game.\n" << endl;
				break;
			}
			(*gptr).after_round();
		}
		//end game
		Game::stopGame();
	}
}

