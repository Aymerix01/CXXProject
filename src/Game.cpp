#include "Game.hpp"
#include "StringHelpers.hpp"
#include <iostream>

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(const std::string& playerName, const pugi::xml_node& node,
			const sf::Sprite& backgroundSprite, const sf::Sprite& menuPrincipalSprite,
			const sf::Sprite& menuCartesSprite, const sf::Sprite& menuPauseSprite,
			const sf::Sprite& deckSprite, EventCardManager& eventCardManager) : 
eventCardManager(eventCardManager), player(playerName), 
deck(node, deckSprite, eventCardManager),
menuStateManager(backgroundSprite, menuPrincipalSprite, menuCartesSprite, menuPauseSprite)
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
		}
		if (menuStateManager.inGame)
			update(TimePerFrame);
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
	player.getDefuseCard(deck);
	deck.placeExplodingCard();
	deck.shuffle();
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
	if (!player.hasLost())
	{
		cout << "Please choose an action" << endl;
		cout << "0 : Draw card" << endl;
		cout << "1 : Play card" << endl;
		cin >> playerInput;
		if (playerInput == 0)
		{
			player.drawCard(deck);
			cout << "Your hand" << endl;
			player.showHand();
		}
		else if (playerInput == 1)
		{
			if (player.getHandLength() <= 0)
			{
				cout << "You don't have  a card to play" << endl;
				playerInput = -1;
			}
			else
			{
				cout << "Your hand" << endl;
				player.showHand();
				cout << "Choose a card to play from 0-" << player.getHandLength() - 1 << endl;
				cin >> playerInput;
				player.playCard(playerInput);
			}
		}
	}
	else {
		cout << "Game Over" << endl;
	}
}

void Game::render()
{
	mWindow.clear();
	menuStateManager.render(mWindow);
	if (menuStateManager.inGame)
	{
		deck.render(mWindow);
		player.renderHand(mWindow);
		player.renderScore(mWindow);
		player.renderPlayedCard(mWindow);
	}
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
