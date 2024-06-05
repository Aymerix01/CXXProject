#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <pugixml.hpp>
#include <memory>
#include "EventCardManager.h"


class Deck;
class Card
{
private:
	std::string name;
	EventCardManager& eventCardManager;

public:
	explicit Card(const pugi::xml_node& node, EventCardManager& eventCardManager);
	virtual void play();
	std::string getName() const;
	virtual std::string getClassType() const = 0;
	virtual void render(sf::RenderWindow& window, const sf::Vector2f& position) const = 0;

	virtual ~Card() = default;
};