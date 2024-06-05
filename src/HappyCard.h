#pragma once

#include <string>
#include <pugixml.hpp>
#include "Card.h"
#include "Deck.h"
#include "Game.hpp"

class Deck;
class HappyCard : public Card
{
private:
	std::string classType = "HappyCard";
public:
	explicit HappyCard(const pugi::xml_node& node, EventCardManager& eventCardManager);
	void play() override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position) const override;
};