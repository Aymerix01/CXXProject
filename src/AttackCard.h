#pragma once

#include <string>
#include <pugixml.hpp>
#include "Card.h"
#include "Deck.h"


class Deck;
class AttackCard : public Card
{
private:
	std::string classType = "AttackCard";
	sf::Sprite attackCardSprite;
	sf::Texture attackCardTexture;
public:
	explicit AttackCard(const pugi::xml_node& node, EventCardManager& eventCardManager);
	void play() override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position) override;
};