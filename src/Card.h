#pragma once

#include "SFML/Graphics.hpp"
#include <string>
#include <pugixml.hpp>
#include <memory>
#include "EventCardManager.h"
#include "AudioManager.h"

class Deck;
class Card
{
private:
	std::string classType;
	std::string name;
	EventCardManager& eventCardManager;
	sf::Sprite cardSprite;
	sf::Texture cardTexture;

public:

	/**
	* \brief Constructor of Card
	* \param node : const pugi::xml_node&, eventCardManager : EventCardManager&
	*/
	explicit Card(const pugi::xml_node& node, EventCardManager& eventCardManager);

	/**
	* \brief Play a card
	*/
	virtual void play();

	/**
	* \brief Send message to every listener
	* \param eventCard : EventCard
	*/
	void notifyEventCardManager(EventCard eventCard) const;

	/**
	* \brief Get the name of the card
	* \return std::string
	*/
	std::string getName() const;

	/**
	* \brief Get the class type of the card
	* \return std::string
	*/
	virtual std::string getClassType() const;

	/**
	* \brief Render the card
	*/
	virtual void render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size);

	/**
	* \brief Destructor of Card
	*/
	virtual ~Card() = default;
};