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
	int min_args = 4;
	if (argc < min_args) {
		// usageM, "must include name of game and 2+ players
	}
	else {
		shared_ptr<Game> gptr = nullptr;
		try {
			Game::startGame(argv[1]);
		}
		catch (errors & e) {
			// switch case, should just be gameAlreadyStarted, unknownGame, or allocException at this point
			return -100;
		}
		try {
			gptr = Game::instance();
		}
		catch (errors & e) {
			// switch case, should just be instanceNotAvailable
			return -101;
		}
		try {
			for (int i = 2; i < argc; ++i) {
				(*gptr).addPlayer(argv[i]);
			}
		}
		catch (errors & e) {
			// switch case, should just be alreadyPlaying
			return -102;
		}
		while ((*gptr).getNumPlayers() > 1) {
			// need try catches here
			(*gptr).before_round();
			(*gptr).round();
			(*gptr).after_round();
		}
		(*gptr).gameOver();
	}
}

