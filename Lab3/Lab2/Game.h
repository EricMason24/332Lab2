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
	//virtual ~Game(); no destructor needed because we are using shared_ptr
	virtual int before_Turn(Player &) = 0;
	virtual int turn(Player &) = 0;
	virtual int after_Turn(Player &) = 0;
	virtual int before_round() = 0;
	virtual int round() = 0;
	virtual int after_round() = 0;
protected:
	static shared_ptr<Game> gptr;
	Deck mainD;
	vector<shared_ptr<Player>> players;
};