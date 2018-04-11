// Game.h
// Abstract class for a game object, which controls players and main deck and provides virtual methods for gameplay.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#pragma once

#include <string>
#include <memory>
#include "Deck.h"
#include "Player.h"
#include <vector>

using namespace std;

class Game {
public:
	static shared_ptr<Game> instance();
	static void startGame(const string &);
	static void stopGame();
	void addPlayer(const string &);
	shared_ptr<Player> findPlayer(const string &);
	virtual ~Game();
	virtual int before_turn(Player &) = 0;
	virtual int turn(Player &) = 0;
	virtual int after_turn(Player &) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
	size_t getNumPlayers();
	void gameOver();
protected:
	static shared_ptr<Game> gptr;
	Deck mainD;
	vector<shared_ptr<Player>> players;
};