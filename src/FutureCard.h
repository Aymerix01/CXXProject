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
	sf::Sprite futureCardSprite;
	sf::Texture futureCardTexture;
public:
	explicit FutureCard(const pugi::xml_node& node, EventCardManager& eventCardManager);
	void play() override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size) override;
};