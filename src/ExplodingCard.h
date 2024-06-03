#pragma once

#include <string>
#include <pugixml.hpp>
#include "Card.h"

class Deck;
class ExplodingCard : public Card
{
private:
	std::string classType = "ExplodingCard";
public:
	explicit ExplodingCard(const pugi::xml_node& node);
	void play(Deck& deck) override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position) const override;
};
