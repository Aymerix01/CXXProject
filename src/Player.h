#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <memory>
#include "Deck.h"
#include "EventCardListener.h"

class Card;
class Game;
class Player : public EventCardListener
{
private:
	const std::string playerName;
	int score = 0;
	std::vector<std::unique_ptr<Card>> hand;
	std::vector<std::unique_ptr<Card>> lastPlayedCards;

	std::unique_ptr<Card> selectedCard;
	int indexSelectedCard = -1;

	sf::Font fontScore;
	sf::Text textScore;

public:
	/**
	* \brief Constructor of the Player class
	* \param name : string
	*/
	explicit Player(const std::string& name);

	void getDefuseCard(Deck& deck);

	/**
	* \brief Draw a card from the deck
	* \param deck : Deck&
	*/
	void drawCard(Deck& deck);

	/**
	* \brief Show the player's cards
	*/
	void showHand() const;

	/**
	* \brief Play a card
	* \param card : unique_ptr<Card>
	*/
	void playCard(int index);

	/*
	* Dumps the players hand
	*/
	std::string dump() const;


	/**
	* \brief Check if the player has lost
	* \return bool
	*/
	bool hasLost(Deck& deck);

	/**
	* \brief Render the player's hand
	* \param window : sf::RenderWindow&
	*/
	void renderHand(sf::RenderWindow& window, sf::Vector2i mousePos, bool playerDragDrop);
	void renderScore(sf::RenderWindow& window);
	void renderPlayedCard(sf::RenderWindow& window) const;

	void addPoints(int points) { score += points; };
	int getScore() const{ return score; };
	void onEventCard(EventCard eventCard) override;
	auto getHandLength() const { return hand.size(); };
};