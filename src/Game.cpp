#include "Game.hpp"
#include "StringHelpers.hpp"
#include <iostream>

using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

Game::Game(const string &playerName, const pugi::xml_node& node, 
		   const sf::Sprite& bgSprite, const sf::Sprite& deckSprite,
		   const sf::Sprite& MPSprite, const sf::Sprite& MCSprite, 
		   const sf::Sprite& MPauseSprite, EventCardManager& eventCardManager) :
backgroundSprite(bgSprite), menuPrincipalSprite(MPSprite), menuCartesSprite(MCSprite), menuPauseSprite(MPauseSprite),
eventCardManager(eventCardManager), player(playerName), deck(node, deckSprite, eventCardManager)
{
	mFont.loadFromFile("media/Sansation.ttf");
	mStatisticsText.setFont(mFont);
	mStatisticsText.setPosition(5.f, 5.f);
	mStatisticsText.setCharacterSize(10);

	menuCartesText.setFont(mFont);
	menuCartesText.setPosition(370.f, 493.f);
	menuCartesText.setCharacterSize(50);

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
	else if (event.type == sf::Event::MouseButtonPressed) {
		if (menuPrincipal && !menuCartes && !menuPause && event.mouseButton.x >= 780 && event.mouseButton.x <= 1136 &&
			event.mouseButton.y >= 365 && event.mouseButton.y <= 605)
		{
			menuPrincipal = false;
		}
		else if (menuPrincipal && !menuCartes && !menuPause && event.mouseButton.x >= 785 && event.mouseButton.x <= 1141 &&
				event.mouseButton.y >= 709 && event.mouseButton.y <= 948)
		{
			mWindow.close();
		}
		else if (menuPrincipal && !menuCartes && !menuPause && event.mouseButton.x >= 194 && event.mouseButton.x <= 382 &&
				 event.mouseButton.y >= 475 && event.mouseButton.y <= 756)
		{
			menuCartesText.setString("Cliquez sur une carte pour voir sa description");
			menuCartes = true;
		}
		else if (menuCartes && event.mouseButton.x >= 836 && event.mouseButton.x <= 1118 &&
			     event.mouseButton.y >= 825 && event.mouseButton.y <= 1014)
		{
			menuCartes = false;
		}
		else if (menuPause && event.mouseButton.x >= 772 && event.mouseButton.x <= 1123 &&
				event.mouseButton.y >= 356 && event.mouseButton.y <= 593)
		{
			menuPause = false;
		}
		else if (menuPause && event.mouseButton.x >= 774 && event.mouseButton.x <= 1122 &&
				 event.mouseButton.y >= 750 && event.mouseButton.y <= 987)
		{
			menuPause = false;
			menuPrincipal = true;
		}
		else if (menuPause && event.mouseButton.x >= 132 && event.mouseButton.x <= 316 &&
				 event.mouseButton.y >= 448 && event.mouseButton.y <= 725)
		{
			menuCartes = true;
		}
	}
	else if (event.type == sf::Event::KeyPressed) {
		if (!menuPrincipal && !menuPause && event.key.code == sf::Keyboard::Escape) {
			menuPause = true;
		}
		else if (menuPause && event.key.code == sf::Keyboard::Escape) {
			menuPause = false;
			menuCartes = false;
		}
	}
	if (menuCartes) {
		if (event.mouseButton.x >= 188 && event.mouseButton.x <= 375 &&
			event.mouseButton.y >= 107 && event.mouseButton.y <= 389) 
		{							 
			menuCartesText.setString("Cette carte vous permet d'éviter les sanglots du bébé");
		}
		else if (event.mouseButton.x >= 465 && event.mouseButton.x <= 652 &&
			     event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			menuCartesText.setString("Cette carte vous permet de mélanger les cartes du Deck");
		}
		else if (event.mouseButton.x >= 734 && event.mouseButton.x <= 923 &&
				 event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			menuCartesText.setString("Cette carte vous permet de faire exploser de rire le bébé");
		}
		else if (event.mouseButton.x >= 1013 && event.mouseButton.x <= 1197 &&
			     event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			menuCartesText.setString("Cette carte vous permet de voir les 3 premières cartes du Deck");
		}
		else if (event.mouseButton.x >= 1277 && event.mouseButton.x <= 1463 &&
			     event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			menuCartesText.setString("Cette carte vous permet de renvoyer la première carte du Deck");
		}
		else if (event.mouseButton.x >= 1573 && event.mouseButton.x <= 1788 &&
			     event.mouseButton.y >= 107 && event.mouseButton.y <= 389)
		{
			menuCartesText.setString("Cette carte fait exploser le bébé en sanglots. Evitez la !");
		}
	}
}

void Game::update(sf::Time elapsedTime)
{
    //TODO: Implement the update method
}

void Game::render()
{
	mWindow.clear();
	if (menuCartes) {
		mWindow.draw(menuCartesSprite);
		mWindow.draw(menuCartesText);
	}
	else if (menuPause)
	{
		mWindow.draw(menuPauseSprite);
	}
	else if (menuPrincipal)
	{
		mWindow.draw(menuPrincipalSprite);
	}
	else {
		mWindow.draw(backgroundSprite);
		deck.render(mWindow);
	}
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