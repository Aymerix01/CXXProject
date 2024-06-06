#include "Game.hpp"
#include "StringHelpers.hpp"
#include <iostream>

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(const string &playerName, const pugi::xml_node& node, 
		   const sf::Sprite& bgSprite, const sf::Sprite& deckSprite,
			EventCardManager& eventCardManager) :
backgroundSprite(bgSprite), eventCardManager(eventCardManager),
mPlayer(playerName), deck(node, deckSprite, eventCardManager)
{
	mFont.loadFromFile("media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	this->eventCardManager.addEventCardListener(&mPlayer);
	this->eventCardManager.addEventCardListener(&deck);
	this->eventCardManager.addEventCardListener(this);
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
		mPlayer.drawCard(deck);
	}
	mPlayer.showHand();
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
	switch (event.type)
	{
		case sf::Event::Closed:
			mWindow.close();
			break;

		default:
			break;
	}
}

void Game::update(sf::Time elapsedTime)
{
    //TODO: Implement the update method
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(backgroundSprite);
	deck.render(mWindow);
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

void Game::onEventCard(EventCard eventCard) {
	if (eventCard == EventCard::FUTURE) {
		cout << "Game: Future event card" << endl;
		deck.showSomeCards(3);
	}
}