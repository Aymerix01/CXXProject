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
	sf::Sprite defuseCardSprite;
	sf::Texture defuseCardTexture;
public:
	/**
	* \brief Constructor of DefuseCard
	* \param node : const pugi::xml_node&, eventCardManager : EventCardManager&
	*/
	explicit DefuseCard(const pugi::xml_node& node, EventCardManager& eventCardManager);
	void play() override;
	std::string getClassType() const override;
	void render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size) override;
};