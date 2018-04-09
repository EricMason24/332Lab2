#include "stdafx.h"
#include "Deck.h"
#include "PlayingCard.h"
#include "Player.h"
#include "Game.h"
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

using namespace std;

shared_ptr<Game> Game::gptr = nullptr;

shared_ptr<Game> Game::instance() {
	if (gptr == nullptr) {
		throw(InstanceNotAvailable);
	}
	//is this the right copy???
	return gptr;
}

void Game::startGame(const string & func) {
	if (gptr != nullptr) {
		throw(gameAlreadyStarted);
	}
	if (func.find("FiveCardDraw") == string::npos) {
		throw(unknownGame);
	}
	try {
		//gptr = make_shared<FiveCardDraw>();
		
	}
	catch (...) {
		throw(allocException);
	}
}

void Game::stopGame() {
	if (gptr != nullptr) {
		throw(gameAlreadyStarted);
	}
	gptr = nullptr;
}

void Game::addPlayer(const string & p) {
	for (size_t i = 0; i < players.size(); ++i) {
		if ((*players[i]).name == p) {
			throw(alreadyPlaying);
		}
	}
	//char * name = (char *)p.c_str();
	//Player newP();
	shared_ptr<Player> pp =  make_shared<Player>((char *)p.c_str());

}

shared_ptr<Player> Game::findPlayer(const string & name) {
	for (size_t i = 0; i < players.size(); ++i) {
		if ((*players[i]).name == name) {
			return players[i];
		}
	}
	return nullptr;
}