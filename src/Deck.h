#pragma once

//#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <pugixml.hpp>
#include "Card.h"
#include "EventCardListener.h"
#include "EventCardManager.h"

class Deck : public EventCardListener
{
private:
	std::vector<std::unique_ptr<Card>> cards;
	sf::Sprite deckSprite;
	sf::Vector2f deckPosition = sf::Vector2f(125, 715);
	EventCardManager& eventCardManager;

public:
	/**
	* \brief Constructor of the Deck class
	* \param node : pugi::xml_node, evntCrdMngr : const EventCardManager&
	*/
	explicit Deck(const pugi::xml_node& node, const sf::Sprite& sprite, EventCardManager& eventCardManager);

	/**
	* \brief Add a card to the deck
	* \param node : pugi::xml_node, evntCrdMngr : const EventCardManager&
	*/
	void buildCard(const pugi::xml_node& node, EventCardManager& eventCardManager);

	/**
	* \brief Dump the deck
	* \return string
	*/
	std::string dump() const;

	/**
	* \brief Shuffle the deck
	*/
	void shuffle();

	/**
	* Puts the first card of the deck in the back
	* if the card is a bomb then the player gains points
	*/
	std::string attack();

	/**
	* \brief Draw the last card from the deck (cards.back())
	* \return unique_ptr<Card>
	*/
	std::unique_ptr<Card> drawCard();

	/**
	* \brief Add a card to the deck at a random position
	* \param card : unique_ptr<Card>
	*/
	void addCardToRandom(std::unique_ptr<Card> card);

	/**
	* \brief Move the first card of the deck to a random position
	*/
	void moveFirstCardToRandom();

	/**
	* \brief Show the nbCards first cards of the deck
	* \param card : unique_ptr<Card>
	* \return vector<Card*> : vector of observed cards
	*/
	std::vector<Card*> showSomeCards(int nbCards);

	/**
	* \brief Show if the deck is empty
	* \return bool
	*/
	bool empty() const;

	/**
	* \brief Render the deck
	* \param window : sf::RenderWindow
	*/
	void render(sf::RenderWindow& window) const;

	void onEventCard(EventCard eventCard) override;
};