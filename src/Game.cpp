#include "Game.hpp"
#include "StringHelpers.hpp"
#include <iostream>

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(const std::string& playerName, const pugi::xml_node& node,
			const sf::Sprite& backgroundSprite, const sf::Sprite& menuPrincipalSprite,
			const sf::Sprite& menuCartesSprite, const sf::Sprite& menuPauseSprite,
			const sf::Sprite& deckSprite, EventCardManager& eventCardManager) : 
menuStateManager(backgroundSprite, menuPrincipalSprite, menuCartesSprite, menuPauseSprite),
eventCardManager(eventCardManager), player(playerName), 
deck(node, deckSprite, eventCardManager)
{
	mFont.loadFromFile("media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	this->eventCardManager.addEventCardListener(&player);
	this->eventCardManager.addEventCardListener(&deck);
}

void Game::run()
{
	start();
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			if (!menuPrincipal)
				update(TimePerFrame);
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::start()
{
	deck.shuffle();
	for (int i = 0; i < nbCardPlayerinitial; i++)
	{
		player.drawCard(deck);
	}
	player.showHand();
}

void Game::processEvents()
{
    sf::Event event{sf::Event::Count};
	while (mWindow.pollEvent(event))
	{
		userEvents(event);
	}
}

void Game::userEvents(sf::Event event)
{
	if (event.type == sf::Event::Closed) {
		mWindow.close();
	}
	menuStateManager.onUserEvent(event, mWindow);
}

void Game::update(sf::Time elapsedTime)
{
    //TODO: Implement the update method
}

void Game::render()
{
	mWindow.clear();
	menuStateManager.render(mWindow);
	//deck.render(mWindow);
	
    //TODO: Implement the render method
	mWindow.draw(mStatisticsText);
	mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + toString(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + toString(mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames) + "us");
							 
		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}
