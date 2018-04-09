/*
description
*/

#include "stdafx.h"
#include <string>
#include <memory>
#include "Deck.h"
#include "Player.h"
#include "PlayingCard.h"
#include <vector>
#include "Game.h"
#include "FiveCardDraw.h"

using namespace std;

FiveCardDraw::FiveCardDraw() : cDealer(0) {
	for (int s = Card::diamonds; s <= Card::clubs; ++s) {
		for (int r = Card::two; r <= Card::ace; ++r) {
			Card c((Card::Suits)s, (Card::Ranks)r);
			mainD.add_card(c);
		}
	}
}

int FiveCardDraw::before_Turn(Player & p) {
	return 0;
}

int FiveCardDraw::turn(Player & p) {
	return 0;
}

int FiveCardDraw::after_Turn(Player & p) {
	return 0;
}

int FiveCardDraw::before_round() {
	return 0;
}

int FiveCardDraw::round() {
	return 0;
}

int FiveCardDraw::after_round() {
	return 0;
}