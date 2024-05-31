#pragma once

#include "Card.h"
#include <vector>
#include <string>
#include <memory>

class Game;
class Deck;
class Player
{
private:
	std::string playerName;
	int score = 0;
	std::vector<std::unique_ptr<Card>> hand;

public:
	explicit Player(const std::string& name);
	void drawCard(Deck& deck);
	void playCard(std::unique_ptr<Card> card);
	bool hasLost() const;
};