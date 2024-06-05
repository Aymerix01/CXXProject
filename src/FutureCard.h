#pragma once

#include <string>
#include <pugixml.hpp>
#include "Card.h"
#include "Deck.h"

class Deck;
class FutureCard : public Card
{
private:
	std::string classType = "FutureCard";
public:
	explicit FutureCard(const pugi::xml_node& node);
	int play(Deck& deck) override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position) const override;
};