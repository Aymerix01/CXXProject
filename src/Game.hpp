#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Deck.h"
#include "MenuStateManager.h"
#include <AudioManager.h>

class Game : private sf::NonCopyable, public EventCardListener
{
public:
	/**
	* \Brief Constructor of the Game
	* \param playerName The name of the player
	*/
	explicit Game(const std::string& playerName);

	/**
	* \Brief Run the game
	*/
	void run();
		
private:
	void start();
	void processEvents(); // Handle user input
	void userEvents(sf::Event event);
	void update();
	void render();
	void updateStatistics(sf::Time elapsedTime);
	void onEventCard(EventCard eventCard) override;

	static const sf::Time	TimePerFrame;
	sf::RenderWindow		mWindow{sf::VideoMode{1910, 1050}, "SFML Application", sf::Style::Close};
	sf::Texture				mTexture;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames{0};

	int nbCardPlayerinitial = 5;
	sf::Vector2f cardSize = sf::Vector2f(100, 150);
	sf::Vector2f deckPosition = sf::Vector2f(100, 100);

	EventCardManager eventCardManager;
	Player player;
	Deck deck;

	MenuStateManager menuStateManager;

	sf::Vector2i mousePos;
	bool isMousePressed = false;

	AudioManager am;
	
};

#endif // BOOK_GAME_HPP
