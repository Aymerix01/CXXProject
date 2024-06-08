#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <memory>
#include "MenuState.h"

class MenuStateManager
{
private:
	std::unique_ptr<MenuState> menuState;
	sf::Font mFont;

public:
	MenuStateManager(const sf::Sprite& backgroundSprite, const sf::Sprite& menuPrincipalSprite,
					 const sf::Sprite& menuCartesSprite, const sf::Sprite& menuPauseSprite);

	void render(sf::RenderWindow& window);
	void onUserEvent(sf::Event event, sf::RenderWindow& window);
	void changeState(std::unique_ptr<MenuState> state);

	sf::Sprite backgroundSprite;
	sf::Sprite menuPrincipalSprite;
	sf::Sprite menuCartesSprite;
	sf::Sprite menuPauseSprite;
	sf::Text menuCartesText;
	bool paused = false;
};