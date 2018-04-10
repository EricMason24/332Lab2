/*
description
*/

#pragma once

#include <string>
#include <memory>
#include "Deck.h"
#include "Player.h"
#include <vector>
#include "Game.h"

using namespace std;

class FiveCardDraw : public Game {
protected:
	size_t cDealer;
	Deck discard;
	void winsLosses();
	void recycleDeck();
	void askLeave();
	void askJoin();
public:
	FiveCardDraw();
	virtual int before_turn(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};

bool poker_rank(shared_ptr<Player>, shared_ptr<Player>);