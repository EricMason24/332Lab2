// FiveCardDraw.h
// Implements the game class for a specific game of Five Card Draw.
// Authors: Eric Mason (m.mason@wustl.edu) and Tommy Blackwell (tommy.blackwell@wustl.edu)

#pragma once

#include <string>
#include <memory>
#include "Deck.h"
#include "Hand.h"
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
	void checkChips();
	bool check(int);
	void fcr(int);
	int bettingPhase();
public:
	int pot;
	int currBet;
	FiveCardDraw();
	virtual int before_turn(Player &);
	virtual int turn(Player &);
	virtual int after_turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
};

bool poker_rank(shared_ptr<Player>, shared_ptr<Player>);