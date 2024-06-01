#pragma once

#include "Card.h"
#include <vector>
#include <memory>
#include <pugixml.hpp>

class Deck
{
private:
	std::vector<std::unique_ptr<Card>> cards;

public:
	explicit Deck(const pugi::xml_node& node);
	void buildCard(const pugi::xml_node& node);
	void shuffle();
	std::unique_ptr<Card> drawCard();
	void addCardToEnd(std::unique_ptr<Card> card);
	std::vector<std::unique_ptr<Card>> showSomeCards(int nbCards);
	bool empty() const;
};