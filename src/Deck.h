#pragma once

#include <vector>
#include <memory>
#include <pugixml.hpp>
#include "Card.h"
#include "EventCardListener.h"
#include "EventCardManager.h"
#include "AudioManager.h"

class Deck : public EventCardListener
{
private:
	std::vector<std::unique_ptr<Card>> cards;
	std::unique_ptr<Card> defuseCard;
	std::unique_ptr<Card> bombCard;
	pugi::xml_document doc;
	pugi::xml_node root;
	sf::Texture textureDosCarte;
	sf::Sprite deckSprite;
	sf::Vector2f deckPosition = sf::Vector2f(125, 715);
	EventCardManager& eventCardManager;

	bool renderTopCard = false;
	AudioManager am;

public:
	/**
	* \brief Constructor of the Deck class
	* \param evntCrdMngr : EventCardManager&
	*/
	explicit Deck(EventCardManager& eventCardManager);

	/**
	* \brief Build the deck
	*/
	void buildDeck();

	/**
	* \brief Add a card to the deck
	* \param node : pugi::xml_node, evntCrdMngr : EventCardManager&
	*/
	void buildCard(const pugi::xml_node& node, EventCardManager& evntCrdMnger);

	/**
	* \brief Get the defuse card
	* \return unique_ptr<Card>
	*/
	std::unique_ptr<Card> getDefuseCard();

	/**
	* \brief Get the exploding card
	* \return unique_ptr<Card>
	*/
	std::unique_ptr<Card> getExplodingCard();

	/**
	* \brief Place the exploding card in the deck
	*/
	void placeExplodingCard();

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
	* \brief Draw the first card from the deck (cards.back())
	* \return unique_ptr<Card>
	*/
	std::unique_ptr<Card> drawCard();

	/**
	* \brief Add a card to the deck at a random position
	* \param card : unique_ptr<Card>
	*/
	void addCardToRandom(std::unique_ptr<Card> card);

	/**
	* \brief Move the first card (cards.back()) of the deck to a random position
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
	void render(sf::RenderWindow& window);

	/**
	* \brief Observer pattern method
	* \param eventCard : EventCard
	*/
	void onEventCard(EventCard eventCard) override;

	/**
	* \brief Reset the deck
	*/
	void reset();
};