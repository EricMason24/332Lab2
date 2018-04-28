// Game.cpp
// Abstract class for a game object, which controls players and main deck and provides virtual methods for gameplay.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#include "stdafx.h"
#include "Deck.h"
#include "Hand.h"
#include "PlayingCard.h"
#include "Player.h"
#include "Game.h"
#include "FiveCardDraw.h"
#include "SevenCardStud.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

shared_ptr<Game> Game::gptr = nullptr;

//destructor for game
//do nothing because we are using shared pointers
Game::~Game() {

}

//returns a shared pointer pointing to the current game object
shared_ptr<Game> Game::instance() {
	if (gptr == nullptr) {
		throw(InstanceNotAvailable);
	}
	return gptr;
}

//begins a game, making sure that a game isn't already in progress
void Game::startGame(const string & func) {
	if (gptr != nullptr) {
		throw(gameAlreadyStarted);
	}
	if (func.find("FiveCardDraw") == string::npos) {
		if (func.find("SevenCardStud") == string::npos) {
			throw(unknownGame);
		}
		try {
			gptr = make_shared<SevenCardStud>();
		}
		catch (...) {
			throw(allocException);
		}
	}
	else {
		try {
			gptr = make_shared<FiveCardDraw>();
		}
		catch (...) {
			throw(allocException);
		}
	}
}

//stops the game, calling gameover to write the player wins and losses
void Game::stopGame() {
	if (gptr == nullptr) {
		throw(noGameInProgress);
	}
	(*gptr).gameOver();
	gptr = nullptr;
	cout << "\nGame stopped." << endl;
}

//adds a player to the current game, and throws an exception if that name is already in use
void Game::addPlayer(const string & p) {
	for (size_t i = 0; i < players.size(); ++i) {
		if ((*players[i]).name == p) {
			throw(alreadyPlaying);
		}
	}
	shared_ptr<Player> pp =  make_shared<Player>((char *)p.c_str());
	Player player = *pp;
	if ((*pp).chips == 0) {
		bool goodR = false;
		while (!goodR) {
			cout << player.name << " is out of chips!" << endl;
			cout << "Reset chip count to 20? y/n (n will have you leave the game)" << endl;
			string s = "";
			getline(cin, s);
			if (s == "y") {
				player.chips = 20;
				goodR = true;
				players.push_back(pp);
			}
			else if (s == "n") {
				cout << player.name << " did not join the game" << endl;
				goodR = true;
			}
			else {
				cout << "Please enter y or n" << endl;
			}
		}
	}
	else {
		players.push_back(pp);
	}
}

//returns a shared pointer to the player that matches the name given, or nullptr if the name given does not match any of the current players
shared_ptr<Player> Game::findPlayer(const string & name) {
	for (size_t i = 0; i < players.size(); ++i) {
		if ((*players[i]).name == name) {
			return players[i];
		}
	}
	return nullptr;
}

//returns the total number of players in the game
size_t Game::getNumPlayers() {
	return players.size();
}

//ends the game, and writes the players wins and losses to the appropriate files
void Game::gameOver() {
	for (size_t i = 0; i < players.size(); ++i) {
		ofstream ofs((*players[i]).name + ".txt");
		ofs << (*players[i]);
		ofs.close();
		cout << "\nPlayer '" << (*players[i]).name << "' has left the game." << endl;
	}
}