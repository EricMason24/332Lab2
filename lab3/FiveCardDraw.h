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
public:
	FiveCardDraw();
	virtual int before_Turn(Player &);
	virtual int turn(Player &);
	virtual int after_Turn(Player &);
	virtual int before_round();
	virtual int round();
	virtual int after_round();
	
};