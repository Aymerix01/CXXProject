#pragma once

#include "Card.h"
#include <vector>
#include <string>
#include <memory>
#include "Deck.h"

class Game;
class Player
{
private:
	const std::string playerName;
	int score = 0;
	std::vector<std::unique_ptr<Card>> hand;

public:
	explicit Player(const std::string& name);
	void drawCard(Deck& deck);
	void showHand() const;
	void playCard(int index, Deck& deck);
	bool hasLost() const;
};