#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "MenuState.h"

class Deck;
class Player;
class MenuStateManager
{
private:
	std::unique_ptr<MenuState> menuState;
	sf::Font mFont;

	sf::Texture texturePlateau;
	sf::Texture textureMenuPrincipal;
	sf::Texture textureMenuCartes;
	sf::Texture textureMenuPause;
	sf::Texture textureMenuFin;

public:
	MenuStateManager();

	void render(sf::RenderWindow& window);
	void onUserEvent(sf::Event event, sf::RenderWindow& window);
	void changeState(std::unique_ptr<MenuState> state);

	sf::Sprite backgroundSprite;
	sf::Sprite menuPrincipalSprite;
	sf::Sprite menuCartesSprite;
	sf::Sprite menuPauseSprite;
	sf::Sprite menuFinSprite;
	sf::Text menuCartesText;
	bool paused = false;
	bool inGame = false;
	bool endGame = false;
};