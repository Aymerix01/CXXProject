#pragma once

//#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include <pugixml.hpp>
#include "Card.h"


class Deck
{
private:
	std::vector<std::unique_ptr<Card>> cards;
	sf::Sprite deckSprite;
	sf::Vector2f deckPosition = sf::Vector2f(125, 715);

public:
	/**
	* \brief Constructor of the Deck class
	* \param node : pugi::xml_node
	*/
	explicit Deck(const pugi::xml_node& node, const sf::Sprite& sprite);

	/**
	* \brief Add a card to the deck
	* \param node : pugi::xml_node
	*/
	void buildCard(const pugi::xml_node& node);

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
};