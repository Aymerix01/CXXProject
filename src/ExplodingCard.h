#pragma once

#include "Card.h"
#include <string>
#include <pugixml.hpp>
#include "Player.h"
#include "Deck.h"

class ExplodingCard : public Card
{
private:
	std::string classType = "ExplodingCard";
public:
	explicit ExplodingCard(const pugi::xml_node& node);
	void play(Deck& deck) override;
	std::string getClassType() const override;
};
