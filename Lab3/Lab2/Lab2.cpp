// Lab2.cpp : is the main function for lab3, will take in 4 arguments including the program name and create a poker game from them.
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

//main function
//will take in at least 4 arguments, Program name, game name, and player names (at least 2)
int main(int argc, char * argv[])
{
	int min_args = 4;
	string programName = argv[0];
	string gameName = argv[1];
	if (argc < min_args) {
		usageMessage(programName, "must include name of game and 2+ players");
		return wrongNumberOfArguments;
	}
	else {
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
		try {
			for (int i = 2; i < argc; ++i) {
				(*gptr).addPlayer(argv[i]);
			}
		}
		catch (errors e) {
			if (e == alreadyPlaying) {
				cout << "Already Playing error" << endl;
				return alreadyPlaying;
			}
			else {
				cout << "Unknown error" << endl;
				return e;
			}
		}
		//start the rounds process (begin the game)
		while ((*gptr).getNumPlayers() > 1) {
			// need try catches here
			//do we? there is nothing thrown from any of the dereference to the gptr or any of the rounds
			(*gptr).before_round();
			(*gptr).round();
			(*gptr).after_round();
			
		}
		//end game, as there is only 1 player left
		(*gptr).gameOver();
	}
}

