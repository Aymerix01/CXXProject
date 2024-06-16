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
	std::string name;
	EventCardManager& eventCardManager;

public:

	/**
	* \brief Constructor of Card
	* \param node : const pugi::xml_node&, eventCardManager : EventCardManager&
	*/
	explicit Card(const pugi::xml_node& node, EventCardManager& eventCardManager);

	/**
	* \brief Play a card
	*/
	virtual void play() = 0;

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
	virtual std::string getClassType() const = 0;

	/**
	* \brief Render the card
	*/
	virtual void render(sf::RenderWindow& window, const sf::Vector2f& position, const sf::Vector2f& size) = 0;

	/**
	* \brief Destructor of Card
	*/
	virtual ~Card() = default;
};