#pragma once

#include "Card.h"
#include <vector>
#include <memory>

class Deck
{
private:
	std::vector<std::unique_ptr<Card>> cards;

public:
	Deck();
	void shuffle();
	std::unique_ptr<Card> drawCard();
	void addCardToEnd(std::unique_ptr<Card> card);
	std::vector<std::unique_ptr<Card>> showSomeCards(int nbCards);
	bool empty() const;
};