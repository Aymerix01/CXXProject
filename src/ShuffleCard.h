#pragma once

#include <string>
#include <pugixml.hpp>
#include "Card.h"
#include "Deck.h"

class Deck;
class ShuffleCard : public Card
{
private:
	std::string classType = "ShuffleCard";
	sf::Sprite shuffleCardSprite;
	sf::Texture shuffleCardTexture;
public:
	explicit ShuffleCard(const pugi::xml_node& node, EventCardManager& eventCardManager);
	void play() override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size) override;
};