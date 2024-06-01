#ifndef BOOK_GAME_HPP
#define BOOK_GAME_HPP

#include "SFML/Graphics.hpp"
#include "Player.h"
#include "Deck.h"

class Game : private sf::NonCopyable
{
public:
	explicit Game(const std::string &playerName, const pugi::xml_node& node);
	void run();
		
private:
	void start();
	void processEvents(); // Handle user input
	void update(sf::Time elapsedTime);
	void render();
	void updateStatistics(sf::Time elapsedTime);	

	static const sf::Time	TimePerFrame;
	sf::RenderWindow		mWindow{sf::VideoMode{640, 480}, "SFML Application", sf::Style::Close};
	sf::Texture				mTexture;
	sf::Font				mFont;
	sf::Text				mStatisticsText;
	sf::Time				mStatisticsUpdateTime;
	std::size_t				mStatisticsNumFrames{0};

	int nbCardPlayerinitial = 5;

	Player mPlayer;
	Deck deck;

};

#endif // BOOK_GAME_HPP
