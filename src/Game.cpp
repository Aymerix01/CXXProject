#include "Game.hpp"
#include "StringHelpers.hpp"
#include <iostream>
#include "MenuFin.h"


using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(const std::string& playerName) :
player(playerName), deck(eventCardManager), menuStateManager(eventCardManager)
{
	mFont.loadFromFile("media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	this->eventCardManager.addEventCardListener(&player);
	this->eventCardManager.addEventCardListener(&deck);
	this->eventCardManager.addEventCardListener(this);
}

void Game::run()
{
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
			update();
		updateStatistics(elapsedTime);
		render();
	}
}

void Game::start()
{
	//am.playMusic(0);
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
	if (event.type == sf::Event::MouseButtonPressed) {
		isMousePressed = true;
	}
	else if (event.type == sf::Event::MouseButtonReleased) {
		isMousePressed = false;
	}
	if (event.type == sf::Event::MouseButtonPressed && 
		event.mouseButton.x >= 192 && event.mouseButton.x <= 370 &&
		event.mouseButton.y >= 710 && event.mouseButton.y <= 924)
	{
		
		player.drawCard(deck);
		
	}
	menuStateManager.onUserEvent(event, mWindow);
	mousePos = sf::Mouse::getPosition(mWindow);
}

void Game::update()
{
	if (player.hasLost(deck)) {
		cout << "You lost" << endl;
		menuStateManager.inGame = false;
		menuStateManager.endGame = true;
		menuStateManager.changeState(make_unique<MenuFin>(menuStateManager));
	}
}

void Game::render()
{
	mWindow.clear();
	menuStateManager.render(mWindow);
	if (menuStateManager.inGame)
	{
		deck.render(mWindow);
		player.renderHand(mWindow, mousePos, isMousePressed);
		player.renderScore(mWindow);
		player.renderPlayedCard(mWindow);
	}
	if (menuStateManager.endGame)
	{
		player.renderScoreEndGame(mWindow);
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

void Game::onEventCard(EventCard eventCard) {
	if (eventCard == EventCard::ATTACKPOINTS) {
		menuStateManager.inGame = false;
		menuStateManager.endGame = true;
		menuStateManager.changeState(make_unique<MenuFin>(menuStateManager));
	}
	else if (eventCard == EventCard::RESET) {
		deck.reset();
		player.reset();
		start();
	}
}

