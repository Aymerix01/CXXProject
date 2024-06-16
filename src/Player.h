#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include <string>
#include <memory>
#include "Deck.h"
#include "EventCardListener.h"
#include "AudioManager.h"

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

	AudioManager am;

public:
	/**
	* \brief Constructor of the Player class
	* \param name : string
	*/
	explicit Player(const std::string& name);

	/**
	* \brief Get the defuse card
	* \param deck : Deck&
	*/
	void getDefuseCard(Deck& deck);

	/**
	* \brief Get the exxploding card
	* \param deck : Deck&
	*/
	void getExplodingCard(Deck& deck);

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
	* \param index : int
	*/
	void playCard(int index);

	/*
	* Dumps the players hand
	* \return string
	*/
	std::string dump() const;

	/**
	* \brief Check if the player has lost
	* \param deck : Deck&
	* \return bool
	*/
	bool hasLost(Deck& deck);

	/**
	* \brief Render the player's hand
	* \param window : sf::RenderWindow&, mousePos : sf::Vector2i, playerDragDrop : bool
	*/
	void renderHand(sf::RenderWindow& window, sf::Vector2i mousePos, bool playerDragDrop);

	/**
	* \brief Render the player's score
	* \param window : sf::RenderWindow&
	*/
	void renderScore(sf::RenderWindow& window);

	/**
	* \brief Render the player's score at the end of the game
	* \param window : sf::RenderWindow&
	*/
	void renderScoreEndGame(sf::RenderWindow& window);

	/**
	* \brief Render the cards played by the player
	* \param window : sf::RenderWindow&
	*/
	void renderPlayedCard(sf::RenderWindow& window) const;

	/**
	* \brief Add points to the player's score
	* \param points : int
	*/
	void addPoints(int points) { score += points; };

	/**
	* \brief Get the player's score
	* \return int
	*/
	int getScore() const{ return score; };

	/**
	* \brief Obsever design pattern method
	* \param eventCard : EventCard
	*/
	void onEventCard(EventCard eventCard) override;

	/**
	* \brief Get the number of cards in the player's hand
	* \return size_t
	*/
	auto getHandLength() const { return hand.size(); };

	/**
	* \brief Reset the player
	*/
	void reset();
};