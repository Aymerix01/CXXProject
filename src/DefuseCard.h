#pragma once

#include <string>
#include <pugixml.hpp>
#include "Card.h"
#include "Deck.h"

class Deck;
class DefuseCard : public Card
{
private:
	std::string classType = "DefuseCard";
public:
	explicit DefuseCard(const pugi::xml_node& node, EventCardManager& eventCardManager);
	void play() override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position) const override;
};