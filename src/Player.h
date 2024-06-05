#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <memory>
#include "Deck.h"

class Card;
class Game;
class Player
{
private:
	const std::string playerName;
	int score = 0;
	std::vector<std::unique_ptr<Card>> hand;

public:
	/**
	* \brief Constructor of the Player class
	* \param name : string
	*/
	explicit Player(const std::string& name);

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
	void playCard(int index, Deck& deck);

	/*
	* Dumps the players hand
	*/
	std::string dump() const;


	/**
	* \brief Check if the player has lost
	* \return bool
	*/
	bool hasLost() const;

	/**
	* \brief Render the player's hand
	* \param window : sf::RenderWindow&
	*/
	void renderHand(sf::RenderWindow& window) const;

	void addPoints(int points) { score += points; };
	int getScore() const{ return score; };
};