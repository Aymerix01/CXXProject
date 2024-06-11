#pragma once

#include <string>
#include <pugixml.hpp>
#include "Card.h"

class Deck;
class ExplodingCard : public Card
{
private:
	std::string classType = "ExplodingCard";
	sf::Sprite explodingCardSprite;
	sf::Texture explodingCardTexture;
public:
	explicit ExplodingCard(const pugi::xml_node& node, EventCardManager& eventCardManager);
	void play() override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size) override;
};
